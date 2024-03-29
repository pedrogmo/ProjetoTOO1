#include <stdlib.h>
#include "arvore.h"
#include "bits.h"

NoArvore* novaArvore(
    InfoChar info,
    NoArvore* esq,
    NoArvore* dir)
{
    NoArvore* nova = (NoArvore*) malloc(sizeof(NoArvore));
    nova->infoChar = info;
    nova->esquerda = esq;
    nova->direita = dir;
    return nova;
}

static void recCaminho(
    NoArvore* no,
    CharCodigo* vetorCodigos,
    char* codigoCompleto,
    uint32 tamanhoCodigo,
    uint32* contagem,
    uint32* ultimoIndice)
{
    if (no->esquerda != NULL)
    {
        strcat(codigoCompleto, "0");
        recCaminho(no->esquerda, vetorCodigos, codigoCompleto, ++tamanhoCodigo, contagem, ultimoIndice);
        codigoCompleto[--tamanhoCodigo] = 0;
    }
    if (no->direita != NULL)
    {
        strcat(codigoCompleto, "1");
        recCaminho(no->direita , vetorCodigos, codigoCompleto, ++tamanhoCodigo, contagem, ultimoIndice);
        codigoCompleto[--tamanhoCodigo] = 0;
    }
    if (no->infoChar.temConteudo)
    {
        *contagem += tamanhoCodigo * no->infoChar.frequencia;
        vetorCodigos[*ultimoIndice] = novoCharCodigo(no->infoChar.caractere, codigoCompleto, tamanhoCodigo);
        (*ultimoIndice)++;
    }
}

uint32 pegarCodigos(
    NoArvore* raiz,
    CharCodigo* vetorCodigos)
{
    char codigo[MAX_STRING_CODIGO];
    uint32 contagem = 0, ultimoIndice = 0;
    codigo[0] = '\0';
    recCaminho(raiz, vetorCodigos, codigo, 0, &contagem, &ultimoIndice);
    return contagem;
}

void excluirArvore(
    NoArvore* raiz)
{
    if (raiz)
    {
        excluirArvore(raiz->esquerda);
        excluirArvore(raiz->direita);
        free(raiz);
    }
}
NoArvore* montarArvore(
    Lista* fila)
{
    NoArvore *noArvore, *esq, *dir;
    InfoChar infoChar;
    No* no;
    CharCodigo* charCodigo;

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
