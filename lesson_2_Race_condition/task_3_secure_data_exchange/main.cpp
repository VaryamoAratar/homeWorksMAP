#include <iostream>
#include <mutex>
#include <thread>

class Data {
public:
    int value;
    std::mutex mtx;

    Data(int v) : value(v) {}
};

void swap_lock(Data& lhs, Data& rhs) {
    std::lock(lhs.mtx, rhs.mtx);
    std::lock_guard lock1(lhs.mtx, std::adopt_lock);
    std::lock_guard lock2(rhs.mtx, std::adopt_lock);
    std::swap(lhs.value, rhs.value);
}

void swap_scoped_lock(Data& lhs, Data& rhs) {
    std::scoped_lock lock(lhs.mtx, rhs.mtx);
    std::swap(lhs.value, rhs.value);
}

void swap_unique_lock(Data& lhs, Data& rhs) {
    std::unique_lock<std::mutex> lock1(lhs.mtx, std::defer_lock);
    std::unique_lock<std::mutex> lock2(rhs.mtx, std::defer_lock);
    std::lock(lock1, lock2);
    std::swap(lhs.value, rhs.value);
}

int main() {
    Data d1(1);
    Data d2(2);

    std::cout << "Before swap: d1.value = " << d1.value << ", d2.value = " << d2.value << std::endl;

    swap_lock(d1, d2);
    swap_scoped_lock(d1, d2);
    swap_unique_lock(d1, d2);

    std::cout << "After swap:  d1.value = " << d1.value << ", d2.value = " << d2.value << std::endl;

    return 0;
}