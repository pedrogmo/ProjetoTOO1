#include <string.h>
#include "charcodigo.h"

CharCodigo *novoCharCodigo(
    char caractere,
    char *codigoString)
{
    CharCodigo *novo = (CharCodigo*) malloc(sizeof(CharCodigo));
    novo->caractere = caractere;
    strcpy(novo->codigo, codigoString);
    return novo;
}
