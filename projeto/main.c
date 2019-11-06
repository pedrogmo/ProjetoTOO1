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

static bool arquivoInvalido(
    FILE *arquivo,
    bool podeVazio)
{
    if (!arquivo)
    {
        printf("Nao foi possivel abrir arquivo");
        getchar();
        return true;
    }

    if (!podeVazio)
    {
        int dado = fgetc(arquivo);
        if (dado == EOF)
        {
            printf("O arquivo esta vazio");
            getchar();
            return true;
        }
        ungetc(dado, arquivo);
    }

    return false;
}


static void compactar()
{
    unsigned int frequencias[TAMANHO_VETOR];
    Lista fila;
    char buff[256];
    FILE *arqEntrada, *arqSaida;
    short int qtdCharCodigos;
    int dado;
    unsigned int i;
    InfoChar infoChar;
    NoArvore* noArvore;
    No *noLista;
    Lista listaCodigos;
    unsigned char bitsLixo;
    unsigned char byte;
    unsigned int tamanhoString;
    char *textoCodificado;
    char *codigoObtido;


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

    /*lê arquivo e coloca frequência de cada char na posição correspondente*/
    while((dado = fgetc(arqEntrada)) != EOF)
        frequencias[dado]++;

    /*percorre vetor de frequências e insere nós na fila*/
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

    /*bits que são lixo, será sobrescrito depois*/
    fputc(0, arqSaida);

    /*quantidade de caracteres*/
    qtdCharCodigos = quantidade(&fila);
    fwrite(&qtdCharCodigos, sizeof(short int), 1, arqSaida);

    /*escreve cada char e frequência dele*/
    for(noLista = fila.inicio;
        noLista;
        noLista = noLista->prox)
    {
        infoChar = ((NoArvore*) noLista->info)->infoChar;
        fputc(infoChar.caractere, arqSaida);
        fwrite(&infoChar.frequencia, sizeof(unsigned int), 1, arqSaida);
    }

    noArvore = montarArvore(&fila);

    tamanhoString = pegarCodigos(noArvore, &listaCodigos);
    excluirArvore(noArvore);

    /*aloca dinamicamente string com todo o texto codificado*/
    textoCodificado = (char*)malloc(tamanhoString + 1);
    textoCodificado[0] = 0;

    /*reinicia arquivo para segunda leitura*/
    rewind(arqEntrada);

    /*lê cada caractere do arquivo e concatena seu código no textoCodificado*/
    for (dado = getc(arqEntrada); dado != EOF; dado = getc(arqEntrada))
    {
        codigoObtido =  codigoDe(dado, &listaCodigos);
        if (codigoObtido)
            strcat(textoCodificado, codigoObtido);
    }

    /*percorre a string; gera e escreve os bytes correspondentes*/
    for(i=0; i < tamanhoString; ++i)
    {
        if (i != 0 && i % 8 == 0)
        {
            fputc(byte, arqSaida);
            byte = 0;
        }
        if (textoCodificado[i] == '1')
            setBit(i % 8, &byte);
    }

    /*calcula-se a quantidade de bits que sobram e escreve no arquivo*/
    bitsLixo = 8 - (tamanhoString % 8);
    if (bitsLixo)
    {
        fputc(byte, arqSaida);
        fseek(arqSaida, 0, SEEK_SET);
        fputc(bitsLixo, arqSaida);
    }

    /*limpa memória dinamicamente alocada*/
    excluirCodigos(&listaCodigos);
    limparLista(&listaCodigos);

    /*fecha os arquivos*/
    fclose(arqEntrada);
    fclose(arqSaida);

    /*trava a execução*/
    printf("\nArquivo compactado");
    getchar();
}

static void descompactar()
{
    FILE *arqEntrada, *arqSaida;
    char buff[256];
    char bitsLixo;
    short int quantidadeInfoChars;
    unsigned int i;
    InfoChar infoChar;
    Lista listaInfoChars;
    No* noLista;
    NoArvore *noArvore;
    NoArvore *raiz;
    int dado;

    limparTela();
    inicializar(&listaInfoChars);

    printf("Digite o arquivo para descompactar: ");
    gets(buff);
    fflush(stdin);
    arqEntrada = fopen(buff, "rb");

    if(arquivoInvalido(arqEntrada, false))
        return;

    printf("Digite o arquivo de saida: ");
    gets(buff);
    fflush(stdin);
    arqSaida = fopen(buff, "wb");

    if(arquivoInvalido(arqSaida, true))
        return;

    /*lê a quantidade de bits de lixo*/
    bitsLixo = fgetc(arqEntrada);

    /*lê a quantidade de caracteres presentes e codificados*/
    fread(&quantidadeInfoChars, sizeof(short int), 1, arqEntrada);

    /*lê cada char e sua frequência e adiciona na lista*/
    for (i = 0; i < quantidadeInfoChars; ++i)
    {
        infoChar.caractere = fgetc(arqEntrada);
        fread(&infoChar.frequencia, sizeof(unsigned int), 1, arqEntrada);
        infoChar.temConteudo = true;
        inserirFim(&listaInfoChars, novaArvore(infoChar, NULL, NULL));
    }
    raiz = montarArvore(&listaInfoChars);

    /*percurso pela árvore com o texto codificado*/
    noArvore = raiz;
    for (dado = fgetc(arqEntrada); dado != EOF; dado = fgetc(arqEntrada))
    {
        /*determina-se a quantidade de bits que deve ser considerada do byte atual*/
        unsigned char ateOnde;
        int dado2 = fgetc(arqEntrada);

        if (dado2 == EOF)
            ateOnde = (8 - bitsLixo) + 1;
        else
            ateOnde = 8;
        ungetc(dado2, arqEntrada);

        /*percorre-se cada bit do byte atual percorrendo a árvore*/
        for (i = 0; i < ateOnde; i++)
        {
            /*se nó atual tem conteúdo, é escrito no arquivo*/
            if (noArvore->infoChar.temConteudo)
            {
                fputc(noArvore->infoChar.caractere, arqSaida);
                fflush(arqSaida);
                noArvore = raiz;
            }

            /*se pode continuar, vai para esquerda ou direita dependendo do bit*/
            if (ateOnde == 8 || i < ateOnde - 1)
            {
                if (isUm(i, dado))
                    noArvore = noArvore->direita;
                else
                    noArvore = noArvore->esquerda;
            }
        }
    }

    /*exclui nós da árvore*/
    excluirArvore(raiz);

    /*fecha os arquivos*/
    fclose(arqEntrada);
    fclose(arqSaida);

    /*trava a execução*/
    printf("\nArquivo descompactado");
    getchar();
}

int main()
{
    static void(*funcoes[2])() =
    {
        &compactar, &descompactar
    };

    for(;;)
    {
        char opcao = 0;

        puts("1- Compactar");
        puts("2- Descompactar");
        puts("0- Sair");
        printf("Qual opcao deseja? ");
        fflush(stdout);
        scanf("%i", &opcao);
        fflush(stdin);

        if(opcao <= 0 || opcao > 2)
            break;

        (*funcoes[opcao-1]) ();
        limparTela();
    }

    return 0;
}
