#include <stdio.h>
#include <stdlib.h>

#include "fila.h"
#include "charcodigo.h"

#define TAMANHO_VETOR 256

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

static bool arquivoInvalido(
    FILE *arquivo,
    bool podeVazio)
{
    int dado;

    if (!arquivo)
    {
        printf("Nao foi possivel abrir arquivo");
        getchar();
        return false;
    }

    if (!podeVazio)
    {
        dado = fgetc(arquivo);
        if (dado == EOF)
        {
            printf("O arquivo esta vazio");
            getchar();
            return false;
        }
        ungetc(dado, arquivo);
    }

    return true;
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
    No *noLista;
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

    if (arquivoInvalido(arqEntrada, false))
        return;

    printf("Digite o arquivo de saida: ");
    gets(buff);
    fflush(stdin);
    arqSaida = fopen(buff, "wb");

    if (arquivoInvalido(arqSaida, true))
        return;

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

    /*bits que são lixo. será alterado depois*/
    fputc(0, arqSaida);
    /*quantidade de caracteres*/
    fputc(quantidade(&fila), arqSaida);
    /*todos os infochars:*/
    for(noLista = fila.inicio;
        noLista;
        noLista = noLista->prox)
    {
        infoChar = ((NoArvore*) noLista->info)->infoChar;
        fputc(infoChar.caractere, arqSaida);
        fwrite(&infoChar.frequencia, sizeof(unsigned int), 1, arqSaida);
    }

    montarArvore(&fila, &listaCodigos);

    /*fecha os arquivos*/
    fclose(arqEntrada);
    fclose(arqSaida);
    /* TRAVA A EXECUÇÃO */
    getchar();
}

static void descompactar()
{
    FILE *arqEntrada, *arqSaida;
    char buff[256];
    char bitsLixo;
    char quantidadeInfoChars;
    Lista listaInfoChars;
    Lista listaCharCodigos;

    limparTela();
    inicializar(&listaInfoChars);
    inicializar(&listaCharCodigos);

    printf("Digite o arquivo para descompactar: ");
    gets(buff);
    fflush(stdin);
    arqEntrada = fopen(buff, "rb");

    if(arquivoInvalido(arqEntrada, false))
        return;

    printf("Digite o arquivo de saida: ");
    gets(buff);
    fflush(stdin);
    arqSaida = fopen(buff, "rb");

    if(arquivoInvalido(arqSaida, true))
        return;

    puts("OK");

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
