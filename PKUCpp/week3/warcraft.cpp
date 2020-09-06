#include<iostream>
using namespace std;

#define TOTAL_TYPES 5
#define NAME_LENGTH 5

#define SUCCESS 0
#define STOPPED -1

// define the id for different type of warriers
#define ICEMAN_IDX 0
#define LION_IDX 1
#define WOLF_IDX 2
#define NINJA_IDX 3
#define DRAGON_IDX 4



class Warrior{
    private:
        int id;
        int PH;
        int attack;
        char* type;
        static int PHcost[TOTAL_TYPES];
    public:
        static void set_PHcost(int newPH[]);   // set PH cost
        static int phcost(int type);        // get the PH cost of a certain warrior
};

// the static attributes must be initialized
int Warrior::PHcost[TOTAL_TYPES] = {0,0,0,0,0};

// get the PH cost of a certain type of warrior
int Warrior::phcost(int type){
    return Warrior::PHcost[type];
}

// set the ph cost to produce new warriers
void Warrior::set_PHcost(int newPH[]){
    int i;
    for(i=0; i<TOTAL_TYPES;i++){
        Warrior::PHcost[i] = newPH[i];
    }
}


class Tribe{
    private:
        int remained_PH;    // remained pH in this tribe
        int *wcount;    // count total number of warriers produced
        int *worder;     // the order for the tribe to produce warrier
        int next;       // next type of warrier to be produced
        char *name;    // the name of the tribe
        int aid;    // auto incremented id
        int status; // continue production or stopped
    
    public:
        int produce_warrior();  // produce next warrior, if success, return the warrier type, otherwise return -1
        void set_worder(int order[]);       // set in which order the warriers should be produced
        int numberof_warrier(int type); // the number of this warrier type in the tripe
        Tribe(int ph, int order[], const char name_[]);     // customer constructor
        void print_event(int t, int wtype, const char wname[]); // print the event 
        int pstatus();  // production status
};

// constructor for tribe
Tribe::Tribe(int ph, int order[], const char name_[]){
    remained_PH = ph;
    next = 0;
    aid = 0;
    status = SUCCESS;
    name = new char[TOTAL_TYPES];
    worder = new int[TOTAL_TYPES];
    wcount = new int[TOTAL_TYPES];
    
    int i;
    for(i=0;i<NAME_LENGTH;i++){
        name[i] = name_[i]; // copy names
    }

    for(i=0;i<TOTAL_TYPES;i++){
        worder[i] = order[i];
        wcount[i] = 0;  // init to zero
    }
}

void Tribe::set_worder(int order[]){
    int i;
    for(i=0;i<TOTAL_TYPES;i++){
        worder[i] = order[i];
    }
}

int Tribe::pstatus(){
    return status;
}
void Tribe::print_event(int t, int wtype, const char wname[])
{
    if(wtype==STOPPED){
        printf("%03d %s headquarter stops making warriors\n", t, name);
    }
    else{
        printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter\n", t, name, wname, aid, Warrior::phcost(wtype), wcount[wtype], wname,name);
    }

    
    // printf("%d\n", Warrior::phcost(wtype));
    // printf("%d\n", wcount[wtype]);
    // printf("%s\n", name);
    // printf("%s\n", wname);
    // printf("%s\n", name);
}

int Tribe::numberof_warrier(int type){
    return wcount[type];
}

int Tribe::produce_warrior(){
    int tries = 0;  // number of tries
    
    // search until find the warrier that can be produced
    while(tries<TOTAL_TYPES&&Warrior::phcost(worder[next])>remained_PH){
        tries++;
        next++;
        if(next==TOTAL_TYPES)   next = 0;
    }
    if(tries<TOTAL_TYPES){
        // can produce one warrier
        int current = next;
        remained_PH -= Warrior::phcost(worder[current]);  // deduce remained PH value
        wcount[worder[current]]++;    // increment warrier count
        aid++;

        next++; // point to next warrier type
        if(next==TOTAL_TYPES)   next = 0;

        return worder[current];

    }
    else{
        status = STOPPED;
        return STOPPED;  // not possible to produce warriers anymore
    }
    
}


int main()
{
    // define some constants
    const char *names[TOTAL_TYPES] = { "iceman", "lion", "wolf", "ninja","dragon" }; 
    int red_worder[TOTAL_TYPES] = {ICEMAN_IDX, LION_IDX, WOLF_IDX, NINJA_IDX, DRAGON_IDX};
    int blue_worder[TOTAL_TYPES] = {LION_IDX, DRAGON_IDX, NINJA_IDX, ICEMAN_IDX, WOLF_IDX};
    // for(int i=0;i<TOTAL_TYPES;i++){
    //     cout<<names[i]<<endl;
    // }
    // printf("here");

    int tests;
    scanf("%d", &tests);
    
    for(int test=0;test<tests;test++){
        int total_ph;
        scanf("%d", &total_ph);
        int *ph_cost = new int[TOTAL_TYPES];
        scanf("%d %d %d %d %d", &ph_cost[DRAGON_IDX], &ph_cost[NINJA_IDX], &ph_cost[ICEMAN_IDX], &ph_cost[LION_IDX], &ph_cost[WOLF_IDX]);

        
        // printf("stes");
        // ph_cost[DRAGON_IDX] = 3;
        // ph_cost[NINJA_IDX] = 4;
        // ph_cost[ICEMAN_IDX] = 5;
        // ph_cost[LION_IDX] = 6;
        // ph_cost[WOLF_IDX] = 7;

        Warrior::set_PHcost(ph_cost);       // set the ph cost to produce warriers
        // printf("success1");
        Tribe red(total_ph, red_worder, "red");
        Tribe blue(total_ph, blue_worder, "blue");

        // printf("success1");
        
        int t = 0;
        // int wtype = 0;
        printf("Case:%d\n", test+1);
        do{
            if(red.pstatus()!=STOPPED){
                int wtype = red.produce_warrior();
                red.print_event(t, wtype, names[wtype]);
            }

            if(blue.pstatus()!=STOPPED){
                int wtype = blue.produce_warrior();
                blue.print_event(t, wtype, names[wtype]);

            }
            
            t++;
        }while(blue.pstatus()!=STOPPED||red.pstatus()!=STOPPED);

    }

    

    // printf("%03d\n", 3);
    // printf("%03d\n", 10);

    return 0;

}
