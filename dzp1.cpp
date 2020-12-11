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
bool cmpNodeID(Node* a, Node* b) {
	return a->ID < b->ID;
}

void Graph::addElement(int node)
{
	int firstEdge;
	Node* n;
	if (nodes.empty()) {
		firstEdge = 0;
	}
	else
	{
		firstEdge = edges.size();
	}
	n = new Node(node, firstEdge);
	nodes.insert(lower_bound(nodes.begin(), nodes.end(), n, cmpNodeID),n);
	//da li postoji vec node sa istim imenom exc
}


void Graph::removeElement(int node)
{
	int begin,end,index;
	int removedEdges = 0;
	Node* it=nullptr;

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

	int  first,second,begin,end,id, inc = 0;
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
			if (inc == 0)
				e = new Edge(second);
			else
				e = new Edge(first);
			begin = n->firstEdge;
			endCheck = (i + 1) != nodes.size();
			if (endCheck)
				end = nodes[i + 1]->firstEdge+inc;
			else
				end = edges.size();
			if (edges.empty())
				edges.push_back(e);
			else
			edges.insert(lower_bound(edges.begin()+begin,edges.begin()+end,e, cmpEdgesID), e);


			inc++;
		}
	}
}


void Graph::removeEdge(int node1, int node2)
{
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
					edges.erase(edges.begin() + i);
					break;
				}
			}
			dec--;
		}
	}

}

void Graph::outputGraph()
{
	int begin, end, i = 0;
	Node* node;
	for (int index = 0; index < nodes.size();index++) {
		node = nodes[index];
		cout << "ID cvora-" << node->ID << "ID njegovih susednih cvorova-";
		begin = nodes[index]->firstEdge;
		if ((index + 1) != nodes.size()) {
			end = nodes[index + 1]->firstEdge;
		}
		else
			end = edges.size();
		for (int i = begin; i < end; i++)
		{
			cout << edges[i]->IDSinkNode<<setw(3);
		}
		cout << endl;
	}
}

Graph::~Graph()
{
	for (Node* it : nodes) {
		delete it;
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


void showOptions(Graph* graph)
{
	static int numberOFcalls = 0;
	if(numberOFcalls==0)cout << "Mozete izabrati neku od sledecih operacija :\n";
	if (graph)
	{
		cout << "1.Ubaciti element \n";
		cout << "2.Izbaciti element\n";
		cout << "3.Dodati granu izmedju dva cvora\n";
		if (!graph->emptyEdges())
			cout << "4.Izbaciti granu izmedju dva cvora\n";
		cout << "5.Prikaz grafa\n";
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
	int node,node2,length;
	switch (i)
	{
	case 0:
		graph = new Graph();
		cout << "Unesite broj elementa graf" << endl;
		cin >> length;
		cout << "Unesite element u jednom redu" << endl;
		for (int i=0;i< length;i++)
		{
			cin >> node;
			graph->addElement(node);
		}
		break;
	case 1:
		cout << "Unesite element koji hocete da ubacite" << endl;
		cin >> node;
		graph->addElement(node);
		// if(cin.peek()!='\n') exception
		break;
	case 2:
		cout << "Unesite element koji hocete da izbacite" << endl;
		cin >> node;
		graph->removeElement(node);
		// if(cin.peek()!='\n') exception
		break;
	case 3:
		cout << "Unesite dva element izmedju kojih hocete da dodate vezu" << endl;
		cin >> node;
		cin >> node2;
		graph->addEdge(node,node2);
		// if(cin.peek()!='\n') exception
		break;
	case 4:
		cout << "Unesite dva element izmedju kojih hocete da izbrisete vezu" << endl;
		cin >> node;
		cin >> node2;
		graph->removeEdge(node, node2);
		// if(cin.peek()!='\n') exception
		break;
	case 5:
		graph->outputGraph();
		// if(cin.peek()!='\n') exception
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
