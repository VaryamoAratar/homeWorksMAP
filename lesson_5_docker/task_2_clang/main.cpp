#include <iostream>
#include <list>
#include <random>
#include <future>
#include <exception>

int rand_incr(int begin_of_range, int end_of_range)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(begin_of_range, end_of_range);
    return dist(gen);
}

void Find_min(std::promise<std::list<int>::iterator> pos_promise, std::list<int>::iterator pos_begin, std::list<int>::iterator pos_end) {
    try {
        if (pos_begin == pos_end) {
            throw std::runtime_error("Empty range provided.");
        }

        int value = *pos_begin;
        std::list<int>::iterator min_it = pos_begin;

        for (auto j = pos_begin; j != pos_end; j++)
        {
            if (*j < value)
            {
                value = *j;
                min_it = j;
            }
        }
        pos_promise.set_value(min_it);
    }
    catch (const std::exception& e) {
        pos_promise.set_exception(std::current_exception());
    }
}

int main(int argc, char* argv[]) {

    setlocale(LC_ALL, "ru-RU.utf8");

    try {
        std::list<int> my_list;
        int number_of_elements = 100;
        int begin_of_range = -50;
        int end_of_range = 50;

        // Заполняем список случайными числами в диапазоне
        for (size_t i = 0; i < number_of_elements; i++)
        {
            my_list.push_back(rand_incr(begin_of_range, end_of_range));
        }

        // Выводим список
        std::cout << "Список до сортировки: ";
        for (auto i : my_list) {
            std::cout << i << ' ';
        }
        std::cout << std::endl;

        for (auto i = my_list.begin(); i != my_list.end(); i++)
        {
            std::promise<std::list<int>::iterator> pos_promise;
            std::future<std::list<int>::iterator> pos_future = pos_promise.get_future();

            // Передаем начальный итератор списка и итератор, указывающий на послед. элемент
            std::async(Find_min, std::move(pos_promise), i, my_list.end());

            // Обработка исключений при получении результата
            try {
                auto pos_min = pos_future.get();

                // Меняем местами только если это не тот же элемент
                if (pos_min != i) {
                    std::swap(*i, *pos_min);
                }
            }
            catch (const std::exception& e) {
                std::cerr << "Ошибка при выполнении асинхронной операции: " << e.what() << std::endl;
            }
        }

        std::cout << "Список после сортировки: ";
        for (auto i : my_list) {
            std::cout << i << ' ';
        }
        std::cout << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}