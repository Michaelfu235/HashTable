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
void deleet(Student** &table, int size);
void rehash(Student** &table, int &size);

int main(){
  int size = 100;
  Student** table = new Student*[size];

  srand(time(NULL));
  bool justKeepGoing = true;
  char input[20];

  int whatidwereone = 0;

  while(justKeepGoing == true){
    cout << "---------------------------------------------------" << endl;
    cout << "ADD, PRINT, DELETE, or QUIT" << endl;
    cin.get(input, 20, '\n');
    cin.ignore();

    if(strcmp(input, "ADD")==0){
      cout << "manually or generate?" << endl;
      cin.get(input, 20, '\n');
      cin.ignore();
      if(strcmp(input, "generate")==0){
	cout << "How many students to generate?" << endl;
	int numtoo = 0;
	cin >> numtoo;
	cin.ignore();
	for(int i = 0;i<numtoo;i++){
	  table = add(generate(whatidwereone), table, size);
	}
 

      } else if(strcmp(input, "manually")==0){
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
	  

	  rehash(table, size);
	}
      }
    } else if (strcmp(input, "PRINT")==0){
      printTable(table, size);
    }
    
    
  }
  /*
  cout << "num of students to put?" << endl;
  int num = 0;
  cin >> num;
  cin.ignore();
  for(int i = 0;i<num;i++){
    table = add(generate(whatidwereone), table, size);
  }
  printTable(table, size);

  cout << "break" << endl;

  
  rehash(table, size);

  int randooo = 201;
  cout << "before" << endl;
  printTable(table, size);
  cout << "after" << endl;
  table = add(generate(randooo), table, size);
  printTable(table, size);
    
  /*while(true){
    deleet(table, size);
    printTable(table, size);
    }*/
}





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


Student** add(Student* student, Student** table, int size){
  //cout << "started add function" << endl;

  int tempy = student->id%size;
  Student* current = table[tempy];
  
  if(current==NULL){
    table[tempy] = student;
  } else if (table[tempy] != NULL){
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
  /*
  for(int i = 0;i<size;i++){
    
    if(table[i] != NULL){
      Student* temp = table[i];
      if(temp->id == idtodel){
	if(temp->next==NULL){
	  table[i] = NULL;
	} else {
	  table[i] = temp->next;
	}
      } else{
	while(temp->next!=NULL){
	  temp = temp->next;
	  if(temp->id == idtodel){
	    if(temp->next==NULL){
	      table[i] = NULL;
	    } else {
	      table[i] = temp->next;
	    }
	  }
	} 
      
      /*Student* temp = table[i];
      if(temp->next == NULL){
	if(temp->id == idtodel){
	  table[i] == NULL;
	}
      } else if (table[i]->id == idtodel){
	table[i] = table[i]->next;
      } else {
	Student* temp2;
	while(temp->id != idtodel){
	  temp2 = temp;
	  temp = temp->next;
	}

	temp2->next = temp->next;
}
	
      
    }
  }
}
*/

void rehash(Student** &table, int &size){
  int count = 0;

  Student** newTable = new Student*[size*2];
  for(int i = 0;i<size*2;i++){
    newTable[i] = NULL;
  }
  
  for(int i=0; i < size; i++){
    cout << "rehashing..." << endl;
    Student* temp = table[i];
    bool keepGoing2 = true;
    while(temp != NULL && keepGoing2 == true){
      
      newTable = add(temp, newTable, size*2);
      temp = temp->next;
      count++;
      if(count > 3){
        keepGoing2 = false;
      }

    }
  }
  for(int i = 0;i<size;i++){
    table[i]->~Student();
  }

  size*=2;
  table = new Student*[size];
  table = newTable;

  
  /*
  Student** newTable = new Student*[size*2];
  for(int i = 0;i<size*2;i++){
    newTable[i] = NULL;
  }

  for(int i = 0;i<size;i++){
    Student* temp = table[i];
    while(temp != NULL){
      temp->hash = student->id % SIZE*2;
      Student* newS = new Student();
      newS->fname = temp->fname;
      newS->lname = temp->lname;
      newS->id = temp->id;
      newS->gpa = temp->gpa;

      newTable = add(newS, newTable, size*2);
      newS = newS->next
    }
    }*/

  
}
