#ifndef CHARCODIGO
#define CHARCODIGO

#define MAX_STRING 256

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
    Lista *lista);

extern char *codigoDe(
    unsigned char caractere,
    Lista *lista);

#endif /*CHARCODIGO*/
