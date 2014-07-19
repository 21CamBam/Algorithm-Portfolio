#ifndef AVL_H
#define AVL_H

#include <random>
#include <string>
#include <ctime>
#include <iostream>
#include "TreeNode.h"

using namespace std;

class AVL : public TreeNode
{
public:
	AVL(void)
	{
		_num_inputs = 0;
		_benchmark = nullptr;
		_num_clicks = 0;
		_bench_time = 0, 0;
		root = nullptr;
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
			insert_node(root, num);
		}
		t = clock() - t;
		return t;
	}

	void insert_node(TreeNode* rootptr, int num)
	{
		if (rootptr == NULL) // New root
		{
			rootptr = new TreeNode(num);
			return;
		}

		if (rootptr->value == num) // No duplicates test
		{
			return;
		}

		if (rootptr->value > num) // If num is less than root
		{
			if (rootptr->left == NULL) // If root has no left child
			{
				TreeNode* new_leaf = new TreeNode(num);
				rootptr->left = new_leaf;
				new_leaf->parent = rootptr;
				if (!is_balanced(rootptr))
				{
					int left = get_height(rootptr->left);
					int right = get_height(rootptr->right);

					if ((left - right) > 1)
					{
						left_rotation(rootptr->left);
					}
					else if ((left - right) < 1)
					{
						right_rotation(rootptr->right);
					}
					else
					{
						return;
					}
				}
				return;
			}
			insert_node(rootptr->left, num);
		}
		else // If num is more than root
		{
			if (rootptr->right == NULL) // If root has no right child
			{
				TreeNode* new_leaf = new TreeNode(num);
				rootptr->right = new_leaf;
				new_leaf->parent = rootptr;
				if (!is_balanced(rootptr))
				{
					int left = get_height(rootptr->left);
					int right = get_height(rootptr->right);

					if ((left - right) > 1)
					{
						left_rotation(rootptr->left);
					}
					else if ((left - right) < 1)
					{
						right_rotation(rootptr->right);
					}
					else
					{
						return;
					}
				}
				return;
			}
			insert_node(rootptr->right, num);
		}
	}

	int get_height(TreeNode *rootptr)
	{
		int l_height = 1 + get_height(rootptr->left);
		int r_height = 1 + get_height(rootptr->right);

		if (l_height > r_height)
		{
			return l_height;
		}
		else
		{
			return r_height;
		}
	}

	bool is_balanced(TreeNode *rootptr)
	{
		int left = get_height(rootptr->left);
		int right = get_height(rootptr->right);

		if ((left - right) > 1 || (left - right) < -1)
		{
			return false;
		}
		return true;
	}

	void right_rotation(TreeNode *rootptr)
	{
		TreeNode *temp;
		if (rootptr->parent->value < rootptr->value) // Right-Left
		{
			temp = rootptr->right;
			rootptr->right = rootptr->parent;
			rootptr->parent->left = temp;
			
			temp = rootptr->left;
			rootptr->left = rootptr->parent;
			rootptr->parent->right = temp;
			return;
		}
		else
		{
			temp = rootptr->left;
			rootptr->left = rootptr->parent;
			rootptr->parent->right = temp;
			return;
		}
	}

	void left_rotation(TreeNode *rootptr)
	{
		TreeNode *temp;
		if (rootptr->parent->value < rootptr->value) // Right-Left
		{
			temp = rootptr->left;
			rootptr->left = rootptr->parent;
			rootptr->parent->right = temp;

			temp = rootptr->right;
			rootptr->right = rootptr->parent;
			rootptr->parent->left = temp;
			return;
		}
		else
		{
			temp = rootptr->right;
			rootptr->right = rootptr->parent;
			rootptr->parent->left = temp;
			return;
		}
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

		if (root == nullptr)
		{
			Add();
		}

		clock_t t;
		t = clock();

		for (int i = 0; i <= _num_inputs; i++)
		{
			num = distribution(generator);
			search_and_destroy(root, num);
		}
		t = clock() - t;
		return t;
	}

	void search_and_destroy(TreeNode* parent, int num) // If num is in tree, then returns true
	{
		if (parent->value == num)
		{
			if (parent->left == nullptr && parent->right == nullptr)
			{
				delete parent;
				if (!is_balanced(parent))
				{
					int left = get_height(parent->left);
					int right = get_height(parent->right);

					if ((left - right) > 1)
					{
						left_rotation(parent->left);
					}
					else if ((left - right) < 1)
					{
						right_rotation(parent->right);
					}
					else
					{
						return;
					}
				}
				return;
			}
			else if (parent->left == nullptr && parent->right != nullptr)
			{
				parent = parent->right;
				if (!is_balanced(parent))
				{
					int left = get_height(parent->left);
					int right = get_height(parent->right);

					if ((left - right) > 1)
					{
						left_rotation(parent->left);
					}
					else if ((left - right) < 1)
					{
						right_rotation(parent->right);
					}
					else
					{
						return;
					}
				}
				return;
			}
			else if (parent->left != nullptr && parent->right == nullptr)
			{
				parent = parent->left;
				if (!is_balanced(parent))
				{
					int left = get_height(parent->left);
					int right = get_height(parent->right);

					if ((left - right) > 1)
					{
						left_rotation(parent->left);
					}
					else if ((left - right) < 1)
					{
						right_rotation(parent->right);
					}
					else
					{
						return;
					}
				}
				return;
			}
			else
			{
				TreeNode* rightmost_in_left = find_rightmost_in_left(parent->left);
				parent->value = rightmost_in_left->value;
				if (rightmost_in_left->left == nullptr && rightmost_in_left->right != nullptr)
				{
					rightmost_in_left = rightmost_in_left->right;
					if (!is_balanced(parent))
					{
						int left = get_height(parent->left);
						int right = get_height(parent->right);

						if ((left - right) > 1)
						{
							left_rotation(parent->left);
						}
						else if ((left - right) < 1)
						{
							right_rotation(parent->right);
						}
						else
						{
							return;
						}
					}
					return;
				}
				else if (rightmost_in_left->left != nullptr && rightmost_in_left->right == nullptr)
				{
					rightmost_in_left = rightmost_in_left->left;
					if (!is_balanced(parent))
					{
						int left = get_height(parent->left);
						int right = get_height(parent->right);

						if ((left - right) > 1)
						{
							left_rotation(parent->left);
						}
						else if ((left - right) < 1)
						{
							right_rotation(parent->right);
						}
						else
						{
							return;
						}
					}
					return;
				}
				return;
			}
		}
		else if (parent->value > num)
		{
			search_and_destroy(parent->left, num);
		}
		else if (parent->value < num)
		{
			search_and_destroy(parent->right, num);
		}
	}

	TreeNode* find_rightmost_in_left(TreeNode *rootptr)
	{
		TreeNode *rightmost;
		if (rootptr->right == nullptr)
		{
			return rootptr;
		}
		rightmost = find_rightmost_in_left(rootptr->right);
		return rightmost;
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
			search(root, num);
		}
		t = clock() - t;
		return t;
	}

	void search(TreeNode* rootptr, int num) // If num is in tree, then returns true
	{
		if (rootptr->value == num)
		{
			return;
		}
		else if (rootptr->value > num)
		{
			search(rootptr->left, num);
		}
		else if (rootptr->value < num)
		{
			search(rootptr->right, num);
		}
		else
		{
			return;
		}
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
	TreeNode *root;
	int _num_inputs;
	string _benchmark;
	int _num_clicks;
	float _bench_time;
};


#endif
