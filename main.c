#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define debug() printf("kappa")



void init(){
    setlocale(LC_ALL, NULL);
}

void clearScreen(){
    system("cls");
}

void blankLine(){
    printf("\n\n");
}

int selecionarFase(){
    int fase=0;
    while(1){
        blankLine();
        printf("Por favor, selecione uma fase de 1 a 5(0 para voltar).\n");
        scanf("%d", &fase);
        if(fase>=0 && fase<=5)
            return fase;
    }
    
}

void start(){
    int op=-1;
    while(op!=0){
        printf("\nSeleciona uma opção:\n");
        printf("1. Jogar\t2. Inteligência Artificial\t0. Sair\n");
        scanf("%d", &op);
        if(op!=0){
            int fase = selecionarFase();
            if(fase!=0){
                printf("Função de load fase\n");
                if(op==1){
                    printf("Mostra dados da fase ao usuário, pede input, mostra o timer...\n");
                    if(1){//Se o jogo terminou...
                        printf("Mostra o score, salva no arquivo records.txt, se for um recorde\n");
                    }
                }
                else if(op==2){
                    int dificuldade;
                    printf("\nSelecione uma dificuldade:\n");
                    printf("1. Fácil\t2. Médio\t3. Difícil\t0. Sair\n");
                    scanf("%d", &dificuldade);
                    printf("Roda probabilidade para decidir se será usada a solução ótima...\n");
                    if(1){//Solução ótima
                        printf("Roda programação dinâmica\n");
                    }else{
                        printf("Roda outra solução\n");
                    }
                }
            }
        }

    }
}

int main(){
    printf("%s", setlocale(LC_ALL, ""));
    
    start();
    
}