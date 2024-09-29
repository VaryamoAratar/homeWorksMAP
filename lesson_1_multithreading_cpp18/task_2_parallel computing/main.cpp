#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <iomanip>
#include <random>
#include <exception>

using namespace std;

bool flag = false;

void fillInVector(int size, vector<int>& v);
struct vec_times
{
	vec_times() {};
	vec_times(int size) {
		fillInVector(size, lVectors);
		fillInVector(size, rVectors);
	};


	vector<int> lVectors;
	vector<int> rVectors;
	double times{ 0 };
};
//void createVecTime(vec_times &v, int numElem) {
//	v = vec_times(numElem);
//}
enum number_of_threads
{
	ONE = 1,
	TWO,
	FOUR = 4,
	EIGHT = 8,
	SIXTEEN = 16
};
short rand_incr()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(1, 9);
	return dist(gen);
}
void fillInVector(int size, vector<int>& v) {
	//v.resize(size);
	for (int i = 0; i < size; i++) {
		v.push_back(rand_incr());
	}
}
void printHeader() {
	cout << "Количество аппаратных ядер - " << thread::hardware_concurrency() << endl;
};
vector<int> sumVectors(vector<int> const& lhv, vector<int> const& rhv, int begin, int end) {
	vector<int> vRes;
	for (int i = 0, j = begin; i < (end - begin); i++, j++) {
		vRes.push_back(lhv[j] + rhv[j]);
	}
	return vRes;
};
vector<int> devVectors(vec_times& vectors, const int& Thread) {
	int size{ 0 };
	int begin{ 0 };
	int end{ 0 };
	vector<vector<int>> res;
	vector<int> result;
	vector<thread> threads;
	for (int i = 0; i < Thread; i++) {
		if ((i + 1) != Thread) {
			size = vectors.rVectors.size() / Thread;
			begin = size * i;
			end = size * (i + 1);
			//res[i].resize(size);
		}
		else {
			size = vectors.rVectors.size() - (vectors.rVectors.size() / Thread) * (i );
			begin = (vectors.rVectors.size() / Thread) * (i);
			end = vectors.rVectors.size();
			//res[i].resize(size);
		}

		threads.push_back(thread([&vectors, &res, begin, end, i]() { res.push_back(sumVectors(vectors.lVectors, vectors.rVectors, begin, end)); }));
	}
	for (int i = 0; i < Thread; i++) {
		threads[i].join();
	}
	for (int i = 0; i < Thread; i++) {
		if ((i + 1) != Thread) {
			 size = vectors.rVectors.size() / Thread;
		}
		else {
			size = vectors.rVectors.size() - (vectors.rVectors.size() / Thread) * (i);
		}
		for (int j = 0; j < size; j++)
		{
			result.push_back(res[i][j]);
		}
	}

	return result;
}
void calcTime(vec_times& vectors, const int& Thread) {
		auto start = chrono::steady_clock::now();

		if (Thread == number_of_threads::ONE) {
			vector<int>resVector = sumVectors(vectors.lVectors, vectors.rVectors, 0, vectors.lVectors.size());
		}
		else {
			vector<int>resVector = devVectors(vectors, Thread);
		}

		auto end = chrono::steady_clock::now();
		chrono::duration<double> result = end - start;
		vectors.times = result.count();
}
;

void printResult(vector<vec_times>& vectors, const int& numThread) {
	if (!flag) {
		printHeader();

		cout << setw(30) << "Число элементов:";
		for (auto i : vectors)
		{
			cout << setw(14) << i.lVectors.size();
		}
		cout << endl;
		flag = true;
	}
	switch (numThread)
	{
	case number_of_threads::ONE: cout << setw(2) << numThread << setw(13) << " Поток" << setw(6) << ' ';
		break;
	case number_of_threads::TWO: cout << setw(2) << numThread << setw(14) << " Потока" << setw(6) << ' ';
		break;
	case number_of_threads::FOUR: cout << setw(2) << numThread << setw(14) << " Потока" << setw(6) << ' ';
		break;
	case number_of_threads::EIGHT: cout << setw(2) << numThread << setw(14) << " Потоков" << setw(6) << ' ';
		break;
	case number_of_threads::SIXTEEN: cout << setw(2) << numThread << setw(14) << " Потоков" << setw(6) << ' ';
		break;
	}

	for (auto i : vectors)
	{
		cout << setw(14) << i.times;
	}
	cout << endl;
};


int main(int argc, char* argv[]) {

	setlocale(LC_ALL, "ru_RU.utf8");

	try {

		auto startFill = chrono::steady_clock::now();
		short n = 4;
		vector<vec_times> m_vectors;
		{
			vector<thread> threads;
			int numElem{ 100 };
			for (int i = 0; i < n; i++) {
				numElem = numElem * 10;
				threads.push_back(thread([numElem, &m_vectors](){m_vectors.push_back(numElem); }));
			}
			for (int i = 0; i < threads.size(); i++) {
				if (threads[i].joinable()) threads[i].join();
			}
			auto endFill = chrono::steady_clock::now();
			auto resultTimeFill = chrono::duration_cast<chrono::milliseconds>(endFill - startFill);
			cout << "Векторы созданы и заполнены." << endl;
			cout << "Число векторов: " << n << endl;
			cout << "Время заполнения : " << resultTimeFill.count() << " милисекунд" << endl;
			cout << "Максимальное число элементов: " << numElem << endl;
		}
		for (auto& i : m_vectors) {
			calcTime(i, number_of_threads::ONE);
		}
		printResult(m_vectors, number_of_threads::ONE);
		for (auto& i : m_vectors) {
			calcTime(i, number_of_threads::TWO);
		}
		printResult(m_vectors, number_of_threads::TWO);
		for (auto& i : m_vectors) {
			calcTime(i, number_of_threads::FOUR);
		}
		printResult(m_vectors, number_of_threads::FOUR);
		for (auto& i : m_vectors) {
			calcTime(i, number_of_threads::EIGHT);
		}
		printResult(m_vectors, number_of_threads::EIGHT);
		for (auto& i : m_vectors) {
			calcTime(i, number_of_threads::SIXTEEN);
		}
		printResult(m_vectors, number_of_threads::SIXTEEN);

	}
	catch (const std::exception& ex) {
		cerr << ex.what() << endl;
	}

	return 0;
}