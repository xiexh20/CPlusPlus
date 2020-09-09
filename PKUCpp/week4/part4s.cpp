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
    int compare_to(BigInt &that); // compare two number
    void set_sign(int sign_);
    BigInt &operator+(BigInt &that); // overload +
    BigInt &operator-(BigInt &that);
    BigInt &operator*(BigInt &that); // overload multiplication
    // BigInt& operator /(BigInt& that);
    const char *to_string();
    // return the actual length of the integer
    int length()
    {
        for (int startidx = num.size(); startidx > 0; startidx--)
        {
            if (num[startidx - 1] > 0)
                return startidx;
        }

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

    // truncate leading zeros
    int startidx;
    for (startidx = size - 1; startidx >= 0; startidx--)
        if (num[startidx] > 0)
            break;

    for (int i = 0; i <= startidx; i++)
    {
        str[startidx - i + offset] = num[i] + '0';
    }
    str[startidx + offset + 1] = '\0'; // explicitly set the ending of the sequence
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
    if (that.sign == NEGATIVE)
    {
        // add a negative number
        BigInt abs(that.num);
        return operator-(abs);
    }
    else if (sign == NEGATIVE)
    {
        BigInt abs(num); // the number itself is negative
        return that.operator-(abs);
    }
    else
    {
        // both are positive
        int N; // choose the longest size
        if (num.size() > that.num.size())
        {
            N = num.size();
            that.num.resize(N);
            for (int i = that.num.size(); i < N; i++)
            {
                that.num[i] = 0;
            }
        }
        else
        {
            N = that.num.size();
            num.resize(N);
            for (int i = num.size(); i < N; i++)
            {
                num[i] = 0;
            }
        }
        vector<int> carry(N + 1);
        vector<int> result(N + 1);
        carry[0] = 0;
        for (int i = 0; i < N; i++)
        {
            int t = num[i] + that.num[i] + carry[i];
            if (t < 10)
            {
                result[i] = t;
            }
            else
            {
                result[i] = t % 10;
                carry[i + 1] = t / 10;
            }
        }
        result[N] = carry[N];
        BigInt *result_int = new BigInt(result);
        return *result_int;
    }
}

//overload -
BigInt &BigInt::operator-(BigInt &that)
{
    if (that.sign == NEGATIVE)
    {
        BigInt abs_that(that.num);
        return operator+(abs_that);
    }

    if (this->compare_to(that) == SMALLER)
    {
        // if smaller, return negative result of the abs
        BigInt *oppsite = new BigInt(that.operator-(*this));
        oppsite->set_sign(NEGATIVE);
        return *oppsite;
    }
    else if (this->compare_to(that) == EQUAL)
    {
        BigInt *zero = new BigInt("0");
        return *zero;
    }
    else
    {
        // if larger, perform subtract operation
        int N = (int)num.size(); // the length of the minute
        vector<int> borrow(N);   //the borrow array
        vector<int> result(N);   // the result array
        if ((int)that.num.size() < N)
        {
            that.num.resize(N); // increase to the same length
            for (int i = that.num.size(); i < N; i++)
                that.num[i] = 0; // init higher digits to zero
        }
        borrow[0] = 0;
        for (int i = 0; i < N; i++)
        {
            if (num[i] >= that.num[i] + borrow[i])
            {
                result[i] = num[i] - that.num[i] - borrow[i];
            }
            else
            {
                result[i] = 10 + num[i] - that.num[i] - borrow[i];
                borrow[i + 1] = 1;
            }
        }

        BigInt *result_int = new BigInt(result);
        return *result_int;
    }
}

// overload multiplication
BigInt &BigInt::operator*(BigInt &that)
{
    int sizea = length();
    int sizeb = that.length();
    int result_size = sizea + sizeb;
    int factor_size;
    vector<int> A, B; // A is the longer one while B is the short one
    if (sizea >= sizeb)
    {
        A = num;
        B = that.num;
        factor_size = sizeb;
    }
    else
    {
        A = that.num;
        B = num;
        factor_size = sizea;
    }
    vector<vector<int> > temp(factor_size, vector<int>(result_size)); //store intermediate results;
    BigInt* result = new BigInt("0");                                                  // init sum to zero
    for (int i = 0; i < factor_size; i++)
    {
        // for each digit, perform multiplication
        vector<int> carry(result_size);
        carry[i] = 0; // set the initial carry number
        for (int j = 0; j < A.size(); j++)
        {
            int product = B[i] * A[j] + carry[i + j]; // the product, do not foget the i offset
            carry[i + j + 1] = product / 10;
            temp[i][j + i] = product % 10; // do not forget the i shift
        }
        // also add the carry number
        temp[i][A.size()+i] = carry[i+A.size()];
        BigInt tempr(temp[i]); // temp result
        *result = *result + tempr;
    }
    if((sign==POSITIVE&&that.sign==POSITIVE)||(sign==NEGATIVE&&that.sign==NEGATIVE)){
        result->set_sign(POSITIVE);
    }
    else{
        result->set_sign(NEGATIVE);
    }
    
    return *result;
}

void test_multiply()
{
    BigInt n1("123");
    BigInt n2("12");
    BigInt result;

    result = n1*n2;
    printf("positive times positive: %s*%s=%s\n", n1.to_string(), n2.to_string(), result.to_string());

    n1.set_sign(NEGATIVE);
    result = n1*n2;
    printf("negative times positive: %s*%s=%s\n", n1.to_string(), n2.to_string(), result.to_string());

    printf("\n another pair of number:\n");
    BigInt n3("4567");
    BigInt n4("9999");
    result = n3*n4;
    printf("%s*%s=%s\n", n3.to_string(), n4.to_string(), result.to_string());

    printf("\n another pair of number:\n");
    BigInt n5("999999999999");
    BigInt n6("999999999999");
    n5.set_sign(NEGATIVE);
    n6.set_sign(NEGATIVE);
    result = n5*n6;
    printf("%s*%s=%s\n", n5.to_string(), n6.to_string(), result.to_string());
}

void test_vector()
{
    vector<int> va(5);
    for (int i = 0; i < 5; i++)
    {
        va[i] = i;
    }
    vector<int> vb = va;
    for (int i = 0; i < 5; i++)
    {
        cout << vb[i] << endl;
    }

    for (int i = 0; i < 5; i++)
    {
        va[i] = i + 3;
    }

    // for (int i = 0; i < 5; i++)
    // {
    //     cout << vb[i] << endl;
    // }

    vector<vector<int> > t2(5, vector<int>(3));
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("i=%d, j=%d, value=%d\n", i, j, t2[i][j]);
        }
    }
}

void test_plusminus()
{
    BigInt n1("123456789012345678901234567890123456789012345678901234567890");
    BigInt n2("1234");
    BigInt result;

    result = n1 - n2;
    printf("positive minus positive, result positive:%s-%s=%s\n", n1.to_string(), n2.to_string(), result.to_string());
    result = n2 - n1;
    printf("positive minus positive, result negative:%s-%s=%s\n", n2.to_string(), n1.to_string(), result.to_string());
    n1.set_sign(NEGATIVE);
    result = n2 - n1;
    printf("positive minus negative, result positive:%s-%s=%s\n", n2.to_string(), n1.to_string(), result.to_string());
    n2.set_sign(NEGATIVE);
    result = n2 - n1;
    printf("negative minus negative, result positive:%s-%s=%s\n", n2.to_string(), n1.to_string(), result.to_string());

    BigInt n9("1234567890123456789012345678901234567890");
    BigInt n10("1234567890123456789012345678901234567891");
    result = n9 + n10;
    printf("two positive numbers addition: %s + \t\t%s = \t%s\n", n9.to_string(), n10.to_string(), result.to_string());

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
    // test_plusminus();

    // test_vector();
    test_multiply();

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