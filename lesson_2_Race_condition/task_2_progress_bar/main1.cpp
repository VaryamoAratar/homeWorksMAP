#include <iostream>
#include <thread>
#include <chrono>
#include <windows.h>
#include <mutex>

std::mutex console_mutex;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void print_first_row() {
    for (int i = 0; i < 10; ++i) {
        {
            std::lock_guard<std::mutex> guard(console_mutex);
            gotoxy(0, 0);
            std::cout << "First row, count: " << i;// << "      ";  // Пробелы для очистки прежнего вывода
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void print_second_row() {
    for (int i = 0; i < 10; ++i) {
        {
            std::lock_guard<std::mutex> guard(console_mutex);
            gotoxy(0, 1);
            std::cout << "Second row, count: " << i << "      ";  // Пробелы для очистки прежнего вывода
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main1() {
    std::thread t1(print_first_row);
    std::thread t2(print_second_row);

    t1.join();
    t2.join();

    return 0;
}