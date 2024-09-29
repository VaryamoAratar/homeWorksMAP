#include <exception>
#include <future>
#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <iterator>

//using namespace std;
int rand_incr(int begin_of_range, int end_of_range)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(begin_of_range, end_of_range);
    return dist(gen);
}


template<class InputIt, class UnaryFunc>
void my_for_each(InputIt first, InputIt last, UnaryFunc f)
{
    unsigned long const length = std::distance(first, last);
    if (length == 0) {
        return;
    }
    if (length == 1) {
        f(*first);
        return;
    }

    InputIt mid_point = first;
    std::advance(mid_point, length / 2);
    std::future<void> first_for_each = std::async(std::launch::async, my_for_each<InputIt, UnaryFunc>, first, mid_point, f);
    my_for_each<InputIt, UnaryFunc>(mid_point, last, f);

    try
    {
        first_for_each.get();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Ошибка при выполнении асинхронной операции: " << e.what() << std::endl;
    }
}


int main() {

    setlocale(LC_ALL, "rus");

    std::vector<int> vec;
    unsigned int number_of_elements = 1000;
    int begin_of_range = -50;
    int end_of_range = 50;


    for (size_t i = 0; i < number_of_elements; i++)
    {
        vec.push_back(rand_incr(begin_of_range, end_of_range));
    }


    my_for_each(vec.begin(), vec.end(), [](int& n) {n *= n; });

    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
}
