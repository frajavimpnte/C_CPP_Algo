// g++ e01_fibonacci.cpp -o e01_fibonacci.exe
// e01_fibonacci.exe

/*
The heart of dynamic programming is tabulation, which is the inverse approach to
memoization. In fact, though the term dynamic programming is sometimes applied to
both memoization and tabulation, its use is generally assumed to refer specifically to
the latter.


Fibonacci problem solving
>top-down solution because it begins at the top of the recursion tree 
(that is, the solution) and traverses down its branches until it reaches 
the base cases.

>Memoization – The Top-Down Approach
This technique of recursively caching solutions in a top-down manner is known 
as memoization, and can essentially be employed for any DP problem, assuming 
the following are true:
	1. You can devise a caching scheme that exploits the similarity of different states
		while preserving their uniqueness.
	2. You can accumulate the solutions for the requisite subproblems before exceeding
		the available stack space.

>Tabulation – the Bottom-Up Approach
The standard implementation of tabulation consists of storing the solutions for the base
cases and then iteratively filling a table with the solutions for every subproblem, which
can then be reused to find the solutions for other subproblems. Tabulated solutions are
generally considered to be a bit harder to conceptualize than memoized ones because
the state of each subproblem must be represented in a way that can be expressed
iteratively.
*/
#include <iostream>
#include <vector>
#include <chrono>

const int UNKNOWN = -1;
const int MAX_SIZE = 100000;

std::vector<int> memo(MAX_SIZE, UNKNOWN);

int FibonacciTopDown(int n)
{
	if(n < 2)
	{
		return n;
	}
	
	return FibonacciTopDown(n - 1) + FibonacciTopDown(n - 2);
}



int FibonacciTopDownMemoization(int n)
{
	if(n < 2)
	{
		return n;
	}
	
	if(memo[n] != UNKNOWN)
	{
		return memo[n];
	}
	
	int result = FibonacciTopDownMemoization(n - 1) + FibonacciTopDownMemoization(n - 2);
	memo[n] = result;
	return result;
}

int FibonacciBottomUpTabulation(int n)
{
	std::vector<int> DP(n + 1, 0);
	
	DP[1] = 1;
	
	for(int i = 2; i <= n; i++)
	{
		DP[i] = DP[i-1] + DP[i-2];
	}
	return DP[n];
}

int main()
{

	std::cout << "Fibonacci top-down ---------------------------------" << std::endl;
	// Get starting timepoint
    auto start = std::chrono::high_resolution_clock::now();

	std::cout << "Fibonacci(40): " << FibonacciTopDown(40) << std::endl;

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
	std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;


	std::cout << "Fibonacci top-down memoization---------------------------------" << std::endl;
	start = std::chrono::high_resolution_clock::now();

	std::cout << "FibonacciTopDownMemoization(40): " << FibonacciTopDownMemoization(40) << std::endl;

	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;


	std::cout << "Fibonacci Tabulation Bottom-Up---------------------------------" << std::endl;
	start = std::chrono::high_resolution_clock::now();

	std::cout << "FibonacciBottomUpTabulation(40): " << FibonacciBottomUpTabulation(40) << std::endl;

	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;

	return 0;
}