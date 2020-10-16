#include <iostream>
#include <iomanip>  // in order to use setw
#include <string>
#include <string.h>
#include <stack>
#include <vector>
#include<cstring>
#include <stdio.h>
#include <cstdlib>  // for atoi()
using namespace std;

// define ID for each operation
#define COPY    0
#define ADD     1
#define FIND    2
#define RFIND   3
#define INSERT  4
#define RESET   5
#define PRINT   6
#define PRINTALL 7

#define MAX_LEN 500     // maximum length of an input string

int main()
{
    int opnum[] = {3, 2, 2, 2, 3, 2, 1, 0}; // required number of operands for each operation
    int opfound[] = {0,0,0, 0, 0, 0, 0, 0};
    int n;
    cin>>n;
    // cout<<"n="<<n<<endl;

    // read input strings
    string** strs = new string*[n+1];
    for(int i=0;i<=n;i++){
        char buf[MAX_LEN];
        cin.getline(buf, MAX_LEN);
        strs[i] = new string(buf);
    }

    // cout<<"input strings:"<<endl;
    // for(int i=1;i<=n;i++){
    //     cout<<*strs[i]<<":"<<strs[i]->length()<<endl;
    // }

    bool resume = true;
    do
    {
        char buffer[MAX_LEN];
        cin.getline(buffer, MAX_LEN);
        string command(buffer);
        if(command=="over"){
            resume = false;
        }
        else{
            resume = true;
            vector<string> args;
            stack<int> opstack; // operations stack
            stack<string> operands;
            int pos = command.find_first_of(' ');
            char * cut = strtok(buffer, " ");

            // int opfound = 0;
            while(cut!=NULL){
                // cout<<cut<<endl;
                string op(cut);

                // parse each individual arguments
                if(op=="copy")  {opstack.push(COPY);opfound[opstack.top()]=0;}
                else if(op=="add")  {opstack.push(ADD);opfound[opstack.top()]=0;}
                else if(op=="find") {opstack.push(FIND);opfound[opstack.top()]=0;}
                else if(op=="rfind") {opstack.push(RFIND);opfound[opstack.top()]=0;}
                else if(op=="insert")   {opstack.push(INSERT);opfound[opstack.top()]=0;}
                else if(op=="reset") {opstack.push(RESET);opfound[opstack.top()]=0;}
                else if(op=="print")   {opstack.push(PRINT);opfound[opstack.top()]=0;}
                else if(op=="printall") {opstack.push(PRINTALL);opfound[opstack.top()]=0;}
                else{
                    // this is an operand, push to another stack
                    operands.push(op);
                    // opfound++;
                    opfound[opstack.top()]++;   // the corresponding operands count increment
                }

                
                while(opstack.size()>=1&&opfound[opstack.top()]==opnum[opstack.top()]){
                // if(opfound[operation]==opnum[operation]){
                    opfound[opstack.top()] = 0;
                    int operation = opstack.top();
                    opstack.pop();  // do not forget to pop out the top element
                    // enough operands found for this operation, then perform it
                    if(operation==COPY){
                        // copy N X L
                        int L = atoi(operands.top().c_str());
                        operands.pop();
                        int X = atoi(operands.top().c_str());
                        operands.pop();
                        int N = atoi(operands.top().c_str());
                        operands.pop();
                        string temp = strs[N]->substr(X, L);
                        operands.push(temp);
                        opfound[opstack.top()]++; //next operation have one more operands
                    }
                    else if(operation==ADD){
                        // add S1 S2
                        int N1=-1, N2=-1;
                        string s2 = operands.top();
                        operands.pop();
                        string s1 = operands.top();
                        operands.pop();
                        
                        // check if s2 is a number
                        string::const_iterator it = s2.begin();
                        while(it!=s2.end()&&isdigit(*it)) it++;
                        if(it==s2.end()){
                            N2 = atoi(s2.c_str());
                        }
                        // check if s1 is a number
                        it = s1.begin();
                        while(it!=s1.end()&&isdigit(*it)) it++;
                        if(it==s1.end()){
                            N1 = atoi(s1.c_str());
                        }

                        if(N1>=0&&N2>=0){   // two numbers
                            int sum = N1 + N2;
                            char nbuf[10];
                            snprintf(nbuf, 10, "%d", sum);
                            string spos(nbuf);
                            operands.push(spos);
                        }
                        else{
                            string sum = s1 + s2;
                            operands.push(sum);
                        }
                        if(opstack.size()>=1){
                            opfound[opstack.top()]++;
                        }
                        
                    }
                    else if(operation==FIND){
                        // find S N
                        int N = atoi(operands.top().c_str());
                        operands.pop();
                        string S = operands.top();
                        operands.pop();

                        if(opstack.size()>=1){
                            int pos = strs[N]->find(S);
                            if(pos==string::npos){
                                pos = strs[N]->length();    
                            }
                            char nbuf[5];
                            snprintf(nbuf, 5, "%d", pos);
                            string spos(nbuf);
                            operands.push(spos);
                            if(opstack.size()>=1) opfound[opstack.top()]++;
                        }
                        
                    }
                    else if(operation==RFIND){
                        // rfind S N
                        int N = atoi(operands.top().c_str());
                        operands.pop();
                        string S = operands.top();
                        operands.pop();
                        
                        int pos = strs[N]->rfind(S);
                        if(pos==string::npos){
                            pos = strs[N]->length();    
                        }
                        char nbuf[5];
                        snprintf(nbuf, 5, "%d", pos);
                        string spos(nbuf);
                        if(opstack.size()>=1){
                            operands.push(spos);    // push returned value back to stack
                            opfound[opstack.top()]++;
                        }
                        

                    }
                    else if(operation==INSERT){
                        // insert S N X
                        int X = atoi(operands.top().c_str());
                        operands.pop();
                        int N = atoi(operands.top().c_str());
                        operands.pop();
                        *strs[N] = strs[N]->insert(X, operands.top().c_str());
                        operands.pop();
                        // operands.push(*strs[N]);
                    }
                    else if(operation==RESET){
                        // reset S N, set the N-th str to S
                        int N = atoi(operands.top().c_str());
                        operands.pop();
                        *(strs[N]) = operands.top();
                        operands.pop();
                        // operands.push(*strs[N]);
                    }
                    else if(operation==PRINT){
                        // print N
                        int N = atoi(operands.top().c_str());
                        operands.pop();
                        // operands.push(*strs[N]);
                        cout<<*strs[N]<<endl;
                    }
                    else if(operation==PRINTALL){
                        for(int i=1;i<=n;i++){
                            cout<<*strs[i]<<endl;
                        }

                    }


                }
                cut = strtok(NULL, " ");
            }
            stack<string> empty;
            operands = empty;
            // cout<<operands.top()<<endl;
            // operands.pop();
            // while(pos!=string::npos){
            //     args.push_back(command.substr(0, pos));
            //     command = command.substr(pos+1, command.length()-pos);
            //     pos = command.find_first_of(' ');
            // }
            // args.push_back(command);

            // cout<<"all commands:"<<endl;
            // for(int i=0;i<args.size();i++){
            //     cout<<args[i]<<endl;
            // }



        }



    } while (resume);
    
    return 0;
}