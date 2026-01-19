#ifndef h_structs
#define h_structs

#include <string>
using namespace std;

struct Rule
{
    int beginRm;
    char direction;
    int destRm;
};
struct Effect
{
    int effectID;
    int effectAmt;
};


struct Rest
{
    string rest;
};

struct Event
{
    int eventID;	//Positive or Negative Event
    char effectedStat;	//what stat that is effected
    int statChange;	//How much stat is changed
};
#endif
