
// g++ e01_array.cpp -o e01_array.exe
// e01_array.exe

#include <iostream>
#include <array>


void print(std::array<int, 5> arr);
void printBeginEnd(std::array<int, 5> arr);

int main() 
{

	std::cout << "array sample ---------------------------------------" << std::endl;
	std::array<int, 5> arr;        // array of int of size 10

	arr[0] = 1;                    // Sets the first element as 1
	std::cout << "First element: " << arr[0] << std::endl;
	
	std::array<int, 4> arr2 = {1, 2, 3, 4};
	
	std::cout << "Elements in second array: ";
	for(int i = 0; i < arr.size(); i++)
    	std::cout << arr2[i] << " ";

    std::cout << std::endl;


    std::cout << "array exception -------------------------------------" << std::endl;
    try
	{
		std::cout << arr2.at(3) << std::endl; // No error
		std::cout << arr2.at(4) << std::endl; // Throws exception std::out_of_range
	}
	catch (const std::out_of_range& ex)
	{
		std::cerr << ex.what() << std::endl;
	}

	std::cout << "function: pass array by value--------------------------------" << std::endl;
	print(arr);
	
	std::cout << "function: array begin and end -------------------------------" << std::endl;
	printBeginEnd(arr);


	std::cout << "array: front, back, data----- -------------------------------" << std::endl;
	std::array<int, 5> arr3 = {1, 2, 3, 4, 5};
	std::cout << arr3.front() << std::endl;       // Prints 1
	std::cout << arr3.back() << std::endl;        // Prints 5
	std::cout << *(arr3.data() + 1) << std::endl; // Prints 2

	return 0;
}

// pass array by value
void print(std::array<int, 5> arr)
{
    for(auto ele: arr)
    {
        std::cout << ele << ", ";
    }
    std::cout << std::endl;

}

// iterator begin and end
void printBeginEnd(std::array<int, 5> arr)
{
	for(auto it = arr.begin(); it != arr.end(); it++)
	{
    	auto element = (*it);
    	std::cout << element << ", ";
	}
	std::cout << std::endl;
}