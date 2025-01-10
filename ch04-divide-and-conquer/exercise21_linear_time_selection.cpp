// g++ exercise21_linear_time_selection.cpp -o exercise21_linear_time_selection.exe
// exercise21_linear_time_selection.exe


/*
Imagine that you are in charge of organizing a marching band parade for your school.
To ensure that all the band members look uniform, it is important that the heights of
students be the same. Moreover, students from all grades are required to participate.
To solve these problems, you come up with the following solution – you will select only
the 15th shortest student in every grade to participate in the parade. The problem can
be formalized as follows: given a randomly ordered set of elements, S, you are asked to
find the ith smallest element in S. A simple solution could be sorting the input and then
selecting the ith element. However, the algorithmic complexity of this solution is O(n log
n). In this section, we will work through a divide-and-conquer solution that solves the
problem in O(n).
*/

#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <numeric>


template <typename T>
auto partition(typename std::vector<T>::iterator begin,
	typename std::vector<T>::iterator end)
{
	auto pivot_val = *begin;
	auto left_iter = begin + 1;
	auto right_iter = end;

	while (true)
	{
		while (*left_iter <= pivot_val && left_iter != right_iter)
			left_iter++;
		while (*right_iter >= pivot_val && left_iter != right_iter)
			right_iter--;


		if (left_iter == right_iter)
			break;
		else
			std::iter_swap(left_iter, right_iter);
	}
	if (pivot_val > * right_iter)
		std::iter_swap(begin, right_iter);

	return right_iter;
}

template <typename T>
void quick_sort(typename std::vector<T>::iterator begin,
	typename std::vector<T>::iterator last)
{
	if (std::distance(begin, last) >= 1)
	{
		auto partition_iter = partition<T>(begin, last);

		quick_sort<T>(begin, partition_iter - 1);
		quick_sort<T>(partition_iter, last);
	}
}


template<typename T> auto find_median(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator last)
{
	// Sort the array
	quick_sort<T>(begin, last);
	// Return the middle element, i.e. median
	return begin + (std::distance(begin, last)/2);
}


/*
Quicksort, our partition function assumed that the first element in a
given vector was always the pivot to be used. We now need a more general form of
the partition operation that can work with any pivot element
*/
template <typename T> auto partition_using_given_pivot( 
typename std::vector<T>::iterator begin,
	typename std::vector<T>::iterator end,
	typename std::vector<T>::iterator pivot)
{
	// Since the pivot is already given,
	// Create two iterators pointing to the first and last element of the vector respectively
	auto left_iter = begin;
	auto right_iter = end;
	while (true)
	{
		// Starting from the first element of vector, find an element that is greater than pivot.
		while (*left_iter < *pivot && left_iter != right_iter)
			left_iter++;
		
		// Starting from the end of vector moving to the beginning, find an element that is lesser than the pivot.
		while (*right_iter >= *pivot && left_iter != right_iter)
			right_iter--;

		// If left and right iterators meet, there are no elements left to swap. Else, swap the elements pointed to by the left and right iterators.
		if (left_iter == right_iter)
			break;
		else
			std::iter_swap(left_iter, right_iter);
	}
	if (*pivot > *right_iter)
		std::iter_swap(pivot, right_iter);

	return right_iter;
}

// Finds ith smallest element in vector V
template<typename T> typename std::vector<T>::iterator linear_time_select(
	typename std::vector<T>::iterator begin,
	typename std::vector<T>::iterator last, 
	size_t i)
{
	auto size = std::distance(begin, last);
	if (size > 0 && i < size) {
		// Get the number of V_i groups of 5 elements each
		auto num_Vi = (size+4) / 5;
		size_t j = 0;
		// For each V_i, find the median and store in vector M
		std::vector<T> M;
		
		for (; j < size/5; j++)
		{
			auto b = begin + (j * 5);
			auto l = begin + (j * 5) + 5;
			M.push_back(*find_median<T>(b, l));
		}
		
		if (j * 5 < size)
		{
			auto b = begin + (j * 5);
			auto l = begin + (j * 5) + (size % 5);
			M.push_back(*find_median<T>(b, l));
		}

		// Find the middle element ('q' as discussed)
		auto median_of_medians = (M.size() == 1)? M.begin(): 
			linear_time_select<T>(M.begin(), M.end()-1, M.size() / 2);

		// Apply the partition operation and find correct position 'k' of
		// pivot 'q'.
		auto partition_iter = partition_using_given_pivot<T>(begin, last, median_of_medians);
		auto k = std::distance(begin, partition_iter)+1;
		if (i == k)
			return partition_iter;
		else if (i < k)
			return linear_time_select<T>(begin, partition_iter - 1, i);
		else if (i > k)
			return linear_time_select<T>(partition_iter + 1, last, i-k);
	}
	else {
		return begin;
	}
}

template <typename T> std::vector<T> merge(std::vector<T>& arr1, std::vector<T>& arr2)
{
	std::vector<T> merged;
	auto iter1 = arr1.begin();
	auto iter2 = arr2.begin();
	while (iter1 != arr1.end() && iter2 != arr2.end())
	{
		if (*iter1 < *iter2)
		{
			merged.emplace_back(*iter1);
			iter1++;
		}
		else
		{
			merged.emplace_back(*iter2);
			iter2++;
		}
	}
	
	if (iter1 != arr1.end())
	{
		for (; iter1 != arr1.end(); iter1++)
			merged.emplace_back(*iter1);
	}
	else
	{
		for (; iter2 != arr2.end(); iter2++)
			merged.emplace_back(*iter2);
	}
	return merged;
}

template <typename T> std::vector<T> merge_sort(std::vector<T> arr)
{
	if (arr.size() > 1)
	{
		auto mid = size_t(arr.size() / 2);
		auto left_half = merge_sort(std::vector<T>(arr.begin(), arr.begin() + mid));
		auto right_half = merge_sort(std::vector<T>(arr.begin() + mid, arr.end()));
		return merge<T>(left_half, right_half);
	}
	return arr;
}

template <typename T> void print_vector(std::vector<T> arr)
{
	for (auto i : arr)
		std::cout << i << " ";

	std::cout << std::endl;
}


void run_linear_select_test()
{
	std::vector<int> S1{ 45, 1, 3, 1, 2, 3, 45, 5, 1, 2, 44, 5, 7 };
	std::cout << "Original vector:" << std::endl;	
	print_vector<int> (S1);

	std::cout << "Sorted vector:" << std::endl;
	print_vector<int>(merge_sort<int>(S1));
	std::cout << "3rd element: " << *linear_time_select<int>(S1.begin(), S1.end() - 1, 3) << std::endl;
	std::cout << "5th element: " << *linear_time_select<int>(S1.begin(), S1.end() - 1, 5) << std::endl;
	std::cout << "11th element: " << *linear_time_select<int>(S1.begin(), S1.end() - 1, 11) << std::endl;
}

int main()
{
	run_linear_select_test();
	return 0;
}

