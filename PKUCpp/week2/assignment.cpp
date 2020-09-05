#include <iostream>
#include<stdio.h>
#include<cstring>
#include<string>
#include<string.h>
// #include <string>
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
    string inputStr;
    getline(cin, inputStr);
    
    //process the input string
    // int comma = inputStr.find_first_of(',');
    // while (comma!=std::string::npos)
    // {
    //     string temp = inputStr.substr(0, comma);
    //     inputStr = inputStr.substr(comma+1, inputStr.length() - comma);
    //     comma = inputStr.find_first_of(',');
    //     cout << temp << endl;
    // }
    // cout << inputStr << endl;
    Student student;

    unsigned int pos = inputStr.find_first_of(','); // if signed, compiler will complain
    student.set_name(inputStr.substr(0, pos));  // read the name out
    inputStr = inputStr.substr(pos + 1, inputStr.length() - pos);
    pos = inputStr.find_first_of(',');
    student.set_age(stoi(inputStr.substr(0, pos)));
    inputStr = inputStr.substr(pos + 1, inputStr.length() - pos);
    pos = inputStr.find_first_of(',');
    student.set_stunnum(inputStr.substr(0, pos));    // student number
    inputStr = inputStr.substr(pos + 1, inputStr.length() - pos);
    
    int total_grade = 0;
    pos = inputStr.find_first_of(',');
    
    while(pos!=string::npos){
        total_grade += stoi(inputStr.substr(0, pos));   // read all grade out
        inputStr = inputStr.substr(pos + 1, inputStr.length() - pos);
        pos = inputStr.find_first_of(',');
    }
    total_grade += stoi(inputStr);
    student.set_avggrage(total_grade/4);
    // int avg_grade = total_grade/4;

    cout<< student.get_name() << ',' << student.get_age() << ',' << student.get_stunum() << ',' << student.get_avggrade() << endl;
    return 0;
}