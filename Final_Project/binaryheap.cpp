#include "binaryheap.hpp"
#include <fstream>
#include <sstream>
#include <chrono>

minHeap::minHeap(int cap)
{
	currentSize = 0;
	capacity = cap;
}
minHeap::~minHeap()
{

}

void minHeap::buildMyHeap(char *filename){
	ifstream file(filename);
	string name;
	string priority;
	string treatment;
	int i = 0;
		while(!file.eof())
		{
			getline(file, name, ',');
			getline(file, priority, ',');
			getline(file, treatment, '\r');
			if(name != "Name"){
				int p = stoi(priority);
				int t = stoi(treatment);
				patientHeap *newPatientHeap = new patientHeap(name, p, t);
				push(newPatientHeap); 
			}
		}
	file.close();
	printHeap();
}

void minHeap::printHeap()
{
	int j = 1;
	int i=0;
	cout<<j<<":"<<'\t'<<heap[1]->Name<<",  "<<heap[1]->Priority<<",  "<<heap[1]->Treatment<<endl;
	j++;
	for(i = 1; i < currentSize + 1; i++){
		if(i*2 <= currentSize+1){
			cout<<j<<":"<<'\t'<<heap[i*2]->Name<<",  "<<heap[i*2]->Priority<<",  "<<heap[i*2]->Treatment<<endl;
			j++;
		}
		if(i*2+1 < currentSize+1){
			cout<<j<<":"<<'\t'<<heap[i*2+1]->Name<<",  "<<heap[i*2+1]->Priority<<",  "<<heap[i*2+1]->Treatment<<endl;
			j++;
		}
	}
}

void minHeap::push(patientHeap* k){
	if(currentSize == capacity){
		cout<<"Full"<<endl;
	}
	else{
		currentSize++;
		int i = currentSize;
		heap[i] = k; //put at first unused array index
		//heap[i/2] is the parent of the node we are looking at.
		while(i > 1 && (heap[i/2]->Priority > heap[i]->Priority || (heap[i/2]->Priority == heap[i]->Priority && heap[i/2]->Treatment > heap[i]->Treatment))){
			patientHeap *temp = heap[i];
			heap[i] = heap[i/2];
			heap[i/2] = temp;
			i = i/2;
		}
	}
}

patientHeap* minHeap::pop()
{
	if(currentSize == 0){
		cout<<"Empty"<<endl;
		return heap[0];
	}
	if(currentSize == 1){
		currentSize--;
		return heap[1];
	}
	patientHeap* popVal = heap[1];
	heap[1] = heap[currentSize]; //move element @ last index to root position
	currentSize--;
	minHeapify(1);
	return popVal;
}

void minHeap::minHeapify(int i)
{ 
	//i is an index in the heap
	int left = 2*i;
	int right = 2*i+1;
	int smallest = i;
	if(left <= currentSize && (heap[left]->Priority < heap[i]->Priority)){
		smallest = left;
	}
	if(left <= currentSize && (heap[left]->Priority == heap[i]->Priority && heap[left]->Treatment < heap[i]->Treatment)){
		smallest = left; //element at left < element at i
	}
	if(right <= currentSize && heap[right]->Priority < heap[smallest]->Priority){
		smallest = right; //gives smallest heap val left, right, parent
	}
	if(right <= currentSize && (heap[right]->Priority == heap[smallest]->Priority && heap[right]->Treatment < heap[smallest]->Treatment)){
		smallest = right; //gives smallest heap val left, right, parent
	}
	if(smallest != i){
		patientHeap *temp = heap[i];
		heap[i] = heap[smallest];
		heap[smallest] = temp;
		minHeapify(smallest);
	}
}

void minHeap::deleteHeap()
{
	cout<<"Rank"<<'\t'<<"patient,  Priority,  Treatment"<<endl;
	int startingSize = currentSize;
	for(int i = 1; i <= startingSize; i++)
	{
		patientHeap* deletedVal = pop();
		cout<<i<<":"<<'\t'<<deletedVal->Name<<",  "<<deletedVal->Priority<<",  "<<deletedVal->Treatment<<endl;
	}
}

void minHeap::timeTest(char* filename)
{
	ofstream fout("heaps.csv");
	fout<<"Build time, Delete time"<<endl;
	for(int i=0; i<500; i++)
	{
		auto t1 = std::chrono::high_resolution_clock::now();
		buildMyHeap(filename);
		auto t2 = std::chrono::high_resolution_clock::now();
		chrono::duration<double> t3 = t2-t1;
		//time_t end_time = std::chrono::high_resolution_clock::to_time_t(t2);

		auto t4 = std::chrono::high_resolution_clock::now();
		deleteHeap();
		auto t5 = std::chrono::high_resolution_clock::now();
		chrono::duration<double> t6 = t5-t4;
		//time_t end_time = std::chrono::high_resolution_clock::to_time_t(t5);
		fout<< t3.count()<<','<< t6.count() <<endl;

	}
}