#ifndef CHARCODIGO
#define CHARCODIGO

#define MAX_STRING 256

#include "lista.h"

typedef
    struct
    {
        char caractere;
        char *codigo;
    } CharCodigo;

extern CharCodigo *novoCharCodigo(
    char caractere,
    char *codigoString,
    int tamanhoString);

extern void excluirCodigos(
    Lista *lista);

extern char *codigoDe(
    char caractere,
    Lista *lista);

#endif /*CHARCODIGO*/
