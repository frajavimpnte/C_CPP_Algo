// g++ exercise06_std_list.cpp -o exercise06_std_list.exe
// exercise06_std_list.exe

/*
	std::list double linked list: push_back, size, insert, emplace, 
		emplace_back, pop_back, remove, remove_if, sort, unique, reverse

	The following exercise demonstrates the use of insertion and deletion functions for std::list.
*/


#include <iostream>
#include <list>

int main()
{
	std::list<int> list1 = {1, 2, 3, 4, 5};
	
	std::cout << "List: ";
	for(auto i: list1)
		std::cout << i << " ";
	std::cout << std::endl;

	list1.push_back(6);					 // list becomes {1, 2, 3, 4, 5, 6}

	std::cout << "List push_back";
	for(auto i: list1)
		std::cout << i << " ";
	std::cout << std::endl;

	list1.insert(next(list1.begin()), 0); // list becomes {1, 0, 2, 3, 4, 5, 6}
	std::cout << "list1.insert(next(list1.begin()), 0): ";
	for(auto i: list1)
		std::cout << i << " ";
	std::cout << std::endl;

	list1.insert(list1.end(), 7); 		  // list becomes {1, 0, 2, 3, 4, 5, 6, 7}
	std::cout << "list1.insert(list1.end(), 7)";
	for(auto i: list1)
		std::cout << i << " ";
	std::cout << std::endl;



	list1.pop_back(); // list becomes {1, 0, 2, 3, 4, 5, 6}
	std::cout << "list1.pop_back():";
	for(auto i: list1)
		std::cout << i << " ";
	std::cout << std::endl;


	return 0;
}