#include "fila.h"


void inserirFila(
    Lista *fila,
    NoArvore *noArvore)
{
    int pos = 0;

    for (; pos < fila->quantidade; pos++)
    {
        if (noArvore->infoChar.frequencia < ((NoArvore*)dadoEm(fila, pos))->infoChar.frequencia){
                inserir(fila, noArvore, pos);
            return;
        }
    }
    inserirFim(fila, noArvore);
}

NoArvore *removerFila(
    Lista *fila)
{
    NoArvore* primeiroValor = (NoArvore*) dadoInicio(fila);
    excluirInicio(fila);
    return primeiroValor;
}
