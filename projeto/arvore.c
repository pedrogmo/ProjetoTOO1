#include "arvore.h"
#include "lista.h"
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
    CharCodigo* vetorCodigos,
    char* codigoCompleto,
    unsigned int tamanhoCodigo,
    unsigned int* contagem,
    unsigned int* ultimoIndice)
{
    if (no->esquerda != NULL)
    {
        strcat(codigoCompleto, "0");
        ++tamanhoCodigo;
        recCaminho(no->esquerda, vetorCodigos, codigoCompleto, tamanhoCodigo, contagem, ultimoIndice);
        codigoCompleto[tamanhoCodigo - 1] = 0;
        --tamanhoCodigo;
    }
    if (no->direita != NULL)
    {
        strcat(codigoCompleto, "1");
        ++tamanhoCodigo;
        recCaminho(no->direita , vetorCodigos, codigoCompleto, tamanhoCodigo, contagem, ultimoIndice);
        codigoCompleto[tamanhoCodigo - 1] = 0;
    }
    if (no->infoChar.temConteudo)
    {
        *contagem += tamanhoCodigo * no->infoChar.frequencia;
        vetorCodigos[*ultimoIndice] = novoCharCodigo(no->infoChar.caractere, codigoCompleto, tamanhoCodigo);
        (*ultimoIndice)++;
    }
}

unsigned int pegarCodigos(
    NoArvore* raiz,
    CharCodigo* vetorCodigos,
    unsigned int tamanhoCharCodigos)
{
    char codigo[MAX_STRING_CODIGO];
    unsigned int contagem = 0, ultimoIndice = 0;
    vetorCodigos = (CharCodigo*) malloc(tamanhoCharCodigos * sizeof(CharCodigo));
    codigo[0] = '\0';
    recCaminho(raiz, vetorCodigos, codigo, 0, &contagem, &ultimoIndice);
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
NoArvore *montarArvore(
    Lista* fila)
{
    NoArvore *noArvore, *esq, *dir;
    InfoChar infoChar;
    No *no;
    CharCodigo *charCodigo;

    while(quantidade(fila) >= 2)
    {
        esq = removerFila(fila);
        dir = removerFila(fila);

        infoChar.caractere = 0;
        infoChar.temConteudo = false;
        infoChar.frequencia =
            esq->infoChar.frequencia +
            dir->infoChar.frequencia;

        noArvore = novaArvore(
            infoChar,
            esq,
            dir);

        inserirFila(
            fila,
            noArvore);
    }

    return removerFila(fila);
}
