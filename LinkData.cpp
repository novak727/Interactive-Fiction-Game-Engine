#include <iostream>

#include "LinkData.h"

//---------------------------------------------------------------------------
/* setDigits() sets the connecting areas for the current area the user is in.
*/
void LinkData::setDigits(int u, int d, int l, int r)
{
    // u,l,d,r
    digits[0] = u;
    digits[1] = d;
    digits[2] = l;
    digits[3] = r;
}

//---------------------------------------------------------------------------
/* LinkData() sends the area number that is connected to the current area
* based on the directional input by the user.
*/
int LinkData::getDigit(int pos)
{
    return digits[pos];
}
