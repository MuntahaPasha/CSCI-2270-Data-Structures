#include <iostream>
#include <fstream>
#include <sstream>
#include "Graph.hpp"

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
				myGraph->addEdge(currentCity, cityList[column], stoi(empty2)); 
				//empty 2 holds our weights so we convert it to an integer and pass it in
			}
			column++;
		}
	}

	string option;
	bool quit = false;
	while(quit != true){
		cout<<"======Main Menu======"<<endl;
		cout<<"1. Print vertices"<<endl;
		cout<<"2. Find districts"<<endl;
		cout<<"3. Find shortest path"<<endl; 
		cout<<"4. Find shortest weighted path"<<endl;
		cout<<"5. Quit"<<endl;
		getline(cin, option);

		if(stoi(option) == 1)
		{
			myGraph->displayEdges();                
		}

		else if(stoi(option) == 2)
		{
 			myGraph->assignDistricts();
		}
		else if(stoi(option) == 3)
		{
			string first;
			string second;
			cout << "Enter a starting city:" << endl; 
			getline(cin,first);
			cout << "Enter an ending city:" << endl; 
			getline(cin,second); 
			myGraph->shortestPath(first, second);
		}
		else if(stoi(option) == 4)
		{
			string first;
			string second;
			cout << "Enter a starting city:" << endl; 
			getline(cin,first);
			cout << "Enter an ending city:" << endl; 
			getline(cin,second); 
			myGraph->shortestWeightedPath(first, second);
		}
		else if(stoi(option) == 5)
		{
			quit=true; 
		}
	}
		cout << "Goodbye!" << endl;
		return 0;
}