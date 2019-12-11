#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <locale.h>
#include <time.h>
#define max(a, b) (a>b ? (a) : (b))
#define debug() printf("kappa\n")

int **dp;

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
int *getRecords();
int *ordenarRecords(int *,int );
void registraScore(int );
int dpSolve(int, int, Item*);
void showHighScores();


int selecionarFase();

int main()
{
    init();
    start();
}

int isOtima(int chance){
    srand((unsigned) time(NULL));
    if(chance<=((rand()%100)+1))
        return 1;
    return 0;
}

int getProbability(int difficulty){
    if(difficulty==1)
        return 50;
    if(difficulty==2)
        return 75;
    if(difficulty==3)
        return 95;
}

int gulosoSolve(Item *itens){
    int r = 0, peso=0;
    for(int i=0; i<numItens; i++){
        int largerValor = -1, largerId;
        for(int j=0; j<numItens; j++){
            if(i!=j){
                if(itens[j].valor > largerValor){
                    largerValor = itens[j].valor;
                    largerId = j;
                }
            }
        }
        if(peso+itens[largerId].peso>tamMochila)
            break;
        peso += itens[largerId].peso;
        r += itens[largerId].valor;
        itens[largerId].valor = -10;
    }
    return r;
}

int dpSolve(int id, int peso, Item *itens){
    if(peso==0 || id==numItens)
        return 0;
    if(dp[id][peso]!=-1)
        return dp[id][peso];
    if(itens[id].peso>peso)
        return dp[id][peso] = dpSolve(id+1, peso, itens);
    return dp[id][peso] = max(dpSolve(id+1, peso, itens), itens[id].valor+dpSolve(id+1, peso-itens[id].peso, itens));
}

void start()
{
    int op = -1;
    while (op != 0)
    {
        printf("\nSeleciona uma opção:\n");
        printf("1. Jogar\t2. Inteligência Artificial\t3. High scores\t0. Sair\n");
        scanf("%d", &op);
        if (op != 0)
        {
            int fase;
            if(op!=3)
                fase = selecionarFase();
            if (fase != 0)
            {
                Item *dadosFase;
                if(op!=3)
                    Item *dadosFase = getArq(fase);
                if (op == 1){
                    int escolha=-1, weightLeft = tamMochila, quantItensEscolhidos=0;
                    int *itensEscolhidos = NULL;
                    while(escolha!=0 && weightLeft!=0){
                        printArq(dadosFase);
                        printf("\nPeso sobrando: %d\n", weightLeft);
                        printf("Seu score: %d\n", getScore(dadosFase,itensEscolhidos, quantItensEscolhidos));
                        printf("\nEscolha um item de 1 à %d (digite 0 para encerrar gameplay)\n", numItens);
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
                    int score = getScore(dadosFase, itensEscolhidos, quantItensEscolhidos);
					//printf("Pontuação Total: %d\n",scoret);
                    printf("score: %d\n", score);
                    registraScore(score);
					//if (scoret>highscore) registraScore(scoret);
                    //Mostra o score, salva no arquivo records.txt, se for um recorde
                }
                else if (op == 2)
                {
                    int dificuldade;
                    printf("\nSelecione uma dificuldade:\n");
                    printf("1. Fácil\t2. Médio\t3. Difícil\t0. Sair\n");
                    scanf("%d", &dificuldade);
                    if (!isOtima(getProbability(dificuldade)))
                    { //Solução ótima
                        dp = (int**)malloc(sizeof(int*)*(numItens+1));
                        for(int i=0; i<numItens+1; i++)
                            *(dp+i) = (int*)malloc((sizeof(int)*(tamMochila+10)));
                        for(int i=0; i<numItens+1; i++){
                            for(int j=0; j<tamMochila+10; j++)
                                dp[i][j] = -1;
                        }
                        printf("Resultado: R$%d\n", dpSolve(0, tamMochila, dadosFase));
                    }
                    else{
                        printf("Resultado: %d\n", gulosoSolve(dadosFase));
                    }
                }
                else if(op == 3){
                    showHighScores();
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






int *getRecords()
{
    int *v = (int*)malloc(sizeof(int)*11);
    for(int i=0; i<11; i++)
        v[i] = -1;
    FILE *arq;
    arq = fopen("./scores/records.txt", "r");
    if (arq == NULL) printf("Erro de leitura!\n");
    int cont = 0;
    while(!feof(arq))
        fscanf(arq, "%d", &v[cont++]);
    
    
    fclose(arq);
    return v;
}

int *ordenarRecords(int *v,int tam)
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

void registraScore(int score){
	int *v = getRecords();
    int lastPosition = 0;
    for(int i=0; i<11; i++)
        if(v[i]==-1)
            lastPosition = i;
    v[lastPosition] = score;
    v = ordenarRecords(v, lastPosition+1);
	FILE *f = fopen("./scores/records.txt", "w");
    for(int i=0; i<10; i++)
        fprintf(f, "%d\n", v[i]);
    fclose(f);

}

void showHighScores(){
    int *v = getRecords();
    for(int i=0; i<10; i++){
        if(v[i]!=-1)
            printf("%d. %d\n", i+1, v[i]);
    }
    
}





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