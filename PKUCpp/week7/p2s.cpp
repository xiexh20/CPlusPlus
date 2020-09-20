#include <iostream>
using namespace std;

int main()
{
    double x;
    cin>>x;
    cout<<fixed;    // set to output with fixed point, clear previous settings
    cout.precision(5);  // set to five floating digits
    cout<<x<<endl;
    cout<<scientific;   // set to output in scientific notation
    cout.precision(7);  // set precision to 7 digits
    cout<<x<<endl;
    return 0;

}