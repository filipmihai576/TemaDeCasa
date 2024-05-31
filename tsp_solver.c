#include "tsp_solver.h"
#include "data_structures.h"

void dfs(TSPInstance *instance, Path *currentPath, int *visited, Path *bestPath, int currentCity, int depth) {
    if (depth == instance->numCities) {
        int returnCost = instance->distances[currentCity][currentPath->path[0]];
        if (returnCost < INT_MAX) {
            currentPath->cost += returnCost;
            currentPath->maxDist = currentPath->maxDist > returnCost ? currentPath->maxDist : returnCost;
            if (currentPath->maxDist < bestPath->maxDist) {
                *bestPath = *currentPath;
            }
            currentPath->cost -= returnCost;
            currentPath->maxDist = currentPath->maxDist > returnCost ? returnCost : currentPath->maxDist;
        }
        return;
    }

    for (int i = 0; i < instance->numCities; i++) {
        if (!visited[i]) {
            visited[i] = 1;
            currentPath->path[depth] = i;
            int newCost = instance->distances[currentCity][i];
            currentPath->cost += newCost;
            int prevMaxDist = currentPath->maxDist;
            currentPath->maxDist = currentPath->maxDist > newCost ? currentPath->maxDist : newCost;

            dfs(instance, currentPath, visited, bestPath, i, depth + 1);

            visited[i] = 0;
            currentPath->cost -= newCost;
            currentPath->maxDist = prevMaxDist;
        }
    }
}

Path solveDFS(TSPInstance *instance) {
    Path bestPath;
    bestPath.cost = INT_MAX;
    bestPath.maxDist = INT_MAX;
    bestPath.length = instance->numCities;

    Path currentPath;
    currentPath.cost = 0;
    currentPath.maxDist = 0;
    currentPath.length = instance->numCities;

    int visited[MAX_CITIES] = {0};

    for (int i = 0; i < instance->numCities; i++) {
        visited[i] = 1;
        currentPath.path[0] = i;

        dfs(instance, &currentPath, visited, &bestPath, i, 1);

        visited[i] = 0;
    }

    return bestPath;
}

Path solveUCS(TSPInstance *instance) {
    Path bestPath;
    bestPath.cost = INT_MAX;
    bestPath.maxDist = INT_MAX;
    bestPath.length = instance->numCities;

    Node *queue = NULL;

    for (int i = 0; i < instance->numCities; i++) {
        Path initialPath;
        initialPath.cost = 0;
        initialPath.maxDist = 0;
        initialPath.path[0] = i;
        initialPath.length = 1;

        push(&queue, initialPath, i);
    }

    while (!isEmpty(queue)) {
        Node *currentNode = pop(&queue);
        Path currentPath = currentNode->path;
        int currentCity = currentNode->currentCity;
        free(currentNode);

        if (currentPath.length == instance->numCities) {
            int returnCost = instance->distances[currentCity][currentPath.path[0]];
            if (returnCost < INT_MAX) {
                currentPath.cost += returnCost;
                currentPath.maxDist = currentPath.maxDist > returnCost ? currentPath.maxDist : returnCost;
                if (currentPath.maxDist < bestPath.maxDist) {
                    bestPath = currentPath;
                }
            }
            continue;
        }

        for (int i = 0; i < instance->numCities; i++) {
            if (i != currentCity && currentPath.cost + instance->distances[currentCity][i] < bestPath.cost) {
                Path newPath = currentPath;
                newPath.path[currentPath.length] = i;
                int newCost = instance->distances[currentCity][i];
                newPath.cost += newCost;
                newPath.length++;
                newPath.maxDist = newPath.maxDist > newCost ? newPath.maxDist : newCost;

                push(&queue, newPath, i);
            }
        }
    }

    return bestPath;
}

Path solveAStar(TSPInstance *instance) {
    Path bestPath;
    bestPath.cost = INT_MAX;
    bestPath.maxDist = INT_MAX;
    bestPath.length = instance->numCities;

    NodeAStar *queue = NULL;

    for (int i = 0; i < instance->numCities; i++) {
        Path initialPath;
        initialPath.cost = 0;
        initialPath.maxDist = 0;
        initialPath.path[0] = i;
        initialPath.length = 1;

        int fScore = initialPath.cost + heuristic(instance, i, initialPath.path);
        pushAStar(&queue, initialPath, i, fScore);
    }

    while (!isEmptyAStar(queue)) {
        NodeAStar *currentNode = popAStar(&queue);
        Path currentPath = currentNode->path;
        int currentCity = currentNode->currentCity;
        free(currentNode);

        if (currentPath.length == instance->numCities) {
            int returnCost = instance->distances[currentCity][currentPath.path[0]];
            if (returnCost < INT_MAX) {
                currentPath.cost += returnCost;
                currentPath.maxDist = currentPath.maxDist > returnCost ? currentPath.maxDist : returnCost;
                if (currentPath.maxDist < bestPath.maxDist) {
                    bestPath = currentPath;
                }
            }
            continue;
        }

        for (int i = 0; i < instance->numCities; i++) {
            if (i != currentCity) {
                int newCost = currentPath.cost + instance->distances[currentCity][i];
                if (newCost < bestPath.cost) {
                    Path newPath = currentPath;
                    newPath.path[currentPath.length] = i;
                    newPath.cost = newCost;
                    newPath.length++;
                    newPath.maxDist = newPath.maxDist > newCost ? newPath.maxDist : newCost;

                    int fScore = newCost + heuristic(instance, i, newPath.path);
                    pushAStar(&queue, newPath, i, fScore);
                }
            }
        }
    }

    return bestPath;
}
