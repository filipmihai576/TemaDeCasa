#ifndef TSP_SOLVER_H
#define TSP_SOLVER_H

#include "data_structures.h"

Path solveDFS(TSPInstance *instance);
Path solveUCS(TSPInstance *instance);
Path solveAStar(TSPInstance *instance);

#endif /* TSP_SOLVER_H */
