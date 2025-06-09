#include <stdio.h>
#include <stdbool.h>
#include "inference.h"
#include "env.h"

int main(){
    int m = 5;
    int n = 5;

    enviroment E = newEnviroment(m, n);
    int numBuraco = 3; int numMonstro = 1;
    initEnviroment(E,numBuraco,numMonstro);
    agent A = newAgent(E);

    printf("Você está em uma sala com dimensões %d x %d. \n",E.h,E.w);
    printf("Nesta sala há %d buracos, %d monstros e uma barra de ouro. \n", 
        numBuraco,numMonstro);
    printf("Seu objetivo é chegar na posição (%d,%d) em posse do ouro.",
        E.h-1,E.w-1);
    printf("Fazendo a menor quantidade de movimentos possível. \n");
    printf("Você começa na posição (0,0). Boa sorte! \n");

    char mov;

    int maxMoves = 10 * (m * n);
    int countMoves = 0;
    while((!(A.comOuro && A.onde->row==E.h-1 && A.onde->col==E.w-1)) && (countMoves < maxMoves)){
        printf("Score atual: %d \n", A.score);
        printSimulation(A,E);
        sense(A);
        place * melhorMov = inferBestMove(&A, &E);
        printf("Mova-se para: (%d, %d)\n", melhorMov->row, melhorMov->col);
        printf("Para onde você deseja se mover? \n");
        move(&A, E, melhorMov);
        countMoves++;
    }
    printf("Score final: %d \n",A.score);
    free(A.knowledgeBase);

    return 0;
}