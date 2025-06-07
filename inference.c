#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "inference.h"

void inferHoles(agent * A, enviroment * E){
    int i = A->onde->row;
    int j = A->onde->col;

    if (!A->knowledgeBase[i][j].vento)
        return;

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    int possiveisBuracos[4][2];
    int count = 0;

    for (int d = 0; d < 4; d++) {
        int v = i + dx[d];
        int w = j + dy[d];

        if ((v >= 0 && v < E->h && w >= 0 && w < E->w) && (!A->knowledgeBase[v][w].visitado)){
            possiveisBuracos[count][0] = v;
            possiveisBuracos[count][1] = w;
            count++;
        }
    }

    for (int k = 0; k < count; k++) {
        int v = possiveisBuracos[k][0];
        int w = possiveisBuracos[k][1];

        for (int d = 0; d < 4; d++) {
            int x = v + dx[d];
            int y = w + dy[d];

            if ((x >= 0 && x < E->h && y >= 0 && y < E->w) && (A->knowledgeBase[x][y].vento) && (x != i && y != j)){
                A->knowledgeBase[v][w].buraco = true;
                printf("-------------------- Há um buraco em (%d, %d)\n", v, w);
                break;
            }
        }
    }
}

void inferMonsters(agent * A, enviroment * E){
    int i = A->onde->row;
    int j = A->onde->col;

    if (!A->knowledgeBase[i][j].cheiro)
        return;

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    int possiveisMonstros[4][2];
    int count = 0;

    for (int d = 0; d < 4; d++) {
        int v = i + dx[d];
        int w = j + dy[d];

        if ((v >= 0 && v < E->h && w >= 0 && w < E->w) && (!A->knowledgeBase[v][w].visitado)){
            possiveisMonstros[count][0] = v;
            possiveisMonstros[count][1] = w;
            count++;
        }
    }

    for (int k = 0; k < count; k++) {
        int v = possiveisMonstros[k][0];
        int w = possiveisMonstros[k][1];

        for (int d = 0; d < 4; d++) {
            int x = v + dx[d];
            int y = w + dy[d];

            if ((x >= 0 && x < E->h && y >= 0 && y < E->w) && (A->knowledgeBase[x][y].cheiro) && (x != i && y != j)){
                A->knowledgeBase[v][w].monstro = true;
                printf("-------------------- Há um monstro em (%d, %d)\n", v, w);
                break;
            }
        }
    }
}

knowledge ** newKnowledgeBase(enviroment E){
    knowledge ** matriz = malloc(E.h * sizeof(knowledge));
    if (matriz != NULL){
        for (int i = 0; i < E.h; i++){
            matriz[i] = malloc(E.w * sizeof(knowledge));
            if (matriz[i] != NULL){
                for (int j = 0; j < E.w; j++){
                    matriz[i][j].visitado = false;
                    matriz[i][j].cheiro = false;
                    matriz[i][j].vento = false;
                    matriz[i][j].buraco = false;
                    matriz[i][j].monstro = false;
                }
            }
        }
    }
    return matriz;
}