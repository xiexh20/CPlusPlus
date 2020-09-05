#include <iostream>
#include <cstdlib>
using namespace std;

class Student{
    private: 
        string name;
        int age;
        string stunum;
        int avg_grade;
    
    public:
        void set_name(string newname){
            name = newname;
        }
        void set_age(int newage){
            age = newage;
        }
        void set_stunnum(string num){
            stunum = num;
        }
        void set_avggrage(int grade){
            avg_grade = grade;
        }
        string get_name(){
            return name;
        }
        int get_age(){
            return age;
        }
        string get_stunum(){
            return stunum;
        }
        int get_avggrade(){
            return avg_grade;
        }

};

int main()
{
    // int a,b;
    char* inputstr = new char[100];
    cin >> inputstr;
    cout << inputstr << endl;

    Student stu;
    char* temp = new char[20];
    int count = 0;
    // process char by char
    for(int i=0;inputstr[i]!='\0';i++){
        // cout << inputstr[i] << endl;
        if(inputstr[i]!=','){
            temp[count] = inputstr[i];
            count++;
        }
        else{
            count = 0;
            delete temp;
            temp = new char[20];
            cout << temp <<endl;
        }
        // stu.set_stunnum(inputstr);
        // cout<<stu.get_stunum()<<endl;

    }
    return 0;
}