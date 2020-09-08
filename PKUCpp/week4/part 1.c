#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
class Complex {
private:
    double r,i;
public:
    void Print() {
        cout << r << "+" << i << "i" << endl;
    }
    void operator=(const char *str){
        int k;
        int plusidx;    // the index of the plus sign
        for(k=0;str[k]!='\0';k++){
            if(str[k]=='+') {
                plusidx = k;
                break;
            }
        }
        
        char sreal[10];
        strncpy(sreal, str, plusidx);
        str += plusidx + 1;
        char simg[10];  // string for the imaginary part
        int len = strlen(str);
        strncpy(simg, str, len - 1);
        // printf("r=%s, i=%s\n", sreal, simg);
        
        // convert the string to integer number
        r = atof(sreal);
        i = atof(simg);
    }
// 在此处补充你的代码
};
int main() {
    Complex a;
    a = "3+4i"; 
    a.Print();
    a = "5+6i"; 
    a.Print();
    return 0;
}