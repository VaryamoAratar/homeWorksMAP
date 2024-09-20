#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <exception>
#include <iomanip>

enum stream_number {
	ONE = 1,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	ELEVEN,
	TWELVE,
	THIRTEEN,
	FOURTEEN,
	FIFTEEN,
	SIXTEEN
};

void v_sum(std::vector<int>& result, std::vector<int>& v1, std::vector<int>& v2, const int begin, const int end) {
	for (int i = begin; i < end; i++) {
		result[i] = v1[i] + v2[i];
	}
}

float calcTime(int size, int number_of_threads) {
	std::vector<int> v(size);
	std::vector<int> v1(v.size(), 1);
	std::vector<int> v2(v.size(), 1);

	const auto start = std::chrono::steady_clock::now();

	if (number_of_threads == stream_number::ONE) {
		v_sum(v, v1, v2, 0, v.size());
	}
	else {
		int itr = v.size() / number_of_threads;
		std::vector<std::thread> threads;
		for (int i = 1; i <= number_of_threads; i++) {
			if (i == number_of_threads) {
				threads.push_back(std::thread(v_sum, std::ref(v), std::ref(v1), std::ref(v2), (itr * (i - 1)), v.size()));
			}
			else {
				threads.push_back(std::thread(v_sum, std::ref(v), std::ref(v1), std::ref(v2), (itr * (i - 1)), (itr * i)));
			}
		}
		for (int i = 0; i < threads.size(); i++) {
			threads[i].join();
		}

	}
	const auto end = std::chrono::steady_clock::now();
	const auto calcTime = std::chrono::duration<float>(end - start).count();
	return calcTime;
}

void print_result(const std::vector<int>& sizes, int number_of_threads) {
	switch (number_of_threads) {
	case stream_number::ONE: std::cout << std::setw(2) << number_of_threads << std::setw(13) << "поток";
		break;
	case stream_number::TWO: std::cout << std::setw(2) << number_of_threads << std::setw(14) << "потока";
		break;
	case stream_number::THREE: std::cout << std::setw(2) << number_of_threads << std::setw(14) << "потока";
		break;
	case stream_number::FOUR: std::cout << std::setw(2) << number_of_threads << std::setw(14) << "потока";
		break;
	default: std::cout << std::setw(2) << number_of_threads << std::setw(15) << "потоков";
		break;
	}

	for (const auto i : sizes) {
		std::cout << std::setw(16) << calcTime(i, number_of_threads);
	}
	std::cout << std::endl;
}

void print_header(int size) {
	static bool flag{ false };
	if (!flag) {
		auto id2 = std::thread::hardware_concurrency();
		std::cout << "Количество аппаратных ядер - " << '\t' << id2 << std::endl;
		std::cout << std::endl;
		std::cout << std::setw(10) << ' ';
		flag = true;
	}
	
	std::cout << std::setw(16) << size;


}

int main(int argc, char* agrv[]) {

	setlocale(LC_ALL, "ru_RU.utf8");


	try {

		std::vector<int> sizes;

		sizes.push_back(1000);
		sizes.push_back(10000);
		sizes.push_back(100000);
		sizes.push_back(1000000);
		sizes.push_back(10000000);

		if (sizes.empty()) {
			throw std::runtime_error("sizes is empty");
		}

		for (const auto i : sizes) {
			print_header(i);
		}

		std::cout << std::endl;

		print_result(sizes, stream_number::ONE);
		print_result(sizes, stream_number::TWO);
		print_result(sizes, stream_number::FOUR);
		print_result(sizes, stream_number::EIGHT);
		print_result(sizes, stream_number::SIXTEEN);
	}

	catch (const std::exception& e) {
		std::cerr << "Error!" << e.what() << std::endl;
	}

	return 0;
}