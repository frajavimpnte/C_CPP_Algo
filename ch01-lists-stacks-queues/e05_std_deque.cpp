
// g++ e05_std_deque.cpp -o e05_std_deque.exe
// e05_std_deque.exe

/*
So far, we have seen array-based and linked list-based containers. std::deque mixes
both of them and combines each of their advantages to a certain extent. As we have
seen, although vector is a variable-length array, some of its functions, such as push_
front and pop_front, are very costly operations. std::deque can help us overcome that.
Deque is short for double-ended queue.

Such a structure may be used in cases such as boarding queues for flights.
*/

/*
deque: push_front, push_back, insert, emplace_front, emplace_back, emplace, pop_front, 
pop_back, erase, shrink_to_fit
*/

#include <iostream>
#include <deque>

int main()
{

	std::deque<int> deq = {1, 2, 3, 4, 5};
	std::cout << "deque" <<std::endl;
	for (int i : deq) 
 	 	std::cout << i << " ";
 	std::cout << std::endl;

 	std::cout << "deque.push_front(0)" <<std::endl;
	deq.push_front(0);   // deque becomes {0, 1, 2, 3, 4, 5}
	for (int i : deq) 
 	 	std::cout << i << " ";
 	std::cout << std::endl;

 	std::cout << "deque.push_back(6)" <<std::endl;
	deq.push_back(6); 				 // deque becomes {0, 1, 2, 3, 4, 5, 6}
	for (int i : deq) 
 	 	std::cout << i << " ";
 	std::cout << std::endl;

 	std::cout << "deque.insert(begin() + 2, 10)" <<std::endl;
	deq.insert(deq.begin() + 2, 10); // deque becomes {0, 1, 10, 2, 3, 4, 5, 6}
	for (int i : deq) 
 	 	std::cout << i << " ";
 	std::cout << std::endl;

 	std::cout << "deque.pop_back()" <<std::endl;
	deq.pop_back(); 				 // deque becomes {0, 1, 10, 2, 3, 4, 5}
	for (int i : deq) 
 	 	std::cout << i << " ";
 	std::cout << std::endl;

 	std::cout << "deque.pop_front()" <<std::endl;
	deq.pop_front(); 			     // deque becomes {1, 10, 2, 3, 4, 5}
	for (int i : deq) 
 	 	std::cout << i << " ";
 	std::cout << std::endl;


 	std::cout << "deque.erase(deq.begin() + 1)" <<std::endl;
	deq.erase(deq.begin() + 1);      // deque becomes {1, 2, 3, 4, 5}
	for (int i : deq) 
 	 	std::cout << i << " ";
 	std::cout << std::endl;

 	std::cout << "deque.erase(deq.begin() + 3, deq.end())" <<std::endl;
	deq.erase(deq.begin() + 3, deq.end()); // deque becomes {1, 2, 3}
	for (int i : deq) 
 	 	std::cout << i << " ";
 	std::cout << std::endl;

	return 0;
}