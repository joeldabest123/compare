#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include "linkedList.h"

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
    n->data = strdup(word);
    n->counter = 0;
    n->next = NULL;
    l->totalCount++;
    return n;
}



Node* search(List *l, const char *key) {
    Node *ptr = l->head;
    int i = 0;

    while(i < l->totalCount) {
        if(strcmp(ptr->data, key) == 0) {
            ptr->counter++;
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
    Node* prevHead = l->head;
    Node* smaller = initializeNode(l, key);
    int firstletkey = (int)key[0];
    int firstletnode;

    int i = 1;
    while(i < l->totalCount) {
        firstletkey = (int)key[0];
        firstletnode =(int) ptr->data[0];

        if(firstletkey < firstletnode) {
            smaller->next = ptr;
            if(ptr == l->head) {
                l->head = smaller;
                return;
            }
            prev->next = smaller;
            return;
        }

        if(firstletkey == firstletnode) {
            int j = 0;
            while(firstletkey == firstletnode) {
                firstletkey = (int)key[j];
                firstletnode =(int) ptr->data[j];

                if(firstletkey == 0) {
                    smaller->next = ptr;
                    if(ptr == l->head) {
                        l->head = smaller;
                        return;
                    }
                    prev->next = smaller;
                    return;
                } else if(firstletnode == 0) {
                    break;
                } else if(firstletkey < firstletnode) {
                    smaller->next = ptr;
                    if(ptr == l->head) {
                        l->head = smaller;
                        return;
                    }
                    prev->next = smaller;
                    return;
                } else if(firstletkey > firstletnode) {
                    break;
                } else {
                    j++;
                }
            }

        }

        prev = ptr;
        ptr = ptr->next;
        i++;

    }
    prev->next = smaller;

}

void insert (List *l, const char *key) {
    if(l->head == NULL) {
        l->head = initializeNode(l, key);
        
        return;
    }

    Node* found = search(l, key);

    if(found != NULL) {
        found->counter = found->counter + 1;
        return;
    }

    alphabetical(l, key);

    
}

void freeList (List* l) {
    Node* ptr = l->head;
    Node* next;

    while(ptr != NULL) {
        next = ptr->next;
        free(ptr->data);
        free(ptr);
        ptr = next;
    }
    free(l);
}