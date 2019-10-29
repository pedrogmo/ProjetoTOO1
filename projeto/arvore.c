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
    char* codigoCompleto,
    unsigned int tamanhoCodigo,
    unsigned int* contagem)
{
    if (no->esquerda != NULL)
    {
        strcat(codigoCompleto, "0");
        ++tamanhoCodigo;
        recCaminho(no->esquerda, lista, codigoCompleto, tamanhoCodigo, contagem);
        codigoCompleto[tamanhoCodigo - 1] = 0;
        --tamanhoCodigo;
    }
    if (no->direita != NULL)
    {
        strcat(codigoCompleto, "1");
        ++tamanhoCodigo;
        recCaminho(no->direita , lista, codigoCompleto, tamanhoCodigo, contagem);
        codigoCompleto[tamanhoCodigo - 1] = 0;
    }
    if (no->infoChar.temConteudo)
    {
        *contagem += tamanhoCodigo * no->infoChar.frequencia;
        inserirFim(lista, novoCharCodigo(no->infoChar.caractere, codigoCompleto, tamanhoCodigo));
    }
}

unsigned int pegarCodigos(
    NoArvore* raiz,
    Lista* lista)
{
    char codigo[MAX_STRING];
    unsigned int contagem = 0;
    codigo[0] = '\0';
    recCaminho(raiz, lista, codigo, 0, &contagem);
    return contagem;
}

void excluirArvore(
    NoArvore *raiz)
{
    if (raiz)
    {
        excluirArvore(raiz->esquerda);
        excluirArvore(raiz->direita);
        free(raiz);
    }
}
