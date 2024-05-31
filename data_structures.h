#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_CITIES 20

typedef struct {
    int numCities;
    int distances[MAX_CITIES][MAX_CITIES];
} TSPInstance;

typedef struct {
    int path[MAX_CITIES];
    int cost;
    int maxDist; // The longest distance between two consecutive cities
    int length;
} Path;

typedef struct Node {
    Path path;
    int currentCity;
    struct Node *next;
} Node;

typedef struct NodeAStar {
    Path path;
    int currentCity;
    int fScore;
    struct NodeAStar *next;
} NodeAStar;

void push(Node **head, Path path, int currentCity);
Node *pop(Node **head);
int isEmpty(Node *head);

void pushAStar(NodeAStar **head, Path path, int currentCity, int fScore);
NodeAStar *popAStar(NodeAStar **head);
int isEmptyAStar(NodeAStar *head);

#endif /* DATA_STRUCTURES_H */
