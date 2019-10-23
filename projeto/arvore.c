#include "arvore.h"
#include "lista.h"
#include "charcodigo.h"

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
    char* codigo)
{
    if (no->esquerda != NULL && no->direita != NULL)
    {
        recCaminho(no->esquerda, lista, codigo);
        recCaminho(no->direita , lista, codigo);
    }
    inserirFim(lista, novoCharCodigo(no->infoChar.caractere, codigo));
}

void pegarCodigos(NoArvore* raiz, Lista* lista)
{

}
