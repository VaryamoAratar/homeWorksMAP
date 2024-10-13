#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <functional>
#include <exception>
#include <stdexcept>

using namespace std::chrono_literals;

template <typename T>
class safe_queue {
public:
    safe_queue() = default;

    void push(T value) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(std::move(value));
        cond_var_.notify_one();  
    }

    T pop() {
        std::unique_lock<std::mutex> lock(mutex_);
        cond_var_.wait(lock, [this] { return !queue_.empty(); });  
        T value = std::move(queue_.front());  
        queue_.pop(); 
        return value;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }


private:
    std::queue<T> queue_;  
    mutable std::mutex mutex_;
    std::condition_variable cond_var_;  
};

class thread_pool {
public:
    thread_pool(size_t num_threads) {
        for (size_t i = 0; i < num_threads; ++i) {
            threads_.emplace_back([this] { work(); }); 
        }
    }

    ~thread_pool() {
        stop();
    }

    template<typename F>
    void submit(F&& task) {
        queue_.push(std::forward<F>(task)); 
    }

private:
    void stop() {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            stopping_ = true;
        }
        queue_.push([] {});
        for (auto& thread : threads_) {
            thread.join();
        }
    }
    void work() {
        while (true) {
            std::function<void()> task;
            if (stopping_ && queue_.empty()) {
                return;
            }
            if (!queue_.empty()) {
                task = queue_.pop();
            }
             if (task) {
                task();
            }
        }
    }

    std::vector<std::thread> threads_; 
    safe_queue<std::function<void()>> queue_; 
    bool stopping_ = false; 
    std::mutex mutex_;
};
std::mutex m;

void example_task_one() {
    std::lock_guard<std::mutex> lock(m);
    std::cout << "Task one is being executed on thread " << std::this_thread::get_id() << std::endl;
}
void example_task_two() {
    std::lock_guard<std::mutex> lock(m);
    std::cout << "Task two is being executed on thread " << std::this_thread::get_id() << std::endl;
}


int main() {
    const unsigned int num_threads = std::thread::hardware_concurrency();
    try
    {
        thread_pool pool(num_threads);

        for (size_t i = 0; i < 10; i++)
        {
            std::this_thread::sleep_for(1s);
            pool.submit(example_task_one);
            pool.submit(example_task_two);
        }

    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
    }

    return 0;
}