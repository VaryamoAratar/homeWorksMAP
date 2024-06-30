#include <iostream>
#include <thread>
#include <chrono>

void client(int& count)
{
	for (count; count < 10;)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		count++;
		std::cout << "Подошел новый клиент\nОбщее количество клиентов: " << count << std::endl;
	}
};
void the_operator(int& count)
{
	for (count; count > 0;)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		count--;
		std::cout << "Операционист обслужил клиента\nОбщее количество клиентов: " << count << std::endl;
	}
};


int main(int agrc, char* agrv[])
{
	//setlocale(LC_ALL, "rus");

	int count{ 1 };
	std::thread t1{ client, std::ref(count)};
	std::thread t2{ the_operator, std::ref(count) };

	std::cout << "Окошко открылось\nПодошел первый клиент\n";
	std::cout << "Общее количество клиентов: " << count << std::endl;
	
	t1.join();
	t2.join();

	return 0;
}