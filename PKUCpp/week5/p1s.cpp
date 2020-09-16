class MyString:public string{
    public:
        MyString():string(){}
        MyString(const string str_): string(str_){}
        MyString(const char * str_):string(str_){}
        string operator()(int start, int len){
            return string::substr(start, len);
        }
        


};