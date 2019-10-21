#include <stdio.h>
#include <stdlib.h>

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

static void limparVetor(
    int *vet,
    unsigned int tamanho)
{
    for(; tamanho > 0; --tamanho)
        vet[tamanho-1] = 0;
}

static void limparTela()
{
    system("@cls||clear");
}

static void compactar()
{
    char buff[256];
    char dado;
    int count;
    int frequencias[256];
    FILE *arqEntrada, *arqSaida;

    limparTela();
    limparVetor(
        frequencias,
        sizeof(frequencias) / sizeof(int));

    printf("Digite o arquivo para compactar: ");
    scanf("%s", buff);
    fflush(stdin);
    arqEntrada = fopen(buff, "rb");

    if (!arqEntrada)
    {
        printf("Nao foi possivel abrir arquivo");
        getchar();
        return;
    }

    printf("Digite o arquivo de saida: ");
    scanf("%s", buff);
    fflush(stdin);
    arqSaida = fopen(buff, "rb");

    if (!arqSaida)
    {
        printf("Nao foi possivel abrir arquivo");
        getchar();
        return;
    }

    for(count = fread(&dado, sizeof(char), 1, arqEntrada);
        count == 1;
        count = fread(&dado, sizeof(char), 1, arqEntrada))
    {
        ++frequencias[dado];
    }

    printf(
       "%i\n%i",
       frequencias['A'],
       frequencias['B']);

    getchar();
}

static void descompactar()
{
    limparTela();
    getchar();
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
        {
            (*funcoes[opcao-1]) ();
            limparTela();
        }
    }
    while(opcao);

    return 0;
}
