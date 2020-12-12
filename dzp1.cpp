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
	
	auto it = find_if(nodes.begin(), nodes.end(), [node](Node* a) {return a->ID == node; });

	if (it == nodes.end()) {
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
	auto i = find_if(nodes.begin(), nodes.end(), [node](Node* a) {return a->ID == node; });
	if (i == nodes.end())
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
void Graph::addEdge(int node1, int node2, double cost)
{
	auto it1 = find_if(nodes.begin(), nodes.end(), [node1](Node* a) {return a->ID == node1; });
	auto it2 = find_if(nodes.begin(), nodes.end(), [node2](Node* a) {return a->ID == node2; });
	if (it1 == nodes.end()|| it1 == nodes.end())
		throw exception("Ne postoji element");

	int  first,second,begin,end, inc = 0;
	Edge* e;
	Node* n;
	bool endCheck;
	if (node1 < node2) {
		first = node1;
		second = node2;
	}
	else {
		first = node2;
		second = node1;
	}
	for (int i=0;i<nodes.size();i++)
	{
		n = nodes[i];
		n->firstEdge += inc;
		if (n->ID == first || n->ID == second)
		{
			auto startIt=edges.begin()+ n->firstEdge;
			vector<Edge*>::iterator endIt;
			if ((i + 1) != nodes.size()) 
				endIt = edges.begin() + nodes[i + 1]->firstEdge+inc;
			else
				endIt =edges.end();
			if (inc == 0) {
				auto it = find_if(startIt, endIt, [second](Edge* a) {return a->IDSinkNode == second; });
				if (it != endIt)
					throw exception("Vec postoji veza");
				else
					e = new Edge(second, cost);
			}
			else {
				auto it = find_if(startIt, endIt, [first](Edge* a) {return a->IDSinkNode == first; });
				if (it != endIt)
					throw exception("Vec postoji veza");
				else
		 			e = new Edge(first,cost);
			}
			begin = n->firstEdge;
			endCheck = (i + 1) != nodes.size();
			if (endCheck)
				end = nodes[i + 1]->firstEdge+inc;
			else
				end = edges.size();
			if (edges.empty())
				edges.push_back(e);
			else
				edges.insert(lower_bound(edges.begin() + begin, edges.begin() + end, e, cmpEdgesID), e);
			inc++;
		}
	}
}


void Graph::removeEdge(int node1, int node2)
{
	auto it1 = find_if(nodes.begin(), nodes.end(), [node1](Node* a) {return a->ID == node1; });
	auto it2 = find_if(nodes.begin(), nodes.end(), [node2](Node* a) {return a->ID == node2; });
	if (it1 == nodes.end() || it1 == nodes.end())
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
}

int Graph::nodeIndex(int id)
{
	return distance(nodes.begin(),findNode(id));
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
	nodes = move(g.nodes);
	edges = move(g.edges);
	g.nodes.clear();
	g.edges.clear();
	return *this;
}

Graph::Graph(Graph& g):nodes(g.nodes),edges(g.edges)
{
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

Edge::Edge(int IDSink, double cost): IDSinkNode(IDSink),cost(cost)
{
}
