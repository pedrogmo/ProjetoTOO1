#ifndef ARVORE
#define ARVORE

typedef
    enum
    {
        false, true
    } bool;

/*struct para guardar caractere e frequ�ncia*/
typedef
    struct
    {
        unsigned char caractere;
        int frequencia;
        bool temConteudo;
    } InfoChar;

/*struct para um n� da �rvore*/
typedef
    struct NoArvore
    {
        InfoChar info;
        struct NoArvore *esquerda;
        struct NoArvore *direita;
    } NoArvore;

#endif /* ARVORE */
