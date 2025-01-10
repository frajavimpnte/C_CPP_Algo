/*
In this exercise, we will write a function that takes any number of elements of any type,
which can, in turn, be converted into a common type. The function should also return a
container having all the elements converted into that common type, and it should also
be fast to traverse
*/

// g++ exercise02_fast_data_storage.cpp -o exercise02_fast_data_storage.exe
// exercise02_fast_data_storage.exe

#include <iostream>
#include <array>
#include <type_traits>

template< typename ... Args>
auto build_array(Args&&... args) -> std::array<typename std::common_type<Args...>::type, sizeof...(args)>
{
	using commonType = typename std::common_type<Args...>::type;
	return {std::forward<commonType>(args)...};
}

int main()
{
	std::cout << "data converted to float ------------------------------" <<std::endl;
	auto data = build_array(1, 0u, 'a', 3.2f, false);
	for(auto i: data)
	std::cout << i << " ";
	std::cout << std::endl;

	std::cout << "error ------------------------------" <<std::endl;
	//auto data2 = build_array(1, "Packt", 2.0);
	/*
	The exact error message should mention that
	template deduction has failed. This is because there is no single type in which we
	can convert both the string and number
	*/
}