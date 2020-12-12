#include "dzp2.h"
#include<iostream>
#include<set>
using namespace std;


double minimalCost(Graph& mainGraph, vector<Graph>& separatedGraphs) {

	Graph copy;

	Node* n;
	for (int index = 0; index < mainGraph.nodesSize(); index++) {
		n = mainGraph.node(index);
	}

	return 0;
}

void Zadatak2()
{
	try {
		int length, command;
		int node1, node2;
		double price;
		vector<Graph> separatedGraphs;
		Graph mainGraph;
		cout << "Koliko ima kljucnih mesta u gradu" << endl;
		cin >> length;
		cout << "Navadite ID kljucnih mesta u jednom redu" << endl;
		for (int i = 0; i < length; i++)
		{
			cin >> node1;
			mainGraph.addElement(node1);
			separatedGraphs.emplace_back(node1);
		}
		cout << "Unesite ID dva mesta i cenu izgradnje tog puta ili -1 za kraj ubacivanja" << endl;
		while (1) {
			cin >> node1;
			if (node1 == -1)
				break;
			cin >> node2 >> price;
			mainGraph.addEdge(node1, node2, price);
		}
		cout << "Minimalna cena izgradnje je";//minimalCost(mainGraph,separatedGraphs);
	}
	catch (exception& e) {
	}
}
