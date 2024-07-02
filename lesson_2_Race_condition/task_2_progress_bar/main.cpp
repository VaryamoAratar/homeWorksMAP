#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <string>
#include <vector>
#include <Windows.h>
#include <random>
#include <exception>

#define STR string
using namespace std;

enum  Colors {
	Black,
	Blue,
	Green,
	Cyan,
	Red,
	Magenta,
	Brown,
	LightGray,
	DarkGray,
	LightBlue,
	LightGreen,
	LightCyan,
	LightRed,
	LightMagenta,
	Yellow,
	White
};

template<Colors txt = LightGray, Colors bg = Black>
ostream& color(ostream& text) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | txt));
	return text;
}


void goto_xy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

short rand_incr()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(15, 48);
	return dist(gen);
}
mutex m;
short length_bar{ 0 };
void print_bar(int r)
{
			STR bar;
			for (size_t n = 0; n < r; n++)
			{
				bar += 219;
			}
			cout << bar;
}

void progress_bar(int i)
{
	const auto start = chrono::steady_clock::now();

	for (size_t j = 0; j < length_bar; )
	{
		this_thread::sleep_for(chrono::milliseconds(100));
		unique_lock<mutex> m_unique(m);
		goto_xy(0, i);
		cout << color;
		cout.width(0);
		cout.setf(ios::right);
		cout << i;
		cout.width(7);
		cout.setf(ios::right);
		cout << this_thread::get_id();

		goto_xy(9 + j, i);
		int r = rand_incr()/8;
		if (length_bar - r < j)
		{
			r = length_bar - j;
		}

		if (r != 1)
		{
			cout << color<LightGreen, Black>;
			print_bar(r);
		}
		else
		{
			cout << color<Red, Black>;
			print_bar(r);
		}
		j += r;

	}

	const auto end = chrono::steady_clock::now();
	const auto calc_time = chrono::duration<double>(end - start).count();
	unique_lock<mutex> m_unique(m);
	cout << color;
	cout << ' ' << calc_time << " s";
	cout << endl;
}


void print_header(STR col_name_1, STR col_name_2, STR col_name_3, STR col_name_4)
{
	cout << color;
	cout.width(col_name_1.size()+1);
	cout.setf(ios::left);
	cout << col_name_1;
	cout.width(col_name_2.size());
	cout.setf(ios::left);
	cout << col_name_2;
	cout.width(col_name_3.size() / 2 + 39);
	cout.setf(ios::right);
	cout << col_name_3;
	cout.width(col_name_3.size() / 2 + 32);
	cout.setf(ios::right);
	cout << col_name_4;
	cout << endl;
	length_bar = 2 * col_name_3.size() + 50;
}

int main(int argc, char* argv[])
{
	print_header("#", "  ID", "Progress bar", "Time");

	int n{ 5 };
	thread* t = new thread[n];

	for (size_t i = 0; i < n; i++)
	{
		t[i] = thread(progress_bar, i + 1);
	}
	for (size_t i = 0; i < n; i++)
	{
		t[i].join();
	}

	cout << endl;

	delete[] t;
	return 0;
}