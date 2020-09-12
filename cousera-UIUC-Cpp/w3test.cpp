#include<iostream>
#include<stdio.h>
using namespace std;

int reference_count = 0;

class Track {
public:
    Track() { 
        reference_count++; 
        printf("reference count=%d, in constructor.\n", reference_count);
        }
    ~Track() { reference_count--; 
    printf("reference count=%d, in destructor.\n", reference_count);
    }
};

int main()
{
    Track t;
    Track *p = &t;
    // ...
    delete p;   // cause error, since p is not a pointer to the heap
    return 0;

}


