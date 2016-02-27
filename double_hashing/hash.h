#pragma once
#include <cstdlib>
#include <iostream>
#include <assert.h>
#include <vector>
#include <cmath>
using namespace std;

class Hash {
	int mode; //Holds how we are implementing the queue, either as linked list, array, or vector
	int max_size; //Holds the size of our array
	int contains = 0; //Holds how many elements we contain

	int *hash_table;
	int R = 0;

	public:
	static const int LINEAR_MODE = 0;
	static const int QUADRATIC_MODE = 0;
	static const int DOUBLE_MODE = 2;
	Hash(int new_mode = LINEAR_MODE, int new_size=1009) : mode(new_mode), max_size(new_size) {
		if (!prime_test(max_size)) {
			cout << "Your size is not a prime" << endl;
			exit(1);
		}
		hash_table = new int[max_size];
		for (int i = 0; i < max_size; i++) hash_table[i] = 0;
		for (int x = max_size-1; x > 2; x--) {
				if (prime_test(x))
				{
					R = x;
					break;
				}
				else {continue;}
			}
	}

	bool prime_test(int x){
			for (int i=2; i<= sqrt(x); i++) {
			if (x%i==0) return false;
		}
		return true;
	}

	//Returns percentage the array is full
	float get_load() { return contains / float(max_size); }

	//YOU: Print out the hash table for debugging purposes
	void print() {
		for (int i = 0; i < max_size; i++)
			cout<< "Position: " << i << " Value: " << hash_table[i] << endl;
	}

	//YOU: Insert a new int into the hash table using the rules found in mode
	void insert(int newdata) {
		int h1 = newdata % max_size;
		if (hash_table[h1] == 0){
			hash_table[h1] = newdata;
			contains++;
			return;
		}

		if (mode==LINEAR_MODE) {
			int step=1;
			while(true) {
				h1 = (h1 + step) % max_size;
				if (h1 == newdata % max_size) {
					cout<< "Bad user input, array is full" << endl;
					exit(1);
				}

				if (hash_table[h1] == 0) {
					hash_table[h1] = newdata;
					contains++;
					return;
				}
			}
		}

		if (mode == QUADRATIC_MODE) {
			int stepSize = 0;
			int collisions = 0;
			int h2 = newdata % max_size;
			while (true) {
				stepSize = stepSize + (2 * ++collisions) - 1;
				h1 = (h2+stepSize) % max_size;
				if (h1 == newdata % max_size) {
					cout<< "Array is full" << endl;
					exit(1);
				}

				if (hash_table[h1] == 0) {
					hash_table[h1] = newdata;
					contains++;
					return;
				}
			}
		}

		if (mode == DOUBLE_MODE)
		{
			int step_size = h1;
			step_size = R - (newdata % R);
			while (true)
			{
				h1 = (h1 + step_size) % max_size;
				if (h1 == newdata % max_size)
				{
					cout << "Bad User" << endl;
					exit(1);
				}
				if (hash_table[h1] == 0)
				{
					hash_table[h1] = newdata;
					contains++;
					return;
				}
			}
		}
		cout << "Insert Failed" << endl;
		exit(1);
	}
	//YOU: Returns true if the key is in the hash table, false otherwise
	bool search(int key) {
		int initial = key % max_size;
		if (hash_table[initial] == key)
		{
			return true;
		}
		if (mode == LINEAR_MODE)
		{
			int h1 = initial;
			while(true)
			{
				h1+=1;
				if(hash_table[h1] == key)
				{
					return true;
				}
				if(h1 == key % max_size)
				{
					return false;
				}
			}
		return false;
		}
		if (mode == QUADRATIC_MODE)
		{
			int h1 = initial;
			int step_size = 0;
			int collision = 0;
			while (true)
			{
				step_size = step_size + (2 * ++collision) - 1;
				h1 = (initial + step_size) % max_size;
				if(hash_table[h1] == key)
				{
					return true;
				}
				if(h1 == initial)
				{
					return false;
				}
				if (hash_table[h1] == 0)
				{
					return false;
				}
			}
			return false;
		}

		if(mode == DOUBLE_MODE)
		{
			int h1 = initial;
			int step_size = R - (key % R);
			while (true)
			{
				h1 = (h1+step_size) % max_size;
				if(hash_table[h1] == key)
				{
					return true;
				}
				if (h1 == initial)
				{
				//	cout << "Wrapped around" << endl;
					return false;
				}
				if (hash_table[h1] == 0)
				{
				//	cout << "Search thinks it's empty" << endl;
					return false;
				}
			}
		// cout << "Base case" << endl;
		return false;
		}
	return false;
	}


Hash(const Hash&) = delete;
Hash operator=(const Hash&) = delete;
};

