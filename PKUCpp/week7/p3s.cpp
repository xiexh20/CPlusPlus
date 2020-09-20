#include <iostream>
#include <iomanip>  // in order to use setw
using namespace std;

int main()
{
    int x;
    cin>>x;
    cout<<hex<<x<<endl;

    cout.fill('0');
    cout<<dec;  // output in decimal format
    cout<<setw(10)<<x<<endl;
    return 0;
}