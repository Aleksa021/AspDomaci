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
	Edge(int IDSink, double cost);
	friend class Graph;
};
class Graph
{
public:
	Graph();
	Graph(int id);
	void addElement(int node);
	void removeElement(int node);
	void addEdge(int node1, int node2,double cost=0);
	void removeEdge(int node1, int node2);
	void outputGraph();
	vector<Node*>::iterator findNode(int id);
	int nodeIndex(int id);
	Node* node(int index);
	Edge* edge(int index);
	Graph( Graph&& g);
	Graph& operator= (Graph&& g);
	Graph(Graph& g);
	~Graph();
	bool emptyNodes();
	bool emptyEdges();
	int nodesSize();
	int edgesSize();

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

