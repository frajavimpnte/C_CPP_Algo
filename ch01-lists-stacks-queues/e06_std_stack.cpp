
// g++ e06_std_stack.cpp -o e06_std_stack.exe
// e06_std_stack.exe

#include <iostream>
#include <deque>
#include <stack>
/*
template <class T> void Stack<T>::print() const
{
 	if (size!=0)
  	{
  		for(int i=size-1;i>-1;i--)
  		{
  			std::cout << items[i] << " ";
  		}
  		std::cout << std::endl;
	}
}

template <class T> void Stack<T>::printReversed() const
{
 	if (size!=0)
  	{
  		for(int i=0;i<size;i++)
  		{
  			std::cout << items[i] << " ";
  		}
  		std::cout << std::endl;	
	}
}
*/
int main()
{
	// using deque as stack
	std::deque<int> stk;
	stk.push_back(1); // Pushes 1 on the stack = {1}
	std::cout << "deque stk.pop_back(1)" <<std::endl;
	for (int i : stk) 
 	 	std::cout << i << " ";
 	std::cout << std::endl;

 	
	stk.push_back(2); // Pushes 2 on the stack = {1, 2}
	std::cout << "deque stk.push_back(2)" <<std::endl;
	for (int i : stk) 
 	 	std::cout << i << " ";
 	std::cout << std::endl;

	stk.pop_back(); // Pops the top element off the stack = {1}
	std::cout << "deque stk.pop_back()" <<std::endl;
	for (int i : stk) 
 	 	std::cout << i << " ";
 	std::cout << std::endl;
	
	stk.push_front(0); // This operation should not be allowed for a stack
	std::cout << "deque stk.push_front(0)" <<std::endl;
	for (int i : stk) 
 	 	std::cout << i << " ";
 	std::cout << std::endl;


	std::stack<int> stk1;
	stk1.push(1); // Pushes 1 on the stack = {1}
	std::cout << "deque stk1.push(1)" <<std::endl;
	//stk1.print();

	stk1.push(2); // Pushes 2 on the stack = {1, 2}
	std::cout << "deque stk.push(2)" <<std::endl;
	//stk1.print();

	stk1.pop(); // Pops the top element off the stack = {1}
	std::cout << "deque stk.pop()" <<std::endl;
	//stk1.print();
	
	//stk1.push_front(0); // Compilation error

	return 0;
}