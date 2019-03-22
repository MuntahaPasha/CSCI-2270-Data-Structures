#include "linkedlist.hpp"
#include "binaryheap.hpp"
#include <iostream>
#include <string>
#include <time.h>
#include <vector>

int main(int argc, char *argv[])
{
	bool quit = false;
	deliveryQueue ll;
	int capacity=881;
	minHeap build(capacity);
	while(!quit)
	{
		cout<<"======Main Menu======"<<endl;
		cout<<"1. Build LL priority queue"<<endl;
		cout<<"2. Build heap priority queue"<<endl;
		cout<<"3. Dequeue LL"<<endl;
		cout<<"4. Dequeue heap"<<endl;
		cout<<"5. Dequeue all LL"<<endl;
		cout<<"6. Dequeue all heap"<<endl;
		cout<<"7. Heap Time Test"<<endl;
		cout<<"8. Linked List time Test"<<endl;
		cout<<"9. Quit"<<endl;
		int option;
		cin>>option;
		if(option == 1)
		{
			//clock_t t1, t2;
		    //t1 = clock();
			ll.buildQueue(argv[1]);
		    //t2 = clock();
		    //cout << " | Run time: " << ((float)t2-(float)t1) / CLOCKS_PER_SEC << " s" << endl;
		}
		else if(option == 2)
		{
			build.buildMyHeap(argv[1]);
		}
		else if(option == 3)
		{
			ll.dequeuePatient();
			ll.printQueue();
		}
		else if(option == 4)
		{
			build.pop();
		}
		else if(option == 5){
			ll.deletePriorityQueue();
			ll.printQueue();
		}
		else if(option == 6)
		{
			build.deleteHeap();
		}
		else if(option == 7)
		{
			build.timeTest(argv[1]);
		}
		else if(option == 8)
		{
			ll.timeTest(argv[1]);
		}
		else{
			quit = true;
		}


	}
	return 0;
}