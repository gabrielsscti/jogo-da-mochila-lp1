#include "includes.h"
#include "./helpers/gamestates.h"
#include "./functions/functions.h"



int actState;

int main(){
    actState = getDefaultGameState();
    while(isGameRunning(actState)){
        printf("Kappa Pride");
    }
    
}