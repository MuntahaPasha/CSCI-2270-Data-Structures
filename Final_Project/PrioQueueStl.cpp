#include <iostream>
#include <queue>
#include <fstream>
#include <chrono>

using namespace std;

struct patient{
	string name;
	int priority;
	int treatment;
	patient(string n, int p, int t){
		name = n;
		priority = p;
		treatment = t;
	}
};
struct compare{
	bool operator()(const patient &a, const patient &b){
		if(a.priority == b.priority){
			return a.treatment > b.treatment;
		}
		return a.priority > b.priority;
	}
};

void buildSTL(char* filename, priority_queue<patient, vector<patient>, compare>* pq)
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
					patient *newpatient = new patient(name, p, t);
					pq->push(*newpatient);
				}
			}
			file.close();
}

void deleteEntireSTL(priority_queue<patient, vector<patient>, compare>* pq)
{
	int i = 1;
	while(!pq->empty()){
		patient p = pq->top();
		cout<<i<<":"<<'\t'<<p.name<<",  "<<p.priority<<",  "<<p.treatment<<endl;
		pq->pop();
		i++;
	}
}

void timeTest(char* filename, priority_queue<patient, vector<patient>, compare>* pq)
{
	ofstream fout("stlOutputs.csv");
	fout<<"Build time, Delete time"<<endl;
	for(int i=0; i<500; i++)
	{
		auto t1 = std::chrono::high_resolution_clock::now();
		buildSTL(filename, pq);
		auto t2 = std::chrono::high_resolution_clock::now();
		chrono::duration<double> t3 = t2-t1;
		//time_t end_time = std::chrono::high_resolution_clock::to_time_t(t2);

		auto t4 = std::chrono::high_resolution_clock::now();
		deleteEntireSTL(pq);
		auto t5 = std::chrono::high_resolution_clock::now();
		chrono::duration<double> t6 = t5-t4;
		//time_t end_time = std::chrono::high_resolution_clock::to_time_t(t5);
		fout<< t3.count()<<','<< t6.count() <<endl;

	}
}

int main(int argc, char *argv[]){
	
	priority_queue<patient, vector<patient>, compare> pq;
	bool quit = false;

	while(!quit){
		cout<<"======Main Menu======"<<endl;
		cout<<"1. Build STL Queue"<<endl;
		cout<<"2. Dequeue Patient"<<endl;
		cout<<"3. Dequeue Entire STL (Print All)"<<endl;
		cout<<"4. Time Test"<<endl;
		cout<<"5. Quit"<<endl;
		int option;
		cin>>option;
		if(option == 1)
		{
			buildSTL(argv[1], &pq);
		}
		if(option == 2){
			patient p = pq.top();
			cout<<p.name<<" "<<p.priority<<", "<<p.treatment<<endl;
			pq.pop();
		}
		if(option == 3)
		{
			deleteEntireSTL(&pq);
		}
		if(option == 4)
		{
			timeTest(argv[1], &pq);
		}
		if(option == 5){
			quit = true;
		}
	}
	return 0;
}
