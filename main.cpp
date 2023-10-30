#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Employee {
   string name;
   int nKeysPossessed;
   string keys[5];
};

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
bool returnAKey(Employee employees[], int nEmployees, string emp_name, string returnKey) {
   int i;
   int j;
   bool check1 = false;
   bool check2 = false;
   int key;
   for (i=0; i < nEmployees; i++) {
      if (emp_name == employees[i].name) {
         check2 = true;
         for (j=0; j < employees[i].nKeysPossessed; j++) {
            if (employees[i].keys[j] == returnKey) {
               check1 = true;
               key = j;
               break;
            }
         }
         if(!check1) {
            cout << "This employee does not have the specified key!" << endl;
         } else {
            for (j = key; j < employees[i].nKeysPossessed; j++) {
               employees[i].keys[j] = employees[i].keys[j+1];
            }
            employees[i].nKeysPossessed--;
            return true;
         }
      }
   }
   if(!check2) {
      cout << "Cannot find the specified employee!" << endl;
   }
   return false;
}
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
   } else {
   
   while(true) {
      cout <<"Please select from the following options: "<< endl; 
      cout <<"  1. show all employees and their keys"<< endl;
      cout <<"  2. show the keys an employee possesses"<< endl;
      cout <<"  3. show which employees possess a specific key"<< endl;
      cout <<"  4. add a key to an employee"<< endl;
      cout <<"  5. return a key by an employee"<< endl;
      cout <<"  6. save the current key status"<< endl;
      cout <<"  7. exit the program"<< endl;
      
      cin >> option;
      cin.ignore();
      if (option == 1) {
         for (i =0; i < nEmployees; i++) {
            cout << "Name: " << employees[i].name << endl;
            cout << "Keys possessed: ";
            for ( j = 0; j < employees[i].nKeysPossessed; j ++ ) {
               cout << employees[i].keys[j] << " ";
            }
            cout << endl;
         }

      } else if (option == 2) {
         cout << "Please enter employee's name: "; 
         getline(cin, inputName);
         for (i=0; i< nEmployees;i++) {
            if(inputName == employees[i].name) {
               check1 = true;
               cout << inputName << " possess the following keys: ";
               for ( j = 0; j < employees[i].nKeysPossessed; j ++ ) {
                  cout << employees[i].keys[j] << " ";
               }
               cout << endl;
            }
         }
         if (!check1) {
            cout << "Cannot find the specified employee!" << endl;
         }
      } else if(option==3){
         cout << "Please enter a key: "; 
         getline(cin, key); 
         for (i =0; i < nEmployees; i++) {
            for (j = 0; j < employees[i].nKeysPossessed; j ++ ) {
               if (key == employees[i].keys[j]) {
                  check2 = true;
                  cout << employees[i].name << ", ";
               }
            }
         }
         if(!check2) {
            cout << "No one possesses this key." << endl;
         } else { 
            cout << "possess this key." << endl;
         }
      } else if(option == 4) {
         cout <<  "Please enter employee's name: "; 
         getline(cin, inputName);
         cout << "Please enter a new key: ";
         getline(cin, key); 
         if (addKeyForEmployee(employees, nEmployees, inputName, key)) {
            cout << "Key added successfully." << endl;
         } 
      } else if(option == 5) {
         cout <<  "Please enter employee's name: "; 
         getline(cin, inputName);
         cout << "Please enter the returned key: ";
         getline(cin, key);
         if(returnAKey(employees, nEmployees, inputName, key)) {
            cout << "Key returned successfully." << endl;
         }
      } else if(option == 6) {
         cout << "Please enter output file name: ";
         getline(cin, outputFile);
         writer(outputFile, employees, nEmployees); 
      } else if(option == 7) {
         outputFile = "keys_updated.txt";
         writer(outputFile, employees, nEmployees); 
         cout << "Thank you for using the system! Goodbye!" << endl;
         return false;
      } else {
         cout << "Not a valid option. Please try again." << endl;
      }
      cout << endl;
   }
   }
}
