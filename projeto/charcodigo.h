#ifndef CHARCODIGO
#define CHARCODIGO

#define MAX_STRING 17

typedef
    struct
    {
        char caractere;
        char codigo[MAX_STRING];
    } CharCodigo;

extern CharCodigo *novoCharCodigo(
    char caractere,
    char *codigoString);

#endif /*CHARCODIGO*/
