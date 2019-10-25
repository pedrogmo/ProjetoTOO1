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
    unsigned int* contagem)
{
    if (no->esquerda != NULL)
    {
        strcat(codigoCompleto, "0");
        recCaminho(no->esquerda, lista, codigoCompleto, contagem);
        codigoCompleto[strlen(codigoCompleto) - 1] = 0;
    }
    if (no->direita != NULL)
    {
        strcat(codigoCompleto, "1");
        recCaminho(no->direita , lista, codigoCompleto, contagem);
        codigoCompleto[strlen(codigoCompleto) - 1] = 0;
    }
    if (no->infoChar.temConteudo)
    {
        *contagem += strlen(codigoCompleto) * no->infoChar.frequencia;
        inserirFim(lista, novoCharCodigo(no->infoChar.caractere, codigoCompleto));
    }

}

unsigned int pegarCodigos(NoArvore* raiz, Lista* lista)
{
    char codigo[MAX_STRING];
    unsigned int contagem;
    codigo[0] = '\0';
    recCaminho(raiz, lista, codigo, &contagem);
    return contagem;
}
