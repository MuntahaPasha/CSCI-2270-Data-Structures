#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "MovieTree.hpp"

using namespace std;


int main(int argc, char *argv[]){
	MovieTree call;
	ifstream file;
	string parse;
	string line;
	file.open(argv[1]);
	if(file.is_open()){
		while(!file.eof()){
			int ranking;
			string title;
			int year;
			int quantity;
			string tempRanking;
			string tempYear;
			string tempQuantity;
			getline(file, line);

			stringstream ss(line);
			getline(ss, tempRanking, ',');
			ranking = stoi(tempRanking);
			getline(ss, title, ',');
			getline(ss, tempYear, ',');
			year = stoi(tempYear);
			getline(ss, tempQuantity, ',');
			quantity = stoi(tempQuantity);

			call.addMovieNode(ranking, title, year, quantity);
		}
	file.close();
	}
	string option;
	bool quit = false;
	while(quit != true){
		cout<<"======Main Menu======"<<endl;
		cout<<"1. Find a movie"<<endl;
		cout<<"2. Rent a movie"<<endl;
		cout<<"3. Print the inventory"<<endl;
		cout<<"4. Delete a movie"<<endl;
		cout<<"5. Count the movies"<<endl;
		cout<<"6. Quit"<<endl;
		getline(cin, option);

		if(stoi(option) == 1){
			string title;
			cout<<"Enter title:"<<endl;
			getline(cin, title);

			call.findMovie(title);
		}
		else if(stoi(option) == 2){
			string title;
			cout << "Enter title:" << endl;
			getline(cin, title);

			call.rentMovie(title);
		}
		else if(stoi(option) == 3){
			call.printMovieInventory();
		}
		else if(stoi(option) == 4){
		    string title;
			cout << "Enter title:" << endl;
			getline(cin, title);
			
			call.deleteMovieNode(title);
		}
		else if(stoi(option) == 5){
			int numb = call.countMovieNodes();
			cout<<"Tree contains: "<<numb<<" movies."<<endl;
		}
		else if(stoi(option) == 6){
			quit = true;
		}
		else{
			cout<<"Please enter a number between 1 and 6."<<endl;
		}
	}
	cout<<"Goodbye!"<<endl;
	return 0;
}