#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
using namespace std;

struct patient{
	string Name;
	int Priority;
	int Treatement;
	patient *next;
	patient *prev;
	patient(){};
	patient(string name, int pri, int treat){
		Name = name;
		Priority = pri;
		Treatement = treat;
		next = NULL;
		prev = NULL;
	}
};

class deliveryQueue{
	public:
		deliveryQueue(); //done
		~deliveryQueue(); //done deletes everything in ll
		void dequeuePatient(); //finds by name and deletes node
		void deletePriorityQueue(); //deletes all nodes in LL
		void buildQueue(char*); //main needs to do this first, reads in file and puts info into addPatinet
		void printQueue();
		void timeTest(char*);


	private:
		void addPatient(string, int, int); //done
		patient *head;
		patient *tail;
};

#endif