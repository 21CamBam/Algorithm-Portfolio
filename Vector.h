#ifndef VECTOR_H
#define VECTOR_H

#include <vector>
#include <random>
#include <string>
#include <ctime>
#include <algorithm>
#include <iostream>

using namespace std;

class Vector
{
public:
	Vector(void)
	{
		_num_inputs = 0;
		_benchmark = nullptr;
		_num_clicks = 0;
		_bench_time = 0, 0;
		VECTstL.clear();
		it = VECTstL.begin();
	}

	void set_num_inputs(int value)
	{
		_num_inputs = value;
	}

	void set_benchmark(string bench_in)
	{
		_benchmark = bench_in;
	}

	void control(void) // Determines which function to use based on benchmark value
	{
		string add = "add";
		string remove = "remove";
		string find = "find";
		string composite = "composite";
		string quicksort = "quicksort";
		string mergesort = "mergesort";
		string heapsort = "heapsort";

		if (_benchmark.compare(add) == 0)
		{
			_num_clicks = Add();
			_bench_time = ((float)_num_clicks) / CLOCKS_PER_SEC;
			cout << "Total runtime of Add function: " << _bench_time << endl;
			return;
		}
		else if (_benchmark.compare(remove) == 0)
		{
			_num_clicks = Remove();
			_bench_time = ((float)_num_clicks) / CLOCKS_PER_SEC;
			cout << "Total runtime of Remove function: " << _bench_time << endl;
			return;
		}
		else if (_benchmark.compare(find) == 0)
		{
			_num_clicks = Find();
			_bench_time = ((float)_num_clicks) / CLOCKS_PER_SEC;
			cout << "Total runtime of Find function: " << _bench_time << endl;
			return;
		}
		else if (_benchmark.compare(composite) == 0)
		{
			_num_clicks = Composite();
			_bench_time = ((float)_num_clicks) / CLOCKS_PER_SEC;
			cout << "Total runtime of Composite function: " << _bench_time << endl;
			return;
		}
		else if (_benchmark.compare(quicksort) == 0)
		{
			_num_clicks = Quicksort();
			_bench_time = ((float)_num_clicks) / CLOCKS_PER_SEC;
			cout << "Total runtime of Remove function: " << _bench_time << endl;
			return;
		}
		else if (_benchmark.compare(mergesort) == 0)
		{
			_num_clicks = Mergesort();
			_bench_time = ((float)_num_clicks) / CLOCKS_PER_SEC;
			cout << "Total runtime of Find function: " << _bench_time << endl;
			return;
		}
		else if (_benchmark.compare(heapsort) == 0)
		{
			_num_clicks = Heapsort();
			_bench_time = ((float)_num_clicks) / CLOCKS_PER_SEC;
			cout << "Total runtime of Composite function: " << _bench_time << endl;
			return;
		}
		else
		{
			return;
		}
	}

	/*
	* Begin Benchmark
	* For i = 0 to _num_inputs
	*	Generate a random number between 0 and N
	*	Add the number to the data structure
	* End Benchmark
	* returns # of clicks
	*/
	int Add(void) // adds _num_inputs random ints to data structure
	{
		default_random_engine generator;
		uniform_int_distribution<int> distribution(0, _num_inputs);
		int num;
		clock_t t;
		t = clock();

		for (int i = 0; i <= _num_inputs; i++)
		{
			num = distribution(generator);
			VECTstL.push_back(num);
		}
		t = clock() - t;
		return t;
	}

	/*
	* For i = 0 to _num_inputs
	*	Generate a random number between 0 and N
	*	Add the number to the data structure
	* Begin Benchmark
	* For i = 0 to _num_inputs
	*	Generate a random number between 0 and N
	*	Remove the first occurance of the number from the data structure
	* End Benchmark
	* returns # of clicks
	*/
	int Remove(void)
	{
		default_random_engine generator;
		uniform_int_distribution<int> distribution(0, _num_inputs);
		int num;

		if (VECTstL.empty())
		{
			Add();
		}

		clock_t t;
		t = clock();

		for (int i = 0; i <= _num_inputs; i++)
		{
			num = distribution(generator);
			if (VECTstL.empty())
			{
				break;
			}
			for (it = VECTstL.begin(); it != VECTstL.end(); ++it)
			{
				if (*it == num)
				{
					VECTstL.erase(it);
					break;
				}
			}
		}
		t = clock() - t;
		return t;
	}

	/*
	* For i = 0 to _num_inputs
	*	Generate a random number between 0 and N
	*	Add the number to the data structure
	* Begin Benchmark
	* For i = 0 to _num_inputs
	*	Generate a random number between 0 and N
	*	Check to see if this value exists in the data structure
	* End Benchmark
	* returns # of clicks
	*/
	int Find(void)
	{
		default_random_engine generator;
		uniform_int_distribution<int> distribution(0, _num_inputs);
		int num;

		clock_t t;
		t = clock();

		for (int i = 0; i <= _num_inputs; i++)
		{
			num = distribution(generator);
			for (it = VECTstL.begin(); it != VECTstL.end(); ++it)
			{
				if (*it == num)
				{
					break;
				}
			}
		}
		t = clock() - t;
		return t;
	}

	/*
	* Performs an add, find and remove benchmark in succession and outputs the total runtime
	*/
	int Composite(void)
	{
		clock_t t;
		t = clock();

		Add();
		Remove();
		Find();

		t = clock() - t;
		return t;
	}

	int Quicksort(void)
	{
		default_random_engine generator;
		uniform_int_distribution<int> distribution(0, _num_inputs);

		if (VECTstL.empty())
		{
			Add();
		}

		clock_t t;
		t = clock();

		qsort(0, VECTstL.size());
		
		t = clock() - t;
		return t;
	}

	void qsort(int begin, int end)
	{
		if (end - begin <= 1)
		{
			return;
		}
		/////////////Partition///////////////
		int pivot = end - 1, left = begin, temp;

		for (int i = begin; i < end; i++)
		{
			if (VECTstL[i] <= VECTstL[pivot])
			{
				temp = VECTstL[left];
				VECTstL[left] = VECTstL[i];
				VECTstL[i] = temp;
			}
			left++;
		}
		temp = VECTstL[left];
		VECTstL[left] = VECTstL[pivot];
		VECTstL[pivot] = temp;
		pivot = left;
		////////////////////////////////////
		qsort(begin, pivot - 1);
		qsort(pivot + 1, end);
	}


	int Mergesort(void)
	{
		default_random_engine generator;
		uniform_int_distribution<int> distribution(0, _num_inputs);

		if (VECTstL.empty())
		{
			Add();
		}

		clock_t t;
		t = clock();

		VECTstL = msort(VECTstL);

		t = clock() - t;
		return t;
	}

	vector<int> msort(vector<int> &vect_temp)
	{
		
		if (vect_temp.size() <= 1)
		{
			return vect_temp;
		}
		vector<int>::iterator mid = vect_temp.begin() + (vect_temp.size() / 2);
		vector<int> left(vect_temp.begin(), mid);
		vector<int> right(mid + 1, vect_temp.end());

		left = msort(left);
		right = msort(right);

		return merge(left, right);
	}

	vector<int> merge(vector<int> left, vector<int> right)
	{
		vector<int> sorted;
		unsigned int i = 0, j = 0;

		while (i < left.size() && j < right.size())
		{
			if (left[i] < right[j])
			{
				sorted.push_back(left[i]);
				i++;
			}
			else
			{
				sorted.push_back(right[j]);
				j++;
			}
		}

		while (i < left.size())
		{
			sorted.push_back(left[i]);
			i++;
		}
		while (j < right.size())
		{
			sorted.push_back(right[j]);
			j++;
		}

		return sorted;
	}

	int Heapsort(void)
	{
		default_random_engine generator;
		uniform_int_distribution<int> distribution(0, _num_inputs);

		if (VECTstL.empty())
		{
			Add();
		}

		clock_t t;
		t = clock();

		make_heap(VECTstL.begin(), VECTstL.end());
		sort_heap(VECTstL.begin(), VECTstL.end());

		t = clock() - t;
		return t;
	}

private:
	vector<int> VECTstL;
	vector<int>::iterator it;
	int _num_inputs;
	string _benchmark;
	int _num_clicks;
	float _bench_time;
};


#endif
