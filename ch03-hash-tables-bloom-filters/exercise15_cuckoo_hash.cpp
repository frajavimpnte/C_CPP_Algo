// g++ exercise15_cuckoo_hash.cpp -o exercise15_cuckoo_hash.exe
// exercise15_cuckoo_hash.exe

/*
we'll implement cuckoo hashing to create a hash table and insert
various elements in it. We shall also get a trace of how the operation proceeds, which
will allow us to take a look at how insertion works.
*/

#include <iostream>
#include <vector>

class hash_map
{
	std::vector<int> data1;
	std::vector<int> data2;
	int size;

	int hash1(int key) const
	{
		return key % size;
	}
	
	int hash2(int key) const
	{
		return (key / size) % size;
	}

public:
	/*
We are trying to find the key in both tables and return the relevant iterator if one
is found. We don't always need the iterator, but we'll use it in the deletion function
to make things easier. We are returning the end of the data2 table if the element is
not found. As we can see, the lookup will have a time complexity of O(1) and will be
performed pretty quickly.
	*/
	hash_map(int n) : size(n)
	{
		data1 = std::vector<int>(size, -1);
		data2 = std::vector<int>(size, -1);
	}

	std::vector<int>::iterator lookup(int key)
	{
		auto hash_value1 = hash1(key);
		if(data1[hash_value1] == key)
		{
			std::cout << "Found " << key << " in first table" << std::endl;
			return data1.begin() + hash_value1;
		}
		auto hash_value2 = hash2(key);
		if(data2[hash_value2] == key)
		{
			std::cout << "Found " << key << " in second table" << std::endl;
			return data2.begin() + hash_value2;
		}
		return data2.end();
	}
	/*
	As we can see, most of the job is done by calling the lookup function. We just need
	to validate the result and reset the value to remove it from the table.
	*/
	void erase(int key)
	{
		auto position = lookup(key);
		if(position != data2.end())
		{
			*position = -1;
			std::cout << "Removed the element " << key << std::endl;
		}
		else
		{
			std::cout << "Key " << key << " not found." << std::endl;
		}
	}

	/*
	For insertion, we shall implement the actual logic in a different function because it
	will be recursive. One more thing we want to do is avoid cycles. However, keeping
	a record of all the values that are visited can be costly. To avoid that, we will simply
	stop the function once it is called more than n times. Since the threshold of the
	recursion depth of n is dependent on our memory (or hash table size), this gives
	good performance.
	*/
	void insert(int key)
	{
		insert_impl(key, 0, 1);
	}

	void insert_impl(int key, int cnt, int table)
	{
		if(cnt >= size)
		{
			std::cout << "Cycle detected, while inserting " << key << ".Rehashing required." << std::endl;
			return;
		}
		if(table == 1)
		{
			int hash = hash1(key);
			if(data1[hash] == -1)
			{
				std::cout << "Inserted key " << key << " in table " << table << std::endl;
				data1[hash] = key;
			}
			else
			{
				int old = data1[hash];
				data1[hash] = key;
				std::cout << "Inserted key " << key << " in table " << table << " by replacing " << old << std::endl;
				insert_impl(old, cnt + 1, 2);
			}
		}
		else
		{
			int hash = hash2(key);
			if(data2[hash] == -1)
			{
				std::cout << "Inserted key " << key << " in table " << table << std::endl;
				data2[hash] = key;
			}
			else
			{
				int old = data2[hash];
				data2[hash] = key;
				std::cout << "Inserted key " << key << " in table " << table << " by replacing " << old << std::endl;
				insert_impl(old, cnt + 1, 2);
			}
		}
	}

	void print()
	{
		std::cout << "Index: ";
		for(int i = 0; i < size; i++)
			std::cout << i << '\t';
		std::cout << std::endl;

		std::cout << "Data1: ";
		for(auto i: data1)
			std::cout << i << '\t';	
		std::cout << std::endl;

		std::cout << "Data2: ";
		for(auto i: data2)
			std::cout << i << '\t';
		std::cout << std::endl;
	}
};


int main()
{
	hash_map map(7);

	map.print();
	map.insert(10);
	map.insert(20);
	map.insert(30);
	std::cout << std::endl;

	map.insert(104);
	map.insert(2);
	map.insert(70);
	map.insert(9);
	map.insert(90);
	map.insert(2);
	map.insert(7);
	std::cout << std::endl;
	
	map.print();	
	std::cout << std::endl;
	
	map.insert(14); // This will cause cycle.
}