#ifndef DZP1
#define DZP1
#include<vector>
using namespace std;
class Node {
public:
	int ID;
	int firstEdge;
	double cost;
private:
	Node(int id, int start,double cost=0);

	friend class Graph;
};
class Graph
{
public:
	Graph();
	void addElement(int node);
	void removeElement(int node);
	void addEdge(int node1, int node2);
	void removeEdge(int node1, int node2);
	void outputGraph();
	~Graph();
	bool emptyNodes();
	bool emptyEdges();
private:

	vector<Node*> nodes;
	vector <int> edges;

};
//napravi da bude singleton
class Menu {
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
};
#endif // !DZP1

