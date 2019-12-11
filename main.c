#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <locale.h>
//#define debug() printf("kappa\n")

typedef struct
{
    int valor, peso;
} Item;
int numItens, tamMochila;

Item *getArq(int);

void start();
void init();
void clearScreen();
void blankLine();
void printArq(Item*);
int isItemEscolhido(int*, int, int);
int getPesoFromData(Item*, int);
int getScore(Item*, int*, int);

int selecionarFase();

int main()
{
    init();
    start();
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
                Item *dadosFase = getArq(fase);
                if (op == 1)
                {
                    int escolha=-1, weightLeft = tamMochila, quantItensEscolhidos=0;
                    int *itensEscolhidos = NULL;
					//int scoret=getScore(dadosFase, itensEscolhidos, quantItensEscolhidos);
                    //printf("scoret: %d\n",scoret);
                    while(escolha!=0 && weightLeft!=0){
                        printArq(dadosFase);
                        //printf("\nPeso sobrando: %d\t Pontuação Atual: %d\n", weightLeft,scoret);
                        printf("Escolha um item de 1 à %d (digite 0 para encerrar gameplay)\n", numItens);
                        scanf("%d", &escolha);
                        if(escolha!=0){
                            if(!isItemEscolhido(itensEscolhidos, quantItensEscolhidos, escolha-1)){
                                int temp = escolha-1;
                                int pesoAtual = getPesoFromData(dadosFase, temp);
                                if(weightLeft-pesoAtual<0){
                                    clearScreen();
                                    printf("Não é possível botar o item %d na mochila\n", escolha);
                                }
                                else{
                                    if(quantItensEscolhidos==0)
                                        itensEscolhidos = (int*)malloc(sizeof(int)*(++quantItensEscolhidos));
                                    else
                                        itensEscolhidos = (int*)realloc(itensEscolhidos, sizeof(int)*(++quantItensEscolhidos));
                                    *(itensEscolhidos+(quantItensEscolhidos-1)) = escolha-1;
                                    weightLeft -= pesoAtual;
                                    clearScreen();
                                }
                            }else{
                                clearScreen();
                                printf("Item %d já foi escolhido. Escolha outro!\n", escolha);
                            }/*
                                for(int i=0;i<quantItensEscolhidos;i++) printf("%d",itensEscolhidos[i]);
                                printf("%d",quantItensEscolhidos);
                                */
                        }
                        
                    }

					//printf("Pontuação Total: %d\n",scoret);
                    printf("score: %d\n", getScore(dadosFase, itensEscolhidos, quantItensEscolhidos));
					//if (scoret>highscore) registraScore(scoret);
                    //Mostra o score, salva no arquivo records.txt, se for um recorde
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

int getPesoFromData(Item *data, int pos){
    return (data+pos)->peso;
}

int isItemEscolhido(int *itensEscolhidos, int tamanhoEscolhidos, int itemProcurado){
    if(itensEscolhidos==NULL)
        return 0;
    for(int i=0; i<tamanhoEscolhidos; i++){
        if(*(itensEscolhidos+i)==itemProcurado)
            return 1;
    }
		free(itensEscolhidos);
    return 0;
}

int getScore(Item* data, int* itensEscolhidos, int quantItensEscolhidos){
    int score = 0;
    for(int i=0; i<quantItensEscolhidos; i++)
        score += (data+(*(itensEscolhidos+i)))->valor;
    return score;   
}

Item * getArq(int fase)
{
    FILE *arq;
    char str[] = "mochila", ext[] = ".txt", path[] = "./inputs/";
    int aux, tam, max;
    char *r = (char*)calloc(100, sizeof(char));
    char *temp = (char*)malloc(2*sizeof(char));
    *temp = fase+'0';
    *(temp+1)='\0';
    
    //ABRINDO O ARQUIVO DA FASE ESCOLHIDA
    strcat(r, path);
    strcat(r, str);
    strcat(r, temp);
    strcat(r, ext);

    arq = fopen(r,"r");
    if(arq == NULL) printf("ERRO DE LEITURA!\n");

    fscanf(arq,"%d", &tam);
    fscanf(arq,"%d", &max);
    numItens = tam;
    tamMochila = max;

    Item *itens = (Item*)malloc(tam * sizeof(Item));

    for (int i = 0; i < tam; i++) fscanf(arq,"%d", &itens[i].valor);
    for (int i = 0; i < tam; i++) fscanf(arq,"%d", &itens[i].peso);

    //for (int i = 0; i < tam; i++) printf("%d - VALOR:%d PESO:%d\n", i, itens[i].valor, itens[i].peso);

    fclose(arq);
    return itens;
}
/*
int getRecords(int *v, int tam)
{
    FILE *arq;
    arq = fopen("./inputs/records.txt", "r");
    if (arq == NULL) printf("Erro de leitura!\n");

    v = malloc(tam * sizeof(int));
    
    for (int i = 0; i < tam; i++) fscanf(arq, "%d", &v[i]);
    for (int j = 0; j < tam; j++) printf("%d\n", v[j]);
    fclose(arq);
    return *v;
}
int ordenarRecords(int *v,int tam)
{
    for (int i = 1; i < tam;i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (v[i] > v[j])
            {
                int aux = v[i];
                v[i] = v[j];
                v[j] = aux;
            }
        }
    }
    return v;
}
void registraScore(int *scoret){
	FILE*pont_records;

	pont_records=fopen("inputs\records.txt","w");

	if (pont_records==NULL){
		printf("Erro na abertura!\n");
		return 1;
	}

	fprintf(pont_arq,"%d",*scoret);
	fclose(pont_arq);
}
*/
void printArq(Item *data){
    for(int i=0; i<numItens; i++){
        if(i%5==0)
            printf("\n");
        
        printf("Item %d: %dkg\tR$%d | ", i+1, (data+i)->peso, (data+i)->valor);
        
    }
}

void init()
{
    setlocale(LC_ALL, "");
}

void clearScreen()
{
//    system("clear");
}

void blankLine()
{
    printf("\n\n");
}

void erro(){
    printf("Erro, digite um valor válido.\n");
}

int selecionarFase()
{
    int fase = 0;
    while (1)
    {
        blankLine();
        printf("Por favor, selecione uma fase de 1 a 5 (pressione 0 para voltar).\n");
        scanf("%d", &fase);
        if (fase >= 0 && fase <= 5)
            return fase;
        else erro();
    }
}
/*
int getScore2(Item* item,int quantItensEscolhidos,int ){
    Item *itema;
    if (quantItensEscolhidos>0) {
        for(i=0;i<quantItensEscolhidos;i++){
            itema=item[i];
        }
    }
}
*/