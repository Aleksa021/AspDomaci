#ifndef DZP1
#define DZP1
#include<vector>
#include<string>
using namespace std;
class Path {
public:
	Path();
	Path(double l, int p);
	double lenght;
	int endID;
	vector<pair<string, int>>outputPaths;
	//vector<string> outputPaths;
	//vector<int> numberOfSpecialPaths;
};
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
	bool newPath;
private:
	Edge(int IDSink, double cost, bool np);
	friend class Graph;
};
class Graph
{
public:
	Graph();
	Graph(int id);
	void addElement(int node);
	void removeElement(int node);
	void addEdge(int node1, int node2,double cost=0,bool np=false);
	void removeEdge(int node1, int node2);
	void outputGraph();
	vector<Node*>::iterator findNode(int id);
	int nodeIndex(int id);
	void edgeIndex(int id1, int id2,int& index1,int& index2);
	void edgeRange(int nodeindex,int& index1, int& index2);
	void sortedEdgeInsert(int begin, int end, Edge* e);
	void sortedNodeInsert(Node* n);
	double findMinimalCost(int& id1, int& id2);
	void mergeGraphs(Graph& g);
	void clearEdges();
	Node* node(int index);
	Edge* edge(int index);
	Graph( Graph&& g);
	Graph& operator= (Graph&& g);
	Graph(const Graph& g);
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

