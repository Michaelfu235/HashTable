#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>


using namespace std;

struct Student {
  //variables
  char* fname = new char[30];
  char* lname = new char[30];
  int id;
  float gpa;
  int hash;
  Student* next;
public:
  // Constructor
  Student() {
    fname = new char[30];
    lname = new char[30];
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
  void printStudent(){/*
    cout.setf(ios::fixed, ios::floatfield);
    cout.setf(ios::showpoint);
    cout.precision(2);*/
    cout << "name: " << endl;;
    cout << fname << endl;
    cout << lname << endl;

    cout << "id: " << setw(6) << setfill('0') << id << endl;
    cout << "gpa: " << gpa << endl;
    cout << endl;
    //cout << fname << "   " << lname << "  " << id << "  " << gpa << endl; 
  }
};


void printTable(Student** table, int size);
Student** add(Student* studenttoadd, Student** table, int size);
Student* generate(int &idd);


int main(){
  int size = 100;
  Student** table = new Student*[size];

  srand(time(NULL));
  bool justKeepGoing = true;
  char input[20];

  int whatidwereone = 0;
  /*
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
  */

  //int temp = 1;
  //generate(temp)->printStudent();
  //  table = add(generate(whatidwereone), table, size);

  cout << "num of students to put?" << endl;
  int num = 0;
  cin >> num;
  cin.ignore();
  for(int i = 0;i<num;i++){
    table = add(generate(whatidwereone), table, size);
  }
  printTable(table, size);

  /*
  cout << " empty" << endl;
  cout << table[1]->fname << endl;
  cout << table[1]->lname << endl;
  cout << table[1]->id << endl;
  cout << table[1]->gpa << endl;
  /*  Student* student = new Student();

  int randnum = rand()%1001;
  ifstream inputFile("fname.txt");
  //inputFile.open("fname.txt");
  char randomfirst[20];
  int templine = 0;
  while(randnum != templine  && inputFile.getline(randomfirst, 30)){
    ++templine;
  }
  if(templine == randnum){
    strcpy(student->fname, randomfirst);
  }
  inputFile.close();
  cout << student->fname << endl;
  */
  
  
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
  //cout << "started add function" << endl;

  Student* current = table[(student->id)%size];
  if(current==NULL){
    table[(student->id)%size] = student;
  } else if (table[(student->id)%size] != NULL){
    while(current->next != NULL){
      current = current->next;
    }

    current->next = student;
  }

  //cout << "ran add function" << endl;

  return table;
}


Student* generate(int &idd){
  Student* student = new Student();
  /*
  int randnum2 = rand()%1001;
  ifstream inputFile("fname.txt");
  char randomfirst[50];
  int templine = 0;
  while(randnum2 != templine  && inputFile.getline(randomfirst, 50)){
    ++templine;
  }
  student->fname = randomfirst;
    //strcpy(student->fname, randomfirst);
    
  
  inputFile.close();
  */

  int numLine = 0;
  int fRandom = rand()%100;
  ifstream ffile;
  ffile.open("fname.txt");
  //char idk[50];
  //  char line [50];
  
  char fvalue[30];
  //Go till random generated line #
  while (fRandom!=numLine && ffile.getline(fvalue, 30)) {
    ++numLine;
  }
  if (numLine == fRandom) {
    strcpy(student->fname, fvalue);
  }
  
  ffile.close();

  
  int lRandom = rand()%100;
  ifstream lfile;
  lfile.open("lname.txt");
  numLine = 0;
  char lvalue[30];
  while (lRandom!=numLine && lfile.getline(lvalue, 30)) {
    ++numLine;
  }
  if (numLine == lRandom) {

    strcpy(student->lname, lvalue);
  }
  lfile.close();
  
  idd++;
  student->id = idd;
  float gpt = (double)(rand()%401)/100;
  student->gpa = gpt;

  //student->printStudent();
  
  return student;
}
