#include "data_structures.h"

void push(Node **head, Path path, int currentCity) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->path = path;
    newNode->currentCity = currentCity;
    newNode->next = *head;
    *head = newNode;
}

Node *pop(Node **head) {
    Node *temp = *head;
    *head = (*head)->next;
    return temp;
}

int isEmpty(Node *head) {
    return head == NULL;
}

void pushAStar(NodeAStar **head, Path path, int currentCity, int fScore) {
    NodeAStar *newNode = (NodeAStar *)malloc(sizeof(NodeAStar));
    newNode->path = path;
    newNode->currentCity = currentCity;
    newNode->fScore = fScore;
    newNode->next = NULL;

    if (*head == NULL || (*head)->fScore > fScore) {
        newNode->next = *head;
        *head = newNode;
    } else {
        NodeAStar *current = *head;
        while (current->next != NULL && current->next->fScore <= fScore) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

NodeAStar *popAStar(NodeAStar **head) {
    NodeAStar *temp = *head;
    *head = (*head)->next;
    return temp;
}

int isEmptyAStar(NodeAStar *head) {
    return head == NULL;
}
