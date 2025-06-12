#include <stdio.h>
#include <stdbool.h>
#include "inference.h"
#include "env.h"
#include <unistd.h>

FILE* criar_arquivo(const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "w");  // ou "a" para adicionar ao final
    if (arquivo == NULL) {
        perror("Erro ao criar o arquivo");
    }
    return arquivo;
}

void fechar_arquivo(FILE* arquivo) {
    if (arquivo != NULL) {
        fclose(arquivo);
    }
}

void game(enviroment E, FILE * arq){
    agent A = newAgent(E);

    // printf("Você está em uma sala com dimensões %d x %d. \n",E.h,E.w);
    // printf("Seu objetivo é chegar na posição (%d,%d) em posse do ouro.",
    //     E.h-1,E.w-1);
    // printf("Fazendo a menor quantidade de movimentos possível. \n");
    // printf("Você começa na posição (0,0). Boa sorte! \n");

    int maxMoves = 10 * (E.h * E.w);
    int countMoves = 0;
    while((!(A.comOuro && A.onde->row==E.h-1 && A.onde->col==E.w-1)) && (countMoves < maxMoves)){
        // printf("Score atual: %d \n", A.score);
        // printSimulation(A,E);
        sense(A);
        place * melhorMov = inferBestMove(&A, &E);
        // printf("Mova-se para: (%d, %d)\n", melhorMov->row, melhorMov->col);
        move(&A, E, melhorMov);
        countMoves++;
    }
    // printf("Score final: %d \n", A.score);
    fprintf(arq, "Ganhou: %d;Moves: %d; Score: %d; Quedas no buraco: %d; Pego pelo monstro: %d; Matou o monstro: %d\n", A.ganhou,countMoves, A.score, A.quedasBuracos, A.contatoMonstro, A.matouMonstro);
    free(A.knowledgeBase);
}

int main(){

    FILE * arq;
    arq = criar_arquivo("dados5x5.dat");
    enviroment * E5x5 = generatePresets5x5();
    for (int i = 0; i < 10; i++){
        enviroment E = E5x5[i];
        
        game(E, arq);
    }
    free(E5x5);
    fechar_arquivo(arq);

    arq = criar_arquivo("dados7x7.dat");
    enviroment * E7x7 = generatePresets7x7();
    for (int i = 0; i < 10; i++){
        enviroment E = E7x7[i];
        
        game(E, arq);
    }
    free(E7x7);
    fechar_arquivo(arq);

    arq = criar_arquivo("dados9x9.dat");
    enviroment * E9x9 = generatePresets9x9();
    for (int i = 0; i < 10; i++){
        enviroment E = E9x9[i];
        
        game(E, arq);
    }
    free(E9x9);
    fechar_arquivo(arq);

    arq = criar_arquivo("dados10x10.dat");
    enviroment * E10x10 = generatePresets10x10();
    for (int i = 0; i < 10; i++){
        enviroment E = E10x10[i];
        
        game(E, arq);
    }
    free(E10x10);
    fechar_arquivo(arq);

    arq = criar_arquivo("dados5x10.dat");
    enviroment * E5x10 = generatePresets5x10();
    for (int i = 0; i < 10; i++){
        enviroment E = E5x10[i];
        
        game(E, arq);
    }
    free(E5x10);
    fechar_arquivo(arq);

    return 0;
}