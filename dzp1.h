#ifndef DZP1
#define DZP1
#include<vector>
using namespace std;
class Node {
public:
	int ID;
	int firstEdge;
private:
	Node(int id, int start);

	friend class Graph;
};
class Edge {
public:
	int IDSinkNode;
	double cost;
private:
	Edge(int IDSink, double cost = 0);
	friend class Graph;
};
class Graph
{
public:
	Graph();
	void addElement(int node);
	void removeElement(int node);
	void addEdge(int node1, int node2,double cost=0);
	void removeEdge(int node1, int node2);
	void outputGraph();
	~Graph();
	bool emptyNodes();
	bool emptyEdges();

private:

	vector<Node*> nodes;
	vector <Edge*> edges;

};
void showOptions(Graph* graph);
Graph* doOperation(int i, Graph* graph, bool& end);
void Zadatak1();
//napravi da bude singleton
/*class Menu {
public:
	Menu(const Menu&) = delete;
	Menu& operator=(const Menu&) = delete;
	static Menu& getInstance() {
		static Menu instance;
		return instance;
	}
	
	void showOptions();
	void doOperation(int i);

private:
	Menu() = default;

	Graph graph;
};*/
#endif // !DZP1

