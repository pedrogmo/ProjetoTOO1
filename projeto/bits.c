#include "bits.h"

void setBit(
    unsigned char qualBit,
    char *byte)
{
    unsigned char bitDesejado = 1;
    bitDesejado <<= qualBit;
    *byte |= bitDesejado;
}