#include<iostream>
#include<string>

using namespace std;

class Employee
{
    public:
        int emp_id;
        string name;
        string position;

        Employee(int id, const string n, const string p)
        {
            emp_id = id;
            name = n;
            position = p;
        }
};

class Node
{
    public:
        Employee *employee; //pointer to the employee object
        Node *next; //pointer to the next node

        Node(Employee *emp): employee(emp), next(nullptr) {}
};

class Hashtable
{
    private:
        Node **table;
        int size;

        int hash_function(int key)
        {
            return key % size;
        }

    public:
        Hashtable(int s):size(s)
        {
            table = new Node*[size]; //allocating memory for an array of pointers
            for(int i = 0; i<size; ++i)
            {
                table[i] = nullptr; //initilizing each entry to nullptr
            }
        }

        ~Hashtable() //destructor called, to clean up memory
        {
            for(int i = 0; i<size; ++i) {
                Node *current = table[i];
                while (current != nullptr) {
                    Node *todelete = current;
                    current = current->next;
                    delete todelete->employee; //deleting the employee object
                    delete todelete;
                }
            }
            delete[] table; //deleting the array of pointers
        }

    void insert(const Employee& employee) {
        int index = hash_function(employee.emp_id);
        Node *newNode = new Node(new Employee(employee)); //creating a new node

        //to check if the employee alreayd exists in the hash table
        Node *current = table[index];
        while (current != nullptr) {
            if (current->employee->emp_id == employee.emp_id) {
                //update existing employee
                current->employee->name = employee.name;
                current->employee->position = employee.position;
                delete newNode;
                return;
            }
            current = current->next;
        }

        //inserting a new node at the beginning of a linked list
        newNode->next = table[index];
        table[index] = newNode;
    }

    Employee *lookup(int emp_id) {
        int index = hash_function(emp_id);
        Node *current = table[index];
        while(current != nullptr)
        {
            if(current->employee->emp_id == emp_id) {
                return current->employee; //returning the pointer to the employee object if found
            }
            current = current ->next;
        }
        return nullptr; //returning a nullptr if not found
    }

    bool deleteEmployee(int emp_id) {
        int index = hash_function(emp_id);
        Node *current = table[index];
        Node *previous = nullptr;

        while (current != nullptr) {
            if (current->employee->emp_id == emp_id) {
                //found the previous employee to delete
                if(previous == nullptr) {
                    table[index] = current->next;
                }
                else{
                    //deleting a middle or the last node
                    previous->next = current->next;
                }

                delete current->employee; //deleting the employee object
                delete current;
                return true;
            }
            previous = current;
            current = current->next;
        }
        return false; //returning false if not found
    }
};

int main() {
    Hashtable hashtab(10); //creating a hash table with the size of 10

    //adding employees
    Employee emp1(101, "Carl", "Developer");
    Employee emp2(102, "Bob", "Designer");
    Employee emp3(203, "Charlie", "Manager");

    hashtab.insert(emp1);
    hashtab.insert(emp2);
    hashtab.insert(emp3);

    //looking up and employee
    Employee *foundEmp = hashtab.lookup(102);
    if(foundEmp) {
        cout<<"Found Employee: "<<foundEmp->name<<", Position: "<<foundEmp->position<<endl;
    }
    else {
        cout<<"Employee not found."<<endl;
    }

    //attemting to look up the deleted employee
    foundEmp = hashtab.lookup(200);
    if(foundEmp) {
        cout<<"Found Employee: "<<foundEmp->name<<", Position: "<<foundEmp->position<<endl;
    }
    else {
        cout<<"Employee not found."<<endl;
    }

    return 0;
}