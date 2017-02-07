/*
 * http://www.geeksforgeeks.org/graph-and-its-representations/
 * http://www.geeksforgeeks.org/graph-implementation-using-stl-for-competitive-programming-set-1-dfs-of-unweighted-and-undirected/
 * http://www.geeksforgeeks.org/depth-first-traversal-for-a-graph/
 * */
#include <iostream>
#include <vector>
#include <list>
#include <memory>
#include <map>

using namespace std;

template <class someType>
class Vertice{
public:
	someType m_value;
};

template <class someType>
class Edge{
public:
	shared_ptr<Vertice<someType>> m_Vertice = nullptr;
	int m_weight;
};

template <class someType>
class Graph {
private:
	// We will represent the graph with a map of
	// Nodes and list of vertices
	map<shared_ptr<Vertice<someType>>, shared_ptr<list<Edge<someType>>>> m_mapGraph;
public:
	shared_ptr<Vertice<someType>> addVertice(someType value) {
		// Create a vertice instance
		shared_ptr<Vertice<someType>> vertInst(new Vertice<someType>{value});
		shared_ptr<list<Edge<someType>>> listEdge(new list<Edge<someType>>);
		m_mapGraph[vertInst] = listEdge;
		return vertInst;
	}

	void addEdge(const shared_ptr<Vertice<someType>> &v1, const shared_ptr<Vertice<someType>> &v2){
		// Get list reference for v1 and v2
		shared_ptr<list<Edge<someType>>> v1List = m_mapGraph[v1];
		shared_ptr<list<Edge<someType>>> v2List = m_mapGraph[v2];

		// Connect edges (Non directional)
		v1List->push_back(Edge<someType>{v2,0});
		v2List->push_back(Edge<someType>{v1,0});
	}
};

int main(){
	Graph<int> graph;

	// Add vertices
	auto v0 = graph.addVertice(0);
	auto v1 = graph.addVertice(1);
	auto v2 = graph.addVertice(2);
	auto v3 = graph.addVertice(3);
	auto v4 = graph.addVertice(4);
	auto v5 = graph.addVertice(5);

	// Add edges (7 edges)
	graph.addEdge(v0,v1);
	graph.addEdge(v0,v4);
	graph.addEdge(v1,v4);
	graph.addEdge(v1,v3);
	graph.addEdge(v1,v2);
	graph.addEdge(v2,v3);
	graph.addEdge(v3,v4);

	cout << "End" << endl;

	return 0;
}

