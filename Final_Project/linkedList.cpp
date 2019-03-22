#include "linkedlist.hpp"
#include <fstream>
#include <sstream>
#include <chrono>

deliveryQueue::deliveryQueue()
{
	head=NULL;
	tail=NULL;
}
deliveryQueue::~deliveryQueue()
{
	deletePriorityQueue();
	head = NULL;
	tail = NULL;
}

void deliveryQueue::addPatient(string namePat, int prior, int treat){
	static int n=0;
	n++;
	patient* tracker;
	tracker = head;
	patient* newPatient = new patient(namePat, prior, treat);
	if(head == NULL){
		head = newPatient;
		return;
	}
	while(tracker != NULL){
		if((newPatient->Priority < tracker->Priority) || ((newPatient->Priority == tracker->Priority) && (newPatient->Treatement < tracker->Treatement))){
			newPatient->next = tracker;
			newPatient->prev = tracker->prev;
			if(tracker != head){
				tracker->prev->next = newPatient;
				tracker->prev = newPatient;
			}
			else{
				tracker->prev = newPatient;
				head = newPatient;
			}
			return;
		}
		else if((newPatient->Priority > tracker->Priority) && tracker->next==NULL)
		{
			tracker->next = newPatient;
			newPatient->prev = tracker;
			tail = newPatient;
			return;
		}
		tracker = tracker->next;
	}
}
void deliveryQueue::buildQueue(char* filename)
{
	ifstream file(filename); 
	
	string name;
	string priority;
	string treatment;
	while(!file.eof()){
		getline(file, name, ',');
		getline(file, priority, ',');
		getline(file, treatment, '\r');
		if(name != "Name"){
			int p = stoi(priority);
			int t = stoi(treatment);
			addPatient(name, p, t);
		}
	}
	file.close();
	printQueue();

}

void deliveryQueue::printQueue()
{
	patient *temp=head;
	int i=1;
	cout<<"Rank"<<'\t'<<"patient,"<<"  "<<"Priority,"<<"  "<<"Treatment"<<endl;
	while(temp!= NULL)
	{
		cout<<i<<":"<<'\t'<<temp->Name<<",  "<<temp->Priority<<",  "<<temp->Treatement<<endl;
		temp = temp->next;
		i++;
	}
}

void deliveryQueue::dequeuePatient()
{
	patient *temp = head;
	head = temp->next;
	head->prev = NULL;
	delete temp;
}

void deliveryQueue::deletePriorityQueue()
{
	patient *current = head;
	patient *nextNode = head;
	while(current != NULL){
		nextNode = current->next;
		delete current;
		current = nextNode;
	}
	head = NULL;
	tail = NULL;
}

void deliveryQueue::timeTest(char* filename)
{
	ofstream fout("linkedListBuild.csv");
	fout<<"Build time, Delete time"<<endl;
	for(int i=0; i<500; i++)
	{
		auto t1 = std::chrono::high_resolution_clock::now();
		buildQueue(filename);
		auto t2 = std::chrono::high_resolution_clock::now();
		chrono::duration<double> t3 = t2-t1;
		//time_t end_time = std::chrono::high_resolution_clock::to_time_t(t2);

		auto t4 = std::chrono::high_resolution_clock::now();
		deletePriorityQueue();
		auto t5 = std::chrono::high_resolution_clock::now();
		chrono::duration<double> t6 = t5-t4;
		//time_t end_time = std::chrono::high_resolution_clock::to_time_t(t5);
		fout<< t3.count()<<','<< t6.count() <<endl;

	}
}