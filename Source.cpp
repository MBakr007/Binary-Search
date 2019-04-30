#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <random>


using namespace std;
int comparasions[100];
double sum_time = 0;
int sum_comparasion = 0;
int x = 0, y = 0;
int n;

vector<string> temp(100);

template <class  T>
class Searcher
{
private:
	vector<T> data;


public:
	Searcher()
	{

	}
	void load_data()
	{
		fstream file;
		T word;
		file.open("data.txt", ios::in);
		while (!file.eof() || file.peek() != EOF)
		{
			file >> word;
			data.push_back(word);
		}
		sort(data.begin(), data.end());
	}

	int Binary_search(int index,T word)
	{
		if (n == 1)
			 word = data[index];
		else
		{
			word = temp[y];
			y++;
		}
		int start = 0, end = data.size() - 1;
		int mid;
		while (start <= end)
		{
			mid = (end + start) / 2;
			if (data[mid] == word)
			{
				comparasions[x] = sum_comparasion;
				sum_comparasion = 0;
				x++;			
				return mid;
			}
			else if (data[mid] > word)
				end = mid - 1;

			else
				start = mid + 1;
			
			sum_comparasion++;
		}
		comparasions[x] = sum_comparasion;
		sum_comparasion = 0;
		x++;
		return -1;
	}
	void Graph(double t[] , int c[])
	{
		fstream file;
		file.open("graph.csv", ios::out);
		for (int i = 0; i < 100; i++)
		{
			file << t[i] << ',' << c[i] << endl;
		}
	}
	void test_performance()
	{
		cout << "Enter The Operation You Want To Do : " << endl;
		cout << "1- Search For a existing word." << endl;
		cout << "2- Search For a not existing word." << endl;
		cout << "Enter Your Choice : ";
		cin >> n;
		unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
		default_random_engine generator(seed);
		if (n == 1)
		{
			double time[100];
			clock_t start, end;
			uniform_int_distribution <int> distribution(0, data.size() - 1);
			for (int i = 0; i < 100; i++)
			{
				int index = distribution(generator);
				start = clock();
				cout << "The Word Found And The Index = " << Binary_search(index,"") << endl;
				end = clock();
				time[i] = (end - start);
				time[i] /= CLOCKS_PER_SEC;
			}
			int sum = 0;
			for (int j = 0; j < 100; j++)
			{
				sum_time += time[j];
				sum += comparasions[j];
			}
			cout << "The Average Time = " << sum_time / 100 << endl;
			cout << "The Average Number Of Comparsions = " << sum / 100 << endl;
			Graph(time, comparasions);
		}
		else if (n == 2)
		{
			vector<T>temp(100);
			fstream file;
			T key;
			file.open("temp.txt", ios::in);
			for (int i = 0; i < 100; i++)
			{
				file >> key;
				temp.push_back(key);
			}
				double time[100];
				clock_t start, end;
				uniform_int_distribution <int> distribution(0, data.size() - 1);
				for (int i = 0; i < 100; i++)
				{
					int index = distribution(generator);
					start = clock();
					cout << "The Word Found And The Index = " << Binary_search(index, "") << endl;
					end = clock();
					time[i] = (end - start);
					time[i] /= CLOCKS_PER_SEC;
				}
				int sum = 0;
				for (int j = 0; j < 100; j++)
				{
					sum_time += time[j];
					sum += comparasions[j];
				}
				cout << "The Average Time = " << sum_time / 100 << endl;
				cout << "The Average Number Of Comparsions = " << sum / 100 << endl;
				Graph(time, comparasions);
			}
		}
};


int main()
{
	Searcher<string> s;
	s.load_data();
	s.test_performance();
	system("pause");
	return 0;
}