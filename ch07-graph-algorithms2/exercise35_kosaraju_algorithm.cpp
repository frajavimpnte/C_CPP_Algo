// g++ -std=c++17 exercise35_kosaraju_algorithm.cpp -o exercise35_kosaraju_algorithm.exe
// exercise35_kosaraju_algorithm.exe
/*
Kosaraju's Algorithm
One of the most common and conceptually easy to grasp methods of finding the
strongly connected components of a graph is Kosaraju's algorithm. Kosaraju's algorithm
works by performing two independent sets of DFS traversals, first exploring the graph
in its original form, and then doing the same with its transpose.
*/

#include <iostream>
#include <vector>
#include <stack>

using namespace std;


void FillStack(int node, vector<bool> &visited, vector<vector<int>> &adj, stack<int> &stack)
{
	visited[node] = true;
	for(auto next : adj[node])
	{
		if(!visited[next])
		{
			FillStack(next, visited, adj, stack);
		}
	}
	stack.push(node);
}

/*
For the second half of our algorithm, we will need to define our second DFS
function, CollectConnectedComponents(),
*/
void CollectConnectedComponents(int node, vector<bool> &visited, 
		vector<vector<int>> &adj, vector<int> &component)
{
	visited[node] = true;
	component.push_back(node);
	for(auto next : adj[node])
	{
		if(!visited[next])
		{
			CollectConnectedComponents(next, visited, adj, component);
		}
	}
}


vector<vector<int>> Transpose(int V, vector<vector<int>> adj)
{
	vector<vector<int>> transpose(V);
	for(int i = 0; i < V; i++)
	{
		for(auto next : adj[i])
		{
			transpose[next].push_back(i);
		}
	}
	return transpose;
}



vector<vector<int>> Kosaraju(int V, vector<vector<int>> adj)
{
	/*
	Our first step is to declare our stack container and visited array (with every index
	initialized to false). We then iterate through each node of the graph, beginning
	our DFS traversals at every index that has not yet been marked as visited:
	*/
	vector<bool> visited(V, false);
	stack<int> stack;
	
	for(int i = 0; i < V; i++)
	{
		if(!visited[i])
		{
			FillStack(i, visited, adj, stack);
		}
	}

	/*
	In preparation for the next set of traversals, we declare the adjacency list
	transpose (initialized to the output of our Transpose() function) and reinitialize
	our visited array to false:
	*/
	vector<vector<int>> transpose = Transpose(V, adj);
	fill(visited.begin(), visited.end(), false);

	/*
	we define a vector of integer vectors called
	connectedComponents, which is where we will store the result of each traversal
	we perform on the transpose. We then iteratively pop elements from the stack
	in a while loop, once again beginning each DFS traversal exclusively from
	unvisited nodes.
	*/
	vector<vector<int>> connectedComponents;
	while(!stack.empty())
	{
		int node = stack.top();
		stack.pop();
		if(!visited[node])
		{
			vector<int> component;
			CollectConnectedComponents(node, visited, transpose, component);
			connectedComponents.push_back(component);
		}
	}
	return connectedComponents;
}

int main()
{
	int V = 9;

	vector<vector<int>> adj =
	{
		{ 1, 3 },
		{ 2, 4 },
		{ 3, 5 },
		{ 7 },
		{ 2 },
		{ 4, 6 },
		{ 7, 2 },
		{ 8 },
		{ 3 }
	};

	auto connectedComponents = Kosaraju(V, adj);
	//vector<vector<int>> connectedComponents = Kosaraju(V, adj);

	std::cout << "Graph contains " << connectedComponents.size() 
		<< " strongly connected components." << std::endl;
	
	for(auto component : connectedComponents)
	{
		cout << "\t";
		for(auto node : component)
		{
			cout << node << " ";
		}
		cout << std::endl;
	}
	
}