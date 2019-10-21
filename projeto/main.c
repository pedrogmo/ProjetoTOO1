#include <stdio.h>

#include "fila.h"

/*
Algoritmo de Huffman:

    1-  ler texto e guardar ocorrências de cada caractere
    2-  ordenar ou priorizar caracteres pelo número de ocorrências
    3-  construir árvore baseada na lista priorizada
    4-  realizar percurso na árvore para determinar código de cada caractere
    5-  ler texto de novo e botar o código no lugar de cada caractere
        isso deve ser feito byte a byte, aglutinando os códigos

    O arquivo final deve conter a quantidade de bits que são lixo (ao final)
    e a lista priorizada para formar a árvore e realizar os percursos
*/

static void compactar()
{
    puts("C\n");
}

static void descompactar()
{
    puts("D\n");
}

int main()
{
    char opcao;

    static void(*funcoes[2])() =
    {
        &compactar, &descompactar
    };

    do
    {
        puts("1- Compactar");
        puts("2- Descompactar");
        puts("0- Sair");
        printf("Qual opcao deseja? ");
        fflush(stdout);
        scanf("%i", &opcao);
        fflush(stdin);

        if (opcao > 0)
            (*funcoes[opcao-1]) ();
    }
    while(opcao);

    return 0;
}
