#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <queue>
#include <random>
#include <string>
#include <ctime>
#include <iostream>

using namespace std;

class PriorityQueue
{
public:
	PriorityQueue(void)
	{
		_num_inputs = 0;
		_benchmark = nullptr;
		_num_clicks = 0;
		_bench_time = 0, 0;
		for (unsigned int i = 0; i < PQstL.size(); i++)
		{
			PQstL.pop();
		}
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
			PQstL.push(num);
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

		if (PQstL.empty())
		{
			Add();
		}

		clock_t t;
		t = clock();

		for (int i = 0; i <= _num_inputs; i++)
		{
			num = distribution(generator);
			if (PQstL.empty())
			{
				break;
			}
			while (PQstL.top() != num)
			{
				PQstL.pop();
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
			if (PQstL.top() == num)
			{
				PQstL.pop();
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

private:
	priority_queue<int> PQstL;
	int _num_inputs;
	string _benchmark;
	int _num_clicks;
	float _bench_time;
};


#endif
