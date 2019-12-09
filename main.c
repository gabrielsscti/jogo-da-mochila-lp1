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
                    while(escolha!=0 && weightLeft!=0){
                        printArq(dadosFase);
                        printf("\nPeso sobrando: %d\n", weightLeft);
                        printf("Escolha um item de 1 à %d(0 para encerrar gameplay)", numItens);
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
                            }
                        }
                    }
                    printf("%d", getScore(dadosFase, itensEscolhidos, quantItensEscolhidos));
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
//ideias para a função de salvar o score
/*
int saveScore(){
	static tam=1;
	int *ptr_vector_score;
	ptr_vector_score = (int *)malloc(sizeof(int));
	ptr_vector_score[tam]= getScore();
	FILE*records;
	records=fopen("\inputs\records.txt","w");
	fprint(ptr_vector_score[tam]);
	tam++;
	fclose(records);
	free(ptr_vector_score);
}
*/
/*
int ordenateRecords(){
	int tam;
	FILE*records;
	records=fopen("\inputs\records.txt","r");
	char *ptr_ordnt_score;
	ptr_ordnt_score=(int*)malloc(sizeof(int));
	fgets(ptr_ordnt_score,sizeof(ptr_ordnt_score),records);
	//codigo de ordenar vetor
}
*/
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


void printArq(Item *data){
    for(int i=0; i<numItens; i++){
        if(i%5==0)
            printf("\n");
        
        printf("Item %d: %dkg\tR$%d | ", i+1, (data+i)->peso, (data+i)->valor);
        
    }
    printf("%n");
}

void init()
{
    setlocale(LC_ALL, "");
}

void clearScreen()
{
    system("cls");
}

void blankLine()
{
    printf("\n\n");
}

void erro(){
    printf("Erro\n");
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
        else erro();
    }
}