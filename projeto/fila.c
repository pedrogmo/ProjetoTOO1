#include "fila.h"


void inserirFila(
    Lista *fila,
    NoArvore *noArvore)
{
    int i = 0;

    for (; i < fila->quantidade; i++)
    {
        if (noArvore->infoChar.frequencia < ((NoArvore*)dadoEm(fila, i))->infoChar.frequencia)
            inserir(fila, noArvore, i);
    }
}

NoArvore *removerFila(
    Lista *fila)
{

}
