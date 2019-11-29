#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <locale.h>

#define debug() printf("kappa\n")

typedef struct
{
    int valor, peso;
} item;


item * getArq(char *fase)
{
    FILE *arq;
    char str[] = "mochila", ext[] = ".txt", path[] = "./inputs/";
    int aux, tam, max;
    char *r = (char*)calloc(100, sizeof(char));
    
    //ABRINDO O ARQUIVO DA FASE ESCOLHIDA
    strcat(r, path);
    strcat(r, str);
    strcat(r, fase);
    strcat(r, ext);
    puts(r);

    arq = fopen(r,"r");
    if(arq == NULL) printf("ERRO DE LEITURA!\n");

    fscanf(arq,"%d", &tam);
    fscanf(arq,"%d", &max);

    item *itens = (item*)malloc(tam * sizeof(item));

    for (int i = 0; i < tam; i++) fscanf(arq,"%d", &itens[i].valor);
    for (int i = 0; i < tam; i++) fscanf(arq,"%d", &itens[i].peso);

    //for (int i = 0; i < tam; i++) printf("%d - VALOR:%d PESO:%d\n", i, itens[i].valor, itens[i].peso);

    fclose(arq);
    return itens;
}

void init()
{
    setlocale(LC_ALL, NULL);
}

void clearScreen()
{
    system("cls");
}

void blankLine()
{
    printf("\n\n");
}

int selecionarFase()
{
    int fase = 0;
    while (1)
    {
        blankLine();
        printf("Por favor, selecione uma fase de 1 a 5(0 para voltar).\n");
        scanf("%d", &fase);
        if (fase >= 0 && fase <= 5)
            return fase;
    }
}

void start()
{
    int op = -1;
    while (op != 0)
    {
        printf("\nSeleciona uma opção:\n");
        printf("1. Jogar\t2. Inteligência Artificial\t0. Sair\n");
        scanf("%d", &op);
        if (op != 0)
        {
            int fase = selecionarFase();
            if (fase != 0)
            {
                printf("Função de load fase\n");
                if (op == 1)
                {
                    printf("Mostra dados da fase ao usuário, pede input, mostra o timer...\n");
                    if (1)
                    { //Se o jogo terminou...
                        printf("Mostra o score, salva no arquivo records.txt, se for um recorde\n");
                    }
                }
                else if (op == 2)
                {
                    int dificuldade;
                    printf("\nSelecione uma dificuldade:\n");
                    printf("1. Fácil\t2. Médio\t3. Difícil\t0. Sair\n");
                    scanf("%d", &dificuldade);
                    printf("Roda probabilidade para decidir se será usada a solução ótima...\n");
                    if (1)
                    { //Solução ótima
                        printf("Roda programação dinâmica\n");
                    }
                    else
                    {
                        printf("Roda outra solução\n");
                    }
                }
            }
        }
    }
}
int main()
{
    char temp[] = "1";
    item *escolha = getArq(temp);
    start();
}