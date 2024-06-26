#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <algorithm>
#include <execution>

enum stream_number
{
	ONE = 1,
	TWO = 2,
	FOUR = 4,
	EIGHT = 8,
	SIXTEEN = 16
};

void v_sum(std::vector<int>& result, std::vector<int>& v1, std::vector<int>& v2, const int begin, const int end)
{


	for (int i = begin; i < end; i++)
	{
		result[i] = v1[i] + v2[i];
	}
}

float calcTime (int size, int number_of_threads) 
{
std::vector<int> v(size);
	std::vector<int> v1(v.size(), 1);
	std::vector<int> v2(v.size(), 1);

const auto start = std::chrono::steady_clock::now();

if (number_of_threads == stream_number::ONE)
{
		std::thread t{ v_sum, std::ref(v), std::ref(v1), std::ref(v2), 0 , v.size()};
		t.join();
}
else if (number_of_threads == stream_number::TWO)
{
	int end1 = v.size() / number_of_threads;
	int begin2 = end1;
	std::thread t1{ v_sum, std::ref(v), std::ref(v1), std::ref(v2), 0 , end1 };
	std::thread t2{ v_sum, std::ref(v), std::ref(v1), std::ref(v2), begin2 , v.size()};
	t1.join();
	t2.join();
}
else if (number_of_threads == stream_number::FOUR)
{
	int end1 = v.size() / number_of_threads;
	int begin2 = end1;
	int end2 = end1 * 2;
	int begin3 = end2;
	int end3 = end1 * 3;
	int begin4 = end3;
	std::thread t1{ v_sum, std::ref(v), std::ref(v1), std::ref(v2), 0 , end1 };
	std::thread t2{ v_sum, std::ref(v), std::ref(v1), std::ref(v2), begin2 , end2 };
	std::thread t3{ v_sum, std::ref(v), std::ref(v1), std::ref(v2), begin3 , end3 };
	std::thread t4{ v_sum, std::ref(v), std::ref(v1), std::ref(v2), begin4 , v.size() };
	t1.join();
	t2.join();
	t3.join();
	t4.join();
}
else if (number_of_threads == stream_number::EIGHT)
{
	int end1 = v.size() / number_of_threads;
	int begin2 = end1;
	int end2 = end1 * 2;
	int begin3 = end2;
	int end3 = end1 * 3;
	int begin4 = end3;
	int end4 = end1 * 4;
	int begin5 = end4;
	int end5 = end1 * 5;
	int begin6 = end5;
	int end6 = end1 * 6;
	int begin7 = end6;
	int end7 = end1 * 7;
	int begin8 = end7;

	std::thread t1{ v_sum, std::ref(v), std::ref(v1), std::ref(v2), 0 , end1 };
	std::thread t2{ v_sum, std::ref(v), std::ref(v1), std::ref(v2), begin2 , end2 };
	std::thread t3{ v_sum, std::ref(v), std::ref(v1), std::ref(v2), begin3 , end3 };
	std::thread t4{ v_sum, std::ref(v), std::ref(v1), std::ref(v2), begin4 , end4 };
	std::thread t5{ v_sum, std::ref(v), std::ref(v1), std::ref(v2), begin5 , end5 };
	std::thread t6{ v_sum, std::ref(v), std::ref(v1), std::ref(v2), begin6 , end6 };
	std::thread t7{ v_sum, std::ref(v), std::ref(v1), std::ref(v2), begin7 , end7 };
	std::thread t8{ v_sum, std::ref(v), std::ref(v1), std::ref(v2), begin8 , v.size() };
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();
	t8.join();
}
else if (number_of_threads == stream_number::SIXTEEN)
{
	int end1 = v.size() / number_of_threads;
	int begin2 = end1;
	int end2 = end1 * 2;
	int begin3 = end2;
	int end3 = end1 * 3;
	int begin4 = end3;
	int end4 = end1 * 4;
	int begin5 = end4;
	int end5 = end1 * 5;
	int begin6 = end5;
	int end6 = end1 * 6;
	int begin7 = end6;
	int end7 = end1 * 7;
	int begin8 = end7;
	int end8 = end1 * 8;
	int begin9 = end1;
	int end9 = end1 * 9;
	int begin10 = end9;
	int end10 = end1 * 10;
	int begin11 = end10;
	int end11 = end1 * 11;
	int begin12 = end11;
	int end12 = end1 * 12;
	int begin13 = end12;
	int end13 = end1 * 13;
	int begin14 = end13;
	int end14 = end1 * 14;
	int begin15 = end14;
	int end15 = end1 * 15;
	int begin16 = end15;

	std::thread t1{ v_sum, std::ref(v), std::ref(v1), std::ref(v2), 0 , end1 };
	std::thread t2{ v_sum, std::ref(v), std::ref(v1), std::ref(v2), begin2 , end2 };
	std::thread t3{ v_sum, std::ref(v), std::ref(v1), std::ref(v2), begin3 , end3 };
	std::thread t4{ v_sum, std::ref(v), std::ref(v1), std::ref(v2), begin4 , end4 };
	std::thread t5{ v_sum, std::ref(v), std::ref(v1), std::ref(v2), begin5 , end5 };
	std::thread t6{ v_sum, std::ref(v), std::ref(v1), std::ref(v2), begin6 , end6 };
	std::thread t7{ v_sum, std::ref(v), std::ref(v1), std::ref(v2), begin7 , end7 };
	std::thread t8{ v_sum, std::ref(v), std::ref(v1), std::ref(v2), begin8 , end8 };
	std::thread t9{ v_sum, std::ref(v), std::ref(v1), std::ref(v2), begin9 , end9 };
	std::thread t10{ v_sum, std::ref(v), std::ref(v1), std::ref(v2), begin10 , end10 };
	std::thread t11{ v_sum, std::ref(v), std::ref(v1), std::ref(v2), begin11 , end11 };
	std::thread t12{ v_sum, std::ref(v), std::ref(v1), std::ref(v2), begin12 , end12 };
	std::thread t13{ v_sum, std::ref(v), std::ref(v1), std::ref(v2), begin13 , end13 };
	std::thread t14{ v_sum, std::ref(v), std::ref(v1), std::ref(v2), begin14 , end14 };
	std::thread t15{ v_sum, std::ref(v), std::ref(v1), std::ref(v2), begin15 , end15 };
	std::thread t16{ v_sum, std::ref(v), std::ref(v1), std::ref(v2), begin16 , v.size() };

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();
	t8.join();
	t9.join();
	t10.join();
	t11.join();
	t12.join();
	t13.join();
	t14.join();
	t15.join();
	t16.join();
}

	const auto end = std::chrono::steady_clock::now();
	const auto calcTime = std::chrono::duration<float>(end - start).count();
	return calcTime;
}
void print_result(int size_1, int size_2, int size_3, int size_4, int number_of_threads)
{
		std::cout << number_of_threads << " потоков\t" << calcTime(size_1, number_of_threads) << '\t' << calcTime(size_2, number_of_threads) << '\t'
			<< calcTime(size_3, number_of_threads) << '\t' << calcTime(size_4, number_of_threads) << '\t' << std::endl;
}

int main(int argc, char* agrv[])
{

	setlocale(LC_ALL, "rus");

	int size_1{ 1000 };
	int size_2{ 10000 };
	int size_3{ 100000 };
	int size_4{ 1000000 };

	auto id2 = std::thread::hardware_concurrency();
	std::cout << "Количество аппаратных ядер - " << '\t' << id2 << std::endl;

	std::cout << "\t\t" << size_1 << "\t\t" << size_2 << "\t\t" << size_3 << "\t\t" << size_4 << std::endl;

	print_result(size_1, size_2, size_3, size_4, 1);
	print_result(size_1, size_2, size_3, size_4, 2);
	print_result(size_1, size_2, size_3, size_4, 4);
	print_result(size_1, size_2, size_3, size_4, 8);
	print_result(size_1, size_2, size_3, size_4, 16);


	return 0;
}