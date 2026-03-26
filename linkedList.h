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

List* initializeList ();
Node* initializeNode (List*, const char*);
Node* search(List *, const char *);
void alphabetical(List *, const char *);
void insert (List *, const char *);
void freeList (List* );

#endif