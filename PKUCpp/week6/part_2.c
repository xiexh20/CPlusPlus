#include <iostream>
using namespace std;
class A {
// 在此处补充你的代码
    public: 
    // do not forget to declare the dectructor as virtual function. Only in this way, when a
    // pointer is declared as base class and assigned derived object reference, the derived destructor 
    // will be called upon deletion.
        virtual ~A(){
            cout << "destructor A" << endl; 
        }
};
class B:public A {
    public:
        ~B() { cout << "destructor B" << endl; }
};
int main() {
    A * pa;
    pa = new B;
    delete pa;
    return 0;
}