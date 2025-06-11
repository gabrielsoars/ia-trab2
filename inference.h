#include <stdbool.h>
#include "agent.h"

#ifndef INFERENCE_H
#define INFERENCE_H

bool inferHoles(agent * A, enviroment * E);
bool inferMonsters(agent * A, enviroment * E);
knowledge ** newKnowledgeBase(enviroment E);
place *inferBestMove(agent *A, enviroment *E);

#endif