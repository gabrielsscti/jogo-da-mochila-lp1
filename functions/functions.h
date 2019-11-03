int getDefaultGameState(){
    return MainMenu;
}

int isGameRunning(int gamestate){
    if(gamestate==MainMenu || gamestate==Running)
        return 1;

    return 0;
}