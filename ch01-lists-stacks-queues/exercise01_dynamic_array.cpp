// g++ exercise01_dynamic_array.cpp -o exercise01_dynamic_array.exe
// exercise01_dynamic_array.exe

#include <iostream>
#include <sstream>
#include <algorithm>


// crate template dynamic array
template <typename T> class dynamic_array
{
	T* data;
	size_t n;
public:
	// constructor
	dynamic_array(int n)
	{
		this->n = n;
		data = new T[n];		
	}

	dynamic_array(const dynamic_array<T>& other)
	{
		n = other.n;
		data = new T[n];
		
		for(int i = 0; i < n; i++)
			data[i] = other[i];
	}

	// accessor
	T& operator[](int index)
	{
		return data[index];
	}
	
	const T& operator[](int index) const
	{
		return data[index];
	}

	T& at(int index)
	{
		if(index < n)
		return data[index];
			throw "Index out of range";
	}

	// size
	size_t size() const
	{
		return n;
	}

	// destructor
	~dynamic_array()
	{
		delete[] data; // A destructor to prevent memory leak
	}

	// add iterator functions
	T* begin()
	{
		return data;
	}

	const T* begin() const
	{
		return data;
	}
	
	T* end()
	{
		return data + n;
	}

	const T* end() const
	{
		return data + n;
	}

	// append one array to another using + operator
	friend dynamic_array<T> operator+(const dynamic_array<T>& arr1, dynamic_array<T>& arr2)
	{
		dynamic_array<T> result(arr1.size() + arr2.size());
		std::copy(arr1.begin(), arr1.end(), result.begin());
		std::copy(arr2.begin(), arr2.end(), result.begin() + arr1.size());
		return result;
	}

	// to string
	std::string to_string(const std::string& sep = ", ")
	{
		if(n == 0)
			return "";
		
		std::ostringstream os;
		os << data[0];
		
		for(int i = 1; i < n; i++)
			os << sep << data[i];
		return os.str();
	}
};

// student struct data for test
struct student
{
	std::string name;   //name
	int standard;		//grade
};

// overload << for student structure
std::ostream& operator<<(std::ostream& os, const student& s)
{
	return (os << "[Name: " << s.name << ", Standard: " << s.standard <<"]");
}


//main --------------------------------------------------------
int main()
{
	int nStudents;
	std::cout << "Enter number of students in class 1: ";
	std::cin >> nStudents;
	dynamic_array<student> class1(nStudents);

	for(int i = 0; i < nStudents; i++)
	{
		std::cout << "Enter name and class of student " << i + 1 << ": ";
		std::string name;
		int standard;
		std::cin >> name >> standard;
		class1[i] = student{name, standard};
	}
	
	auto class2 = class1; // Deep copy
	std::cout << "Second class after initialized using first array: " <<
	class2.to_string() << std::endl;
	
	auto class3 = class1 + class2;
	// Combines both classes and creates a bigger one
	std::cout << "Combined class: ";
	std::cout << class3.to_string() << std::endl;
	
	
	// Now, let's try to access the student out of range in the array
	std::cout << "try before" << std::endl;
	try
	{
		class1[nStudents] = student{"John", 8}; // No exception, undefined behavior
		std::cout << "class1 student set out of range without exception" << std::endl;
		class1.at(nStudents) = student{"John", 8}; // Will throw exception
	}
	catch(...)
	{
		std::cout << "Exception caught" << std::endl;
	}
	std::cout << "try after" << std::endl;

	
	return 0;
}