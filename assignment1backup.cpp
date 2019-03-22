#include <iostream>
#include <fstream> //file stream
#include <sstream>

using namespace std;

struct Sale
{
	string name;
	bool listing;
	int price;

	Sale()
	{
		//default constructor
	}

	Sale(string n, bool l, int cost)
	{
		name=n;
		listing=l;
		price=cost;
	}
};

bool conversion(string item)
{
    bool x = 1;
    if(item==" wanted")
    {
        x = 1;
    }
    else
    {
		x=0;
    }
    return x;
}

int main(int argc, char* argv[])
{
	Sale allItems[100];
	ifstream inFile;
	string line;
	int counter=0;
	inFile.open(argv[1]);
	if(inFile.is_open())
	{
		
		/*string itemname;
		string itemlisting;
		int itemprice;*/
		while(getline(inFile, line))
		{

			//cout<<line<<std::endl; //to see if getline is working 
			//string stream - incldue sstream (for strings)

			stringstream ss;
			//write line string into string stream
			ss<<line;
			string item;
			getline(ss, item, ',');
			allItems[counter].name=item;
			//itemname=item;
			
			getline(ss,item,',');
			allItems[counter].listing=conversion(item);
			//itemlisting=item;

			getline(ss,item,',');
			allItems[counter].price=stoi(item);
			//itemprice=stoi(item);

			counter++;
		}
		inFile.close();
	}
	else
	{
		std::cout<<"error";
	}
	bool matchFound=true;
	int wantedRemove=-1;
	int saleRemove=-1;

	while(matchFound)
	{
		for(int i=0; i<counter; i++)
		{
			//if(allItems[i].listing==" wanted")
			{
				for(int j=0; j<counter; j++)
				{
					if(allItems[j].listing!=allItems[i].listing)
					{
						if(allItems[i].name == allItems[j].name)
						{
							if(allItems[i].price >= allItems[j].price)
							{
								wantedRemove=i;
								saleRemove=j;
								cout<<allItems[j].name<<" "<<allItems[j].price<<endl;
								matchFound=true;
								//cout<<"wanted "<<allItems[j].name<<"listing: "<< allItems[j].listing<<"Price: "<<allItems[j].price<<endl;
								//cout<<"sale "<<allItems[i].name<<"listing: "<< allItems[i].listing<<"Price: "<<allItems[i].price<<endl;
								break;
							}
							else
							{
								matchFound=false;
							}
						}
					}
				}
				if(matchFound)
				{
					break;
				}
			}
		}
		if(wantedRemove<saleRemove)
		{
			saleRemove--;
		}
		//cout<<"wanted remove: "<<allItems[wantedRemove].name<<" "<<allItems[wantedRemove].listing<<" "<<allItems[wantedRemove].price<<" "<<endl;
		for(int i=wantedRemove; i<counter; i++)
		{
			
			//cout<<"wantedRemove: "<<wantedRemove<<endl;
				allItems[i]= allItems[i+1];
		}
		allItems[counter]=Sale();
		counter--;
		//cout<<"sale remove: "<<allItems[saleRemove].name<<" "<<allItems[saleRemove].listing<<" "<<allItems[saleRemove].price<<" "<<endl;
		for(int i=saleRemove; i<counter; i++)
		{
			
			//cout<<"saleRemove: "<<saleRemove<<endl;
				allItems[i]= allItems[i+1];
		}
		allItems[counter]=Sale();
		counter--;	
	}
	
	ofstream outfile;
	outfile.open(argv[3]);
	if(outfile.is_open())
	{
		for(int i=0; i<counter; i++)
		{
			cout<<allItems[i].name<<" "<<allItems[i].listing<<" "<<allItems[i].price<<" "<<endl;
		}
	}
	return 0;	
}
