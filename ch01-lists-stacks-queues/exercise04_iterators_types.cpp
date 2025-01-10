// g++ exercise04_iterators_types.cpp -o exercise04_iterators_types.exe
// exercise04_iterators_types.exe

/*
	iterators: [], advance, next, prev, 
	Singapure F1 Grand Prix
*/

#include <iostream>
#include <forward_list>
#include <vector>

int main()
{
	std::cout << "sample data for iterator like std::array-----------------------------------------"<<std::endl;
	std::vector<std::string> vec = {"Lewis Hamilton", "Lewis Hamilton", "NicoRoseberg", 
		"Sebastian Vettel", "Lewis Hamilton", "Sebastian Vettel",
		"Sebastian Vettel", "Sebastian Vettel", "Fernando Alonso"};
	
	for(const auto& c: vec)
		std::cout << c << " ";
	std::cout << std::endl;

	std::cout << "vec.begin iterator like Singly Linked List -------------------------------------" << std::endl;
	// iterator
	auto it = vec.begin(); // Constant time
	std::cout << "Latest winner is: " << *it << std::endl;

	it += 8; // Constant time
	std::cout << "Winner before 8 years was: " << *it << std::endl;
	
	advance(it, -3); // Constant time
	std::cout << "Winner before 3 years of that was: " << *it << std::endl;

	std::cout << "vec   forward_list iterator ---------------------------" << std::endl;
	std::forward_list<std::string> fwd(vec.begin(), vec.end());
	auto it1 = fwd.begin();
	std::cout << "Latest winner is: " << *it << std::endl;

	advance(it1, 5); // Time taken is proportional to the number of elements
	std::cout << "Winner before 5 years was: " << *it << std::endl;

	// Going back will result in compile time error as forward_list only
	// allows us to move towards the end.

	// advance(it1, -2); // Compiler error
}