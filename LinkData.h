#ifndef H_linkdata
#define H_linkdata

#include <iostream>

using namespace std;

//---------------------------------------------------------------------------
/* LinkData
* This class is used to define what areas are connected to other areas based
* on direction.
* An array is used to assign each area that are connected to the current area
* the player is in.
* Methods are available to set the connecting locations for an area and to
* check which area is connected based on a direction chosen by the user.
*/
class LinkData
{
    public:
        static const int SIZE = 4;

        void setDigits(int, int, int, int);
        int getDigit(int);

    private:
        int digits[4];
};

#endif // H_linkdata
