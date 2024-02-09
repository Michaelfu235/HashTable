/*Author: Michael Fu
  Date: 2/9/24
  Description: this program creates a hash table that stores students and alters when more than 3 collisions occur to spread out the data. 
  

 */

#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>


using namespace std;

//create the student struct will all of the data and a pointer to the next student
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
  void printStudent(){
    //function to print the student
    cout << "name: " << endl;;
    cout << fname << endl;
    cout << lname << endl;

    cout << "id: " << setw(6) << setfill('0') << id << endl;
    cout << "gpa: " << gpa << endl;
    cout << endl;
    //cout << fname << "   " << lname << "  " << id << "  " << gpa << endl; 
  }
};

//prototypes
void printTable(Student** table, int size);
Student** add(Student* studenttoadd, Student** table, int size);
Student* generate(int &idd);
void deleet(Student** &table, int size);
Student** rehash(Student** table, int size);

int main(){
  //set the initial size and table
  int size = 100;
  Student** table = new Student*[size];

  //random time and variables to use
  srand(time(NULL));
  bool justKeepGoing = true;
  char input[20];

  //what id we're on so it goes in order
  int whatidwereone = 0;

  while(justKeepGoing == true){
    //ask the user what they want to do
    cout << "---------------------------------------------------" << endl;
    cout << "ADD, PRINT, DELETE, or QUIT" << endl;
    cin.get(input, 20, '\n');
    cin.ignore();

    //if the user put in "add"
    if(strcmp(input, "ADD")==0){
      //ask wether they want to generate or manually add
      cout << "manually or generate?" << endl;
      cin.get(input, 20, '\n');
      cin.ignore();
      if(strcmp(input, "generate")==0){//if they chose to generate, just loop through using i up until the number they put in, making a new student each iteration
	cout << "How many students to generate?" << endl;
	int numtoo = 0;
	cin >> numtoo;
	cin.ignore();
	for(int i = 0;i<numtoo;i++){
	  table = add(generate(whatidwereone), table, size);
	}
 

      } else if(strcmp(input, "manually")==0){//if the user put in manually, just go through and ask them for the info and add it to the table
	Student* student = new Student();	
	cout << "first name: ";
	cin >> student->fname;
	
	cout << "last name: ";
	cin >> student->lname;
	
	cout << "id #: ";
	cin >> student->id;
	
	cout << "gpa: ";
	cin >> student->gpa;
	cin.ignore();
	student->printStudent();
	table = add(student, table, size);

      }

      //after adding the student, go through and check for collisions, and if there is a node that has more than 3 chains, then call the rehash function
      int collisions = 0;
      for(int i = 0;i<size && collisions < 3;i++){
	collisions = 0;
	Student* current = table[i];
	if(current != NULL){
	  while(current != NULL){
	    collisions++;

	    current = current->next;
	  }
	}

	if(collisions > 3){
	  

	  table = rehash(table, size);
	  size *= 2;
	}
      }
    } else if (strcmp(input, "PRINT")==0){//if the user put in print, call the printtable function
      printTable(table, size);
    } else if (strcmp(input, "DELETE")==0){//if they put in delete, call the delete function
      deleet(table, size);
    } else if (strcmp(input, "QUIT")==0){//if they put in quit, then set the boolean o keep going to false
      justKeepGoing = false;
    }
    
    
  }
  
}




//for the print table function, go through each element of the has table, and if it has nodes after it, go through and print out each node after it
void printTable(Student** table, int size){
  for (int i = 0; i < size; i++) {
    if (table[i] != NULL) {
      table[i]->printStudent();

      Student* current = table[i];

      while(current->next != NULL) {
	current = current->next;
	cout << " |" << endl;
	cout << " V" << endl;
	current->printStudent();
      }
    }
 }
}

//for the add function, create a temporary new student (so that the next variable isn't carried over. Then go to the right element in the table and if it's null, then set it to the new student. If there are already elements there, then add the new temporary student to the end of the chain. (the collision detection is in the main code)
Student** add(Student* student, Student** table, int size){
  //cout << "started add function" << endl;

  int tempy = student->id%size;
  Student* current = table[tempy];
  Student* temptwo = new Student();
  temptwo->fname = student->fname;
  temptwo->lname = student->lname;
  temptwo->id = student->id;
  temptwo->gpa = student->gpa;
  temptwo->next = NULL;
  
  if(current==NULL){
    table[tempy] = temptwo;
  } else if (table[tempy] != NULL){
    while(current->next != NULL){
      current = current->next;
    }

    current->next = temptwo;
    current->next->next = NULL;
  }

  //cout << "ran add function" << endl;

  return table;
}


//for generate, create a new student, and get a random first name, last name, and GPA. then increment the ID that was passed by reference
Student* generate(int &idd){
  Student* student = new Student();

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



//for the delete function, ask for the ID of the student to delete, and go through and delete the student whos ID matches the inputted ID, with a prev, head, and first temporary students to keep track of the "next"s
void deleet(Student** &table, int size){
  int id = 0;

  cout << "What is the ID of the student you want to delete?" << endl;
  cin >> id;
  cin.ignore();

  bool studenttodelfound = false;

  for(int i=0; i<size; i++){
    if(table[i]){
      Student* prev = NULL;
      Student* head = table[i];
      Student* first = table[i];
      //If the student is at the beginning of the list
      if(first->id == id){
	Student* temp = first;
	first = first->next;
	temp->~Student();
	table[i] = first;
      }
      else{
	while(head->next != NULL && head->id != id){
	  prev = head;
	  head = head->next;
	}
	//If the student is anywhere else
	if(id == head->id){
	  prev->next = head->next;
	  head->~Student();
	}
      }
    }
  }
  cout << "Deleted!" << endl;
}


//rehash function, create a new table of double the size and go through the old table, putting each element into the new table using the add function. 
Student** rehash(Student** table, int size){
  int count = 0;

  int newSize = size*2;
  Student** newTable = new Student*[newSize];
  for(int i = 0;i<newSize;i++){
    newTable[i] = NULL;
  }
  
  for(int i=0; i < size; i++){
    cout << "rehashing..." << endl;
    Student* temp = table[i];
    //temp->next = NULL;
    bool keepGoing2 = true;
    while(temp != NULL && keepGoing2 == true){
      
      newTable = add(temp, newTable, newSize);
      temp = temp->next;
      count++;
      //if(count > 3){
      //  keepGoing2 = false;
      //}

    }
  }
  for(int i = 0;i<size;i++){
    table[i] = NULL;
  }

  size*=2;
  return newTable;
  

  
}
