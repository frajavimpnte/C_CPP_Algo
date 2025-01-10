// g++ e01_hash_combine_boost.cpp -o e01_hash_combine_boost.exe
// e01_hash_combine_boost.exe

#include <boost/functional/hash.hpp>

struct Car
{
	std::string model;
	std::string brand;
	int buildYear;
};

struct CarHasher
{
	std::size_t operator()(const Car& car) const
	{
		std::size_t seed = 0;
		boost::hash_combine(seed, car.model);
		boost::hash_combine(seed, car.brand);
		return seed;
	}
};

struct CarComparator
{
	bool operator()(const Car& car1, const Car& car2) const
	{
		return (car1.model == car2.model) && (car1.brand == car2.brand);
	}
};

int main()
{
	// We can use the hasher as follows:
	std::unordered_set<Car, CarHasher, CarComparator> carSet;
	std::unordered_map<Car, std::string, CarHasher, CarComparator> carDescriptionMap;
}