#ifndef LISTA
#define LISTA

typedef
    struct No
    {
        /*Dado gen�rico*/
        void* info;
        struct No* prox;
    } No;

typedef
    struct
    {
        No* inicio, * fim;
    } Lista;

/*Fun��es que podem ser usadas externamente, p�blicas*/

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

#endif /*LISTA*/
