#include <iostream>
#include <iomanip>
#include <vector>
#include "dzp1.h"
#include<string>
#include "Exception.h"
#include<algorithm>
Graph::Graph()
{
}
Graph::Graph(int id)
{
	addElement(id);
}
bool cmpNodeID(Node* a, Node* b) {
	return a->ID < b->ID;
}
void Graph::addElement(int node)
{
	int firstEdge,index;
	Node* n;
	if (nodeIndex(node) == nodes.size()) {
		n = new Node(node, 0);
		if (nodes.empty()) {
			firstEdge = 0;
			nodes.insert(lower_bound(nodes.begin(), nodes.end(), n, cmpNodeID), n);
		}
		else
		{
			index = distance(nodes.begin(),lower_bound(nodes.begin(), nodes.end(), n, cmpNodeID));
			nodes.insert(nodes.begin()+ index, n);
			if ((index + 1) != nodes.size())
				n->firstEdge = nodes[index + 1]->firstEdge;
			else
				n->firstEdge = edges.size();
		}
	}
	
	else {
		throw exception("Vec postoji element");
	}
	
}


void Graph::removeElement(int node)
{
	int begin, end;
	int removedEdges = 0;
	Node* it = nullptr;
	int debug = nodeIndex(node);
	if (nodeIndex(node) == nodes.size())
		throw exception("Ne postoji element");

	for (int index=0; index < nodes.size();index++)
	{
		it = nodes[index];
		begin = it->firstEdge-removedEdges ;
		if (it != nodes.back())
			end = nodes[index + 1]->firstEdge - removedEdges ;
		else
			end = edges.size() ;

		if (it->ID == node)
		{

			for (int k = 0; k < end-begin ; k++)
			{
				edges.erase(edges.begin() + begin);
				removedEdges++;
			}
			delete it;
			nodes.erase(index + nodes.begin());
			index--;// da bi posle ++ ostao na istom mestu
		}
		else {
			it->firstEdge -= removedEdges;
			for (int i = begin; i < end; i++)
			{	
				if (edges[i]->IDSinkNode == node)
				{
					removedEdges++;
					edges.erase(edges.begin() + i);
					break;
				}
			}
		}
	}
	
}
bool cmpEdgesID(Edge* a, Edge* b) {
	return a->IDSinkNode < b->IDSinkNode;
}
void Graph::addEdge(int node1, int node2, double cost, bool np)
{
	if (nodeIndex(node1)==nodes.size()|| nodeIndex(node2) == nodes.size())
		throw exception("Ne postoji element");

	int  first,second,indexFirst,indexE,indexSecond,begin,end, inc = 1;
	Edge* e;
	Node* n;
	if (node1 < node2) {
		first = node1;
		second = node2;
	}
	else {
		first = node2;
		second = node1;
	}
	edgeIndex(first, second, indexFirst, indexE);
	if (indexE != edges.size())
		throw exception("Vec postoji veza");
	edgeRange(indexFirst, begin, end);
	e = new Edge(second, cost, np);
	sortedEdgeInsert(begin, end, e);
	indexSecond = nodeIndex(second);
	e = new Edge(first, cost, np);
	for (int i=indexFirst+1;i<nodes.size();i++)
	{
		n = nodes[i];
		n->firstEdge += inc;

		if (i == indexSecond) {
			edgeRange(indexSecond, begin, end);
			if (end != edges.size())
				end += inc;
			sortedEdgeInsert(begin, end, e);
			inc++;
		}
	}
}


void Graph::removeEdge(int node1, int node2)
{
	if (nodeIndex(node1) == nodes.size() || nodeIndex(node2) == nodes.size())
		throw exception("Ne postoji element");

	int  begin, end, dec = 0;
	Node* it;
	for (int index = 0; index < nodes.size(); index++)
	{
		it = nodes[index];
		it->firstEdge += dec;
		if (it->ID == node1 || it->ID == node2)
		{
			begin = it->firstEdge;
			if (it != nodes.back())
				end = nodes[index + 1]->firstEdge + dec ;
			else
				end = edges.size();
			for (int i = begin; i < end ; i++) 
			{
				if (edges[i]->IDSinkNode == ((it->ID == node1) ? node2 : node1)) 
				{
					delete edges[i];
					edges.erase(edges.begin() + i);
					dec--;
					break;
				}
			}
		}
	}
	if (dec != -2)
		throw exception("Ne postoji veza");

}

void Graph::outputGraph()
{
	int begin, end, i = 0;
	Node* node;
	cout <<"Ispis:"<< endl;
	for (int index = 0; index < nodes.size(); index++)
	{
		node = nodes[index];
		cout << node->ID << "  :";
		begin = nodes[index]->firstEdge;
		if ((index + 1) != nodes.size())
			end = nodes[index + 1]->firstEdge;
		else
			end = edges.size();
		cout << "{";
			for (int i = begin; i < end; i++)
			{
				cout << setw(2) << edges[i]->IDSinkNode << ((i==end-1)? "":",");
			}
		cout <<"}"<< endl;
	}
}

vector<Node*>::iterator Graph::findNode(int id)
{
	for (auto it = nodes.begin(); it < nodes.end(); it++)
		if ((*it)->ID == id) {
			return it;
		}
	return nodes.end();
}

int Graph::nodeIndex(int id)
{
	return distance(nodes.begin(),findNode(id));
}

void Graph::edgeIndex(int id1, int id2, int& index1, int& index2)
{
	int index,begin, end;
	index = nodeIndex(id1);
	if (index == nodes.size())
		throw exception("Ne postoji element!");

	index1 = index;
	edgeRange(index, begin, end);
	for (int index = begin; index < end; index++) {
		if (edges[index]->IDSinkNode == id2)
		{
			index2 = index;
			return;
		}
	}
	index2 = edges.size();
}

void Graph::edgeRange(int nodeindex, int& index1, int& index2)
{
	index1 = nodes[nodeindex]->firstEdge;
	if (nodeindex + 1 == nodes.size())
		index2 = edges.size();
	else
		index2 = nodes[nodeindex + 1]->firstEdge;
}

void Graph::sortedEdgeInsert(int begin, int end, Edge* e)
{
	if (begin == end)
		edges.insert(edges.begin() + begin, e);
	else {
		for (int i = begin; i < end; i++) {
			if (e->IDSinkNode < edges[i]->IDSinkNode) {
				edges.insert(edges.begin() + i, e);
				return;
			}
		}
		edges.insert(edges.begin() + end, e);
	}
}

void Graph::sortedNodeInsert(Node* n)
{
	for (int i = 0; i < nodes.size(); i++) {
		if (n->ID < nodes[i]->ID) {
			nodes.insert(nodes.begin() + i, n);
			return;
		}
	}
	nodes.insert(nodes.end(), n);
}

double Graph::findMinimalCost(int& id1, int& id2)
{
	int begin, end, min=edges[0]->cost;
	id1 = nodes[0]->ID;
	id2 = edges[0]->IDSinkNode;
	for (int i = 0;i<nodes.size(); i++) {
		edgeRange(i, begin, end);
		for (int j = begin; j < end; j++) {
			if (edges[j]->cost < min) {
				id1 = nodes[i]->ID;
				id2 = edges[j]->IDSinkNode;
				min=edges[j]->cost;
			}
		}
	}
	return min;
}

void Graph::mergeGraphs(Graph& g)
{
	for (Node* n : g.nodes) {
		sortedNodeInsert(n);
	}
}

void Graph::clearEdges()
{
	for (Edge* e : edges)
		delete e;
	edges.clear();
}


Node* Graph::node(int index)
{
	return nodes[index];
}

Edge* Graph::edge(int index)
{
	return edges[index];
}

Graph::Graph(Graph&& g):nodes(g.nodes),edges(g.edges)
{
	g.nodes.clear();
	g.edges.clear();
}


Graph& Graph::operator=(Graph&& g)
{
	nodes = g.nodes;
	edges = g.edges;
	g.nodes.clear();
	g.edges.clear();
	return *this;
}

Graph::Graph(const Graph& g)
{
	int begin, end;
	Node* n;
	for (Node* it : g.nodes) {
		nodes.insert(nodes.end(), new Node(it->ID, it->firstEdge));
	}
	for (Edge* it : g.edges) {
		edges.insert(edges.end(), new Edge(it->IDSinkNode, it->cost,it->newPath));
	}
}

Graph::~Graph()
{
	if(nodes.size()>0)
	for (Node* it : nodes) {
		delete it;
		it = nullptr;
	}
	if (edges.size() > 0)
	for (Edge* it : edges) {
		delete it;
		it = nullptr;
	}
	nodes.clear();
	edges.clear();
}

bool Graph::emptyNodes()
{
	return nodes.empty();
}

bool Graph::emptyEdges()
{
	return edges.empty();
}

int Graph::nodesSize()
{
	return nodes.size();
}

int Graph::edgesSize()
{
	return edges.size();
}


void showOptions(Graph* graph)
{
	static int numberOFcalls = 0;
	if(numberOFcalls==0)cout << "Mozete izabrati neku od sledecih operacija :\n";
	if (graph)
	{
		cout << "1.Ubaciti element \n";
		if (graph->nodesSize() > 0)
		cout << "2.Izbaciti element\n";
		if (graph->nodesSize() > 1)
		cout << "3.Dodati granu izmedju dva cvora\n";
		if (graph->edgesSize()> 1)
			cout << "4.Izbaciti granu izmedju dva cvora\n";
		if (graph->nodesSize() > 0)
		cout << "5.Prikaz grafa\n";
		if (graph->nodesSize() > 0)
		cout << "6.Brisanje grafa\n";
		cout << "7.Zatavaranje aplikacije\n";

	}
	else {
		cout << "0.Napraviti graf sa nizom cvorova u jednom redu\n";
		cout << "1.Ubaciti element \n";
		cout << "7.Zatavaranje aplikacije\n";
	}
	numberOFcalls++;
}

Graph*  doOperation(int i, Graph* graph ,bool& end)
{
	try {
		int node, node2, length;
		if (i != 1 && i != 7)
		{
			if (i < 0 || i>8) 
				throw exception("Ne dozvoljenja operacija");
			else {
				if (graph) {
					if (i == 0)
						throw exception("Ne dozvoljenja operacija");
					if ((i == 4 && graph->edgesSize() < 2) || (i == 3 && graph->nodesSize() < 2)|| ((i==2||i==5||i==6) && graph->nodesSize() < 1))
						throw exception("Ne dozvoljenja operacija");
				}
				else {
					if (i >= 1 && i <= 6)
						throw exception("Ne dozvoljenja operacija");
				}
			}
		}
			
		switch (i)
		{
		case 0:
			graph = new Graph();
			cout << "Unesite broj elementa graf" << endl;
			cin >> length;
			cout << "Unesite element u jednom redu" << endl;
			for (int i = 0; i < length; i++)
			{
				cin >> node;
				graph->addElement(node);
			}
			break;
		case 1:
			cout << "Unesite element koji hocete da ubacite" << endl;
			cin >> node;
			if (!graph)
				graph = new Graph();
			graph->addElement(node);
			break;
		case 2:
			cout << "Unesite element koji hocete da izbacite" << endl;
			cin >> node;
			graph->removeElement(node);
			break;
		case 3:
			cout << "Unesite dva element izmedju kojih hocete da dodate vezu" << endl;
			cin >> node;
			cin >> node2;
			graph->addEdge(node, node2);
			break;
		case 4:
			cout << "Unesite dva element izmedju kojih hocete da izbrisete vezu" << endl;
			cin >> node;
			cin >> node2;
			graph->removeEdge(node, node2);
			break;
		case 5:
			graph->outputGraph();
			break;
		case 6:
			delete graph;
			graph = nullptr;
			break;

		case 7:
			delete graph;
			graph = nullptr;
			end = true;
			break;
		}
		return graph;
	}
	catch (exception& e) {

		delete graph;
		cout << e.what() << endl;
		exit(2);
		
	}
}

void Zadatak1()
{
	Graph* G = nullptr;
	int op;
	bool end = false;
	while (!end)
	{
		showOptions(G);
		cin >> op;
		G = doOperation(op, G,end);
		if (end)break;
		cout << "Gotova operacija,mozete izabrati jednu od sledecih:" << endl;
		

	}
}

Node::Node(int id,int start):ID(id),firstEdge(start)
{
	
}

Edge::Edge(int IDSink, double cost, bool np): IDSinkNode(IDSink),cost(cost), newPath(np)
{
}
