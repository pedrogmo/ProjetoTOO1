#ifndef CHARCODIGO
#define CHARCODIGO

#define MAX_STRING_CODIGO 257

#include "lista.h"

typedef
    struct
    {
        unsigned char caractere;
        char *codigo;
    } CharCodigo;

extern CharCodigo *novoCharCodigo(
    unsigned char caractere,
    char *codigoString,
    int tamanhoString);

extern void excluirCodigos(
    CharCodigo *vetor,
    unsigned int tamanho);

extern void ordenar(
    CharCodigo *vetor,
    unsigned int tamanho);

extern char *codigoDe(
    unsigned char caractere,
    CharCodigo *vetor,
    unsigned int tamanho);

#endif /*CHARCODIGO*/
