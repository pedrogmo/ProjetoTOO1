#ifndef ARVORE
#define ARVORE

#include "bool.h"
#include "lista.h"

/*struct para guardar caractere e frequ�ncia*/
typedef
    struct
    {
        unsigned char caractere;
        unsigned int frequencia;
        bool temConteudo;
    } InfoChar;

/*struct para um n� da �rvore*/
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
    NoArvore *raiz,
    Lista* lista);

extern void excluirArvore(
    NoArvore *raiz);

#endif /*ARVORE*/
