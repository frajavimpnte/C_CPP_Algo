// g++ exercise22_map_reduce_STL.cpp -o exercise22_map_reduce_STL.exe
// exercise22_map_reduce_STL.exe

/*
MapReduce is a programming model and an associated implementation for processing
and generating large datasets. Users specify a map function that processes a key-value
pair to generate a set of intermediate key/value pairs, and a reduce function that merges
all the intermediate values associated with the same intermediate key.

MapReduce programming model have appeared, the most notable of which is Hadoop.
Hadoop provides a programming toolkit for the user to write map and reduce functions
that can be applied to data stored in a distributed filesystem called the Hadoop
Distributed File System (HDFS).

The terms map and reduce have their origins in functional programming languages such
as Lisp.
*/

#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <numeric>

void transform_test(size_t size)
{
	std::vector<int> S, Tr;
	std::random_device rd;
	std::mt19937 rand(rd());
	std::uniform_int_distribution<std::mt19937::result_type> uniform_dist(1, size);

	// Insert random elements
	for (auto i = 0; i < size; i++)
		S.push_back(uniform_dist(rand));

	std::cout << "Original array, S: ";	
	for (auto i : S)
		std::cout << i << " ";
	std::cout << std::endl;

	std::transform(S.begin(), S.end(), std::back_inserter(Tr),[](int x) {return std::pow(x, 2.0); });
	std::cout << "Transformed array, Tr: ";
	for (auto i : Tr)
		std::cout << i << " ";
	std::cout << std::endl;
	
	// For_each
	std::for_each(S.begin(), S.end(), [](int &x) {
		x = std::pow(x, 2.0);
	});

	std::cout << "After applying for_each to S: ";
	for (auto i : S)
		std::cout << i << " ";
	std::cout << std::endl;
}

/*
The reduce operation is implemented in the C++ Standard Library as
std::accumulate() and std::reduce() (available only in C++ 17 and later)
*/
void reduce_test(size_t size)
{
	std::vector<int> S;
	std::random_device rd;
	std::mt19937 rand(rd());
	std::uniform_int_distribution<std::mt19937::result_type> uniform_dist(1, size);

	// Insert random elements
	for (auto i = 0; i < size; i++)
		S.push_back(uniform_dist(rand));

	std::cout << std::endl << "Reduce test== " << std::endl << "Original array, S: ";
	for (auto i : S)
		std::cout << i << " ";
	std::cout << std::endl;

	// Accumulate
	std::cout<<"std::accumulate() = " << std::accumulate(S.begin(), S.end(), 0, [](int acc, int x) {return acc+x; });
	std::cout << std::endl;
}

int main()
{
	transform_test(10);
	reduce_test(10);
	return 0;
}