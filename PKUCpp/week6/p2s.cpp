public: 
    // do not forget to declare the dectructor as virtual function. Only in this way, when a
    // pointer is declared as base class and assigned derived object reference, the derived destructor 
    // will be called upon deletion.
        virtual ~A(){
            cout << "destructor A" << endl; 
        }