#include "bits.h"

void setBit(
    unsigned char qualBit,
    char *byte)
{
    char bitDesejado = 0b10000000;
    bitDesejado >>= qualBit;
    *byte |= bitDesejado;
}

bool isUm(
    unsigned char qualBit,
    char byte)
{
    char byteComparacao = 0b10000000;
    byteComparacao >>= qualBit;
    return byteComparacao & byte;
}
