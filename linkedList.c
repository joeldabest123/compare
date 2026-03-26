#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include "linkedList.h";

//initializers

List* initializeList () {

    List* l = malloc(sizeof(List));

    if (l == NULL) {
        return NULL;
    }
    l->totalCount = 0;
    l->head = NULL;
    return l;
}

Node* initializeNode (List* l, const char* word) {
    Node* n = malloc(sizeof(Node));

    if(n == NULL) {
        return NULL;
    }
    n->data = word;
    n->counter = 0;
    n->next = NULL;
    l->totalCount++;
    return n;
}


//word counter

int addToCount (List* l, const char *key) {
    Node *ptr = l->head;
    int i = 0;

    while(i < l->totalCount) {
        if(strcmp(ptr->data, key) == 0) {
            ptr->counter = ptr->counter + 1;
            return 0;
        }
        ptr = ptr->next;
        i++;
    }

    return -1; //tokenizer sees -1 and calls initalizer
}

Node* search(List *l, const char *key) {
    Node *ptr = l->head;
    int i = 0;

    while(i < l->totalCount) {
        if(strcmp(ptr->data, key) == 0) {
            return ptr;
        }
        ptr = ptr->next;
        i++;
    }
    return NULL;
}

void alphabetical(List *l, const char *key) {
    Node* ptr = l->head;
    Node* prev = l->head;
    Node* biggest = l->head;

    int i = 0;
    while(i < l->totalCount) {
        
    }
}

void insert (List *l, const char *key) {
    if(l->head == NULL) {
        initializeNode(l, key);
        return;
    }

    Node* found = search(l, key);

    if(found != NULL) {
        return;
    }
    alphabetical(l, key);

    
}

void remove () {

}

void free () {

}

//remember to free