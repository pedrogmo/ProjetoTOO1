#ifndef LISTA
#define LISTA

#include "bool.h"

typedef
    struct No
    {
        void *info;
        struct No *prox;
    } No;

typedef
    struct
    {
        No *inicio;
        No *fim;
        unsigned int quantidade;
    } Lista;

/*Funções que podem ser usadas externamente, públicas*/

extern void inicializar(
    Lista *lista);

extern int quantidade(
    Lista *lista);

extern bool vazia(
    Lista *lista);

extern void inserirInicio(
    Lista *lista,
    void *info);

extern void inserirFim(
    Lista *lista,
    void *info);

extern void inserir(
    Lista *lista,
    void *info,
    unsigned int pos);

extern void *dadoInicio(
    Lista* lista);

extern void *dadoFim(
    Lista* lista);

extern void *dadoEm(
    Lista *lista,
    unsigned int pos);

extern void excluirInicio(
    Lista *lista);

extern void excluirFim(
    Lista *lista);

extern void excluir(
    Lista *lista,
    unsigned int pos);

extern void limpar(
    Lista *lista);

#endif /*LISTA*/
