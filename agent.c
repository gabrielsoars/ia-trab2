#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "agent.h"
#include "inference.h"

agent newAgent(enviroment E){
    agent A;
    A.score = 0;
    A.temFlecha = true;
    A.onde = &E.grid[0][0];
    A.comOuro = false;
    A.knowledgeBase = newKnowledgeBase(E);
    return A;
}

void sense(agent A){
    if (A.onde->S.cheiro){
        A.knowledgeBase[A.onde->row][A.onde->col].cheiro = true;
        printf("Aqui há um cheiro monstruoso. \n");
    }
    if (A.onde->S.vento){
        A.knowledgeBase[A.onde->row][A.onde->col].vento = true;
        printf("Aqui está batendo um vento estranho. \n");
    }
}

bool move(agent* A, enviroment E, place* target){
/*
    Movimenta o agente para a posição place, desde que esta seja uma vizinha de
    cleaner.ondeCleaner e que a bateria de C não esteja vazia.
*/
    if (isNeighbor(*A->onde,*target)){
        A->onde = target;
        A->score--;
        A->knowledgeBase[A->onde->row][A->onde->col].visitado = true;
        if (A->onde->monstro){
            if (A->temFlecha){
                printf("Matou o monstro. \n");
                A->score -= 10;
                A->onde->monstro = false;
                A->knowledgeBase[A->onde->row][A->onde->col].monstro = false;
            }
            else{
                A->knowledgeBase[A->onde->row][A->onde->col].monstro = true;
                printf("Pego pelo monstro.\n");
                A->score -= 1000;
            }
        }
        if (A->onde->buraco){
            A->knowledgeBase[A->onde->row][A->onde->col].buraco = true;
            printf("Caiu no buraco. \n");
            A->score -= 1000;
        }
        if (A->onde->ouro){
            printf("O ouro está aqui! \n");
            A->comOuro = true;
        }
        if (A->comOuro && A->onde->row==E.h-1 && A->onde->col==E.w-1){
            printf("Escapou com o ouro! Parabéns. \n");
        }
        return true;
    }
    return false;
}

void printSimulation(agent A, enviroment E){
    for (int i=0; i<E.h; i++){
        for (int j=0; j<E.w; j++){
            place current = E.grid[i][j];
            if (&E.grid[i][j]==A.onde){
                printf("O ");
            }
            else if (current.buraco) {
                printf("+ ");
            }
            else if (current.monstro){
                printf("# ");
            }
            else if (current.ouro){
                printf("$ ");
            }
            else{
                printf("_ ");
            }
        }
        printf("\n");
    }
}