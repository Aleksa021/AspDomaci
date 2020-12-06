#include<iostream>
#include "dzp1.h"
#include "dzp2.h"

using namespace std;


int main() {

	vector<int > firstNodes;
	string node;
	int op;
	/*cout << "Napisite niz cvorova za pravljenje grafa";
	while (cin.peek()!= '\n')
	{
		cin >> node;
		firstNodes.push_back(node);
	}*/
	Menu::getInstance().showOptions();
	while (1) 
	{
		cin >> op;
		Menu::getInstance().doOperation(op);
		cout << "Gotova operacija moze sledeca\n";
		Menu::getInstance().showOptions();

	}

}