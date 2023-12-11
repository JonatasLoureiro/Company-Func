#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_FUNCIONARIO 50

typedef struct
{
    int dia;
    int mes;
    int ano;

} tipoData;

typedef struct
{
    int numero;
    char nome[50];
    float vencimento;
    tipoData dataAdmissao;

} tipoFunc;

//Funcoes para ler dados
void limpaBufferStdin(void);
int lerInteiro(int min, int max);
void lerString(char vetor[], int max);
float lerFloat(float min, float max);
tipoData lerData(void);
int procuraFunc(tipoFunc vetorFunc[MAX_FUNCIONARIO], int numFunc, int numeroDoFunc);


char menu(int quantidadeFunc, float mediaVencimento, int funcAdmitidos);
tipoFunc lerDadosFunc(void);
int addFunc(tipoFunc vetorFunc[MAX_FUNCIONARIO], int numFunc);
void mostraDados(tipoFunc funcionario);
void mostraTodosDados(tipoFunc vetorFunc[MAX_FUNCIONARIO],int numFunc);
void mostraDadosFunc(tipoFunc vetorFunc[MAX_FUNCIONARIO],int numFunc, int numero);
int calculaFuncNovembro(tipoFunc vetorFunc[MAX_FUNCIONARIO],int numFunc);
float calculoMediaVenc(tipoFunc vetorFunc[MAX_FUNCIONARIO],int numFunc);
void calculaVencimentoSuperior(tipoFunc vetorFunc[MAX_FUNCIONARIO],int numFunc);

int main(void)
{
    char opcao;
    tipoFunc vetorFunc[MAX_FUNCIONARIO];
    int numFunc, numFuncNovembro;
    float mediaVenc;
    numFunc = 0;
    numFuncNovembro = 0;
    mediaVenc = 0.0;
    int numero = 0;
    do
    {
        mediaVenc = calculoMediaVenc(vetorFunc, numFunc);
        numFuncNovembro = calculaFuncNovembro(vetorFunc,numFunc);
        opcao = menu(numFunc, mediaVenc,numFuncNovembro);
        switch(opcao)
        {
        case 'N':
            numFunc = addFunc(vetorFunc,numFunc);
            break;
        case 'L':
            if(numFunc==0)
            {
                printf("Nao existem funcionarios\n");
            }
            else
            {
                mostraTodosDados(vetorFunc,numFunc);
            }
            break;
        case 'M':
            if(numFunc==0)
            {
                printf("Nao existem funcionarios\n");
            }
            else
            {
                printf("Indique o numero do funcionario: ");
                numero = lerInteiro(0,9999);
                mostraDadosFunc(vetorFunc,numFunc,numero);
            }
            break;
        case 'P':
            calculaVencimentoSuperior(vetorFunc,numFunc);
            break;
        }


    }
    while(opcao!='S');
    return 0;
}


char menu(int quantidadeFunc, float mediaVencimento, int funcAdmitidos)
{
    char op;

    printf("\n*****************EMPRESA*****************");
    printf("\nFuncionario na empresa: %d \t\t Media dos Vencimentos: %.2f \nFuncionarios Admitidos em Novembro: %d", quantidadeFunc, mediaVencimento,funcAdmitidos);
    printf("\nNovo Funcionario - 'N'");
    printf("\nListar dados de funcionarios - 'L'");
    printf("\nMostrar Dados de um funcionario - 'M'");
    printf("\nPercentagem de funcionarios com vencimento superior a 1000 euros - 'P'");
    printf("\nSair - 'S'");
    printf("\n \t\t Opcao (N, L, M, P, S ) --> ");
    op = getchar();
    op = toupper(op);
    limpaBufferStdin();
    return op;
}

int procuraFunc (tipoFunc vetorFunc[], int numFunc, int numeroDoFunc)
{
    int i, pos;        /* posicao dos dados do estudante a procurar */
    pos = -1;

    for (i=0; i<numFunc; i++)
    {
        if (vetorFunc[i].numero == numeroDoFunc) 	/* Encontrado */
        {
            pos = i;	/* guarda posição de numero em vFunc */
            i = numFunc;	/* para concluir pesquisa (sair do for) */
        }
    }
    return pos;
}

tipoFunc lerDadosFunc() /*Le Dados de 1 funcionario*/
{
    tipoFunc dados;
    printf("Numero do funcionario: ");
    dados.numero = lerInteiro(0,99999);
    printf("Nome do Funcionario: ");
    lerString(dados.nome,50);
    printf("Vencimento do funcionario %s: ",dados.nome);
    dados.vencimento = lerFloat(0.0,9999.99);
    printf("Data de admissao do Funcionario: ");
    dados.dataAdmissao = lerData();
    return dados;

}
int addFunc(tipoFunc vetorFunc[MAX_FUNCIONARIO], int numFunc) /*Adiciona funcionario*/
{
    int pos;
    tipoFunc dados;
    if(numFunc==MAX_FUNCIONARIO) /*Verifica se excedeu-se a quantidade maxima de funcionario*/
    {
        printf("\nNao e possivel adicionar mais funcionarios");
    }
    else
    {
        dados=lerDadosFunc(); /*Le os dados de um funcionario*/
        pos = procuraFunc(vetorFunc,numFunc,dados.numero); /*Verifica se o funcionario ja existe*/
        if(pos!= -1)
        {
            printf("\nImpossivel inserir - Funcionario ja existe");
        }
        else
        {
            vetorFunc[numFunc]=dados;
            numFunc++;
        }
    }
    return numFunc;
}

void mostraDados(tipoFunc funcionario)
{

    printf("\n%d \t\t %s \t\t %.2f \t\t ",funcionario.numero,funcionario.nome,funcionario.vencimento);
    printf("%2d/%2d/%4d",funcionario.dataAdmissao.dia,funcionario.dataAdmissao.mes,funcionario.dataAdmissao.ano);
}
void mostraTodosDados(tipoFunc vetorFunc[MAX_FUNCIONARIO],int numFunc)
{
    int i;
    if(numFunc ==0)
    {
        printf("\nNao existem funcionarios");
    }
    else
    {
        printf("\nNumero \t\t Nome \t\t vencimento \t\t Data de Admissao\n");
        for(i=0; i<numFunc; i++)
        {
            mostraDados(vetorFunc[i]);

        }
    }
}

void mostraDadosFunc(tipoFunc vetorFunc[MAX_FUNCIONARIO],int numFunc, int numero)
{
    int pos;
    pos = procuraFunc(vetorFunc,numFunc,numero);
    if(pos!=-1)
    {
        printf("\nNumero \t\t Nome \t\t vencimento \t\t Data de Admissao\n");
        mostraDados(vetorFunc[pos]);
    }
    else{
        printf("Funcionario Nao existe");

    }
}

int calculaFuncNovembro(tipoFunc vetorFunc[MAX_FUNCIONARIO],int numFunc)
{
    int i,conta=0;
    for(i=0; i<numFunc; i++)
    {
        if(vetorFunc[i].dataAdmissao.mes == 11)
        {
            conta++;
        }
    }
    return conta;
}

float calculoMediaVenc(tipoFunc vetorFunc[MAX_FUNCIONARIO], int numFunc)
{
    float mediaVenc, somaVencimento;
    somaVencimento=0;
    int conta, i;
    conta = 0;
    if(numFunc==0)
    {
        mediaVenc=0;
    }
    else
    {
        for(i=0; i<numFunc; i++)
        {
            somaVencimento+=vetorFunc[i].vencimento;
        }
        mediaVenc = (float)somaVencimento/numFunc;
    }
    return mediaVenc;
}
void calculaVencimentoSuperior(tipoFunc vetorFunc[MAX_FUNCIONARIO],int numFunc)
{

    float mediaVenc, somaVencimento;
    int i, conta = 0;
    somaVencimento = 0.0;
    if(numFunc==0)
    {
        printf("\nNao existem Funcionarios\n");
        mediaVenc=0;
    }
    else
    {
        for(i=0; i<numFunc; i++)
        {
            if(vetorFunc[i].vencimento>=1000)
            {
                conta++;
            }
        }
        mediaVenc = (float)conta*100/numFunc;
        printf("Media dos funcionarios com vencimento superior a 1000 euros: %.2f",mediaVenc);
    }
}



/*Funcoes de Leitura de Dados*/
void lerString(char vetor[80], int max)
{

    int tamanhoString;

    do
    {
        fgets(vetor, max, stdin);
        tamanhoString = strlen(vetor);
    }
    while (tamanhoString == 1);	   /* Repete leitura se introduzida string apenas com o \n */

    if (vetor[tamanhoString-1] != '\n')
    {
        limpaBufferStdin(); 	/* limpa dados do buffer stdin */
    }
    else
    {
        vetor[tamanhoString-1] ='\0'; 	/* substitui por \0 o caracter \n da string armazenada */
    }

}


int lerInteiro(int min, int max) /*Le um numero inteiro entre min e max, confirmando se o utilizador nao colocou um carater*/
{
    int numero, controlo;

    do
    {
        controlo = scanf("%d", &numero);
        limpaBufferStdin();   /*limpa dados do buffer*/
    }
    while (numero<min || numero>max || controlo==0); /*repete a leitura enquando o numero estiver fora do intervalo e nao for digitado um caracter*/

    return numero;
}

float lerFloat(float min, float max) /*Le um numero inteiro entre min e max, confirmando se o utilizador nao colocou um carater*/
{
    float numero;
    int controlo;

    do
    {
        controlo = scanf("%f", &numero);
        limpaBufferStdin();   /*limpa dados do buffer*/
    }
    while (numero<min || numero>max || controlo==0); /*repete a leitura enquando o numero estiver fora do intervalo e nao for digitado um caracter*/

    return numero;
}


void limpaBufferStdin(void) 	/*Limpa o buffer*/
{
    char lixo;

    do
    {
        lixo=getchar();
    }
    while (lixo!='\n' && lixo!=EOF);
}

tipoData lerData(void) /*Le a data introduzida pelo utilizador confirmando se o ano e bissexto ou nao*/
{
    tipoData data;
    int maxDiaMes;

    printf("\n Ano (%d a %d): ",2014,2023);
    data.ano = lerInteiro(2014,2023);

    printf("Mes (%d a %d): ",1,12);
    data.mes = lerInteiro(1,12);

    switch (data.mes)
    {
    case 2:
        if((data.ano%400==0) || (data.ano%4==0 && data.ano%100!=0))
        {
            maxDiaMes = 29;    /* Ano bissexto */
        }
        else
        {
            maxDiaMes = 28;

        }
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        maxDiaMes = 30;
        break;
    default:
        maxDiaMes = 31;
    }
    printf("Dia (%d a %d): ",1,maxDiaMes);
    data.dia = lerInteiro(1, maxDiaMes);

    return data;
}
