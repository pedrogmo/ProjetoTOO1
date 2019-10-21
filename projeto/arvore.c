#include "arvore.h"

NoArvore *novaArvore(
    InfoChar info,
    NoArvore *esq,
    NoArvore *dir)
{
    NoArvore *nova = (NoArvore*) malloc(sizeof(NoArvore));
    nova->infoChar = info;
    nova->esquerda = esq;
    nova->direita = dir;
    return nova;
}
