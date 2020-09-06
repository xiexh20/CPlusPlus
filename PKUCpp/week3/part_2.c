#include <iostream>
using namespace std;
class Sample{
public:
    int v;
    Sample(int n):v(n) { }

    // add new copy constructor
    Sample(Sample &p){
        v = 10;
    }
// 在此处补充你的代码
};
int main() {
    Sample a(5);
    Sample b = a;
    cout << b.v;
    return 0;
}