#include <stdio.h>
#include <stdlib.h>

#include "fila.h"
#include "charcodigo.h"

#define TAMANHO_VETOR 256

/*
Algoritmo de Huffman:

    1-  ler texto e guardar ocorr�ncias de cada caractere
    2-  ordenar ou priorizar caracteres pelo n�mero de ocorr�ncias
    3-  construir �rvore baseada na lista priorizada
    4-  realizar percurso na �rvore para determinar c�digo de cada caractere
    5-  ler texto de novo e botar o c�digo no lugar de cada caractere
        isso deve ser feito byte a byte, aglutinando os c�digos

    O arquivo final deve conter a quantidade de bits que s�o lixo (ao final)
    e a lista priorizada para formar a �rvore e realizar os percursos
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
static void montarArvore(Lista* fila, Lista* listaCodigos)
{
    NoArvore *noArvore, *esq, *dir;
    InfoChar infoChar;
    No *no;
    CharCodigo *charCodigo;

    while(quantidade(fila) >= 2)
    {
        esq = removerFila(fila);
        dir = removerFila(fila);

        infoChar.caractere = 0;
        infoChar.temConteudo = false;
        infoChar.frequencia =
            esq->infoChar.frequencia +
            dir->infoChar.frequencia;

        noArvore = novaArvore(
            infoChar,
            esq,
            dir);

        inserirFila(
            fila,
            noArvore);
    }

    noArvore = removerFila(fila);

    pegarCodigos(noArvore, listaCodigos);

    /*for(no = listaCodigos->inicio; no != NULL; no = no->prox)
    {
        charCodigo = ((CharCodigo*)no->info);
        printf(
           "%c |%s|\n",
           charCodigo->caractere,
           charCodigo->codigo);
    }*/
}
static void compactar()
{
    unsigned int frequencias[TAMANHO_VETOR];
    Lista fila;
    char buff[256];
    FILE *arqEntrada, *arqSaida;
    int dado;
    unsigned int i;
    InfoChar infoChar;
    NoArvore* noArvore;
    Lista listaCodigos;


    limparTela();
    limparVetor(
        frequencias,
        TAMANHO_VETOR);
    inicializar(&fila);
    inicializar(&listaCodigos);


    printf("Digite o arquivo para compactar: ");
    gets(buff);
    fflush(stdin);
    arqEntrada = fopen(buff, "rb");

    if (!arqEntrada)
    {
        printf("Nao foi possivel abrir arquivo");
        getchar();
        return;
    }

    dado = fgetc(arqEntrada);
    if (dado == EOF)
    {
        printf("O arquivo esta vazio");
        getchar();
        return;
    }
    ungetc(dado, arqEntrada);


    printf("Digite o arquivo de saida: ");
    gets(buff);
    fflush(stdin);
    arqSaida = fopen(buff, "wb");

    if (!arqSaida)
    {
        printf("Nao foi possivel abrir arquivo");
        getchar();
        return;
    }

    while((dado = fgetc(arqEntrada)) != EOF)
    {
        frequencias[dado]++;
    }

    for(i = 0; i < TAMANHO_VETOR; ++i)
    {
        if (frequencias[i])
        {
            infoChar.caractere = i;
            infoChar.frequencia = frequencias[i];
            infoChar.temConteudo = true;

            noArvore = novaArvore(
                infoChar,
                NULL,
                NULL);

            inserirFila(&fila, noArvore);
        }
    }

    montarArvore(&fila, &listaCodigos);


    /* TRAVA A EXECUSS�O */
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
