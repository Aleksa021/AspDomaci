#include <iostream>
#include <iomanip>
#include <vector>
#include "dzp1.h"
#include<string>
#include "Exception.h"

Graph::Graph()
{
}


void Graph::addElement(int node)
{
	int firstEdge;
	if (nodes.empty()) {
		firstEdge = 0;
	}
	else
	{
		firstEdge = edges.size();
	}
	nodes.push_back(new Node(node,firstEdge));
	//da li postoji vec node sa istim imenom exc
}


void Graph::removeElement(int node)
{
	int begin,end;
	int removedEdges = 0;
	Node* it;
	vector<int> toBeRemoved;
	for (int index=0; index < nodes.size();index++)
	{
		it = nodes[index];
		begin = it->firstEdge-removedEdges ;
		if (it != nodes.back())
			end = nodes[index + 1]->firstEdge - removedEdges - begin;
		else
			end = edges.size() ;

		if (it->ID == node)
		{

			for (int k = 0; k < end-begin ; k++)
			{
				toBeRemoved.push_back(edges[k + begin]);
				edges.erase(edges.begin() + begin);
				removedEdges++;
			}
			delete it;
			nodes.erase(index + nodes.begin());
			index--;// da bi posle ++ ostao na istom mestu
		}
		else {
			it->firstEdge -= removedEdges;
			for (int i = 0; i < end - begin; i++)
			{	
				if (edges[begin+i] == node)
				{
					removedEdges++;
					edges.erase(edges.begin() + begin+ i);
				}
			}
		}
	}
	
}

void Graph::addEdge(int node1, int node2)
{
	int  begin, end, id, inc=0;
	for (Node* it : nodes)
	{
		it->firstEdge += inc;
		if (it->ID == node1 || it->ID == node2)
		{
			edges.insert(edges.begin()+ it->firstEdge, it->ID == node1 ? node2 : node1);
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
				end = nodes[index + 1]->firstEdge - dec - begin;
			else
				end = edges.size();
			for (int i = begin; i < end - begin; i++) 
			{
				if(edges[i]== ((it->ID == node1 )? node2 : node1))
					edges.erase(edges.begin() + begin + i);
			}
			dec--;
		}
	}

}

void Graph::outputGraph()
{
	int begin, end, i = 0;
	Node* node;
	for (Node* it : nodes) {
		cout << "ID cvora " << it->ID << " pocetak u vector za veze " << it->firstEdge<<'\n';
	}

	for (int it : edges)
		cout << it << setw(3);
	cout << '\n' ;
	for (int i = 0; i < edges.size(); i++)
		cout << i << setw(3);
	cout << '\n';
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


void Menu::showOptions()
{
	cout << "Mozete izabrati neku od sledecih operacija :\n";
	if (!graph.emptyNodes())
	{
		cout << "1.Ubaciti element \n";
		cout << "2.Izbaciti element\n";
		cout << "3.Dodati granu izmedju dva cvora\n";
		if (!graph.emptyEdges())
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
}

void Menu::doOperation(int i)
{
	int node,node2,length;
	switch (i)
	{
	case 0:

		cin >> length;
		for (int i=0;i< length;i++)
		{
			cin >> node;
			graph.addElement(node);

			
		}
		break;


	case 1:
		cin >> node;
		graph.addElement(node);
		// if(cin.peek()!='\n') exception
		break;
	case 2:
		cin >> node;
		graph.removeElement(node);
		// if(cin.peek()!='\n') exception
		break;
	case 3:
		cin >> node;
		cin >> node2;
		graph.addEdge(node,node2);
		// if(cin.peek()!='\n') exception
		break;
	case 4:
		cin >> node;
		cin >> node2;
		graph.removeEdge(node, node2);
		// if(cin.peek()!='\n') exception
		break;
	case 5:
		graph.outputGraph();
		// if(cin.peek()!='\n') exception
		break;
	case 6:

		break;

	case 7:
		exit(1);
		break;
	}
}

Node::Node(int id,int start,double cost):ID(id),firstEdge(start),cost(cost)
{
	
}
