// g++ e03_forward_list.cpp -o e03_forward_list.exe
// e03_forward_list.exe

#include <iostream>
#include <forward_list>

// forward_list methods: new, delete, front, back, push_front, insert_after, 
int main() {


	std::cout << "create a forward_list -------------------------------" << std::endl;
	std::forward_list<int> fwd_list = {1, 2, 3};
	for (int& a : fwd_list)
        std::cout << a << " ";
    std::cout << std::endl;
	
	std::cout << "forward_list push_front-------------------------------" << std::endl;
	fwd_list.push_front(0);				// list becomes {0, 1, 2, 3}
	for (int& a : fwd_list)
        std::cout << a << " ";
    std::cout << std::endl;
	
	
	std::cout << "forward_list  begin (returns iterator)-----------------" << std::endl;
	auto it = fwd_list.begin();
	//std::cout << it << std::endl;

	std::cout << "forward_list insert_after-------------------------------" << std::endl;
	fwd_list.insert_after(it, 5);		// list becomes {0, 5, 1, 2, 3}
	for (int& a : fwd_list)
        std::cout << a << " ";
    std::cout << std::endl;

	std::cout << "forward_list insert_after-------------------------------" << std::endl;
	fwd_list.insert_after(it, 6);		// list becomes {0, 6, 5, 1, 2, 3}
	for (int& a : fwd_list)
        std::cout << a << " ";
    std::cout << std::endl;

    // emplace_front, emplace_after

    // pop_front, erase_after

    std::cout << "create forward_list------------------------------------" << std::endl;
    std::forward_list<int> fwd_list2 = {1, 2, 3, 4, 5};
	fwd_list2.pop_front();	
	// list becomes {2, 3, 4, 5}
	for (int& a : fwd_list2)
        std::cout << a << " ";
    std::cout << std::endl;
	
	std::cout << "forward_list begin (returns iterator)------------------" << std::endl;
	auto it2 = fwd_list2.begin();
	//cout << it2 << std::endl;
	
	std::cout << "forward_list erase_after-------------------------------" << std::endl;
	fwd_list2.erase_after(it2);
	// list becomes {2, 4, 5}
	for (int& a : fwd_list2)
        std::cout << a << " ";
    std::cout << std::endl;

	std::cout << "forward_list erase_after-------------------------------" << std::endl;
	fwd_list2.erase_after(it2, fwd_list2.end());
	// list becomes {2}
	for (int& a : fwd_list2)
        std::cout << a << " ";
    std::cout << std::endl;

    // remove, remove_if,


    std::cout << "forward_list sort default std::less<value_type>()--------" << std::endl;
    std::forward_list<int> list1 = {23, 0, 1, -3, 34, 32};
	for (int& a : list1)
        std::cout << a << " ";
    std::cout << std::endl;

	list1.sort();
	// list becomes {-3, 0, 1, 23, 32, 34}
	for (int& a : list1)
        std::cout << a << " ";
    std::cout << std::endl;

	std::cout << "forward_list sort std::greater<int>()-------------------------------" << std::endl;
	list1.sort(std::greater<int>());
	// list becomes {34, 32, 23, 1, 0, -3} 
	for (int& a : list1)
        std::cout << a << " ";
    std::cout << std::endl;


    // reverse, unique functions
    std::cout << "forward_list  list2 for reverse, unique-----------------------------" << std::endl;
    std::forward_list<int> list2 = {2, 53, 1, 0, 4, 10};
    for (int& a : list2)
        std::cout << a << " ";
    std::cout << std::endl;

    std::cout << "forward_list  list2 reverse------------------------------------------" << std::endl;
    list2.reverse();
	// list becomes {2, 53, 1, 0, 4, 10}
	for (int& a : list2)
        std::cout << a << " ";
    std::cout << std::endl;

    std::cout << "forward_list  list2 redefine, sort, unique----------------------------" << std::endl;
	list2 = {0, 1, 0, 1, -1, 10, 5, 10, 5, 0};
	for (int& a : list2)
        std::cout << a << " ";
    std::cout << std::endl;

	list2.sort();
	// list becomes {-1, 0, 0, 0, 1, 1, 5, 5, 10, 10}
	for (int& a : list2)
        std::cout << a << " ";
    std::cout << std::endl;

	list2.unique();
	// list becomes {-1, 0, 1, 5, 10}
	for (int& a : list2)
        std::cout << a << " ";
    std::cout << std::endl;

    std::cout << "forward_list  list2 redefine, sort, unique----------------------------" << std::endl;
	list2 = {0, 1, 0, 1, -1, 10, 5, 10, 5, 0};
	for (int& a : list2)
        std::cout << a << " ";
    std::cout << std::endl;

	list2.sort();
	// list becomes {-1, 0, 0, 0, 1, 1, 5, 5, 10, 10}
	list2.unique([](int a, int b) { return (b - a) < 2; });
	// list becomes {-1, 1, 5, 10}
	for (int& a : list2)
        std::cout << a << " ";
    std::cout << std::endl;


	return 0;
}