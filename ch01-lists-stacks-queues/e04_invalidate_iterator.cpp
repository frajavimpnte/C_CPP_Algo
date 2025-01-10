// g++ e04_invalidate_iterator.cpp -o e04_invalidate_iterator.exe
// e04_invalidate_iterator.exe

/*
a very basic example would be vector::push_back, which simply adds a
new element at the end. However, as we saw earlier, in some cases, it also requires
the movement of all the elements to a new buffer. Hence, all iterators, pointers, and
even the references to any of the existing elements will be invalidated.
*/

/*
Unlike vectors, linked list-based iterators are safer for insertion and deletion operations
because the elements will not be shifted or moved.
*/

#include <iostream>
#include <vector>
#include <list>

int main() 
{
	std::vector<int> vec = {1, 2, 3, 4, 5};
	for (int i : vec) 
 	 	std::cout << i << " ";
 	std::cout << std::endl;

	auto it4 = vec.begin() + 4;   // it4 now points to vec[4]
	std::cout << "it4: " << *it4 << std::endl;

	vec.insert(vec.begin() + 2, 0);
	// vec becomes {1, 2, 0, 3, 4, 5}
	for (int i : vec) 
 	 	std::cout << i << " ";
 	std::cout << std::endl;
	
	std::cout << "it4: " << *it4 << std::endl;
	/*
	it4 is invalid now, since it comes after the insertion position. Accessing it will lead to
	undefined behavior:
	*/

	std::list<int> lst = {1, 2, 3, 4, 5};
	auto l_it4 = next(lst.begin(), 4);
	std::cout << "l_it4: " << *l_it4 << std::endl;
	for(auto i: lst)
		std::cout << i << " ";
	std::cout << std::endl;

	lst.insert(next(lst.begin(), 2), 0);
	// l_it4 remains valid
	for(auto i: lst)
		std::cout << i << " ";
	std::cout << std::endl;
	
	std::cout << "l_it4: " << *l_it4 << std::endl;

	/*
	Hence, std::list is used more frequently compared to
	std::forward_list. forward_list is a better alternative if we have very strict constraints
	of memory and performance, and if we are sure that we don't want to traverse
	backward. So, in most cases, std::list is a safer choice.
	*/

}