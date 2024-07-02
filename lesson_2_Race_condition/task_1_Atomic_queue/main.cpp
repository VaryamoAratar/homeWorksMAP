#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

void client(std::atomic<int> &atomic_count)
{
	for (atomic_count.load(std::memory_order::memory_order_seq_cst); atomic_count.load(std::memory_order::memory_order_seq_cst) < 10;)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		int count = atomic_count.load(std::memory_order::memory_order_seq_cst);
		count++;
		atomic_count.store(count ,std::memory_order::memory_order_seq_cst);
		std::cout << "Подошел новый клиент\nОбщее количество клиентов: " << atomic_count.load(std::memory_order::memory_order_seq_cst) << std::endl;
	}
};
void the_operator(std::atomic<int>& atomic_count)
{
	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	for (atomic_count.load(std::memory_order::memory_order_seq_cst); atomic_count.load(std::memory_order::memory_order_seq_cst) > 0;)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));

		int count = atomic_count.load(std::memory_order::memory_order_seq_cst);
		count--;
		atomic_count.store(count, std::memory_order::memory_order_seq_cst);
		std::cout << "Операционист обслужил клиента\nОбщее количество клиентов: " << atomic_count.load(std::memory_order::memory_order_seq_cst) << std::endl;
	}
};


int main(int agrc, char* agrv[])
{
	setlocale(LC_ALL, "ru_RU.utf8");

	std::atomic<int> atomic_count{ 1 };
	std::thread t1{ client, std::ref(atomic_count) };
	std::thread t2{ the_operator, std::ref(atomic_count) };

	std::cout << "Окошко открылось\nПодошел первый клиент\n";
	std::cout << "Общее количество клиентов: " << atomic_count.load(std::memory_order::memory_order_seq_cst) << std::endl;

	t1.join();
	t2.join();


	return 	atomic_count.is_lock_free();
;
}