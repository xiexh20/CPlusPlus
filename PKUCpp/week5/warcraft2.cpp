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
#define INIT_SIZE 0
#define NUM_BUF_SIZE 10     // the size for the char buffer to print numbers

#define SWORD 0
#define BOMB 1
#define ARROW 2

// some global variables
int red_strength = 10;
int blue_strength = 20;

// first declare all classes
class Tribe;
class Warrier;

// some helper functions
const char* decode_wtype(int wtype);
const char* decode_weapon(int wid);



// the base class
class Warrier{
    public:
        Warrier(int id_, int strength_):id(id_), strength(strength_){ red_strength -= strength_;}  // constructor
        virtual string born_msg();  // the message when this warrier is born, polymorphism can be achieved by using virtual keyword
        virtual string born_extramsg(){} // extra message, should be overloaded by derived classes
    
    protected:
        int id; // the id of this warrier
        int strength;   // 
        // int attack;     // for later


};

// warriers derived from base class
class Dragon:public Warrier{
    public:
        static int ph_cost; // this will be changed for each subtypes accordingly
        Dragon(int id_, int strength_, float morale_):Warrier(id_, strength_), morale(morale_), weapon(id_%3){}
        string born_msg(){
            string name("dragon ");
            return name + Warrier::born_msg();
        }
        string born_extramsg(){
            string msg1("It has a "), w(decode_weapon(weapon)), msg2(",and it's morale is ");
            char char_morale[NUM_BUF_SIZE];
            snprintf(char_morale, NUM_BUF_SIZE, "%.2f", morale);   // should give at least 6 chars to make sure enough to print xx.xx
            string str_morale(char_morale);
            return msg1 + w + msg2 +str_morale;
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
        static int ph_cost; // this will be changed for each subtypes accordingly
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
        static int ph_cost; // this will be changed for each subtypes accordingly
        Iceman(int id_, int strength_):Warrier(id_, strength_), weapon(id_%3){}
        string born_msg(){
            string name("iceman ");
            return name + Warrier::born_msg();
        }
        string born_extramsg(){
            string msg("It has a "), w(decode_weapon(weapon));
            return msg + w;
        }

};

class Lion:public Warrier{
    private:
        int loyalty; 
    
    public:
        static int ph_cost; // this will be changed for each subtypes accordingly    
        Lion(int id_, int strength_, int loyalty_):Warrier(id_, strength_), loyalty(loyalty_){}
        string born_msg(){
            string name("lion ");
            return name + Warrier::born_msg();
        }
        string born_extramsg(){
            string msg("It's loyalty is ");
            char char_loyalty[NUM_BUF_SIZE];
            snprintf(char_loyalty, NUM_BUF_SIZE, "%d", loyalty);
            string str_loyalty(char_loyalty);
            return msg+str_loyalty;
        }

};

class Wolf:public Warrier{
    //currently no extra atrributes
    public:
        static int ph_cost; // this will be changed for each subtypes accordingly
        Wolf(int id_, int strength_):Warrier(id_, strength_){}
        string born_extramsg(){ 
            string empty("NULL");
            return empty;
        }
        string born_msg(){
            string name("wolf ");
            return name + Warrier::born_msg();
        }
};

// static variables
int Dragon::ph_cost = 3;
int Ninja::ph_cost = 4;
int Iceman::ph_cost = 5;
int Lion::ph_cost = 6;
int Wolf::ph_cost = 7;


class Tribe{
    private:
        int aid;    // auto increment id
        int strength;  // remained strength of this tribe
        string name;
        vector<vector<Warrier* > > warriers;
    
    public:
        int nextw;   // next type of warrier to be produced
        int ptries;  // number of attempts to produce a warrier, after 5 failure, stop production and print stop message
        
        Tribe(int strength_, const char* name_):strength(strength_), aid(0), name(name_){
            vector<vector<Warrier* > > temp(TOTAL_TYPES, vector<Warrier* >(INIT_SIZE));
            warriers = temp;
            ptries = 0;
            nextw = 0;  // start from zero
        }  // constructor
        int get_strength(){return strength;}
        string get_name(){return name;}
        // produce a warrier given specific type, return the pointer to the warrier, or NULL if not possible
        bool produce(int t, int wtype);
        string wcount_msg(int wtype);   // return n [warrier_type] in [name] headquarter
        
};
/* functions for class Tribe::START */
bool Tribe::produce(int t, int wtype)
{
    Warrier * w;
    // assign pointers to w based on the type
    if(wtype==DRAGON_IDX){
        if(strength<Dragon::ph_cost)   return false;
        aid++;
        strength -= Dragon::ph_cost;
        w = new Dragon(aid, Dragon::ph_cost, 1.0*strength/Dragon::ph_cost);
    }
    else if(wtype==NINJA_IDX){
        if(strength<Ninja::ph_cost) return false;
        aid++;
        strength -= Ninja::ph_cost;
        w = new Ninja(aid, Ninja::ph_cost);
    }
    else if(wtype==ICEMAN_IDX){
        if(strength<Iceman::ph_cost) return false;
        aid++;
        strength -= Iceman::ph_cost;
        w = new Iceman(aid, Iceman::ph_cost);
    }
    else if(wtype==LION_IDX){
        if(strength<Lion::ph_cost) return false;
        aid++;
        strength -= Lion::ph_cost;
        w = new Lion(aid, Lion::ph_cost, strength);
    }
    else if(wtype==WOLF_IDX){
        if(strength<Wolf::ph_cost) return false;
        aid++;
        strength -= Wolf::ph_cost;
        w = new Wolf(aid, Wolf::ph_cost);

    }

    // successfully produced one warrier
    ptries = 0;
    nextw++;
    if(nextw==TOTAL_TYPES)  nextw = 0;

    warriers[wtype].push_back(w);   // add newly created warrier to the container

    // print out event message
    printf("%03d %s %s%s\n", t, name.c_str(), warriers[wtype].back()->born_msg().c_str(), wcount_msg(wtype).c_str());
    // cout<< name <<" " <<warriers[wtype].back()->born_msg()<<wcount_msg(wtype)<<endl; // remember to call .back() function to get the newly added warrier
    string msg = warriers[wtype].back()->born_extramsg();
    if(msg.compare("NULL")!=0){
        printf("%s\n", msg.c_str());
        // cout<<msg<<endl;
    }
    
    return true;
    
}

const char* decode_wtype(int wtype)
{
    switch (wtype)
    {
    case DRAGON_IDX: return "dragon";
    case NINJA_IDX: return "ninja";
    case ICEMAN_IDX: return "iceman";
    case LION_IDX: return "lion";
    case WOLF_IDX: return "wolf";
    default:    return NULL;
    }
}

// return n [warrier_type] in [name] headquarter
string Tribe::wcount_msg(int wtype)
{
    int n = warriers[wtype].size();
    char char_n[NUM_BUF_SIZE];
    snprintf(char_n, NUM_BUF_SIZE, "%d ", n);
    string str_n(char_n), in(" in "), hq(" headquarter"), w(decode_wtype(wtype));
    return str_n + w + in + get_name() + hq;
    
}
/* functions for class Tribe::END */



/* functions for class Warrier::START */
string Warrier::born_msg()
{
    string born(" born with strength ");
    char char_id[NUM_BUF_SIZE], char_stren[NUM_BUF_SIZE];
    snprintf(char_id, NUM_BUF_SIZE, "%d", id);
    snprintf(char_stren, NUM_BUF_SIZE, "%d,", strength);
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
    int red_worder[TOTAL_TYPES] = {ICEMAN_IDX, LION_IDX, WOLF_IDX, NINJA_IDX, DRAGON_IDX};
    int blue_worder[TOTAL_TYPES] = {LION_IDX, DRAGON_IDX, NINJA_IDX, ICEMAN_IDX, WOLF_IDX};

    int tests;
    scanf("%d", &tests);
    
    for(int test=0;test<tests;test++){
        int total_ph;
        scanf("%d", &total_ph);
        scanf("%d %d %d %d %d", &Dragon::ph_cost, &Ninja::ph_cost, &Iceman::ph_cost, &Lion::ph_cost, &Wolf::ph_cost);
        
        Tribe red(total_ph, "red");
        Tribe blue(total_ph, "blue");
        int t = 0;
        printf("Case:%d\n", test+1);
        while(red.ptries<TOTAL_TYPES||blue.ptries<TOTAL_TYPES){
            while(red.ptries<TOTAL_TYPES){
                bool status = red.produce(t, red_worder[red.nextw]);    // try to produce a warrier
                if(status)  break;  // successful
                else{
                    // unsucessful
                    red.ptries++;
                    if(red.ptries==TOTAL_TYPES) printf("%03d red headquarter stops making warriors\n", t);
                    red.nextw++;
                    if(red.nextw==TOTAL_TYPES)  red.nextw = 0;
                }
            }

            while(blue.ptries<TOTAL_TYPES){
                bool status = blue.produce(t, blue_worder[blue.nextw]);    // try to produce a warrier
                if(status)  break;  // successful
                else{
                    // unsucessful
                    blue.ptries++;
                    if(blue.ptries==TOTAL_TYPES) printf("%03d blue headquarter stops making warriors\n", t);
                    blue.nextw++;
                    if(blue.nextw==TOTAL_TYPES)  blue.nextw = 0;
                }
            }

            t++;

        }
    }
    

    return 0;

}