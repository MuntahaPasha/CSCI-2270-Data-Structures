#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct Sale
{
	string name;
	string listing;
	int price;

	Sale()
	{
		//default constructor
	}

	Sale(string n, string l, int cost)
	{
		name=n;
		listing=l;
		price=cost;
	}
};

int main(int argc, char* argv[])
{
	Sale allItems[100];
	for(int i=0; i<10; i++)
	{
		//setting the values in this to empty spaces
		allItems[i].name="";
		allItems[i].listing="";
		allItems[i].price=0;
	}

	ifstream inFile;
	string line;
	inFile.open(argv[1]);
	if(inFile.is_open())
	{
		int counter=0;
		while(!inFile.eof())
		{
			getline(inFile, line);
			stringstream ss(line);
			string name;
			string listing;
			string price;

			ss >> name;
			ss >> listing;
			ss >> price;
			allItems[counter].name = name;
			allItems[counter].listing = listing;
			allItems[counter].price = stoi(price);

			counter++;
		}
		inFile.close();
	}
	else
	{
		cout<<"error"<<endl;
	}
	
	ofstream outfile;
	outfile.open(argv[3]);
	if(outfile.is_open())
	{
		for(int i=0; i<10; i++)
		{
			cout<<allItems[i].name<<" "<<allItems[i].listing<<" "<<allItems[i].price<<" "<<endl;
		}
	}
	return 0;
}