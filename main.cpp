#include <iostream>
#include <cstring>

using namespace std;

struct Student {
  //variables
  char* fname;
  char* lname;
  int id;
  float gpa;
  int hash;
  Student* next;
public:
  // Constructor
  Student() {
    fname = new char[20];
    lname = new char[20];
    id = 0;
    gpa = 0.0f;
    hash = 0;
    next = NULL;
  }

  // Destructor
  ~Student() {
    delete[] fname;
    delete[] lname;
  }
  void printStudent(){
    cout.setf(ios::fixed, ios::floatfield);
    cout.setf(ios::showpoint);
    cout.precision(2);
    cout << fname << "   " << lname << "  " << id << "  " << gpa << endl; 
  }
};


void printTable(Student** table, int size);
Student** add(Student* studenttoadd, Student** table, int size);
 
int main(){
  int size = 100;
  Student** table = new Student*[size];

  bool justKeepGoing = true;
  char input[20];


  Student* newStu1 = new Student();
  char* hmm = new char[20];
  strcpy(hmm, "bob");
  //strcpy(newStu1->fname, "bob");
  newStu1->fname = hmm;
  strcpy(hmm, "aoa");
  newStu1->lname = hmm;
  
  //strcpy(newStu1->lname, "aoa");
  newStu1->id = 453117;
  newStu1->gpa = 4.32;

  newStu1->printStudent();

  table = add(newStu1, table, size);

  printTable(table, size);
  
}

void printTable(Student** table, int size){
  for (int i = 0; i < size; i++) {
    if (table[i] != NULL) {
      table[i]->printStudent();
      /*cout << "First name: " << table[i]->fname << endl;
      cout << "Last name: " << table[i]->lname << endl;
      cout << "ID: " << table[i]->id << endl;
      cout.setf(ios::fixed, ios::floatfield);
      cout.setf(ios::showpoint);
      cout.precision(2);
      cout << "GPA: " << table[i]->gpa << endl;
      cout << endl;*/

      Student* current = table[i];

      while(current->next != NULL) {
	current = current->next;
	current->printStudent();
	/*
	cout << "First name: "	<< current->fname << endl;
	cout << "Last name: " << current->lname << endl;
	cout << "ID: "	<< current->id	<< endl;
	cout.setf(ios::fixed, ios::floatfield);
	cout.setf(ios::showpoint);
	cout.precision(2);
	cout << "GPA: " << current->gpa << endl;
	cout << endl;
	*/
      }
    }
 }
}


Student** add(Student* student, Student** table, int size){
  cout << "started add function" << endl;

  Student* current = table[(student->id)%size];
  if(current==NULL){
    table[(student->id)%size] = student;
  } else if (table[(student->id)%size] != NULL){
    while(current->next != NULL){
      current = current->next;
    }

    current->next = student;
  }

  cout << "ran add function" << endl;

  return table;
}
