#include "lista.h"
#include <stdlib.h>

/*
Função auxiliar private
Static: só pode ser usada nesse arquivo
*/

static No* novo_no(
    void* info,
    No* prox)
{
    No* ptr_novo = (No*) malloc(sizeof(No));
    ptr_novo->info = info;
    ptr_novo->prox = prox;
    return ptr_novo;
}

void inicializar(
    Lista* lista) /*Lista por referência*/
{
    lista->inicio = NULL;
    lista->fim = NULL;
}

void inserir_inicio(
    Lista* lista, /*Lista por referência*/
    void* info)   /*Para guardar o ponteiro genérico*/
{
    lista->inicio = novo_no(info, lista->inicio);
    if (!lista->fim)
        lista->fim = lista->inicio;
}

void inserir_fim(
    Lista* lista,
    void* info)
{
    No* novo = novo_no(info, NULL);

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
}

void inserir(
    Lista* lista,
    void* info,
    unsigned int pos)
{
    No* anterior = lista->inicio;

    if (pos == 0)
        inserir_inicio(lista,info);
    for (; pos > 1; --pos)
    {
        if (!anterior->prox)
        {
            inserir_fim(lista, info);
            return;
        }
        anterior = anterior->prox;
    }
    anterior->prox = novo_no(info, anterior->prox);
}

void* get(
    Lista* lista,
    unsigned int pos)
{
    No* temp = lista->inicio;

    for(; pos > 0 && temp;
        --pos)
    {
        temp = temp->prox;
    }
    return temp->info;
}

int quantidade(
    Lista* lista)
{
    int c = 0;
    No* cur = lista->inicio;

    for(; cur; cur = cur->prox)
        ++c;
    return c;
}

void excluir_inicio(
    Lista* lista)
{
    No* primeiro = lista->inicio;

    if (primeiro)
    {
        lista->inicio = lista->inicio->prox;
        if (!lista->inicio)
            lista->fim = NULL;
        free(primeiro->info);
        free(primeiro);
    }
}

void excluir_fim(
    Lista* lista)
{
    No* penultimo = lista->inicio;

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
    }
}

void excluir(
    Lista* lista,
    unsigned int pos)
{
    No* anterior = lista->inicio;
    No* temp;

    if (pos == 0)
        excluir_inicio(lista);
    else
    {
        for (; pos > 1; --pos)
        {
            if (!anterior->prox)
            {
                excluir_fim(lista);
                return;
            }
            anterior = anterior->prox;
        }
        temp = anterior->prox;
        anterior->prox = anterior->prox->prox;
        free(temp->info);
        free(temp);
    }
}

void limpar(
    Lista* lista)
{
    while(lista->inicio)
        excluir_inicio(lista);
}
