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

class BigInt
{

private:
    vector<int> num;
    int sign; //

public:
    BigInt() : num(0), sign(POSITIVE) {} // default constructor
    BigInt(vector<int> digits);          // construct from a digits vector
    BigInt(const char *str);             // init with a string
    BigInt(BigInt &that);                // copy constructor
    // ~BigInt();  // destructor
    int compare_to(BigInt &that);    // compare two number
    void set_sign(int sign_);
    BigInt &operator+(BigInt &that); // overload +
    BigInt &operator-(BigInt &that);
    // BigInt& operator *(BigInt& that);
    // BigInt& operator /(BigInt& that);
    const char *to_string();
    int length()
    {
        return num.size();
    }
    int &operator[](int idx)
    {
        return num[idx];
    }
};

// TEST passed!
BigInt::BigInt(vector<int> digits) : num(digits.size())
{
    sign = POSITIVE; // by default positive
    for (unsigned int i = 0; i < digits.size(); i++)
    {
        num[i] = digits[i];
    }
}

// construct the int array from given string
BigInt::BigInt(const char *str)
{
    int size = strlen(str);
    sign = POSITIVE;  // by default positive
    num.resize(size); // constructor a vector with length of the str length
    for (int i = 0; i < size; i++)
    {
        num[i] = str[size - i - 1] - '0'; // lower index means lower significance
    }
}

// copy constructor
BigInt::BigInt(BigInt &that)
{
    num.resize(that.length());
    sign = that.sign;
    for (int i = 0; i < that.length(); i++)
    {
        num[i] = that.num[i];
    }
}

// test passed
const char *BigInt::to_string()
{
    int size = this->length();
    char *str;
    int offset;
    if (sign == NEGATIVE)
    {
        str = new char[size + 1];
        str[0] = '-'; // one extra char for the sign
        offset = 1;
    }
    else
    {
        str = new char[size];
        offset = 0;
    }

    for (int i = 0; i < size; i++)
    {
        str[size - i - 1 + offset] = num[i] + '0';
    }
    return str;
}

// compare two BigInt object
int BigInt::compare_to(BigInt &that)
{
    if (sign == POSITIVE && that.sign == POSITIVE)
    {
        if (this->length() > that.length())
            return LARGER;
        else if (this->length() < that.length())
            return SMALLER;
        else
        {
            for (int i = this->length() - 1; i >= 0; i--)
            {
                if (num[i] > that.num[i])
                    return LARGER;
                else if (num[i] < that.num[i])
                    return SMALLER;
            }
            return EQUAL;
        }
    }
    else if (sign == POSITIVE && that.sign == NEGATIVE)
    {
        return LARGER;
    }
    else if (sign == NEGATIVE && that.sign == POSITIVE)
    {
        return SMALLER;
    }
    else
    {
        BigInt absa(num); // get absolute value
        BigInt absb(that.num);
        return -(absa.compare_to(absb)); // call positive compare
    }
}

void BigInt::set_sign(int sign_)
{
    sign = sign_;
}

// overload +
BigInt &BigInt::operator+(BigInt &that)
{
    if(that.sign==NEGATIVE){
        // add a negative number
        BigInt abs(that.num);
        return operator-(abs);
    }
    else if(sign==NEGATIVE){
        BigInt abs(num);    // the number itself is negative
        return that.operator-(abs); 
    }
    else{
        // both are positive
        int N;  // choose the longest size
        if(num.size()>that.num.size()){
            N = num.size();
            that.num.resize(N);
            for(int i=that.num.size();i<N;i++){
                that.num[i] = 0;       
            }
        }
        else{
            N = that.num.size();
            num.resize(N);
            for(int i=num.size();i<N;i++){
                num[i] = 0;
            }
        }
        vector<int> carry(N+1);
        vector<int> result(N+1);
        carry[0] = 0;
        for(int i=0;i<N;i++){
            int t = num[i]+that.num[i]+carry[i];
            if(t < 10){
                result[i] = t;
            }
            else{
                result[i] = t%10;
                carry[i+1] = t/10;
            }
        }
        result[N] = carry[N];
        if(result[N]<=0)    result.resize(N);
        BigInt* result_int = new BigInt(result);
        return *result_int;
    }
}

//overload -
BigInt & BigInt::operator-(BigInt &that)
{
    if(that.sign==NEGATIVE){
        BigInt abs_that(that.num);
        return operator+(abs_that);
    }

    if(this->compare_to(that)==SMALLER){
        // if smaller, return negative result of the abs
        BigInt* oppsite = new BigInt(that.operator-(*this));
        oppsite->set_sign(NEGATIVE);
        return *oppsite;
    }
    else if(this->compare_to(that)==EQUAL){
        BigInt* zero = new BigInt("0");
        return *zero;
    }
    else{
        // if larger, perform subtract operation
        int N = (int)num.size();       // the length of the minute
        vector<int> borrow(N);     //the borrow array
        vector<int> result(N); // the result array
        if((int)that.num.size()<N){
            that.num.resize(N);     // increase to the same length
            for(int i=that.num.size(); i<N;i++) that.num[i] = 0;    // init higher digits to zero
        }   
        borrow[0] = 0;
        for(int i=0;i<N;i++){
            if(num[i]>=that.num[i]+borrow[i]){
                result[i] = num[i] - that.num[i] - borrow[i];
            }
            else{
                result[i] = 10 + num[i] - that.num[i] - borrow[i];
                borrow[i+1] = 1;
            }
            
        }
        BigInt* result_int = new BigInt(result);
        return *result_int;
    }

}

void test_plusminus()
{
    BigInt n1("54321");
    BigInt n2("1234");
    BigInt result;

    result = n1 - n2;
    printf("%s-%s=%s\n", n1.to_string(), n2.to_string(), result.to_string());

    BigInt n3("12345");
    BigInt n4("234567");
    result = n3 - n4;
    printf("%s-%s=%s\n", n3.to_string(), n4.to_string(), result.to_string());

    BigInt n5("12345");
    BigInt n6("234567");
    n6.set_sign(NEGATIVE);
    result = n5 - n6;
    printf("%s-%s=%s\n", n5.to_string(), n6.to_string(), result.to_string());

    BigInt n7("12345");
    BigInt n8("12345");
    result = n7 - n8;
    printf("%s-%s=%s\n", n7.to_string(), n8.to_string(), result.to_string());

    BigInt n9("12000");
    BigInt n10("12345");
    result = n9 + n10;
    printf("two positive numbers addition: %s+%s=%s\n", n9.to_string(), n10.to_string(), result.to_string());

    n10.set_sign(NEGATIVE);
    result = n9 + n10;
    printf("positive pluse negative numbers: %s+%s=%s\n", n9.to_string(), n10.to_string(), result.to_string());

    n9.set_sign(NEGATIVE);
    result = n9 + n10;
    printf("two negative numbers addition: %s+%s=%s\n", n9.to_string(), n10.to_string(), result.to_string());

    n10.set_sign(POSITIVE);
    result = n9 + n10;
    printf("negative plus positive numbers: %s+%s=%s\n", n9.to_string(), n10.to_string(), result.to_string());


}

void test_compare()
{
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
}

void test_tostring()
{
    vector<int> v(10);

    for (int i = 0; i < 10; i++)
    {
        v[i] = i;
    }
    BigInt t(v);
    t.set_sign(NEGATIVE);
    printf("t=%s\n", t.to_string());
}

void test_constructor()
{
    char *str = new char[MAXSIZE];
    scanf("%s", str);
    // int size = strlen(str);
    BigInt test(str);
    for (int i = 0; i < test.length(); i++)
    {
        cout << test[i] << endl;
    }
    printf("string=%s\n", test.to_string());
}

int main()
{
    // char *str = new char[MAXSIZE];
    // scanf("%s", str);
    // int size = strlen(str);
    // BigInt test(str);
    // for(int i=0;i<test.length();i++){
    //     cout<<test[i]<<endl;
    // }
    // printf("string=%s\n", test.to_string());

    // test_compare();
    test_plusminus();

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