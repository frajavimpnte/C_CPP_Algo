/* 
// g++ exercise36_subset_sum.cpp -o exercise36_subset_sum.exe
// exercise36_subset_sum.exe
*/

/*
Subset Sum Problem
Imagine that you are implementing the logic for a digital cash register. Whenever a
customer needs change, you would like to display a message that tells the cashier
whether or not the money currently in the register can be combined in some way so
that its sum is equal to the amount of change required. For example, if a product costs
$7.50 and the customer pays $10.00, the message would report whether the money in
the register can be used to produce exactly $2.50 in change.

Step 1: Evaluating the Need for DP
Our first step when faced with a problem like this is to determine whether it can (and/
or should) be solved with DP. To reiterate, a problem is solvable with DP if it has the
following properties:
	• Overlapping subproblems: Like the standard divide-and-conquer approach, the
	final solution can be derived by combining the solutions of smaller subproblems in
	some way; in contrast to divide and conquer, however, certain subproblems will be
	encountered multiple times.

	• Optimal substructure: The optimal solution for a given problem can be produced
	by the optimal solutions of its subproblems.

Step 2 – Defining the States and the Base Cases
Having determined that this is a DP problem, we now must determine what constitutes
a state within the context of this problem. In other words, in terms of the question that
we are trying to answer, what makes one possible solution different from another?

Therefore, we will develop our understanding of the subset sum problem's base case(s)
and states by solving it in two different ways that are much simpler to implement.
Throughout our exploration of dynamic programming, we will consider a total of four
different approaches to each problem: brute force, backtracking, memoization, and
tabulation.

Step 2.a: Brute Force
Despite its inefficiency, a brute-force solution can be quite informative in developing an
understanding of the problem at hand. Implementing brute-force approaches can be an
essential step in the process of forming a DP solution for several reasons:
	• Simplicity
	• The certainty of solution correctness
	• Ability to visualize the subproblems

Step 2.b: Optimizing Our Approach – Backtracking
By indiscriminately checking every
possible subset, we consider options long after the point where we could determine
that they will never lead to a solution (for example, subsets with sums exceeding
the target). To improve our algorithm, we can utilize backtracking to exclude all the
branches of subproblems that are guaranteed to be invalid.

The main advantage of implementing a backtracking solution before attempting to
use DP is that it requires us to determine the base case(s) and intermediate recursive
states of the problem.

>>>>
In the subset sum problem, one way to define our base cases would be as follows:
	— If sum of a given subset is equal to target : TRUE
Otherwise:
	— If sum is greater than target : FALSE
	— If end of set is reached : FALSE

Using our brute-force algorithm's output as a reference, we can analyze how subsets of
each size group are formed to plot out our state transitions:
	TARGET = 50
	SIZE = 1
	Base case —> { } [SUM = 0]

	{ } —> { 13 } [0 + 13 = 13]
	{ 79 } [0 + 79 = 79]
	{ 45 } [0 + 45 = 45]
	{ 29 } [0 + 29 = 29]

We can follow the same line of logic for size 2 subsets. Simply take each subset of size
1 and append every element whose index is greater than the highest-indexed element
already in the subset. This is essentially the approach we took in our brute-force
implementation; however, this time, we will consider the sum of each subset as we
process them, and terminating them when the current sum exceeds the target

	TARGET = 50
	SIZE = 2
		{ 13 } -> { 13 79 } (92)      Eliminate 92 > 50
				  { 13 79 } (58)      TRUE 58 == 58
				  { 13 29 } (42)	  Keep 42 < 58

		{ 79 } -> { 79 45 } (125)     Eliminate 125 > 50
			      { 79 29 } (108)     Eliminate 108 > 50

		{ 45 } -> { 45 29 } (74)      Eliminate 74 > 50

	SIZE = 3
		{ 13 79 } -> { 13 79 45 } (137)    Eliminate 139 > 50
				     { 13 79 29 } (121)    Eliminate 121 > 50

		{ 13 45 } -> { 13 45 29 } (87)     Eliminate 87 > 50

		{ 79 45 } -> { 79 45 29 } (153)    Eliminate 166 > 50

	SIZE = 4
		{ 13 79 45 } -> { 13 79 45 29 } (166)    Eliminate 166 > 50

When target is equal to 58, we can see that none of the subsets of size 3 or 4 need to be
considered. Thus, we can describe our intermediate state transition as follows:

	for element of set at index i and subset ss:
		If sum of ss with set[i] is less than or equal to target:
			1) Append set[i] to ss
			2) Increment i
			Next state —> (i = i + 1, ss = ss ∪ set[i])
	In any case:
		1) Do not append set[i] to ss
		2) Increment i
		Next state —> (i = i + 1, ss = ss)

Now, we should ask the following questions:
	• What is the minimal amount of data needed to represent this state?
	• How can we reformulate the preceding logic to remove unnecessary information?

OPTIMIZE
Consider the specific problem we are trying to solve: finding whether a subset of
elements exists within the set whose sum is equal to the target. According to the
problem description, our task does not require that we produce the actual subsets, but
only their sums. So, our pseudocode could be more succinctly expressed as follows:

	for element of set at index i and its sum as sum:
		If sum plus set[i] is less than or equal to target:
			1) Add value of set[i] to sum
			2) Increment i
			Next state —> (i = i + 1, sum = sum + set[i])
	In any case:
		1) Do not add value of set[i] to sum
		2) Increment i
	Next state —> (i = i + 1, sum = sum)

ANALYZE
Using this new approach, we can essentially represent each state transition with only
two integers, sum and i, eliminating the need to store 2n subset arrays in the worst case.

Furthermore, we can remove the need to keep track of the target value by inverting
the problem (that is, starting at target and subtracting set[i] at each step). As a
final optimization, we can sort the set before calling the function, which allows us to
determine that there are no other valid possibilities as soon as the sum exceeds the
target.

Step 3: Memoization
To demonstrate this difference, try running your code from the previous exercise using
6799 as the target (exactly 1 less than the total sum of all the elements of the set). On
the author's machine, the backtracking solution took about 0.268 seconds on average
to produce the result – nearly 350 times longer than the average time taken with the
target value used in the exercise.

Thankfully, we already have all the information we need to devise a top-down solution
while utilizing memoization. Even better, we hardly have to modify our previous
approach at all to implement it!


Devising a Caching Scheme
The most important aspect of using memoization is to define a caching scheme.
Caching results for memoized solutions can be done in a number of ways, but the most
common are as follows:
	• Simple arrays, with states represented by numerical indices
	• Hash tables/maps, with states represented by descriptive strings that are hashed
		using built-in language features
	• Hash tables/maps, with states represented by hash values that are created using
		an original hashing formula

As you may recall from the introduction to this chapter, a caching scheme should be as
follows:
	• Valid: Cache keys must be represented in a way that avoids collisions between
		different states that are not used to solve the same set of subproblems.
	• Worthwhile/useful: If your caching scheme is so specific that it never actually
		produces any "hits", then it essentially accomplishes nothing.

!!!!! In the subset sum problem, we may mistakenly come to believe that failing to find the
target from a state with a given sum value means that it would be impossible to get a
true result from any other state with the same sum.

Step 4: Tabulation
So far, we have implemented three different algorithmic approaches to solving the
subset sum problem, each of which has a significant improvement over the one
preceding it. However, let's say that we wanted a list of every possible subset sum in a
given set. We would have to run our algorithm repeatedly for each sum, from 1 to the
total sum of the entire set. For situations such as these, tabulation is often the only
efficient option.

A tabulated solution has to somehow condense the layers of complexity into a simple 
set of iterations using the standard for/while loops.
           o 			for 
        o  o  o   =>    {   
     ooo ooo   oo       	for ...    
                        }
Like memoization, the first goal after defining the base case(s) and states of the problem
is to develop a scheme for storing the solutions for different states. Typically, tabulated
approaches use simple arrays/vectors for this purpose.

Idea
The subset sum problem is that the minimal way to represent each state uniquely in the latter requires two dimensions —
the index in the set and the current sum.

Let's consider some of the insights we have gained about this problem in greater depth:
	• Each possible subset of size k can be formed by taking new elements and
		appending them onto every subset of size k – 1.
	• If a solution has been found at index i with a sum value of x, then any sequence of
		state transitions that eventually lead to that same set of conditions will produce an
		identical result:

index set: https://www.youtube.com/watch?v=_Oz_vYCI1Vg
  what are we inding?
current sum: suma actual
EXAMPLE:
set = {2, 5, 6, 3, 7, 20}
target = 28

base case -> { } [SUM = 0]
TOP DOWN  - restar
                                index 0 => {}   
                                index 1 => [{2}, {5}, {6}, {3}, {7}, {20}] 
                                index 2 => [{2,5}, {2,6}, {2,3}, {2,7}, {2,8}, {5,6}, {5,3}...
[i] 6   5   4   3   2   1   0
                            28  iter 0
                       26       iter 1  



EXAMPLE:
set = {13, 79, 45, 29 }
TARGET = 50
    SIZE = 0
    Base case —> { } [SUM = 0]

	SIZE = 1	
	{ } —> { 13 } [0 + 13 = 13]
		   { 79 } [0 + 79 = 79]
	       { 45 } [0 + 45 = 45]
	       { 29 } [0 + 29 = 29]

	SIZE = 2
		{ 13 } -> { 13 79 } (92)      Eliminate 92 > 50
				  { 13 79 } (58)      TRUE 58 == 58
				  { 13 29 } (42)	  Keep 42 < 58

		{ 79 } -> { 79 45 } (125)     Eliminate 125 > 50
			      { 79 29 } (108)     Eliminate 108 > 50

		{ 45 } -> { 45 29 } (74)      Eliminate 74 > 50

	SIZE = 3
		{ 13 79 } -> { 13 79 45 } (137)    Eliminate 139 > 50
				     { 13 79 29 } (121)    Eliminate 121 > 50

		{ 13 45 } -> { 13 45 29 } (87)     Eliminate 87 > 50

		{ 79 45 } -> { 79 45 29 } (153)    Eliminate 166 > 50

	SIZE = 4
		{ 13 79 45 } -> { 13 79 45 29 } (166)    Eliminate 166 > 50



>>>>
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <iomanip>

using namespace std;

#define DEBUG 0
#if DEBUG
#define PRINT(x) cerr << x
#else
#define PRINT(x)
#endif

vector<string> types =
{
	"BRUTE FORCE",
	"BACKTRACKING",
	"MEMOIZATION",
	"TABULATION"
};

const int UNKNOWN = INT_MAX;




void GetTime(clock_t &timer, string type)
{
	// Subtract timer value from current time to get time elapsed
	timer = clock() - timer;

	// Display seconds elapsed
	cout << "TIME TAKEN USING " << type << ": " << fixed << setprecision(5)
		 << (float)timer / CLOCKS_PER_SEC << endl;

	timer = clock(); // Reset timer
}





/*
allSubsets:  
			vector subsets of cardinality N
    vector<vector> number of subsets of cardinality i
    vector<vector<vector>> elements of subsets of cardinality i

*/
void GetAllSubsets(vector<int> set, vector<int> subset, int index, vector<vector<vector<int>>> &allSubsets)
{
	// Terminate if the end of the set is reached
	if(index == set.size())
	{
		// Add the accumulated subset to the results, indexed by size
		allSubsets[subset.size()].push_back(subset);
		return;
	}

	// Continue without adding element to subset
	GetAllSubsets(set, subset, index + 1, allSubsets);
	
	// Add element to subset
	subset.push_back(set[index]);
	GetAllSubsets(set, subset, index + 1, allSubsets);
}

bool SubsetSum_BruteForce(vector<int> set, int target)
{
	vector<vector<vector<int>>> allSubsets(set.size() + 1);
	
	GetAllSubsets(set, {}, 0, allSubsets);
	for(int size = 0; size <= set.size(); size++)
	{
		PRINT("SIZE = " << size << endl);
		for(auto subset : allSubsets[size])
		{
			int sum = 0;
			PRINT("\t{ ");
			
			for(auto number : subset)
			{
				PRINT(number << " ");
				sum += number;
			}
			
			PRINT("} = " << sum << endl);
			if(sum == target) return true;
		}
	}
	return false;
}

bool SubsetSum_Backtracking(vector<int> &set, int sum, int i)
{
	// The sum has been found
	if(sum == 0)
	{
		return true;
	}

	// End of set is reached, or sum would be exceeded beyond this point
	if(i == set.size() || set[i] > sum)
	{
		return false;
	}

	// Case 1: Add to sum
	// Case 2: Leave as-is
	return SubsetSum_Backtracking(set, sum - set[i], i + 1) 
		   || SubsetSum_Backtracking(set, sum, i + 1);

}


bool SubsetSum_Memoization(vector<int> &set, int sum, int i, vector<vector<int>> &memo)
{
	if(sum == 0)
	{
		return true;
	}
	
	if(i == set.size() || set[i] > sum)
	{
		return false;
	}

	// the pivotal difference is that after the base cases, rather than immediately
	// investigating the next two states, we check the memo table for cached results

	// Is this state's solution cached?
	if(memo[i][sum] == UNKNOWN)
	{
		// If not, find the solution for this state and cache it
		bool append = SubsetSum_Memoization(set, sum - set[i], i + 1, memo);
		bool ignore = SubsetSum_Memoization(set, sum, i + 1, memo);
		memo[i][sum] = append || ignore;
	}
	// Return cached value
	return memo[i][sum];
}

int main()
{
	// data
	// vector<int> set = { 13, 79, 45, 29 };
	// int target = 58;

	vector<int> set = { 16, 1058, 22, 13, 46, 55, 3, 92, 47, 7, 98, 367, 807,
				106, 333, 85, 577, 9, 3059 };
	//int target = 6076;
    int target = 6799;

	int tests = 3;

	// timer define 
	clock_t timer = clock();

	
	sort(set.begin(), set.end());

	for(int i = 0; i < tests; i++)	
	{
		bool found;


		switch(i)
		{
			case 0: 
				// SubsetSum_BruteForce	
				cout << "SubsetSum_BruteForce-------------------------------------" << endl;
				found = SubsetSum_BruteForce(set, target); 
				break;
			case 1: 
				// SubsetSum_Backtracking
				cout << "SubsetSum_BruteForce-------------------------------------" << endl;
				found = SubsetSum_Backtracking(set, target, 0); 
				break;
			case 2:
				{
				// SubsetSum_SubsetSum_Memoization
				cout << "SubsetSum_SubsetSum_Memoization--------------------------" << endl;
				// Initialize memoization table
				vector<vector<int>> memo(set.size(), vector<int>(7000,
				UNKNOWN));
				found = SubsetSum_Memoization(set, target, 0, memo);
				break;
				}
		}

		if(found)
		{
			cout << "Subset with sum " << target 
			     << " was found in the set." << endl;
		}
		else
		{
			cout << "Subset with sum " << target 
				 << " was not found in the set." << endl;
		}

		GetTime(timer, types[i]);
		cout << endl;
	}

	return 0;	
}