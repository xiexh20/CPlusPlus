#include <iostream>
using namespace std;
// 在此处补充你的代码

template<class T>
class CArray3D{

    class CArray{
        private:
        T * array1D;
        public:
        CArray(int d){
            array1D = new T[d];
        }
        T& operator[](int i){
            return array1D[i];
        }

    };


    class CArray2D{
        private:
            CArray ** array2D;  // use double pointer to init array of objects with parameterized constructors
        public:
            CArray2D(int d1, int d2){
                array2D = new CArray*[d1];
                for(int i=0;i<d1;i++){
                    array2D[i] = new CArray(d2);
                }
            }
            CArray& operator[](int i){
                return *array2D[i];
            }
    };
    public:
        CArray3D(int d1, int d2, int d3){
            array3D = new CArray2D*[d1];
            for(int i=0;i<d1;i++){
                array3D[i] = new CArray2D(d2, d3);
            }
        }
        CArray2D& operator[](int i){
            return *array3D[i]; // with the & sign, we can assign value using a[][][] = x
        }
    private:
        CArray2D ** array3D;

};

int main()
{
    CArray3D<int> a(3,4,5);
    int No = 0;
    for( int i = 0; i < 3; ++ i )
        for( int j = 0; j < 4; ++j )
            for( int k = 0; k < 5; ++k )
                a[i][j][k] = No++;
    for( int i = 0; i < 3; ++ i )
        for( int j = 0; j < 4; ++j )
            for( int k = 0; k < 5; ++k )
                cout << a[i][j][k] << ",";
    return 0;
}