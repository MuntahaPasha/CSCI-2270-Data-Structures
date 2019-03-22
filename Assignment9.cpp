#include "Graph.hpp"
#include <vector>
#include <iostream>
#include <stack>
#include <limits>
#include <queue>

using namespace std;

Graph::Graph(){
    for(int i = 0; i < (int)vertices.size(); i++){
        vertices[i].districtID = 11;
    }
}
Graph::~Graph(){

}
void Graph::addEdge(string v1, string v2, int weight){
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == v1){
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j].name == v2 && i != j){
                    adjVertex av;
                    av.v = &vertices[j];
                    av.weight = weight;
                    vertices[i].adj.push_back(av);
                }
            }
        }
    }
}
void Graph::addVertex(string n){
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == n){
            found = true;
            cout<<vertices[i].name<<" found."<<endl;
        }
    }
    if(found == false){
        vertex v;
        v.name = n;
        v.districtID = -1;
        vertices.push_back(v);

    }
}
void Graph::displayEdges(){
    for(int i = 0; i < (int)vertices.size(); i++){
        cout<< vertices[i].districtID <<":"<<vertices[i].name<<"-->"; 
        for(int j = 0; j < (int)vertices[i].adj.size(); j++){
            cout<<vertices[i].adj[j].v->name;
            if (j != vertices[i].adj.size()-1) 
                cout<<"***"; 
        }
        cout<<endl;
    }
}
vertex* Graph::findVertex(string value) {
    int i=0;
    while (i<vertices.size()) {
        if (vertices[i].name == value) {
            return &vertices[i];
        }
        i++;
    }
    return nullptr;
}
void Graph::assignDistricts(){
    int tempDistNumb = 1;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].visited == false){
            DFSLabel(vertices[i].name, tempDistNumb);
            tempDistNumb++;
        }
    }
}
void Graph::DFSLabel(string startingCity, int distID){ 
    stack<vertex*> vertexStack;

    vertex* currentVertex = findVertex(startingCity); //Find first city
    vertexStack.push(currentVertex); //is like enqueue and pop is like dequeue

    while(vertexStack.size() != 0){
        vertex* curv = vertexStack.top(); //stack doesn't have a front so top
        vertexStack.pop();
        if (!curv->visited) // checks to see if visited if not go into if statement
        {
            curv->visited = true;
            curv->districtID = distID;  
            //now put adj nodes into the queue
            for(int i = 0; i < curv->adj.size(); i++){
                vertexStack.push(curv->adj[i].v); // '.' not "->" because adjVertex is not a pointer
            }
        }
    }
}
// Dijkstras
void Graph::shortestWeightedPath(std::string startingCity, std::string endingCity){
    
    int max = std::numeric_limits<int>::max();

    for(int i = 0; i < (int)vertices.size(); i++){
        vertices[i].visited = false;
        vertices[i].weightedDistance = max;
    }

    vertex* start = findVertex(startingCity);
    vertex* end = findVertex(endingCity);

    if(start == NULL || end == NULL){
        cout<<"One or more citites doesn't exist"<<endl;
    }
    else if(start->districtID == -1 || end->districtID == -1){
        cout<<"Please identify the districts before checking distances" <<endl;
    }
    else if(start->districtID != end->districtID){
        cout<<"No safe path between cities"<<endl;
    }
    else{

        start->visited = true; //step 1: mark start vertex as solved 
        start->weightedDistance = 0; // set distance to start as 0
        vector<vertex*> solved = {start};
        while(!end->visited){
            int minDistance = max;
            vertex* parentN = NULL;
            vertex* solvedV = NULL;
            for(int x = 0; x < (int)solved.size(); x++){
                vertex* s = solved[x];
                for(int y = 0; y < s->adj.size(); y++){
                    if(!s->adj[y].v->visited){
                        int dist = s->weightedDistance + s->adj[y].weight;
                        if(dist < minDistance){
                            solvedV = s->adj[y].v;
                            minDistance = dist;
                            parentN = s;
                        }
                    }
                }
            }
            solvedV->weightedDistance = minDistance;
            solvedV->parent = parentN;
            solvedV->visited = true;
            solved.insert(solved.begin(), solvedV);

        }
        cout<<end->weightedDistance;
        vertex* node = end;
        for(int i = 1; i < solved.size(); i++){
            while(node->parent != solved.at(i)){
                solved.erase(solved.begin()+i);
            }
            node = node->parent;
        }
        for(int i = solved.size()-1; i >= 0; i--){
            vertex* tmp = solved.at(i);
            cout<<", "<<tmp->name;
        }
        cout<<endl;
    }
}
void Graph::shortestPath(string startingCity, string endingCity){
	
	int max = std::numeric_limits<int>::max();
	
	for(int i=0; i < (int)vertices.size(); i++){
		vertices[i].visited = false;
		vertices[i].unweightedDistance = max;
	}
	vertex* start = findVertex(startingCity);
	vertex* end = findVertex(endingCity);
	if(start == nullptr || end == nullptr){
	    cout << "One or more cities doesn't exist" << endl;
	    return;
	}
	if(start->districtID == end->districtID){
		queue<vertex*> Q;
		if(start!=nullptr){
			start->visited = true;
			start->unweightedDistance = 0;
			Q.push(start);
			while(Q.size()!=0){
				vertex* s = Q.front();
				Q.pop();
				for(int i = 0; i < s->adj.size();i++){
					if(!s->adj[i].v->visited){
						s->adj[i].v->unweightedDistance = s->unweightedDistance + 1;
						s->adj[i].v->parent = s;
						s->adj[i].v->visited = true;
						Q.push(s->adj[i].v);
					}
				}
			}
		}
		vertex* tmp = end;
	    vector<string> path;
	    path.push_back(endingCity);
	    while(tmp!=start){
		    path.push_back(tmp->parent->name);
		    tmp = tmp -> parent;
	    }
	    cout << end->unweightedDistance;
	    while(path.size()!=0){
	        cout << ", "<<path.back();
	        path.pop_back();
	    }
	    cout << endl;
	}else{
		cout << "No safe path between cities" << endl;
	}
}