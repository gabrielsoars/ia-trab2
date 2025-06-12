#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "inference.h"


void inferHoles(agent *A, enviroment *E) {
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

        if (v >= 0 && v < E->h && w >= 0 && w < E->w && !A->knowledgeBase[v][w].visitado) {
            possiveisBuracos[count][0] = v;
            possiveisBuracos[count][1] = w;
            count++;

            // Marcar como possivelmente perigoso se ainda nao foi inferido como buraco
            if (!A->knowledgeBase[v][w].buraco)
                A->knowledgeBase[v][w].possivelBuraco = true;
        }
    }

    // Inferencia com cruzamento de informacoes
    for (int k = 0; k < count; k++) {
        int v = possiveisBuracos[k][0];
        int w = possiveisBuracos[k][1];

        for (int d = 0; d < 4; d++) {
            int x = v + dx[d];
            int y = w + dy[d];

            if (x >= 0 && x < E->h && y >= 0 && y < E->w &&
                A->knowledgeBase[x][y].vento && !(x == i && y == j)) {
                A->knowledgeBase[v][w].buraco = true;
                A->knowledgeBase[v][w].possivelBuraco = false;
                printf("-------------------- Inferido: ha um buraco em (%d, %d)\n", v, w);
                break;
            }
        }
    }
}

void inferMonsters(agent *A, enviroment *E) {
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

        if (v >= 0 && v < E->h && w >= 0 && w < E->w && !A->knowledgeBase[v][w].visitado) {
            possiveisMonstros[count][0] = v;
            possiveisMonstros[count][1] = w;
            count++;

            if (!A->knowledgeBase[v][w].monstro)
                A->knowledgeBase[v][w].possivelMonstro = true;
        }
    }

    for (int k = 0; k < count; k++) {
        int v = possiveisMonstros[k][0];
        int w = possiveisMonstros[k][1];

        for (int d = 0; d < 4; d++) {
            int x = v + dx[d];
            int y = w + dy[d];

            if (x >= 0 && x < E->h && y >= 0 && y < E->w &&
                A->knowledgeBase[x][y].cheiro && !(x == i && y == j)) {
                A->knowledgeBase[v][w].monstro = true;
                A->knowledgeBase[v][w].possivelMonstro = false;
                printf("-------------------- Inferido: ha um monstro em (%d, %d)\n", v, w);
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

// Função de distância de Manhattan
int distanciaObjetivo(int i, int j, int fim_i, int fim_j) {
    return abs(fim_i - i) + abs(fim_j - j);
}


bool isBeco(agent *A, enviroment *E, int x, int y) {
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    int vizinhosSeguros = 0;

    for (int d = 0; d < 4; d++) {
        int nx = x + dx[d];
        int ny = y + dy[d];

        if (nx >= 0 && nx < E->h && ny >= 0 && ny < E->w) {
            knowledge k = A->knowledgeBase[nx][ny];

            bool seguro = !k.buraco && !k.monstro && !k.possivelBuraco && !k.possivelMonstro;
            if (seguro && !k.visitado) {
                vizinhosSeguros++;
            }
        }
    }

    return vizinhosSeguros == 0;  
}

place *inferBestMove(agent *A, enviroment *E) {
    int i = A->onde->row;
    int j = A->onde->col;

    inferHoles(A, E);
    inferMonsters(A, E);

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    place *melhorOpcao = NULL;
    int menorPenalidade = 100000;

    for (int d = 0; d < 4; d++) {
        int ni = i + dx[d];
        int nj = j + dy[d];

        if (ni >= 0 && ni < E->h && nj >= 0 && nj < E->w) {
            knowledge k = A->knowledgeBase[ni][nj];

            int penalidade = 0;

            if (k.buraco) penalidade += 1000;
            if (k.monstro) penalidade += A->temFlecha ? 10 : 1000;
            if (k.possivelBuraco) penalidade += 900;
            if (k.possivelMonstro) penalidade += A->temFlecha ? 9 : 900;
            if (k.visitado) penalidade += 5;

            // Penalidade extra se for beco
            if (isBeco(A, E, ni, nj)) {
                penalidade += 9999;
            }

            if (penalidade < menorPenalidade) {
                menorPenalidade = penalidade;
                melhorOpcao = &E->grid[ni][nj];
            }
        }
    }

    return melhorOpcao;
}