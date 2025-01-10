// g++ exercise25_fractional_knapsack_problem.cpp -o exercise25_fractional_knapsack_problem.exe
// exercise25_fractional_knapsack_problem.exe

/*
The Knapsack Problem
Suppose you are given a set of objects, O = {O1, O2, …, On}, with each having a certain
weight, Wi, and a value of Vi. You are also given a bag (or a knapsack) that can carry only
a total weight of T units. Now, say you are tasked with finding out about a set of objects
to keep in your bag so that the total weight is less than or equal to T, and the total value
of the objects is the maximum it can possibly be.
A real-world example of this problem can be understood if you imagine a traveling
trader who earns a fixed percentage profit on all their trades. They would want to carry
the maximum value of goods to maximize their profit, but their vehicle (or knapsack)
can hold only up to T units of weight. The trader knows the exact weight and value of
each object. Which set of objects should they carry so that the total value of the objects
carried for trade is the maximum possible?

The Fractional Knapsack Problem
Now, we will make a small change to the knapsack problem that was given in the
previous subsection: let's say we are now allowed to break each object into as many
parts as we need, and then we can choose what fraction of each object we want to keep
in the knapsack.
In terms of the real-world analogy, let's say that the trader in our previous analogy is
trading items such as oil, grains, and flour. The trader may take any smaller measure of
weight.
Contrary to the NP-completeness of the standard knapsack, the fractional knapsack
problem has a simple solution: order the elements according to their value per weight
ratio and 'greedily' choose as many objects as possible with the maximum ratio.
The following figure shows the optimal selection of a given set of objects when the
knapsack's capacity is set to 8 units. Notice that the chosen objects are the ones with
the highest value per weight ratio.
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <numeric>


template <typename weight_type, typename value_type, typename fractional_type>
struct Object
{
	using Wtype = weight_type;
	using Vtype = value_type;
	using Ftype = fractional_type;

	Wtype weight;
	Vtype value;
	Ftype value_per_unit_weight;

	// NOTE: The following overloads are to be used for std::sort() and I/O	
	inline bool operator< (const Object<Wtype,Vtype,Ftype>& obj) const
	{
		// An object is better or worse than another object only on the
		// basis of its value per unit weight
		return this->value_per_unit_weight < obj.value_per_unit_weight;
	}
	inline bool operator== (const Object<Wtype, Vtype, Ftype>& obj) const
	{
		// An object is equivalent to another object only if
		// its value per unit weight is equal
		return this->value_per_unit_weight == obj.value_per_unit_weight;
	}

	// Overloads the << operator so an object can be written directly to a stream
	// e.g. Can be used as std::cout << obj << std::endl;
	template <typename Wtype, typename Vtype, typename Ftype>
	friend std::ostream& operator<<(std::ostream& os, const Object<Wtype,Vtype,Ftype>& obj);
};

template <typename Wtype, typename Vtype, typename Ftype> std::ostream& operator<<(
	std::ostream& os, const Object<Wtype,Vtype,Ftype>& obj)
{
	os << "Value: "<<obj.value << "\t Weight: " << obj.weight 
			<<"\t Value/Unit Weight: " << obj.value_per_unit_weight;
		
	return os;
}

template<typename weight_type, typename value_type, typename fractional_type>
auto fill_knapsack(std::vector<Object<weight_type, value_type,fractional_type>>& objects,
	weight_type knapsack_capacity)
{
	std::vector<Object<weight_type, value_type, fractional_type>> knapsack_contents;
	knapsack_contents.reserve(objects.size());

	// Sort objects in the decreasing order
	std::sort(objects.begin(), objects.end());
	std::reverse(objects.begin(), objects.end());

	// Add the 'best' objects to the knapsack
	auto current_object = objects.begin();
	weight_type current_total_weight = 0;
	
	while (current_total_weight <= knapsack_capacity && current_object != objects.end())
	{
		knapsack_contents.push_back(*current_object);
		current_total_weight += current_object->weight;
		current_object++;
	}

	// Since the last object overflows the knapsack, adjust weight
	auto weight_of_last_obj_to_remove = current_total_weight - knapsack_capacity;
	knapsack_contents.back().weight -= weight_of_last_obj_to_remove;
	knapsack_contents.back().value -= knapsack_contents.back().value_per_unit_weight * weight_of_last_obj_to_remove;

	return knapsack_contents;
}

void test_fractional_knapsack(unsigned num_objects, unsigned knapsack_capacity)
{
	using weight_type = unsigned;
	using value_type = double;
	using fractional_type = double;

	// Initialize the Random Number Generator
	std::random_device rd;
	std::mt19937 rand(rd());
	std::uniform_int_distribution<std::mt19937::result_type> uniform_dist(1, num_objects);

	// Create a vector of objects
	std::vector<Object<weight_type, value_type, fractional_type>> objects;
	objects.reserve(num_objects);
	for (auto i = 0; i < num_objects; i++)
	{
		// Every object is initialized with a random weight and value
		auto weight = uniform_dist(rand);
		auto value = uniform_dist(rand);
		auto obj = Object<weight_type, value_type, fractional_type> {
			static_cast<weight_type>(weight),
			static_cast<value_type>(value),
			static_cast<fractional_type>(value) / weight
		};
		objects.push_back(obj);
	}

	// Display the set of objects
	std::cout << "Objects available: " << std::endl;
	for (auto& o : objects)
		std::cout << o << std::endl;
	std::cout << std::endl;

	// Arbitrarily assuming that the total knapsack capacity is 25 units
	auto solution = fill_knapsack(objects, knapsack_capacity);
	
	// Display items selected to be in the knapsack
	std::cout << "Objects selected to be in the knapsack (max capacity = "
		<< knapsack_capacity<< "):" << std::endl;
	for (auto& o : solution)
		std::cout << o << std::endl;
	std::cout << std::endl;
}

int main(int argc, char* argv[])
{
	test_fractional_knapsack(10, 25);
}