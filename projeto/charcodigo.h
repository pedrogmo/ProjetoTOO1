#ifndef CHARCODIGO
#define CHARCODIGO

#define MAX_STRING_CODIGO 257

#include "lista.h"

typedef
    struct
    {
        unsigned char caractere;
        char* codigo;
    } CharCodigo;

extern CharCodigo novoCharCodigo(
    uint8 caractere,
    char* codigoString,
    uint32 tamanhoString);

extern void excluirCodigos(
    CharCodigo* vetor,
    uint32 tamanho);

extern void ordenar(
    CharCodigo* vetor,
    uint32 tamanho);

extern char* codigoDe(
    uint8 caractere,
    CharCodigo* vetor,
    uint32 tamanho);

#endif /*CHARCODIGO*/
