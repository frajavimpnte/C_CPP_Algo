// g++ e02_vector.cpp -o e02_vector.exe
// e02_vector.exe
#include <iostream>
#include <bits/stdc++.h>
#include <vector>


int main() 
{	
	std::cout << " Declares vector of size 0--------------------------------" << std::endl;
	std::vector<int> vec1;
	// Declares vector of size 0
	for (int i = 0; i < vec1.size(); i++)
  		std::cout << vec1[i] << " ";
  	std::cout << std::endl;

  	std::cout << " Declares vector of size 5 with provided elements---------" << std::endl;
	std::vector<int> vec2 = {1, 2, 3, 4, 5};
	// Declares vector of size 5 with provided elements
	for (int i : vec2) 
 	 	std::cout << i << " ";
 	std::cout << std::endl;

 	std::cout << " Declares vector of size 5 with provided elements---------" << std::endl;
	std::vector<int> vec3(10);
	// Declares vector of size 10
	for (int i : vec3) 
 	 	std::cout << i << " ";
 	std::cout << std::endl;


 	std::cout << " Declares vector of size 10 with each element's value = 5-" << std::endl;
	std::vector<int> vec4(10, 5);
	// Declares vector of size 10 with each element's value = 5
	for (int i : vec4) 
 	 	std::cout << i << " ";
 	std::cout << std::endl;


	std::cout << " Declares vector of size 5 with provided elements---------" << std::endl;
	// insert
	std::vector<int> vec5 = {1, 2, 3, 4, 5};
	vec5.insert(vec5.begin(), 0);
	for (int i : vec5) 
 	 	std::cout << i << " ";
 	std::cout << std::endl;


	std::cout << " push back ------------------------------------------------" << std::endl;
	//push back
	std::vector<int> vec6; 		// Empty vector {}
	vec6.push_back(1); 			// Vector has one element {1}
	vec6.push_back(2);			// Vector has 2 elements {1, 2}
	vec6.insert(vec6.begin(), 0);	// Vector has 3 elements {0, 1, 2}
	vec6.insert(find(vec6.begin(), vec6.end(), 1), 4);	// Vector has 4 elements {0, 4, 1, 2}
	for (int i : vec6) 
 	 	std::cout << i << " ";
 	std::cout << std::endl;


	// use emplace_back and emplace, for better performance

	// erase
	std::cout << " erase--------------------------------------------------" << std::endl;
	std::vector<int> vec7 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};	
	vec7.pop_back();									// Vector has now 9 elements {0, 1, 2, 3, 4, 5, 6, 7, 8}
	vec7.erase(vec7.begin());							// vector has now 7 elements {1, 2, 3, 4, 5, 6, 7, 8}
	vec7.erase(vec7.begin() + 1, vec7.begin() + 4);	// Now, vector has 4 elements {1, 5, 6, 7, 8}
	for (int i : vec7) 
 	 	std::cout << i << " ";
 	std::cout << std::endl;


	// clear, reserve(capacity), shrink_to_fit()

	// Allocators for std::vector   allocate, deallocate, construct, destroy

	return 0;
}