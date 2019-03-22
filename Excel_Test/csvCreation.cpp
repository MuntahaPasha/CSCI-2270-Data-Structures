#include <iostream>
#include <fstream>
#include <string>

using namespace std;
// Program to get Employee Data as CSV file
int main( int argc, char* argv[] )
{

	// Creating the output file.

	ofstream myfile;
	myfile.open ("EmployeeData.csv");

	// Creating array that has Employee names
	
	myfile << "Employee Name,EmployeeSalary2018, EmployeeSalary2019, EmployeeSalary2020,\n";
	int size = 10;
	string name[size] = {"Alex","Kelly","Bruce","Jane","Kenny","Roger","Katie","Molly","Shane","Rocky"};

	for (int i = 0; i < size; i++)
	{
		// Assigning Salaries for 2018, 2019 and 2020
		// Salary is assigned randomly as a number between 75000 and 100000

		double rnd = 75000 + ( std::rand() % ( 100000 - 75000 + 1 ) );
		double rnd2 = 75000 + ( std::rand() % ( 100000 - 75000 + 1 ) );
		double rnd3 = 75000 + ( std::rand() % ( 100000 - 75000 + 1 ) );

		// Writing to the csv file

		myfile << name[i]+",";
		myfile << to_string(rnd)+",";
		myfile << to_string(rnd2)+",";
		myfile << to_string(rnd3)+",";
		myfile << "\n";
	}

	// CLosing the CSV File
	
	myfile.close();
	return 0;
}