#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

void client(std::atomic<int> &atomic_count)
{
	for (atomic_count.load(std::memory_order::memory_order_relaxed); atomic_count.load(std::memory_order::memory_order_relaxed) < 10;)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		int count = atomic_count.load(std::memory_order::memory_order_relaxed);
		count++;
		atomic_count.store(count ,std::memory_order::memory_order_relaxed);
		std::cout << "Подошел новый клиент\nОбщее количество клиентов: " << atomic_count.load(std::memory_order::memory_order_relaxed) << std::endl;
	}
};
void the_operator(std::atomic<int>& atomic_count)
{
	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	for (atomic_count.load(std::memory_order::memory_order_relaxed); atomic_count.load(std::memory_order::memory_order_relaxed) > 0;)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));

		int count = atomic_count.load(std::memory_order::memory_order_relaxed);
		count--;
		atomic_count.store(count, std::memory_order::memory_order_relaxed);
		std::cout << "Операционист обслужил клиента\nОбщее количество клиентов: " << atomic_count.load(std::memory_order::memory_order_relaxed) << std::endl;
	}
};


int main(int agrc, char* agrv[])
{
	setlocale(LC_ALL, "rus");

	std::atomic<int> atomic_count{ 1 };
	std::thread t1{ client, std::ref(atomic_count) };
	std::thread t2{ the_operator, std::ref(atomic_count) };

	std::cout << "Окошко открылось\nПодошел первый клиент\n";
	std::cout << "Общее количество клиентов: " << atomic_count.load(std::memory_order::memory_order_relaxed) << std::endl;

	t1.join();
	t2.join();


	return 	atomic_count.is_lock_free();
;
}