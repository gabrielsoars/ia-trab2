#include <stdbool.h>
#include "agent.h"

#ifndef INFERENCE_H
#define INFERENCE_H

void inferHoles(agent * A, enviroment * E);
void inferMonsters(agent * A, enviroment * E);
knowledge ** newKnowledgeBase(enviroment E);
place *inferBestMove(agent *A, enviroment *E);
bool isBeco(agent *A, enviroment *E, int x, int y); 

#endif