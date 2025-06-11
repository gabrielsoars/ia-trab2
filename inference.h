#include <stdbool.h>
#include "agent.h"

#ifndef INFERENCE_H
#define INFERENCE_H

void inferHoles(agent * A, enviroment * E);
void inferMonsters(agent * A, enviroment * E);
knowledge ** newKnowledgeBase(enviroment E);
place *inferBestMove(agent *A, enviroment *E);
bool isSafeFromHoles(agent * A, enviroment * E, int i, int j);
bool isSafeFromMonsters(agent * A, enviroment * E, int i, int j);

#endif