#ifndef ARVORE
#define ARVORE

typedef
    enum
    {
        false, true
    } bool;

/*struct para guardar caractere e frequência*/
typedef
    struct
    {
        unsigned char caractere;
        int frequencia;
        bool temConteudo;
    } InfoChar;

/*struct para um nó da árvore*/
typedef
    struct NoArvore
    {
        InfoChar info;
        struct NoArvore *esquerda;
        struct NoArvore *direita;
    } NoArvore;

#endif /* ARVORE */
