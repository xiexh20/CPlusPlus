#include<iostream>
#include <stdio.h>
#include <vector>
#include <string>
using namespace std;

// the base class
class Warrier{
    public:
        static int ph_cost; // this will be changed for each subtypes accordingly
        Warrier(int id_, int strength_):id(id_), strength(strength_){}  // constructor
        string born_msg();  // the message when this warrier is born
        string born_extramsg(); // extra message 
    
    protected:
        int id; // the id of this warrier
        int strength;   // 
        // int attack;     // for later


};
int Warrier::ph_cost = 0;   // init the ph cost, but will be changed in cin

string Warrier::born_msg()
{
    string born(" born with strength ");
    char char_id[5], char_stren[5];
    snprintf(char_id, 5, "%d", id);
    snprintf(char_stren, 5, "%d,", strength);
    string str_id(char_id), str_stren(char_stren);
    return str_id + born + str_stren;

}

// warriers derived from base class
class Dragon:public Warrier{
    public:
        Dragon(int id_, int strength_):Warrier(id_, strength_){}
        string born_msg(){
            string name("dragon ");
            return name + Warrier::born_msg();
        }
        string born_extramsg(); // extra message 

    private:
        int weapon;     // the weapon number is id%3
        float spirit;   //

};

class Ninja:public Warrier{
    private:
        int weapon1;    // id%3
        int weapon2;    // (id+1)%3
};

class Iceman:public Warrier{
    private:
        int weapon;

};

class Lion:public Warrier{
    private:
        int loyalty; 

};

class Wolf:public Warrier{
    //currently no extra atrributes
};



int main()
{
    cout<<Wolf::Warrier::ph_cost<<endl;

    Wolf::Warrier::ph_cost = 10;
    cout<<Wolf::Warrier::ph_cost<<endl;
    
    Dragon d(0, 10), d1(2, 20);
    cout<<d.born_msg()<<endl;
    cout<<d1.born_msg()<<endl;

    return 0;

}