#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include <iostream>
using namespace std;

struct patientHeap{
	string Name;
	int Priority;
	int Treatment;

	patientHeap(){};
	patientHeap(string name, int priority, int treatment){
			Name = name;
			Priority = priority;
			Treatment = treatment;
		}
};

class minHeap
{
	public:
		minHeap(int); // takes capacity
		~minHeap();
		void buildMyHeap(char*); //takes filename parses data and puts it in
		patientHeap* pop();//removes from heap
		void deleteHeap();
		void printHeap();
		void timeTest(char*);

	private:
		patientHeap* heap[881]; //ptr to array
		int capacity; // array capacity
		int currentSize; //how much of array is used
		void minHeapify(int);
		void push(patientHeap*); //adding into heap of ints, assume we have empty heap, add one item at a time

};

#endif