#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include "linkedList.h";

int addToCount (List *l, const char *key) {
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

    return -1;
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
    return 
}

void insert () {
    
}

void remove () {

}