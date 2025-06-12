#include "env.h"

#ifndef AGENT_H
#define AGENT_H

typedef struct {
    bool visitado;
    bool vento;
    bool cheiro;
    bool monstro;
    bool buraco;
    bool possivelBuraco;
    bool possivelMonstro;
} knowledge;

typedef struct {
    place* onde;
    bool comOuro;
    bool temFlecha;
    int score;
    knowledge ** knowledgeBase;
    bool ganhou;
    int quedasBuracos;
    int matouMonstro;
    int contatoMonstro;
}agent;

void printSimulation(agent A, enviroment E);
bool move(agent* A, enviroment E, place* target);
agent newAgent(enviroment E);
void sense(agent A);

#endif 