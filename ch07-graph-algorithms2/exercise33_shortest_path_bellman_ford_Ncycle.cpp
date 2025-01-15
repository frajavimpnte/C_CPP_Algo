// g++ -std=c++17 exercise33_shortest_path_bellman_ford_Ncycle.cpp -o exercise33_shortest_path_bellman_ford_Ncycle.exe
// exercise33_shortest_path_bellman_ford_Ncycle.exe

/*
Implementing the Bellman-Ford Algorithm (Part I), to deal with a graph with negative weight cycles.
*/

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Edge
{
	int start; 	// The starting vertex
	int end; 	// The destination vertex
	int weight; // The edge weight

	// Constructor
	Edge(int s, int e, int w) : start(s), end(e), weight(w) {}
};

const int UNKNOWN = INT_MAX;
vector<Edge*> edges; // Collection of edge pointers
int V; // Total number of vertices in the graph
int E; // Total number of edges in the graph
int start;

void BellmanFord(int start);
void initSample();
void initSampleNcycle();

int main()
{
	/*
	cin >> V >> E;
	for(int i = 0; i < E; i++)
	{
		int node_a, node_b, weight;
		cin >> node_a >> node_b >> weight;
		
		// Add a new edge using the defined constructor
		edges.push_back(new Edge(node_a, node_b, weight));
	}

	// Choose a starting node
	int start;
	cin >> start;
	*/

	//initSample();
	initSampleNcycle();

	// Run the Bellman-Ford algorithm on the graph for
	// the chosen starting vertex
	BellmanFord(start);
	
	return 0;
}

void initSampleNcycle() {

	V = 6;
	E = 8;

	int node_a[] = {0, 1, 2, 2, 3, 2, 4, 5};
	int node_b[] = {1, 3, 1, 5, 2, 4, 5, 1};
	int weight[] = {3,-8, 3, 5, 3, 2,-1, 8};

	for (int i = 0; i < E; i++) {
		edges.push_back(new Edge(node_a[i], node_b[i], weight[i]));
	}

	start = 0;
}


void initSample() {

	V = 5;
	E = 5;

	int node_a[] = {0, 1, 1, 3, 2};
	int node_b[] = {1, 2, 3, 2, 4};
	int weight[] = {3, 5, 10, -7, 2};

	for (int i = 0; i < E; i++) {
		edges.push_back(new Edge(node_a[i], node_b[i], weight[i]));
	}

	start = 0;
}

void BellmanFord(int start)
{
	vector<int> distance(V, UNKNOWN);
	distance[start] = 0;
	// Perform V - 1 iterations
	for(int i = 0; i < V; i++)
	{
		// Iterate over entire set of edges
		for(auto edge : edges)
		{
			int u = edge->start;
			int v = edge->end;
			int w = edge->weight;
		
			// Skip nodes which have not yet been considered
			if(distance[u] == UNKNOWN)
			{
				continue;
			}
		
			// If the current distance value for the destination
			// node is greater than the sum of the source node's
			// distance and the edge's weight, change its distance
			// to the lesser value.
			if(distance[u] + w < distance[v])
			{
				distance[v] = distance[u] + w;
			}
		}
	}

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
			cout << "NEGATIVE CYCLE FOUND" << endl;
			return;
		}
	}

	cout << "DISTANCE FROM VERTEX " << start << ":\n";
	for(int i = 0; i < V; i++)
	{
		cout << "\t" << i << ": ";
		if(distance[i] == UNKNOWN)
		{
			cout << "Unvisited" << endl;
			continue;
		}
		cout << distance[i] << endl;
	}
}