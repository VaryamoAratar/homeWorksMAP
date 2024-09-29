#include <iostream>
#include <chrono>
#include <thread>

void t_customer(int& count) {
	while (count != 10) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "Подошел новый клиент. " << "Всего клиентов в очереди: " << ++count << std::endl;
	}
}

void t_operator(int& count) {
	while (count > 0) {
		std::this_thread::sleep_for(std::chrono::seconds(2));
		std::cout << "Операционист обработал запрос клиента. " << "Всего клиентов в очереди: " << --count << std::endl;
	}
}

int main(int argc, char* argv[]) {

	setlocale(LC_ALL, "ru_RU.utf8");

	int count{ 0 };

	std::cout << "Подошел первый клиент.\t" << "Всего клиентов в очереди: " << ++count << std::endl;
	std::thread cust(t_customer, std::ref(count));
	std::thread oper(t_operator, std::ref(count));
	cust.join();
	oper.join();

	return 0;
}