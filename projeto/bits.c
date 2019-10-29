#include "bits.h"

void setBit(
    unsigned char qualBit,
    char *byte)
{
    unsigned char bitDesejado = 0b10000000;
    bitDesejado >>= qualBit;
    *byte |= bitDesejado;
}
