#include <string.h>
#include "charcodigo.h"

CharCodigo *novoCharCodigo(
    unsigned char caractere,
    char *codigoString,
    int tamanhoString)
{
    CharCodigo *novo = (CharCodigo*) malloc(sizeof(CharCodigo));
    novo->caractere = caractere;
    novo->codigo = (char*) malloc(sizeof(char) * (tamanhoString+1));
    strcpy(novo->codigo, codigoString);
    return novo;
}

void excluirCodigos(
    Lista *lista)
{
    No *no;
    CharCodigo *charCodigo;
    for(no = lista->inicio;
        no;
        no = no->prox)
    {
        charCodigo = (CharCodigo*) no->info;
        free(charCodigo->codigo);
    }
}

char *codigoDe(
    unsigned char caractere,
    Lista *lista)
{
    No *no;
    CharCodigo *charCodigo;
    for(no = lista->inicio;
        no;
        no = no->prox)
    {
        charCodigo = (CharCodigo*) no->info;
        if (charCodigo->caractere == caractere)
            return charCodigo->codigo;
    }
    return NULL;
}
