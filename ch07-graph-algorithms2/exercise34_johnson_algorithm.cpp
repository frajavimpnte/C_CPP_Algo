// g++ -std=c++17 exercise34_johnson_algorithm.cpp -o exercise34_johnson_algorithm.exe
// exercise34_johnson_algorithm.exe

/*
Johnson's Algorithm
Having compared the relative merits and disadvantages of the Bellman-Ford algorithm
and Dijkstra's algorithm, we will now discuss an algorithm that combines both of them
to retrieve the shortest paths between every pair of vertices in a graph. 

Johnson's
algorithm provides us with the advantage of being able to utilize the efficiency of
Dijkstra's algorithm while still producing correct results for graphs with negative edge
weights.

The concept behind Johnson's algorithm is quite novel – to contend with Dijkstra's
limitations when dealing with negative weights, Johnson's algorithm simply reweights
the edges in the graph so they are uniformly non-negative. This is accomplished with
the rather creative use of Bellman-Ford combined with some particularly elegant
mathematical logic.
*/

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct Edge
{
	int start;
	int end;
	int weight;
	Edge(int s, int e, int w) : start(s), end(e), weight(w) {}
};

const int UNKNOWN = INT_MAX;

vector<Edge*> edges;
int V;
int E;



// Find vertex with shortest distance from current position and
// return its index
int GetMinDistance(vector<int> &distance, vector<bool> &visited)
{
	int minDistance = UNKNOWN;
	int result;
	for(int v = 0; v < distance.size(); v++)
	{
		if(!visited[v] && distance[v] <= minDistance)
		{
			minDistance = distance[v];
			result = v;
		}
	}
	return result;
}

vector<int> Dijkstra(int V, int start, vector<Edge*> edges)
{
	vector<int> distance(V, UNKNOWN);
	vector<bool> visited(V, false);

	distance[start] = 0;

	for(int i = 0; i < V - 1; i++)
	{
		// Find index of unvisited node with shortest distance
		int curr = GetMinDistance(distance, visited);
		visited[curr] = true;
		// Iterate through edges
		for(auto edge : edges)
		{
			// Only consider neighboring nodes
			if(edge->start != curr) continue;

			// Disregard if already visited
			if(visited[edge->end]) continue;
			if(distance[curr] != UNKNOWN && distance[curr] + edge->weight < distance[edge->end])
			{
				distance[edge->end] = distance[curr] + edge->weight;
			}
		}
	}

	return distance;
}

bool HasNegativeCycle(vector<int> distance, vector<Edge*> edges)
{
	for(auto edge : edges)
	{
		int u = edge->start;
		int v = edge->end;
		int w = edge->weight;
		if(distance[u] == UNKNOWN) continue;
		if(distance[u] + w < distance[v])
		{
			return true;
		}
	}
	return false;
}


vector<int> BellmanFord(int V, vector<Edge*> edges)
{
	vector<int> distance(V + 1, UNKNOWN);
	int s = V;

	for(int i = 0; i < V; i++)
	{
		edges.push_back(new Edge(s, i, 0));
	}
	
	distance[s] = 0;

	for(int i = 1; i < V; i++)
	{
		for(auto edge : edges)
		{
			int u = edge->start;
			int v = edge->end;
			int w = edge->weight;
			if(distance[u] == UNKNOWN)
			{
				continue;
			}
			if(distance[u] + w < distance[v])
			{
				distance[v] = distance[u] + w;
			}
		}
	}

	if(HasNegativeCycle(distance, edges))
	{
		cout << "NEGATIVE CYCLE FOUND" << endl;
		return {};
	}
	
	return distance;

}

void Johnson(int V, vector<Edge*> edges)
{
	// Get distance array from modified graph
	vector<int> h = BellmanFord(V, edges);

	if(h.empty()) return;

	for(int i = 0; i < edges.size(); i++)
	{
		edges[i]->weight += (h[edges[i]->start] - h[edges[i]->end]);
	}

	// Create a matrix for storing distance values
	vector<vector<int>> shortest(V);
	
	// Retrieve shortest distances for each vertex
	for(int i = 0; i < V; i++)
	{
		shortest[i] = Dijkstra(V, i, edges);
	}

	// Reweight again in reverse to get original values
	for(int i = 0; i < V; i++)
	{
		cout << i << ":\n";
		for(int j = 0; j < V; j++)
		{
			if(shortest[i][j] != UNKNOWN)
			{
				shortest[i][j] += h[j] - h[i];
				cout << "\t" << j << ": " << shortest[i][j] << endl;
			}
		}
	}
}

int main()
{
	int V, E;
	//cin >> V >> E;
	V = 7;
	E = 9;
	int node_a[] = {0, 1, 1, 1, 2, 3, 4, 5, 6};
	int node_b[] = {1, 2, 3, 5, 4, 2, 1, 6, 0}; 
	int weight[] = {3, 5,10,-4, 2,-7,-3,-8,12};

	vector<Edge*> edges;
	for(int i = 0; i < E; i++)
	{		
		edges.push_back(new Edge(node_a[i], node_b[i], weight[i]));
	}

	Johnson(V, edges);

	return 0;
}