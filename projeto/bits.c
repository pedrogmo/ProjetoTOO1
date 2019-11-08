#include "bits.h"

void setBit(
    uint8 qualBit,
    uint8* byte)
{
    uint8 bitDesejado = 0b10000000;
    bitDesejado >>= qualBit;
    *byte |= bitDesejado;
}

bool isUm(
    uint8 qualBit,
    uint8 byte)
{
    uint8 byteComparacao = 0b10000000;
    byteComparacao >>= qualBit;
    return byteComparacao & byte;
}
