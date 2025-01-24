// g++ e03_factorial_backtracking.cpp -o e03_factorial_backtracking.exe
// e03_factorial_backtracking.exe

/*
By indiscriminately checking every
possible subset, we consider options long after the point where we could determine
that they will never lead to a solution (for example, subsets with sums exceeding
the target). To improve our algorithm, we can utilize backtracking to exclude all the
branches of subproblems that are guaranteed to be invalid.

The n = 1 condition is the base case because that is the point at which the solution can
be returned without recursing further

*/
#include <iostream>

int Factorial(int n)
{
	// Base case — stop recursing
	if(n == 1)
	{
		return 1;
	}
	
	// Recurse until base case is reached
	return n * Factorial(n - 1);
}

int main()
{
	std::cout << "Backtrackig base case " << std::endl;
	std::cout << "Factorial: " << Factorial(8) << std::endl;

	return 0;
}