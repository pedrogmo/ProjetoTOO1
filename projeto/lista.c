#include "lista.h"
#include <stdlib.h>

/*
Função auxiliar private
Static: só pode ser usada nesse arquivo
*/

static No *novoNo(
    void *info,
    No *prox)
{
    No *ptrNovo = (No*) malloc(sizeof(No));
    ptrNovo->info = info;
    ptrNovo->prox = prox;
    return ptrNovo;
}

void inicializar(
    Lista *lista)
{
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->quantidade = 0;
}

int quantidade(
    Lista *lista)
{
    return lista->quantidade;
}

bool vazia(
    Lista *lista)
{
    return !lista->inicio;
}

void inserirInicio(
    Lista *lista,
    void *info)
{
    lista->inicio = novoNo(info, lista->inicio);
    if (!lista->fim)
        lista->fim = lista->inicio;
    ++lista->quantidade;
}

void inserirFim(
    Lista *lista,
    void *info)
{
    No *novo = novoNo(info, NULL);

    if (lista->fim)
    {
        lista->fim->prox = novo;
        lista->fim = novo;
    }
    else
    {
        lista->fim = novo;
        lista->inicio = lista->fim;
    }

    ++lista->quantidade;
}

void inserir(
    Lista *lista,
    void *info,
    unsigned int pos)
{
    if (pos == 0)
        inserirInicio(lista, info);
    else
    {
        No *anterior = lista->inicio;

        for (; pos > 1; --pos)
        {
            if (!anterior->prox)
            {
                inserirFim(lista, info);
                return;
            }
            anterior = anterior->prox;
        }
        anterior->prox = novoNo(info, anterior->prox);
        ++lista->quantidade;
    }
}

void *dadoInicio(
    Lista *lista)
{
    return lista->inicio->info;
}

void *dadoFim(
    Lista *lista)
{
    return lista->fim->info;
}

void* dadoEm(
    Lista *lista,
    unsigned int pos)
{
    No *temp = lista->inicio;

    for(; pos > 0 && temp;
        --pos)
    {
        temp = temp->prox;
    }
    return temp->info;
}

void excluirInicio(
    Lista *lista)
{
    No *primeiro = lista->inicio;

    if (primeiro)
    {
        lista->inicio = lista->inicio->prox;
        if (!lista->inicio)
            lista->fim = NULL;
        free(primeiro->info);
        free(primeiro);

        --lista->quantidade;
    }
}

void excluirFim(
    Lista *lista)
{
    No *penultimo = lista->inicio;

    if (lista->inicio)
    {
        if (lista->inicio == lista->fim)
        {
            free(lista->inicio->info);
            free(lista->inicio);
            lista->inicio = NULL;
            lista->fim = NULL;
        }
        else
        {
            for(; penultimo->prox && penultimo->prox->prox ;
                penultimo = penultimo->prox);

            free(lista->fim->info);
            free(lista->fim);
            lista->fim = penultimo;
            lista->fim->prox = NULL;
        }

        --lista->quantidade;
    }
}

void excluir(
    Lista *lista,
    unsigned int pos)
{
    if (pos == 0)
        excluirInicio(lista);
    else
    {
        No *anterior = lista->inicio;
        No *temp;

        for (; pos > 1; --pos)
        {
            if (!anterior->prox)
            {
                excluirFim(lista);
                return;
            }
            anterior = anterior->prox;
        }
        temp = anterior->prox;
        anterior->prox = anterior->prox->prox;
        free(temp->info);
        free(temp);

        --lista->quantidade;
    }
}

void limpar(
    Lista *lista)
{
    while(lista->inicio)
        excluirInicio(lista);
}
