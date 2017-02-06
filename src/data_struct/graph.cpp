#include <iostream>
#include <vector>
#include <iterator>
#include <list>
#include <memory>

using namespace std;

template <class someType>
class Vertice{
public:
	someType m_value;
};

template <class someType>
class Edge{
public:
	unique_ptr<Vertice<someType>> m_Vertice = nullptr;
	int m_weight;
};

template <class someType>
class Graph {
private:
	list<std::unique_ptr<Vertice<someType>>> m_verticeList;
public:
	void addVertice(int value) {
		std::unique_ptr<Vertice<someType>> vertInst(new Vertice<someType>{value});
		m_verticeList.push_back(move(vertInst));
	}

	void addEdge(const someType &v1, const someType &v2){
		// Non directional graph
		//m_verticeList[v1].push_back(v2);
		//m_verticeList[v2].push_back(v1);
	}
};

int main(){
	Graph<int> graph;
	graph.addVertice(0);
	graph.addVertice(1);
	graph.addVertice(2);
	graph.addVertice(3);
	graph.addVertice(4);
	graph.addVertice(5);

	return 0;
}

