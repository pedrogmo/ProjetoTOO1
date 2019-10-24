#include "arvore.h"
#include "lista.h"
#include "charcodigo.h"
#include <stdlib.h>
#include "formabits.h"

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

static void recCaminho(
    NoArvore* no,
    Lista* lista,
    char* codigoCompleto)
{
    if (no->esquerda != NULL)
    {
        strcat(codigoCompleto, "0");
        recCaminho(no->esquerda, lista, codigoCompleto);
        codigoCompleto[strlen(codigoCompleto) - 1] = 0;
    }
    if (no->direita != NULL)
    {
        strcat(codigoCompleto, "1");
        recCaminho(no->direita , lista, codigoCompleto);
        codigoCompleto[strlen(codigoCompleto) - 1] = 0;
    }
    if (no->infoChar.temConteudo)
        inserirFim(lista, novoCharCodigo(no->infoChar.caractere, codigoCompleto));
}

void pegarCodigos(NoArvore* raiz, Lista* lista)
{
    char codigo[MAX_STRING];
    codigo[0] = '\0';
    recCaminho(raiz, lista, codigo);
}
