#include "formabits.h"

void setBit(unsigned char qualBit, unsigned int* bits)
{
    unsigned int bit = 1;
    bit <<= qualBit;
    bits |= bit;
}
