#ifndef LISTA_H
#define LISTA_H

typedef
    struct No
    {
        void* info;         /*Tipo genérico, ponteiro void*/
        struct No* prox;
    } No;

typedef
    struct
    {
        No* inicio, * fim;
    } Lista;

/*Funções que podem ser usadas externamente, públicas*/

extern void inicializar(
    Lista* lista);

extern void inserir_inicio(
    Lista* lista,
    void* info);

extern void inserir_fim(
    Lista* lista,
    void* info);

extern void inserir(
    Lista* lista,
    void* info,
    unsigned int pos);

extern void* get(
    Lista* lista,
    unsigned int pos);

extern int quantidade(
    Lista* lista);

extern void excluir_inicio(
    Lista* lista);

extern void excluir_fim(
    Lista* lista);

extern void excluir(
    Lista* lista,
    unsigned int pos);

extern void limpar(
    Lista* lista);

#endif /* LISTA_H */
