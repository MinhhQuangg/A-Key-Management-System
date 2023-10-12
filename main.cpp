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
void writer(string output_filename, Employee employees[], int nEmployees) {
   int i;
   int j;
   ofstream output; 
   output.open(output_filename);
   
   output << nEmployees << endl;
   for (i=0; i < nEmployees; i++) {
      output << employees[i].name << endl;
      output << employees[i].nKeysPossessed;
      for (j=0; j<employees[i].nKeysPossessed; j++) {
         output << " " << employees[i].keys[j];
      }
      output << endl;
   }
   output.close();
}
bool addKeyForEmployee(Employee employees[], int nEmployees, string emp_name, string newKey) {
   int i;
   int j;
   for (i=0; i < nEmployees; i++) {
      if (emp_name == employees[i].name) {
         if (employees[i].nKeysPossessed ==5) {
            cout << "This employee already has 5 keys!" << endl;
            return false;
         } else if (employees[i].nKeysPossessed < 5) {
            for (j=0; j < employees[i].nKeysPossessed; j++) {
               if (newKey == employees[i].keys[j]) {
                  cout << "This employee already has this key!"<< endl;
                  return false;
               }
            }
         }
         employees[i].keys[employees[i].nKeysPossessed] = newKey; 
         employees[i].nKeysPossessed ++;
         return true;
      }
   }
   cout << "Cannot find the specified employee!" << endl;
   return false;
}