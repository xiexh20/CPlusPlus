class Array2{
    private:
        int **data;
        int row;    // number of rows
        int col;    // number of columns
    
    public:
        Array2(){
            row = 0;
            col = 0;
            data = NULL;
        }
        Array2(int rcount, int colcount){
            data = new int*[rcount];
            for(int i=0;i<rcount;i++){
                data[i] = new int[colcount];
            }
            row = rcount;
            col = colcount;
        }
        Array2& operator =(const Array2 &a){    // for operator: a=b
            // deep copy
            if(data==a.data){
                return *this;   // avoid error when a=a
            }
            if(a.data==NULL){
                if(data){
                    for(int i=0;i<row;i++)  delete[] data[i];
                }   
                data = NULL;
                row = 0;
                col = 0;
                return *this;
            }

            if(col<a.col||row<a.row){
                // if the size is not big enough, increase the size
                if(data){
                    for(int i=0;i<row;i++)  delete[] data[i];
                }
                // printf("Allocate new memory block\n");
                data = new int*[a.row];
                for(int i=0;i<a.row;i++)    data[i] = new int[a.col];
            }
            for(int i=0;i<a.row;i++){
                memcpy(data[i], a.data[i], sizeof(int)*a.col);
            }
            row = a.row;
            col = a.col;
            return *this;
        }
        ~Array2(){
            // destructor
            if(data){
                for(int i=0;i<row;i++)  delete[] data[i];
            }   
            data = NULL;
            row = 0;
            col = 0;
        }
        // to support a(x, y) = number
        int& operator()(int x, int y){
            return data[x][y];
        }

        // to support a[x][y] = number, actually, this function only overload a[], the rest is done by overloading of int*[]
        int* operator[](int x){
            return data[x];
        }

};