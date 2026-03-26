#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct Node {
    char* data;
    int counter;
    struct Node *next;
} Node;

typedef struct linkedList {
    int totalCount;
    Node *head;

} List;

int countWord (List *, const char *);

#endif