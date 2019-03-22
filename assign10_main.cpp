#include <iostream>
#include <fstream>
#include <sstream>
#include "Graph.h"

using namespace std;

int main(int argc, char* argv[])
{
	Graph *myGraph= new Graph();
	ifstream myFile;
	myFile.open(argv[1]);
	string empty="";

	getline(myFile,empty);
	stringstream ss(empty);
	string empty2="";
	vector <string> cityList;

	//add cities as vertex
	getline(ss,empty2,','); //get rid of dump word
	while(getline(ss,empty2,','))
	{
		myGraph->addVertex(empty2);
		cityList.push_back(empty2);
	}

	//make connections
	while(getline(myFile,empty))
	{
		stringstream ss(empty);
		string empty2="";
		string currentCity="";

		getline(ss,currentCity,','); //gets the city name
		int column=0;
		while(getline(ss,empty2,','))
		{
			if(stoi(empty2)>0)
			{
				myGraph->addEdge(currentCity, cityList[column], column);
			}
			column++;
		}
	}
	//myGraph->displayEdges();

	int option;
	bool quit = false;
	while(quit != true){
		cout<<"======Main Menu======"<<endl;
		cout<<"1. Print vertices"<<endl;
		cout<<"2. Vertex adjacent"<<endl;
		cout<<"3. Quit"<<endl; 
		cin>>option;

		if(option == 1)
		{
			myGraph->displayEdges();                 
		}

		else if(option == 2)
		{
		    int variable;
			string first;
			string second;
			cout << "Enter first city:" << endl; 
			cin>>first;
			cout << "Enter second city:" << endl; 
			cin>>second; 
 			
 			variable=myGraph->isAdjacent(first,second);
 			if(variable==0)
 			{
 			    cout<<"False"<<endl;
 			}
 			else
 			{
 			    cout<<"True"<<endl;
 			}
		}
		else if(option == 3)
		{
			quit=true; 
		}
	}
		cout << "Goodbye!" << endl;
		return 0;
}