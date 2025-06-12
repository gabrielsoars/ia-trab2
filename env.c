#include "env.h"
#include <time.h>
#include <stdio.h>
#include <unistd.h>
//#include <windows.h> função sleep no windows

#define NUM_PRESETS 10

void setSensation(place* p, place* v){

    if (isNeighbor(*v,*p)){
        if (v->buraco)
            p->S.vento = true;
        if (v->monstro)
            p->S.cheiro = true;
    }
}

/*------------------------------------------------------------------------------
    Funções básicas do ambiente
------------------------------------------------------------------------------*/

enviroment newEnviroment(int h, int w){
    enviroment E;
    E.h = h; E.w = w;
    E.grid = malloc(E.h*sizeof(place*));
    if (E.grid!=NULL){
        for (int i=0; i<h; i++){
            E.grid[i] = malloc(E.w*sizeof(place));
            if (E.grid[i]!=NULL)
                for (int j=0; j<w; j++){
                    E.grid[i][j].buraco = false;
                    E.grid[i][j].monstro = false;
                    E.grid[i][j].ouro = false;
                    E.grid[i][j].S.cheiro = false;
                    E.grid[i][j].S.vento = false;
                    E.grid[i][j].row = i;
                    E.grid[i][j].col = j;
                }
        }
    }
    return E;
}

void delEnviroment(enviroment* E){
    if (E!=NULL){
        for (int i=0; i<E->h; i++){
            free(E->grid[i]);
        }
        free(E->grid);
    }
}

void initEnviroment(enviroment E, int numBuraco, int numMonstro){
/*
    Inicializa grid de teste.
*/
    E.grid[1][1].monstro = true;
    E.grid[2][1].buraco = true;
    E.grid[2][3].buraco = true;
    E.grid[3][2].buraco = true;
    E.grid[3][1].ouro = true;
    initSensations(E);
}

void initSensations(enviroment E){
    //Itera sobre posições no grid
    for (int i=0; i<E.h; i++)
        for (int j=0; j<E.w; j++){
            //Itera sobre vizinhos
            for (int k=0; k<E.h; k++)
                for (int l=0; l<E.w; l++){
                    setSensation(&E.grid[i][j],&E.grid[k][l]);
                }
        }
}

bool isNeighbor(place p, place q){
/*
    Considerando vizinhança-4 (em cruz). No exemplo abaixo, as posições marcadas
    como v são vizinhas de o, enquanto aquelas marcadas como u não são.
    u v u
    v o v
    u v u
*/
    if (p.row==q.row || p.col==q.col){
        if (p.row==q.row+1 || p.row==q.row-1)
            return true;
        if (p.col==q.col+1 || p.col==q.col-1)
            return true;
    }
    return false;
}

place* getPlace(enviroment E, int i, int j){
/*
    Retorna ponteiro para place com indices i e j no grid.
*/
    return &E.grid[i][j];
}

enviroment* generatePresets5x5() {
    enviroment* presets = malloc(NUM_PRESETS * sizeof(enviroment));

    for (int i = 0; i < NUM_PRESETS; i++) {
        presets[i] = newEnviroment(5, 5);

        // Zera todos os campos
        for (int r = 0; r < 5; r++) {
            for (int c = 0; c < 5; c++) {
                presets[i].grid[r][c].buraco = false;
                presets[i].grid[r][c].monstro = false;
                presets[i].grid[r][c].ouro = false;
            }
        }
    }

    // ---------- Configuração 0 ----------
    presets[0].grid[2][2].ouro = true;
    presets[0].grid[1][2].buraco = true;
    presets[0].grid[3][3].buraco = true;
    presets[0].grid[1][3].buraco = true;
    presets[0].grid[2][1].monstro = true;

    // ---------- Configuração 1 ----------
    presets[1].grid[4][4].ouro = true;
    presets[1].grid[0][1].buraco = true;
    presets[1].grid[2][2].buraco = true;
    presets[1].grid[3][0].buraco = true;
    presets[1].grid[1][1].monstro = true;

    // ---------- Configuração 2 ----------
    presets[2].grid[0][4].ouro = true;
    presets[2].grid[1][0].buraco = true;
    presets[2].grid[2][1].buraco = true;
    presets[2].grid[3][3].buraco = true;
    presets[2].grid[4][2].monstro = true;

    // ---------- Configuração 3 ----------
    presets[3].grid[2][2].ouro = true;
    presets[3].grid[1][1].buraco = true;
    presets[3].grid[0][3].buraco = true;
    presets[3].grid[4][4].buraco = true;
    presets[3].grid[3][2].monstro = true;

    // ---------- Configuração 4 ----------
    presets[4].grid[0][2].ouro = true;
    presets[4].grid[2][1].buraco = true;
    presets[4].grid[3][0].buraco = true;
    presets[4].grid[4][1].buraco = true;
    presets[4].grid[1][4].monstro = true;

    // ---------- Configuração 5 ----------
    presets[5].grid[1][4].ouro = true;
    presets[5].grid[0][1].buraco = true;
    presets[5].grid[2][2].buraco = true;
    presets[5].grid[3][1].buraco = true;
    presets[5].grid[4][0].monstro = true;

    // ---------- Configuração 6 ----------
    presets[6].grid[3][4].ouro = true;
    presets[6].grid[1][1].buraco = true;
    presets[6].grid[1][3].buraco = true;
    presets[6].grid[4][2].buraco = true;
    presets[6].grid[2][2].monstro = true;

    // ---------- Configuração 7 ----------
    presets[7].grid[2][0].ouro = true;
    presets[7].grid[1][1].buraco = true;
    presets[7].grid[3][1].buraco = true;
    presets[7].grid[4][3].buraco = true;
    presets[7].grid[0][4].monstro = true;

    // ---------- Configuração 8 ----------
    presets[8].grid[4][0].ouro = true;
    presets[8].grid[1][2].buraco = true;
    presets[8].grid[2][3].buraco = true;
    presets[8].grid[3][2].buraco = true;
    presets[8].grid[2][0].monstro = true;

    // ---------- Configuração 9 ----------
    presets[9].grid[3][3].ouro = true;
    presets[9].grid[0][1].buraco = true;
    presets[9].grid[1][3].buraco = true;
    presets[9].grid[2][2].buraco = true;
    presets[9].grid[3][0].monstro = true;

    return presets;
}

enviroment* generatePresets7x7() {
    enviroment* presets = malloc(NUM_PRESETS * sizeof(enviroment));

    for (int i = 0; i < NUM_PRESETS; i++) {
        presets[i] = newEnviroment(7, 7);

        for (int r = 0; r < 7; r++) {
            for (int c = 0; c < 7; c++) {
                presets[i].grid[r][c].buraco = false;
                presets[i].grid[r][c].monstro = false;
                presets[i].grid[r][c].ouro = false;
            }
        }
    }

    // ---------- Configuração 0 ----------
    presets[0].grid[3][3].ouro = true;
    presets[0].grid[1][2].buraco = true;
    presets[0].grid[2][4].buraco = true;
    presets[0].grid[3][1].buraco = true;
    presets[0].grid[4][2].buraco = true;
    presets[0].grid[5][5].buraco = true;
    presets[0].grid[1][5].buraco = true;
    presets[0].grid[2][2].monstro = true;
    presets[0].grid[4][4].monstro = true;

    // ---------- Configuração 1 ----------
    presets[1].grid[5][3].ouro = true;
    presets[1].grid[0][1].buraco = true;
    presets[1].grid[2][2].buraco = true;
    presets[1].grid[3][4].buraco = true;
    presets[1].grid[4][0].buraco = true;
    presets[1].grid[5][2].buraco = true;
    presets[1].grid[2][5].buraco = true;
    presets[1].grid[1][4].monstro = true;
    presets[1].grid[3][3].monstro = true;

    // ---------- Configuração 2 ----------
    presets[2].grid[2][6].ouro = true;
    presets[2].grid[0][2].buraco = true;
    presets[2].grid[2][1].buraco = true;
    presets[2].grid[3][0].buraco = true;
    presets[2].grid[4][3].buraco = true;
    presets[2].grid[5][1].buraco = true;
    presets[2].grid[3][5].buraco = true;
    presets[2].grid[1][3].monstro = true;
    presets[2].grid[4][4].monstro = true;

    // ---------- Configuração 3 ----------
    presets[3].grid[4][6].ouro = true;
    presets[3].grid[1][1].buraco = true;
    presets[3].grid[2][3].buraco = true;
    presets[3].grid[3][2].buraco = true;
    presets[3].grid[4][0].buraco = true;
    presets[3].grid[5][4].buraco = true;
    presets[3].grid[1][5].buraco = true;
    presets[3].grid[3][1].monstro = true;
    presets[3].grid[5][2].monstro = true;

    // ---------- Configuração 4 ----------
    presets[4].grid[3][5].ouro = true;
    presets[4].grid[0][2].buraco = true;
    presets[4].grid[1][4].buraco = true;
    presets[4].grid[2][5].buraco = true;
    presets[4].grid[3][2].buraco = true;
    presets[4].grid[5][3].buraco = true;
    presets[4].grid[6][1].buraco = true;
    presets[4].grid[2][1].monstro = true;
    presets[4].grid[4][4].monstro = true;

    // ---------- Configuração 5 ----------
    presets[5].grid[5][5].ouro = true;
    presets[5].grid[1][2].buraco = true;
    presets[5].grid[2][4].buraco = true;
    presets[5].grid[4][1].buraco = true;
    presets[5].grid[5][3].buraco = true;
    presets[5].grid[3][4].buraco = true;
    presets[5].grid[2][0].buraco = true;
    presets[5].grid[1][5].monstro = true;
    presets[5].grid[4][2].monstro = true;

    // ---------- Configuração 6 ----------
    presets[6].grid[4][5].ouro = true;
    presets[6].grid[0][3].buraco = true;
    presets[6].grid[2][2].buraco = true;
    presets[6].grid[3][1].buraco = true;
    presets[6].grid[5][4].buraco = true;
    presets[6].grid[6][2].buraco = true;
    presets[6].grid[3][5].buraco = true;
    presets[6].grid[1][4].monstro = true;
    presets[6].grid[5][1].monstro = true;

    // ---------- Configuração 7 ----------
    presets[7].grid[1][6].ouro = true;
    presets[7].grid[1][1].buraco = true;
    presets[7].grid[2][3].buraco = true;
    presets[7].grid[3][4].buraco = true;
    presets[7].grid[4][0].buraco = true;
    presets[7].grid[5][2].buraco = true;
    presets[7].grid[3][1].buraco = true;
    presets[7].grid[0][5].monstro = true;
    presets[7].grid[4][3].monstro = true;

    // ---------- Configuração 8 ----------
    presets[8].grid[2][5].ouro = true;
    presets[8].grid[1][2].buraco = true;
    presets[8].grid[2][4].buraco = true;
    presets[8].grid[3][3].buraco = true;
    presets[8].grid[4][1].buraco = true;
    presets[8].grid[5][5].buraco = true;
    presets[8].grid[1][4].buraco = true;
    presets[8].grid[2][0].monstro = true;
    presets[8].grid[5][2].monstro = true;

    // ---------- Configuração 9 ----------
    presets[9].grid[3][6].ouro = true;
    presets[9].grid[1][1].buraco = true;
    presets[9].grid[2][2].buraco = true;
    presets[9].grid[3][4].buraco = true;
    presets[9].grid[4][0].buraco = true;
    presets[9].grid[5][3].buraco = true;
    presets[9].grid[1][5].buraco = true;
    presets[9].grid[0][4].monstro = true;
    presets[9].grid[4][2].monstro = true;

    return presets;
}

enviroment* generatePresets9x9() {
    enviroment* presets = malloc(NUM_PRESETS * sizeof(enviroment));

    for (int i = 0; i < NUM_PRESETS; i++) {
        presets[i] = newEnviroment(9, 9);

        for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++) {
                presets[i].grid[r][c].buraco = false;
                presets[i].grid[r][c].monstro = false;
                presets[i].grid[r][c].ouro = false;
            }
        }
    }

    // ---------- Configuração 0 ----------
    presets[0].grid[4][4].ouro = true;

    int buracos0[][2] = {{1,1},{2,3},{3,5},{4,1},{5,6},{6,2},{2,6},{7,4},{1,6},{6,5}};
    int monstros0[][2] = {{3,2},{4,6},{5,3},{7,7}};

    for (int j = 0; j < 10; j++) presets[0].grid[buracos0[j][0]][buracos0[j][1]].buraco = true;
    for (int j = 0; j < 4; j++) presets[0].grid[monstros0[j][0]][monstros0[j][1]].monstro = true;

    // ---------- Configuração 1 ----------
    presets[1].grid[7][6].ouro = true;

    int buracos1[][2] = {{0,2},{2,1},{3,4},{4,2},{5,1},{6,6},{1,7},{2,5},{6,3},{7,1}};
    int monstros1[][2] = {{3,6},{4,5},{5,7},{8,2}};

    for (int j = 0; j < 10; j++) presets[1].grid[buracos1[j][0]][buracos1[j][1]].buraco = true;
    for (int j = 0; j < 4; j++) presets[1].grid[monstros1[j][0]][monstros1[j][1]].monstro = true;

    // ---------- Configuração 2 ----------
    presets[2].grid[2][7].ouro = true;

    int buracos2[][2] = {{1,3},{3,1},{4,4},{5,2},{2,4},{6,6},{7,3},{3,7},{4,6},{5,5}};
    int monstros2[][2] = {{1,6},{2,2},{6,4},{8,5}};

    for (int j = 0; j < 10; j++) presets[2].grid[buracos2[j][0]][buracos2[j][1]].buraco = true;
    for (int j = 0; j < 4; j++) presets[2].grid[monstros2[j][0]][monstros2[j][1]].monstro = true;

    // ---------- Configuração 3 ----------
    presets[3].grid[5][8].ouro = true;

    int buracos3[][2] = {{1,1},{2,3},{3,2},{4,5},{5,3},{6,1},{7,4},{2,6},{3,5},{6,7}};
    int monstros3[][2] = {{1,7},{4,3},{5,6},{7,6}};

    for (int j = 0; j < 10; j++) presets[3].grid[buracos3[j][0]][buracos3[j][1]].buraco = true;
    for (int j = 0; j < 4; j++) presets[3].grid[monstros3[j][0]][monstros3[j][1]].monstro = true;

    // ---------- Configuração 4 ----------
    presets[4].grid[6][5].ouro = true;

    int buracos4[][2] = {{0,3},{1,5},{2,2},{3,4},{4,6},{5,1},{2,5},{6,3},{7,1},{8,4}};
    int monstros4[][2] = {{1,2},{3,6},{4,2},{7,6}};

    for (int j = 0; j < 10; j++) presets[4].grid[buracos4[j][0]][buracos4[j][1]].buraco = true;
    for (int j = 0; j < 4; j++) presets[4].grid[monstros4[j][0]][monstros4[j][1]].monstro = true;

    // ---------- Configuração 5 ----------
    presets[5].grid[3][7].ouro = true;

    int buracos5[][2] = {{1,1},{2,4},{3,3},{4,5},{5,2},{6,4},{2,6},{6,1},{7,3},{7,7}};
    int monstros5[][2] = {{0,6},{1,4},{3,5},{5,6}};

    for (int j = 0; j < 10; j++) presets[5].grid[buracos5[j][0]][buracos5[j][1]].buraco = true;
    for (int j = 0; j < 4; j++) presets[5].grid[monstros5[j][0]][monstros5[j][1]].monstro = true;

    // ---------- Configuração 6 ----------
    presets[6].grid[1][8].ouro = true;

    int buracos6[][2] = {{0,2},{2,5},{3,4},{4,1},{5,3},{5,6},{6,2},{2,7},{3,6},{6,5}};
    int monstros6[][2] = {{1,3},{3,1},{4,6},{7,4}};

    for (int j = 0; j < 10; j++) presets[6].grid[buracos6[j][0]][buracos6[j][1]].buraco = true;
    for (int j = 0; j < 4; j++) presets[6].grid[monstros6[j][0]][monstros6[j][1]].monstro = true;

    // ---------- Configuração 7 ----------
    presets[7].grid[6][7].ouro = true;

    int buracos7[][2] = {{0,1},{1,4},{2,3},{3,5},{4,4},{5,2},{6,1},{3,7},{5,5},{7,2}};
    int monstros7[][2] = {{1,6},{3,2},{4,6},{6,6}};

    for (int j = 0; j < 10; j++) presets[7].grid[buracos7[j][0]][buracos7[j][1]].buraco = true;
    for (int j = 0; j < 4; j++) presets[7].grid[monstros7[j][0]][monstros7[j][1]].monstro = true;

    // ---------- Configuração 8 ----------
    presets[8].grid[4][7].ouro = true;

    int buracos8[][2] = {{1,2},{2,4},{3,6},{4,1},{5,3},{6,4},{3,3},{2,7},{5,5},{7,1}};
    int monstros8[][2] = {{0,5},{2,2},{4,5},{6,6}};

    for (int j = 0; j < 10; j++) presets[8].grid[buracos8[j][0]][buracos8[j][1]].buraco = true;
    for (int j = 0; j < 4; j++) presets[8].grid[monstros8[j][0]][monstros8[j][1]].monstro = true;

    // ---------- Configuração 9 ----------
    presets[9].grid[5][6].ouro = true;

    int buracos9[][2] = {{0,4},{1,3},{2,6},{3,2},{4,4},{5,1},{6,3},{2,5},{3,6},{6,5}};
    int monstros9[][2] = {{1,6},{3,4},{4,6},{7,3}};

    for (int j = 0; j < 10; j++) presets[9].grid[buracos9[j][0]][buracos9[j][1]].buraco = true;
    for (int j = 0; j < 4; j++) presets[9].grid[monstros9[j][0]][monstros9[j][1]].monstro = true;

    return presets;
}

enviroment* generatePresets10x10() {
    enviroment* presets = malloc(NUM_PRESETS * sizeof(enviroment));

    for (int i = 0; i < NUM_PRESETS; i++) {
        presets[i] = newEnviroment(10, 10);

        for (int r = 0; r < 10; r++) {
            for (int c = 0; c < 10; c++) {
                presets[i].grid[r][c].buraco = false;
                presets[i].grid[r][c].monstro = false;
                presets[i].grid[r][c].ouro = false;
            }
        }
    }

    // ---------- Configuração 0 ----------
    presets[0].grid[5][5].ouro = true;

    int buracos0[][2] = {{1,1},{2,3},{3,5},{4,2},{5,6},{6,2},{7,4},{2,7},{3,8},{6,6},{8,3},{7,7}};
    int monstros0[][2] = {{3,2},{4,6},{5,3},{7,2},{6,8},{8,6}};

    for (int j = 0; j < 12; j++) presets[0].grid[buracos0[j][0]][buracos0[j][1]].buraco = true;
    for (int j = 0; j < 6; j++) presets[0].grid[monstros0[j][0]][monstros0[j][1]].monstro = true;

    // ---------- Configuração 1 ----------
    presets[1].grid[6][8].ouro = true;

    int buracos1[][2] = {{0,2},{1,5},{2,1},{3,4},{4,2},{5,1},{6,6},{2,5},{3,7},{6,3},{7,1},{8,4}};
    int monstros1[][2] = {{3,6},{4,5},{5,7},{8,2},{7,6},{2,8}};

    for (int j = 0; j < 12; j++) presets[1].grid[buracos1[j][0]][buracos1[j][1]].buraco = true;
    for (int j = 0; j < 6; j++) presets[1].grid[monstros1[j][0]][monstros1[j][1]].monstro = true;

    // ---------- Configuração 2 ----------
    presets[2].grid[2][9].ouro = true;

    int buracos2[][2] = {{1,3},{3,1},{4,4},{5,2},{6,4},{2,4},{7,3},{3,7},{4,6},{5,5},{7,8},{6,7}};
    int monstros2[][2] = {{1,6},{2,2},{6,6},{8,5},{4,8},{5,8}};

    for (int j = 0; j < 12; j++) presets[2].grid[buracos2[j][0]][buracos2[j][1]].buraco = true;
    for (int j = 0; j < 6; j++) presets[2].grid[monstros2[j][0]][monstros2[j][1]].monstro = true;

    // ---------- Configuração 3 ----------
    presets[3].grid[8][6].ouro = true;

    int buracos3[][2] = {{1,1},{2,3},{3,2},{4,5},{5,3},{6,1},{2,6},{3,5},{6,7},{7,2},{4,3},{8,4}};
    int monstros3[][2] = {{1,7},{4,7},{5,6},{7,6},{2,8},{3,3}};

    for (int j = 0; j < 12; j++) presets[3].grid[buracos3[j][0]][buracos3[j][1]].buraco = true;
    for (int j = 0; j < 6; j++) presets[3].grid[monstros3[j][0]][monstros3[j][1]].monstro = true;

    // ---------- Configuração 4 ----------
    presets[4].grid[6][5].ouro = true;

    int buracos4[][2] = {{0,3},{1,5},{2,2},{3,4},{4,6},{5,1},{2,5},{6,3},{7,1},{8,4},{4,8},{5,4}};
    int monstros4[][2] = {{1,2},{3,6},{4,2},{7,6},{2,7},{6,8}};

    for (int j = 0; j < 12; j++) presets[4].grid[buracos4[j][0]][buracos4[j][1]].buraco = true;
    for (int j = 0; j < 6; j++) presets[4].grid[monstros4[j][0]][monstros4[j][1]].monstro = true;

    // ---------- Configuração 5 ----------
    presets[5].grid[3][9].ouro = true;

    int buracos5[][2] = {{1,1},{2,4},{3,3},{4,5},{5,2},{6,4},{2,6},{6,1},{7,3},{7,7},{5,5},{4,3}};
    int monstros5[][2] = {{0,6},{1,4},{3,5},{5,6},{6,7},{2,8}};

    for (int j = 0; j < 12; j++) presets[5].grid[buracos5[j][0]][buracos5[j][1]].buraco = true;
    for (int j = 0; j < 6; j++) presets[5].grid[monstros5[j][0]][monstros5[j][1]].monstro = true;

    // ---------- Configuração 6 ----------
    presets[6].grid[1][9].ouro = true;

    int buracos6[][2] = {{0,2},{2,5},{3,4},{4,1},{5,3},{5,6},{6,2},{2,7},{3,6},{6,5},{7,4},{7,2}};
    int monstros6[][2] = {{1,3},{3,1},{4,6},{7,5},{5,8},{2,9}};

    for (int j = 0; j < 12; j++) presets[6].grid[buracos6[j][0]][buracos6[j][1]].buraco = true;
    for (int j = 0; j < 6; j++) presets[6].grid[monstros6[j][0]][monstros6[j][1]].monstro = true;

    // ---------- Configuração 7 ----------
    presets[7].grid[6][9].ouro = true;

    int buracos7[][2] = {{0,1},{1,4},{2,3},{3,5},{4,4},{5,2},{6,1},{3,7},{5,5},{7,2},{4,1},{6,3}};
    int monstros7[][2] = {{1,6},{3,2},{4,6},{6,6},{7,6},{5,7}};

    for (int j = 0; j < 12; j++) presets[7].grid[buracos7[j][0]][buracos7[j][1]].buraco = true;
    for (int j = 0; j < 6; j++) presets[7].grid[monstros7[j][0]][monstros7[j][1]].monstro = true;

    // ---------- Configuração 8 ----------
    presets[8].grid[5][8].ouro = true;

    int buracos8[][2] = {{1,2},{2,4},{3,6},{4,1},{5,3},{6,4},{3,3},{2,7},{5,5},{7,1},{4,2},{6,6}};
    int monstros8[][2] = {{0,5},{2,2},{4,5},{6,7},{7,4},{8,5}};

    for (int j = 0; j < 12; j++) presets[8].grid[buracos8[j][0]][buracos8[j][1]].buraco = true;
    for (int j = 0; j < 6; j++) presets[8].grid[monstros8[j][0]][monstros8[j][1]].monstro = true;

    // ---------- Configuração 9 ----------
    presets[9].grid[7][8].ouro = true;

    int buracos9[][2] = {{0,4},{1,3},{2,6},{3,2},{4,4},{5,1},{6,3},{2,5},{3,6},{6,5},{5,3},{7,3}};
    int monstros9[][2] = {{1,6},{3,4},{4,6},{7,5},{6,7},{8,2}};

    for (int j = 0; j < 12; j++) presets[9].grid[buracos9[j][0]][buracos9[j][1]].buraco = true;
    for (int j = 0; j < 6; j++) presets[9].grid[monstros9[j][0]][monstros9[j][1]].monstro = true;

    return presets;
}

enviroment* generatePresets5x10() {
    enviroment* presets = malloc(NUM_PRESETS * sizeof(enviroment));

    for (int i = 0; i < NUM_PRESETS; i++) {
        presets[i] = newEnviroment(5, 10);

        for (int r = 0; r < 5; r++) {
            for (int c = 0; c < 10; c++) {
                presets[i].grid[r][c].buraco = false;
                presets[i].grid[r][c].monstro = false;
                presets[i].grid[r][c].ouro = false;
            }
        }
    }

    // ---------- Configuração 0 ----------
    presets[0].grid[2][7].ouro = true;

    int buracos0[][2] = {{0,2},{1,4},{2,3},{3,1},{3,5},{4,2}};
    int monstros0[][2] = {{0,6},{1,6},{2,5}};

    for (int j = 0; j < 6; j++) presets[0].grid[buracos0[j][0]][buracos0[j][1]].buraco = true;
    for (int j = 0; j < 3; j++) presets[0].grid[monstros0[j][0]][monstros0[j][1]].monstro = true;

    // ---------- Configuração 1 ----------
    presets[1].grid[1][9].ouro = true;

    int buracos1[][2] = {{0,3},{1,1},{2,4},{3,2},{4,1},{3,6}};
    int monstros1[][2] = {{1,4},{2,7},{3,5}};

    for (int j = 0; j < 6; j++) presets[1].grid[buracos1[j][0]][buracos1[j][1]].buraco = true;
    for (int j = 0; j < 3; j++) presets[1].grid[monstros1[j][0]][monstros1[j][1]].monstro = true;

    // ---------- Configuração 2 ----------
    presets[2].grid[4][7].ouro = true;

    int buracos2[][2] = {{0,4},{1,2},{2,6},{3,1},{4,3},{1,7}};
    int monstros2[][2] = {{2,4},{3,6},{4,5}};

    for (int j = 0; j < 6; j++) presets[2].grid[buracos2[j][0]][buracos2[j][1]].buraco = true;
    for (int j = 0; j < 3; j++) presets[2].grid[monstros2[j][0]][monstros2[j][1]].monstro = true;

    // ---------- Configuração 3 ----------
    presets[3].grid[0][8].ouro = true;

    int buracos3[][2] = {{1,3},{2,1},{2,5},{3,3},{4,2},{3,7}};
    int monstros3[][2] = {{1,6},{2,7},{4,6}};

    for (int j = 0; j < 6; j++) presets[3].grid[buracos3[j][0]][buracos3[j][1]].buraco = true;
    for (int j = 0; j < 3; j++) presets[3].grid[monstros3[j][0]][monstros3[j][1]].monstro = true;

    // ---------- Configuração 4 ----------
    presets[4].grid[2][6].ouro = true;

    int buracos4[][2] = {{0,3},{1,5},{2,3},{3,2},{4,1},{3,6}};
    int monstros4[][2] = {{1,2},{2,8},{4,4}};

    for (int j = 0; j < 6; j++) presets[4].grid[buracos4[j][0]][buracos4[j][1]].buraco = true;
    for (int j = 0; j < 3; j++) presets[4].grid[monstros4[j][0]][monstros4[j][1]].monstro = true;

    // ---------- Configuração 5 ----------
    presets[5].grid[3][8].ouro = true;

    int buracos5[][2] = {{0,1},{1,4},{2,2},{3,5},{4,3},{1,7}};
    int monstros5[][2] = {{2,6},{3,3},{4,5}};

    for (int j = 0; j < 6; j++) presets[5].grid[buracos5[j][0]][buracos5[j][1]].buraco = true;
    for (int j = 0; j < 3; j++) presets[5].grid[monstros5[j][0]][monstros5[j][1]].monstro = true;

    // ---------- Configuração 6 ----------
    presets[6].grid[1][8].ouro = true;

    int buracos6[][2] = {{0,2},{1,3},{2,5},{3,1},{3,6},{4,2}};
    int monstros6[][2] = {{2,7},{3,4},{4,6}};

    for (int j = 0; j < 6; j++) presets[6].grid[buracos6[j][0]][buracos6[j][1]].buraco = true;
    for (int j = 0; j < 3; j++) presets[6].grid[monstros6[j][0]][monstros6[j][1]].monstro = true;

    // ---------- Configuração 7 ----------
    presets[7].grid[2][9].ouro = true;

    int buracos7[][2] = {{0,4},{1,1},{2,6},{3,2},{4,3},{3,5}};
    int monstros7[][2] = {{1,5},{2,4},{4,5}};

    for (int j = 0; j < 6; j++) presets[7].grid[buracos7[j][0]][buracos7[j][1]].buraco = true;
    for (int j = 0; j < 3; j++) presets[7].grid[monstros7[j][0]][monstros7[j][1]].monstro = true;

    // ---------- Configuração 8 ----------
    presets[8].grid[3][9].ouro = true;

    int buracos8[][2] = {{0,3},{1,2},{2,1},{3,6},{4,2},{1,6}};
    int monstros8[][2] = {{2,5},{3,3},{4,4}};

    for (int j = 0; j < 6; j++) presets[8].grid[buracos8[j][0]][buracos8[j][1]].buraco = true;
    for (int j = 0; j < 3; j++) presets[8].grid[monstros8[j][0]][monstros8[j][1]].monstro = true;

    // ---------- Configuração 9 ----------
    presets[9].grid[4][7].ouro = true;

    int buracos9[][2] = {{0,2},{1,5},{2,3},{3,1},{3,5},{4,3}};
    int monstros9[][2] = {{1,3},{2,7},{4,5}};

    for (int j = 0; j < 6; j++) presets[9].grid[buracos9[j][0]][buracos9[j][1]].buraco = true;
    for (int j = 0; j < 3; j++) presets[9].grid[monstros9[j][0]][monstros9[j][1]].monstro = true;

    return presets;
}
