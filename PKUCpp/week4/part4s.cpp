#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>
using namespace std;

#define MAXSIZE 100
#define POSITIVE 0
#define NEGATIVE 1
#define EQUAL 0
#define SMALLER -1
#define LARGER 1

class BigInt{

    private:
        vector<int> num;
        int sign;   //     
    
    public:
        BigInt():num(0), sign(POSITIVE){}   // default constructor
        BigInt(vector<int> digits); // construct from a digits vector
        BigInt(const char* str);    // init with a string
        BigInt(BigInt& that);   // copy constructor
        // ~BigInt();  // destructor
        BigInt& operator +(BigInt& that);   // overload +
        int compare_to(BigInt& that);       // compare two number
        void set_sign(int sign_);     
        // BigInt& operator -(BigInt& that);
        // BigInt& operator *(BigInt& that);
        // BigInt& operator /(BigInt& that);
        const char* to_string();
        int length(){
            return num.size();
        }
        int & operator [](int idx){
            return num[idx];
        }
};

// TEST passed!
BigInt::BigInt(vector<int> digits):num(digits.size())
{
    sign = POSITIVE;    // by default positive
    for(int i=0;i<digits.size();i++){
        num[i] = digits[i];
    }
}

// construct the int array from given string
BigInt::BigInt(const char* str)
{
    int size = strlen(str);
    sign = POSITIVE;    // by default positive
    num.resize(size);      // constructor a vector with length of the str length
    for(int i=0;i<size;i++){
        num[i] = str[size - i - 1] - '0';   // lower index means lower significance
    }
}

// copy constructor
BigInt::BigInt(BigInt& that)
{
    num.resize(that.length());
    sign = that.sign;
    for(int i=0; i<that.length();i++){
        num[i] = that.num[i];
    }
}

// test passed
const char* BigInt::to_string(){
    int size = this->length();
    char* str;
    int offset;
    if(sign==NEGATIVE){
        str = new char[size + 1];   
        str[0] = '-';   // one extra char for the sign
        offset = 1;
    }
    else{
        str = new char[size];   
        offset = 0;
    }
     
    for(int i = 0;i<size;i++){
        str[size-i-1 + offset] = num[i] + '0';
    }
    return str;
}

// compare two BigInt object
int BigInt::compare_to(BigInt &that)
{
    if(sign==POSITIVE&&that.sign==POSITIVE){
        if(this->length()>that.length())  return LARGER;
        else if(this->length()<that.length())   return SMALLER;
        else{
            for(int i=this->length()-1;i>=0;i--)
            {
                if(num[i]>that.num[i])  return LARGER;
                else if(num[i]<that.num[i]) return SMALLER;
            }
            return EQUAL;
        }
    }
    else if(sign==POSITIVE&&that.sign==NEGATIVE){
        return LARGER;
    }
    else if(sign==NEGATIVE&&that.sign==POSITIVE){
        return SMALLER;
    }
    else{
        BigInt absa(num);   // get absolute value
        BigInt absb(that.num);
        return -(absa.compare_to(absb));    // call positive compare
    }

}

void BigInt::set_sign(int sign_){
    sign = sign_;
}


// overload + 
BigInt& BigInt::operator+(BigInt & that)
{



}


int main()
{
    char* str = new char[MAXSIZE];
    // scanf("%s", str);
    // int size = strlen(str);
    // BigInt test(str);
    // for(int i=0;i<test.length();i++){
    //     cout<<test[i]<<endl;
    // } 
    // printf("string=%s\n", test.to_string());

    BigInt n1("1234");
    BigInt n2("1235");
    BigInt n3("1234");

    printf("%s compare with %s = %d\n", n1.to_string(), n2.to_string(), n1.compare_to(n2));
    printf("%s compare with %s = %d\n", n2.to_string(), n1.to_string(), n2.compare_to(n1));
    n1.set_sign(NEGATIVE);
    n3.set_sign(NEGATIVE);
    printf("%s compare with %s = %d\n", n2.to_string(), n1.to_string(), n2.compare_to(n1));
    printf("%s compare with %s = %d\n", n1.to_string(), n3.to_string(), n3.compare_to(n1));

    BigInt n4("12345");
    printf("%s compare with %s = %d\n", n4.to_string(), n2.to_string(), n4.compare_to(n2));
    n4.set_sign(NEGATIVE);
    printf("%s compare with %s = %d\n", n4.to_string(), n2.to_string(), n4.compare_to(n2));




    // vector<int> v(10);
    
    // for(int i=0;i<10;i++){
    //     v[i] = i;
    // }
    // BigInt t(v);
    // t.set_sign(NEGATIVE);
    // printf("t=%s\n", t.to_string());

    // BigInt t;
    // printf("size=%d\n", t.length());

    // scanf("%ld\n%c\n%ld", &a, &op, &b);
    // // scanf("\n", &op);
    // // scanf("", &b);
    // if(op=='+') printf("%ld", a+b);
    // else if(op=='-') printf("%ld", a-b);
    // else if(op=='*') printf("%ld", a*b);
    // else printf("%ld", a/b);
}