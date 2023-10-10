#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Employee {
   string name;
   int nKeysPossessed;
   string keys[5];
};

bool reader(string input_filename, Employee employees[], int& nEmployees);

void writer(string output_filename, Employee employees[], int nEmployees);

bool addKeyForEmployee(Employee employees[], int nEmployees, string emp_name, string newKey);

bool returnAKey(Employee employees[], int nEmployees, string emp_name, string returnKey);

int main() {
   int i;
   int nEmployees;
   string inputFile; 
   cin >> inputFile;
   int option;
   int j;
   string inputName;
   bool check1 = false;
   bool check2 = false;
   string key;
   string outputFile;
   
   Employee employees[10]; 
    
   cout << "Please enter key file name to start: ";
   
   if(!reader(inputFile, employees, nEmployees)) {
      cout << "File not found, exiting the program..." << endl;
   }
}

bool reader(string input_filename, Employee employees[], int& nEmployees) {
    int i;
   int j;
   ifstream input;
   input.open(input_filename);
   
   if(!input.is_open()) {
      return false;
   }
   
   input >> nEmployees;
   input.ignore();
   
   for ( i = 0; i < nEmployees; i++ ) {
      getline(input, employees[i].name);

      input >> employees[i].nKeysPossessed;
      for ( j = 0; j < employees[i].nKeysPossessed; j ++ ) {
         input >> employees[i].keys[j];
      }
      input.ignore();
   }
   input.close();
   return true; 
}