// g++ exercise24_shortest_job_first_scheduling.cpp -o exercise24_shortest_job_first_scheduling.exe
// exercise24_shortest_job_first_scheduling.exe

/*
Shortest-Job-First Scheduling
Say you are standing in a queue at your bank. It's a busy day and there are N people
in the queue, but the bank has only one counter open (it's also a really bad day!). Let's
assume that it takes a person, pi, the amount of time of ai to get served at the counter.
Since the people in the queue are quite rational, everyone agrees to reorder their places
in the queue so that the average waiting time for everyone in the queue is minimized.
You are tasked with finding a way of reordering the people in the queue. How would you
solve this problem?

A clue to solving this problem is as follows: since we are looking to minimize the average
waiting time, we must find a way to reduce the waiting time for the largest possible set
of people, as much as possible. One way to reduce the waiting time for all people is the
job that can be completed the quickest.
*/


#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <numeric>

// Given a set of service times, computes the service times for all users
template<typename T> auto compute_waiting_times(std::vector<T>& service_times)
{
	std::vector<T> W(service_times.size());
	W[0] = 0;	
	for (auto i = 1; i < service_times.size(); i++)
		W[i] = W[i - 1] + service_times[i - 1];
	return W;
}

// Generic function to print a vector
template<typename T> void print_vector(std::vector<T>& V)
{
	for (auto& i : V)
		std::cout << i << " "; 
	std::cout << std::endl;
}

template<typename T> void compute_and_print_waiting_times(std::vector<T>& service_times)
{
	auto waiting_times = compute_waiting_times<int>(service_times);
	std::cout << "Service times: " << std::endl;
	print_vector<T>(service_times);

	std::cout << "Waiting times: " << std::endl;
	print_vector<T>(waiting_times);
	std::cout << "Average waiting time = " << 
		std::accumulate(waiting_times.begin(),waiting_times.end(), 0.0) / waiting_times.size();
	std::cout<< std::endl;
}

void shortest_job_first(size_t size)
{
	std::vector<int> service_times;
	std::random_device rd;
	std::mt19937 rand(rd());
	std::uniform_int_distribution<std::mt19937::result_type> uniform_dist(1, size);

	// Insert random elements as service times
	service_times.reserve(size);
	for (auto i = 0; i < size; i++)
		service_times.push_back(uniform_dist(rand));

	compute_and_print_waiting_times<int>(service_times);
	
	// Reorder the elements in the queue
	std::sort(service_times.begin(), service_times.end());
	compute_and_print_waiting_times<int>(service_times);
}

int main(int argc, char* argv[])
{
	shortest_job_first(10);
}