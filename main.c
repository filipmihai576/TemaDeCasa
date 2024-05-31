#include <stdio.h>
#include "tsp_solver.h"

void printPath(Path path) {
    for (int i = 0; i < path.length; i++) {
        printf("%d ", path.path[i]);
    }
    printf("\nMax Distance: %d\n", path.maxDist);
}

int main() {
    TSPInstance instance;
    instance.numCities = 4;
    int distances[4][4] = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            instance.distances[i][j] = distances[i][j];
        }
    }

    Path result;

    // Solve using DFS
    printf("DFS Result:\n");
    result = solveDFS(&instance);
    printPath(result);

    // Solve using Uniform Cost Search
    printf("UCS Result:\n");
    result = solveUCS(&instance);
    printPath(result);

    // Solve using A* Search
    printf("A* Result:\n");
    result = solveAStar(&instance);
    printPath(result);

    return 0;
}
