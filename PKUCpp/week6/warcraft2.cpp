#include<iostream>
#include <stdio.h>
#include <vector>
#include <string>
using namespace std;

#define ICEMAN_IDX 0
#define LION_IDX 1
#define WOLF_IDX 2
#define NINJA_IDX 3
#define DRAGON_IDX 4
#define TOTAL_TYPES 5
#define INIT_VOLUMNE 5

#define SWORD 0
#define BOMB 1
#define ARROW 2

// some global variables
int red_strength = 10;
int blue_strength = 20;

// first declare all classes
class Tribe;
class Warrier;



// the base class
class Warrier{
    public:
        static int ph_cost; // this will be changed for each subtypes accordingly
        Warrier(int id_, int strength_):id(id_), strength(strength_){ red_strength -= strength_;}  // constructor
        string born_msg();  // the message when this warrier is born
        string born_extramsg(){return NULL;} // extra message, should be overloaded by derived classes
    
    protected:
        int id; // the id of this warrier
        int strength;   // 
        // int attack;     // for later


};
int Warrier::ph_cost = 0;   // init the ph cost, but will be changed in cin

// warriers derived from base class
class Dragon:public Warrier{
    public:
        Dragon(int id_, int strength_, float morale_):Warrier(id_, strength_), morale(morale_), weapon(id_%3){}
        string born_msg(){
            string name("dragon ");
            return name + Warrier::born_msg();
        }
        string born_extramsg(){
            string msg("It has a arrow,and it's morale is ");
            char char_morale[5];
            snprintf(char_morale, 5, "%.2f", morale);
            string str_morale(char_morale);
            return msg+str_morale;
        }

    private:
        int weapon;     // the weapon number is id%3
        float morale;   //

};

class Ninja:public Warrier{
    private:
        int weapon1;    // id%3
        int weapon2;    // (id+1)%3
    
    public:
        Ninja(int id_, int strength_):Warrier(id_, strength_){
            weapon1 = id%3;
            weapon2 = (id+1)%3;
        }
        string born_msg(){
            string name("ninja ");
            return name + Warrier::born_msg();
        }
        string born_extramsg(); // TODO: print message based on weapon type 
};

class Iceman:public Warrier{
    private:
        int weapon;

    public:
        Iceman(int id_, int strength_):Warrier(id_, strength_), weapon(id_%3){}
        string born_msg(){
            string name("iceman ");
            return name + Warrier::born_msg();
        }
        string born_extramsg(){
            string msg("It has a sword");
            return msg;
        }

};

class Lion:public Warrier{
    private:
        int loyalty; 
    
    public:
        Lion(int id_, int strength_, int loyalty_):Warrier(id_, strength_), loyalty(loyalty_){}
        string born_msg(){
            string name("lion ");
            return name + Warrier::born_msg();
        }
        string born_extramsg(){
            string msg("It's loyalty is ");
            char char_loyalty[5];
            snprintf(char_loyalty, 5, "%d", loyalty);
            string str_loyalty(char_loyalty);
            return msg+str_loyalty;
        }

};

class Wolf:public Warrier{
    //currently no extra atrributes
    public:
        Wolf(int id_, int strength_):Warrier(id_, strength_){}
};


class Tribe{
    private:
        int aid;    // auto increment id
        int strength;  // remained strength of this tribe
        string name;
        vector<vector<Warrier* > > warriers;
    
    public:
        Tribe(int strength_, const char* name_):strength(strength_), aid(0), name(name_){
            vector<vector<Warrier* > > temp(TOTAL_TYPES, vector<Warrier* >(INIT_VOLUMNE));
            warriers = temp;
        }  // constructor
        int get_strength(){return strength;}
        string get_name(){return name;}
        // produce a warrier given specific type, return the pointer to the warrier, or NULL if not possible
        Warrier* produce(int wtype);
};
/* functions for class Tribe::START */
Warrier* Tribe::produce(int wtype)
{
    Warrier * w;
    w = new Dragon(1, 20, 0.5);
    warriers[0].push_back(w);
    cout<<warriers[0].back()->born_msg()<<endl; // remember to call .back() function to get the newly added warrier
}
/* functions for class Tribe::END */



/* functions for class Warrier::START */
string Warrier::born_msg()
{
    string born(" born with strength ");
    char char_id[5], char_stren[5];
    snprintf(char_id, 5, "%d", id);
    snprintf(char_stren, 5, "%d,", strength);
    string str_id(char_id), str_stren(char_stren);
    return str_id + born + str_stren;

}
/* functions for class Warrier::END */


/* functions for class Dragon::START */

/* functions for class Dragon::END */


/* functions for class Ninja::START */
const char* decode_weapon(int wid)
{
    if(wid==SWORD)  return "sword";
    else if(wid==BOMB) return "bomb";
    else    return "arrow";
}
string Ninja::born_extramsg()
{
    string w1(decode_weapon(weapon1)), w2(decode_weapon(weapon2));
    string msg1("It has a "), msg2(" and a ");
    return msg1 + w1 + msg2 + w2;
}

/* functions for class Ninja::END */


/* functions for class Iceman::START */

/* functions for class Iceman::END */


/* functions for class Lion::START */

/* functions for class Lion::END */


/* functions for class Wolf::START */

/* functions for class Wolf::END */


int main()
{
    cout<<Wolf::Warrier::ph_cost<<endl;

    Wolf::Warrier::ph_cost = 10;
    Dragon::Warrier::ph_cost = 3;
    cout<<Wolf::Warrier::ph_cost<<endl;
    
    // Dragon d(0, 2), d1(2, 2);
    // cout<<d.born_msg()<<endl;
    // cout<<d.born_extramsg()<<endl;
    // cout<<d1.born_msg()<<endl;
    // cout<<d1.born_extramsg()<<endl;

    Tribe red(100, "red");
    red.produce(0);

    return 0;

}