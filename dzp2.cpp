#include "dzp2.h"
#include<iostream>
#include<set>
#include<algorithm>
using namespace std;
bool merge(int id1, int id2, vector<Graph>& separatedGraphs) {
	int index1,index2,found,foundID,notFound,notFoundID;
	bool flag=false;
	for (auto a = separatedGraphs.begin(); a < separatedGraphs.end();a++) {
		index1 = a->nodeIndex(id1);
		index2 = a->nodeIndex(id2);
		if (index1 != a->nodesSize() && index2 != a->nodesSize()) {
			break;
		}
		else 
		{
			if (index1 != a->nodesSize() || index2 != a->nodesSize())
			{
				if (index1 != a->nodesSize()) {
					found = index1;
					foundID = id1;
					notFound = index2;
					notFoundID = id2;
				}
				if (index2 != a->nodesSize()) {
					found = index2;
					foundID = id2;
					notFound = index1;
					notFoundID = id2;
				}
				for (auto b = a+1; b < separatedGraphs.end(); b++) {
					if (b->nodeIndex(notFoundID) != b->nodesSize()) {
						/*if (a->nodesSize() > b->nodesSize()) {
							auto tmp = a;
							a = b;
							b = tmp;
						}*/
						b->mergeGraphs(*a);
						separatedGraphs.erase(a);
						flag = true;
						break;
					}
				}
				if (flag)
					break;

			}
		}
	}
	return flag;
}
double minimalCost(Graph& mainGraph, vector<Graph>& separatedGraphs) {

	Graph copy(mainGraph);
	int id1, id2, count = copy.edgesSize()/2;
	double min,sum=0;
	Node* n;
	for (int i = 0; i < count; i++) {
		min = copy.findMinimalCost(id1, id2);
		copy.removeEdge(id1, id2);
		copy.outputGraph();
		if(merge(id1, id2, separatedGraphs))
		sum += min;
	}
	return sum;
}


Path::Path() :lenght(LONG_MAX),endID(-1)
{

}
Path::Path(double l, int p):lenght(l){

}
bool compareWeight(Path& a, Path& b) {
	return a.lenght < b.lenght;
}
void initializePaths(vector<Path>& paths,Graph& mainGraph,int mainID) {
	int mainIndex = mainGraph.nodeIndex(mainID);
	int begin, end,index=0;
	for (int i = 0; i < mainGraph.nodesSize(); i++,index++) {
		if (i == mainIndex) {
			index--;
			continue;
		}
		mainGraph.edgeRange(i, begin, end);
		paths[index].lenght = LONG_MAX;
		paths[index].endID = mainGraph.node(i)->ID;
		paths[index].outputPaths.push_back(make_pair(to_string(mainID)+"-"+to_string(mainGraph.node(i)->ID),0));
		//paths[index].numberOfSpecialPaths.push_back(0);
		for (int j = begin; j < end; j++) 
		{
			if (mainGraph.edge(j)->IDSinkNode == mainID) 
			{
				paths[index].lenght = mainGraph.edge(j)->cost;
				paths[index].endID = mainGraph.node(i)->ID;
				if(mainGraph.edge(j)->newPath)
					//paths[index].numberOfSpecialPaths[0]=1;
					paths[index].outputPaths[0].second= 1;
				break;
			}

		}

	}
}

void execution(vector<Path>& paths, Graph& mainGraph,int mainID) {
	
	Node* n;
	Path* p;
	int IDi,IDj;
	string outputPath;
	double lenghtI,lenghtItoJ,lenghtJ;
	int indexN, indexE;
	int count;
	for (int i = 0; i < paths.size(); i++) {
		sort(paths.begin() + i, paths.end(), compareWeight);
		p = &paths[i];
		lenghtI = p->lenght;
		for (int j = i+1; j < paths.size(); j++) {
			lenghtJ = paths[j].lenght;
			IDi = p->endID;
			IDj = paths[j].endID;
			mainGraph.edgeIndex(IDi, IDj, indexN, indexE);
			if (indexE == mainGraph.edgesSize())
				continue;
			lenghtItoJ = mainGraph.edge(indexE)->cost;
			if (lenghtI + lenghtItoJ <= lenghtJ)
			{
				count = paths[i].outputPaths.size();
				if (lenghtI + lenghtItoJ < lenghtJ) {
					paths[j].outputPaths.clear();
					//paths[j].numberOfSpecialPaths.clear();
				}
				for(int k=0;k< count;k++)
				{
					paths[j].outputPaths.push_back(make_pair(paths[i].outputPaths[k].first + "-" + to_string(IDj), paths[i].outputPaths[k].second));
					//paths[j].numberOfSpecialPaths.push_back(paths[i].numberOfSpecialPaths[k]);
					if (mainGraph.edge(indexE)->newPath)
						paths[i].outputPaths.back().second++;
						//paths[j].numberOfSpecialPaths.back()++;
				}
			}
		}
	}


}
bool compareID(Path& a, Path& b) {
	return a.endID < b.endID;
}
bool compareSpecialPath(pair<string,int>& a, pair<string,int>& b) {
	return a.second < b.second;
}
void outputPaths(vector<Path>& paths){
	sort(paths.begin(), paths.end(), compareID);
	for (int i = 0; i < paths.size(); i++) {
		sort(paths[i].outputPaths.begin(), paths[i].outputPaths.end(), compareSpecialPath);
		for (int j = 0; j < paths[i].outputPaths.size(); j++) {
			cout << "Putanja:" << paths[i].outputPaths[j].first << " ima "<< paths[i].outputPaths[j].second <<" neizgradjenih deonica\n";
		}

	}
}

void Zadatak2()
{
	try {
		int length;
		int node1, node2,mainID;
		double price;
		vector<Graph> separatedGraphs;
		Graph mainGraph;
		cout <<"Zadataka 2: \n a)\n" ;
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
		cout << "Minimalna cena izgradnje je "<<minimalCost(mainGraph,separatedGraphs)<<endl;
		mainGraph.clearEdges();
		cout << "Zadatal 2:\nb)\n";
		cout << "Unesite ID mesta u odnosu na koga se trazi najkrace putanje" << endl;
		cin >> mainID;
		cout << "Unesite ID dva mesta duzinu puta koji je izgradjen ili -1 za kraj ubacivanja" << endl;
		while (1) {
			cin >> node1;
			if (node1 == -1)
				break;
			cin >> node2 >> price;
			mainGraph.addEdge(node1, node2, price, false);
		}
		cout << "Unesite ID dva mesta duzinu puta koji nije izgradjen ili -1 za kraj ubacivanja" << endl;
		while (1) {
			cin >> node1;
			if (node1 == -1)
				break;
			cin >> node2 >> price;
			mainGraph.addEdge(node1, node2, price, true);
		}
		vector<Path> paths(mainGraph.nodesSize() - 1);
		initializePaths(paths,mainGraph,mainID);
		execution(paths,mainGraph,mainID);
		outputPaths(paths);

		int x;
		cin >>x ;
	}
	catch (exception& e) {
	}
}


