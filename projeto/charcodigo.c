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
    CharCodigo *vetor,
    unsigned int tamanho)
{
    for(; tamanho > 0; --tamanho)
        free(vetor[tamanho-1].codigo);
}

static int comparaCharCodigos(
    void *cc1,
    void *cc2)
{
    CharCodigo *charCod1 = (CharCodigo*) cc1;
    CharCodigo *charCod2 = (CharCodigo*) cc2;

    if (charCod1->caractere < charCod2->caractere)
        return -1;
    else if (charCod1->caractere > charCod2->caractere)
        return 1;
    return 0;
}

void ordenar(
    CharCodigo *vetor,
    unsigned int tamanho)
{
    qsort(vetor, tamanho, sizeof(CharCodigo), &comparaCharCodigos);
}

char *codigoDe(
    unsigned char caractere,
    CharCodigo *vetor,
    unsigned int tamanho)
{
    void *busca;
    CharCodigo charCodigo;
    charCodigo.caractere = caractere;

    busca = bsearch(&charCodigo, vetor, tamanho, sizeof(CharCodigo), &comparaCharCodigos);

    if (!busca)
        return NULL;

    return ((CharCodigo*) busca)->codigo;
}
