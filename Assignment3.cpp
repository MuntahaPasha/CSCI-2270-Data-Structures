//Assignment 3
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

struct city
{
	string cityName;
	string message;
	city *next;
	city()
	{
		//default constructor
	}             
	city(string initName, city *initNext, string initMessage)        
	{
		cityName = initName;            
		next = initNext;            
		message = initMessage;       
	}   
}; 

city *buildNetwork()
{
	city *tenth=new city;
	tenth->cityName="Boston";
	tenth ->message="";
	tenth ->next=NULL;

	city *ninth= new city;
	ninth->cityName="New York";
	ninth->message="";
	ninth->next=tenth;

	city *eight= new city;
	eight->cityName="Washington, D.C.";
	eight->message="";
	eight->next=ninth;

	city *seventh= new city;
	seventh->cityName="Atlanta";
	seventh->message="";
	seventh->next=eight;

	city *sixth=new city;
	sixth ->cityName="Chicago";
	sixth->message="";
	sixth->next=seventh;

	city *fifth=new city;
	fifth->cityName="St. Louis";
	fifth->message="";
	fifth->next=sixth;

	city *fourth= new city;
	fourth->cityName="Dallas";
	fourth->message="";
	fourth->next=fifth;

	city*third= new city;
	third->cityName="Denver";
	third->message="";
	third->next=fourth;

	city *second=new city;
	second->cityName="Phoenix";
	second->message="";
	second->next=third;


	city *first=new city;
	first->cityName="Los Angeles";
	first->message="";
	first->next=second;
	city *head=first;
	
	return head;
	
}

void transmitMsg(city *head)
{
	ifstream inFile;
	inFile.open("messageIn.txt");
	string parse="";
	city *currentcity=head;
	city *previousCity=NULL;
	if(inFile.is_open())
	{
		while(inFile>>parse)
		{
			currentcity=head;
			previousCity=NULL;
			while(currentcity!=NULL)
			{
				//We are assigning word to current city
				currentcity->message=parse;
				if(previousCity!=NULL)
				{
					previousCity->message="";
				}
				previousCity=currentcity;
				cout<<currentcity->cityName<<" received "<<currentcity->message<<endl;
				currentcity=currentcity->next;
			}
		}
	}
	else
	{
		cout<<"Can not Open"<<endl;
	}
}

/*city *addCity(city *head, city *previous, string cityName)
{
    if(head==NULL)
    {
    	city *n=new city;
    	n->cityName=cityName;
    	n->message="";
    	n->next=NULL;
    	city *head=n;
    }
    else
    {
    	city *temp=head;
    	city *prev=NULL;
    	while(temp->next!=previous && temp!=NULL)
    	{
    		prev=temp;
    		temp=temp->next;
    	}
    	if(temp==NULL)
    	{
    		cout<<"City not found"<<endl;
    	}
    	else
    	{
    		city *tempcity=new city;
    		tempcity->cityName=cityName;
    		tempcity->next=temp;
    		if(head==temp)
    		{
    			head=tempcity;
    		}
    		else
    		{
    			prev->next=tempcity;
    		}
    	}
    }
    return head;
}*/

city *addCity(city *head, city *previous, string cityName)
{
    if(head==NULL)
    {
    	city *n=new city;
    	n->cityName=cityName;
    	n->message="";
    	n->next=NULL;
    	head=n;
    }
    else if(previous->cityName=="First")
    {
    	city *newcity=new city;
    	newcity->cityName=cityName;
    	newcity->message="";
    	newcity->next=head;
    	head=newcity;
    }
    else
    {
    	city *temp=head;
    	while(temp!=NULL)
    	{
    		if(temp==previous)
    		{
    			city *newCity=new city(cityName, temp->next, "");
    			temp->next=newCity;
    		}
    		temp=temp->next;
    	}
    }
    return head;
}


city *search(city *head, string targetValue)
{
	city *current;
	city *lastValue;
	current=head;
	if(targetValue=="") 
	{
		//If the value you're searching for is an empty string
		while(current != NULL)
		{
			lastValue=current;
			current=current->next;
		}
		return current;
	}
	else
	{
		while(current!=NULL)
		{
			if(current->cityName==targetValue)
			{
				return current;
			}
			else
			{
				current=current->next;
			}

		}
	}
		
	return NULL;
}

void printPath(city *head)
{
    city *a =head;
    cout<<"===CURRENT PATH==="<<endl;
    while(a!=NULL)
    {
        cout<<a->cityName<<" -> ";
        a = a->next;
    }
    cout<<"NULL"<<endl;
    cout<<"==================";

}


int main()
{
	int choice=0;
	bool built=false;
	while(choice !=5)
	{
		cout<<"======Main Menu======"<<endl;
		cout<<"1. Build Network"<<endl;
		cout<<"2. Print Network Path"<<endl;
		cout<<"3. Transmit Message Coast-to-Coast"<<endl;
		cout<<"4. Add City"<<endl;
		cout<<"5. Quit"<<endl;
		cin>>choice;
		city *newCity=buildNetwork();
		city head;
		cout<<"Choice"<<choice<<endl;
		cout<<"Built"<<built<<endl;
		if(choice==1)
		{
			built=true;
			printPath(newCity);
		}
		else if(choice ==2 && built==true)
		{
			printPath(newCity);
		}
		else if(choice==3 && built==true)
		{
			transmitMsg(newCity);
		}
		else if(choice==4 && built==true)
		{
			string cityNew;
			cout<<"Enter a city name: "<<endl;
			getline(cin,cityNew);
			string cityPrevious;
			cout<<"Enter a previous city name: "<<endl;
			getline(cin, cityPrevious);

			city *target=search(&head,cityPrevious);
			addCity(&head,target,cityNew);

		}
		else if(choice==5)
		{
			cout<<"Goodbye!"<<endl;
			break;
		}
	}

}