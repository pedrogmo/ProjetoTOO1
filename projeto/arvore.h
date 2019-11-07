#ifndef ARVORE
#define ARVORE

#include "charcodigo.h"

/*struct para guardar caractere e frequência*/
typedef
    struct
    {
        unsigned char caractere;
        unsigned int frequencia;
        bool temConteudo;
    } InfoChar;

/*struct para um nó da árvore*/
typedef
    struct NoArvore
    {
        InfoChar infoChar;
        struct NoArvore *esquerda;
        struct NoArvore *direita;
    } NoArvore;

extern NoArvore *novaArvore(
    InfoChar info,
    NoArvore *esq,
    NoArvore *dir);

extern unsigned int pegarCodigos(
    NoArvore* raiz,
    CharCodigo* vetorCodigos,
    unsigned int tamanhoCharCodigos);

extern void excluirArvore(
    NoArvore *raiz);

extern NoArvore *montarArvore(
    Lista* fila);

#endif /*ARVORE*/
