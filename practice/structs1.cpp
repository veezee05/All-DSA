#include<iostream>
using namespace std;

/*struct = A structure that group related variables under one name
structs can contain many different data types(string, integer, etc)
variables in a struct are known as 'membes'
members can be accessed with . 'class member access operator'
*/

struct student{
    string name;
    double gpa;
    bool enrolled;
};

int main(){
    student stud1;

    stud1.name = "Spongebob";
    stud1.gpa = 3.5;
    stud1.enrolled = true;

    cout<<stud1.name<<"\n";
    cout<<stud1.gpa<<"\n";
    cout<<stud1.enrolled<<"\n";
}
