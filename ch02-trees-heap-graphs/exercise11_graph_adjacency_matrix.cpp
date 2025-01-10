// g++ exercise11_graph_adjacency_matrix.cpp -o exercise11_graph_adjacency_matrix.exe
// exercise11_graph_adjacency_matrix.exe

/*
Here is one of the simplest ways to understand a graph – consider a set of nodes, where
any node can connect to any other node among the set directly. This means that we can
represent this using a 2D array that's N × N in size for a graph with N nodes. The value
in each cell will indicate the weight of the edge between the corresponding nodes based
on the indices of the cell. So, data[1][2] will indicate the weight of the edge between
node 1 and node 2. This method is known as an adjacency matrix. We can indicate the
absence of an edge using a weight of -1.
*/

#include <iostream>
#include <vector>

enum class city: int
{
	LONDON,
	MOSCOW,
	ISTANBUL,
	DUBAI,
	MUMBAI,
	SEATTLE,
	SINGAPORE
};

std::ostream& operator<<(std::ostream& os, const city c)
{
	switch(c)
	{
		case city::LONDON:
			os << "LONDON";
			return os;
		case city::MOSCOW:
			os << "MOSCOW";
			return os;
		case city::ISTANBUL:
			os << "ISTANBUL";
			return os;
		case city::DUBAI:
			os << "DUBAI";
			return os;
		case city::MUMBAI:
			os << "MUMBAI";
			return os;
		case city::SEATTLE:
			os << "SEATTLE";
			return os;
		case city::SINGAPORE:
			os << "SINGAPORE";
			return os;
		default:
			return os;
	}
}


struct graph
{
	std::vector<std::vector<int>> data;

	graph(int n)
	{
		data.reserve(n);
		std::vector<int> row(n);
		std::fill(row.begin(), row.end(), -1);
		for(int i = 0; i < n; i++)
		{
			data.push_back(row);
		}
	}

	void addEdge(const city c1, const city c2, int dis)
	{
		std::cout << "ADD: " << c1 << "-" << c2 << "=" << dis << std::endl;
		auto n1 = static_cast<int>(c1);
		auto n2 = static_cast<int>(c2);
		data[n1][n2] = dis;
		data[n2][n1] = dis;
	}

	void removeEdge(const city c1, const city c2)
	{
		std::cout << "REMOVE: " << c1 << "-" << c2 << std::endl;
		auto n1 = static_cast<int>(c1);
		auto n2 = static_cast<int>(c2);
		data[n1][n2] = -1;
		data[n2][n1] = -1;
	}
};


int main()
{
	graph g(7);
	g.addEdge(city::LONDON, city::MOSCOW, 900);
	g.addEdge(city::LONDON, city::ISTANBUL, 500);
	g.addEdge(city::LONDON, city::DUBAI, 1000);
	g.addEdge(city::ISTANBUL, city::MOSCOW, 1000);
	g.addEdge(city::ISTANBUL, city::DUBAI, 500);
	g.addEdge(city::DUBAI, city::MUMBAI, 200);
	g.addEdge(city::ISTANBUL, city::SEATTLE, 1500);
	g.addEdge(city::DUBAI, city::SINGAPORE, 500);
	g.addEdge(city::MOSCOW, city::SEATTLE, 1000);
	g.addEdge(city::MUMBAI, city::SINGAPORE, 300);
	g.addEdge(city::SEATTLE, city::SINGAPORE, 700);
	g.addEdge(city::SEATTLE, city::LONDON, 1800);
	g.removeEdge(city::SEATTLE, city::LONDON);
	return 0;
}