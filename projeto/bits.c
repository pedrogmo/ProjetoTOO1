#include "bits.h"

extern void setBit(
    unsigned char qualBit,
    char *byte)
{
    unsigned char bitDesejado = 1;
    bitDesejado <<= qualBit;
    *byte |= bitDesejado;
}
