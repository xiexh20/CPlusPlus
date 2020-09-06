#include <iostream>
using namespace std;
class A {
public:
    int val;
    int & GetObj(){
        return val;
    }
    // constructor
    A(){
        val = 0;    // init to zero
    }
// 在此处补充你的代码

};
int main()  {
    A a;
    cout << a.val << endl;
    a.GetObj() = 5;
    cout << a.val << endl;
}