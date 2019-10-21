#ifndef FILA
#define FILA

#include "lista.h"
#include "arvore.h"

extern void inserirFila(
    Lista *fila,
    NoArvore *arvore);

extern NoArvore *removerFila(
    Lista *fila);

#endif /*FILA*/
