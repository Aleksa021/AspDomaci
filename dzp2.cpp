#include "dzp2.h"
#include<iostream>
#include<set>
using namespace std;


void initialize()
{
	int length;
	int node1, node2;
	double price;
	int size1,size2;
	Graph* graph = nullptr;
	set<int> nodeSet;
	cout << "Koliko ima kljucnih mesta u gradu" << endl;
	cin >> length;
	graph = new Graph();
	cout << "Navadite kljucna mesta u gradu u formatu :cvor1 cvor2 cena" << endl;
	for (int i = 0; i < length; i++)
	{
		//proveri da li vec postoji
		cin >> node1>>node2 >>price;
		size1 = nodeSet.size();
		nodeSet.insert(node1);
		if (size1 != nodeSet.size()) {
			graph->addElement(node1);
		}
		size2 = nodeSet.size();
		nodeSet.insert(node2);
		if ((size2) != nodeSet.size())
			graph->addElement(node2);
		//if (size1==size2)excp
		graph->addEdge(node1, node2,price);

	}
}

void Zadatak2()
{
	initialize();
}
