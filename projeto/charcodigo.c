#include <string.h>
#include "charcodigo.h"

CharCodigo *novoCharCodigo(
    char caractere,
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
