#include <stdio.h>
#include <stdlib.h>

#include "fila.h"
#include "charcodigo.h"

#define TAMANHO_VETOR 256
#define MAX_BUFFER 1024

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
    uint32 frequencias[TAMANHO_VETOR];
    char buff[MAX_BUFFER];
    FILE *arqEntrada, *arqSaida;
    Lista filaInfoChars;
    int dado;
    uint32 i;
    NoArvore* noArvore;
    short int qtdCharCodigos;
    No *noLista;
    CharCodigo *vetorCodigos;
    uint32 tamanhoString;
    char *textoCodificado;
    unsigned char byte;
    unsigned char bitsLixo;

    limparTela();
    limparVetor(
        frequencias,
        TAMANHO_VETOR);
    inicializar(&filaInfoChars);

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

    /*l� arquivo e coloca frequ�ncia de cada char na posi��o correspondente*/
    while((dado = fgetc(arqEntrada)) != EOF)
        frequencias[dado]++;

    /*percorre vetor de frequ�ncias e insere n�s na filaInfoChars*/
    for(i = 0; i < TAMANHO_VETOR; ++i)
    {
        if (frequencias[i])
        {
            InfoChar infoChar;

            infoChar.caractere = i;
            infoChar.frequencia = frequencias[i];
            infoChar.temConteudo = true;

            noArvore = novaArvore(
                infoChar,
                NULL,
                NULL);

            inserirFila(&filaInfoChars, noArvore);
        }
    }

    /*bits que s�o lixo; ser�o sobrescritos posteriormente*/
    fputc(0, arqSaida);

    /*quantidade de caracteres*/
    qtdCharCodigos = quantidade(&filaInfoChars);
    fwrite(&qtdCharCodigos, sizeof(short int), 1, arqSaida);

    /*escreve cada char e frequ�ncia dele*/
    for(noLista = filaInfoChars.inicio;
        noLista;
        noLista = noLista->prox)
    {
        InfoChar infoChar;

        infoChar = ((NoArvore*) noLista->info)->infoChar;
        fputc(infoChar.caractere, arqSaida);
        fwrite(&infoChar.frequencia, sizeof(unsigned int), 1, arqSaida);
    }

    /*cria��o da �rvore de huffman*/
    noArvore = montarArvore(&filaInfoChars);

    /*monta-se o vetor com caracteres e c�digos*/
    vetorCodigos = (CharCodigo*) malloc(qtdCharCodigos * sizeof(CharCodigo));
    tamanhoString = pegarCodigos(noArvore, vetorCodigos);

    ordenar(vetorCodigos, qtdCharCodigos);

    for(i = 0; i < qtdCharCodigos; ++i)
    {
        CharCodigo charCodigo = vetorCodigos[i];
        printf("%c : %s\n", charCodigo.caractere, charCodigo.codigo);
    }


    /*aloca dinamicamente string com todo o texto codificado*/
    textoCodificado = (char*)malloc(tamanhoString + 1);
    textoCodificado[0] = 0;

    /*reinicia arquivo para segunda leitura*/
    rewind(arqEntrada);

    /*l� cada caractere do arquivo e concatena seu c�digo no textoCodificado*/
    for (i = 0, dado = getc(arqEntrada); dado != EOF; dado = getc(arqEntrada))
    {
        char *codigoObtido =  codigoDe(dado, vetorCodigos, qtdCharCodigos);

        if (codigoObtido)
        {
            strcat(textoCodificado + i, codigoObtido);
            i += strlen(codigoObtido);
        }
    }

    /*percorre a string; gera e escreve os bytes correspondentes*/
    for(byte = 0, i = 0; i < tamanhoString; ++i)
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

    /*limpa mem�ria dinamicamente alocada*/
    excluirArvore(noArvore);
    excluirCodigos(vetorCodigos, qtdCharCodigos);
    free(textoCodificado);
    free(vetorCodigos);

    /*fecha os arquivos*/
    fclose(arqEntrada);
    fclose(arqSaida);

    /*trava a execu��o*/
    printf("\nArquivo compactado");
    getchar();
}

static void descompactar()
{
    char buff[MAX_BUFFER];
    FILE *arqEntrada, *arqSaida;
    char bitsLixo;
    short int quantidadeInfoChars;
    unsigned int i;
    Lista listaInfoChars;
    No* noLista;
    NoArvore *raiz, *noArvore;
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

    /*l� a quantidade de bits de lixo*/
    bitsLixo = fgetc(arqEntrada);

    /*l� a quantidade de caracteres presentes e codificados*/
    fread(&quantidadeInfoChars, sizeof(short int), 1, arqEntrada);

    /*l� cada char e sua frequ�ncia e adiciona na lista*/
    for (i = 0; i < quantidadeInfoChars; ++i)
    {
        InfoChar infoChar;

        infoChar.caractere = fgetc(arqEntrada);
        fread(&infoChar.frequencia, sizeof(unsigned int), 1, arqEntrada);
        infoChar.temConteudo = true;
        inserirFim(&listaInfoChars, novaArvore(infoChar, NULL, NULL));
    }

    /*cria��o da �rvore de huffman*/
    raiz = montarArvore(&listaInfoChars);

    /*percurso pela �rvore com o texto codificado*/
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

        /*percorre-se cada bit do byte atual alterando o ponteiro noArvore*/
        for (i = 0; i < ateOnde; i++)
        {
            /*se n� atual tem conte�do, � escrito no arquivo*/
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

    /*desaloca �rvore alocada dinamicamente*/
    excluirArvore(raiz);

    /*fecha os arquivos*/
    fclose(arqEntrada);
    fclose(arqSaida);

    /*trava a execu��o*/
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
