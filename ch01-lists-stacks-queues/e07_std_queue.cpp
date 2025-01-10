// g++ e07_std_queue.cpp -o e07_std_queue.exe
// e07_std_queue.exe

/*
Just like std::stack, we have another container adapter to deal with the frequent
scenario of FIFO (First In First Out) in many applications, and this structure is provided
by an adaptor called std::queue.

std::priority_queue
Priority queue provides a very useful structure called heap via its interface. A heap data
structure is known for fast access to the minimum (or maximum) element from the
container. Getting the min/max element is an operation with a time complexity of O(1).
Insertion has O(log n) time complexity, while deletion can only be performed for the
min/max element, which always stays on the top.

Benchmarking
https://quick-bench.com/
*/

#include <iostream>
#include <queue>

void print_queue(std::queue<int> q)
{
  while (!q.empty())
  {
    std::cout << q.front() << " ";
    q.pop();
  }
  std::cout << std::endl;
}

int main()
{
	std::queue<int> q;

	std::cout << "push(1)" << std::endl;
	q.push(1); // queue becomes {1}
	print_queue(q);

	std::cout << "push(2)" << std::endl;
	q.push(2); // queue becomes {1, 2}
	print_queue(q);

	std::cout << "push(3)" << std::endl;
	q.push(3); // queue becomes {1, 2, 3}
	print_queue(q);


	std::cout << "pop()" << std::endl;
	q.pop(); // queue becomes {2, 3}
	print_queue(q);

	std::cout << "push(4)" << std::endl;
	q.push(4); // queue becomes {2, 3, 4}
	print_queue(q);

	return 0;
}