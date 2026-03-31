#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include "linkedList.h"

//initializers

List* initializeList (const char* path) {

    List* l = malloc(sizeof(List));

    if (l == NULL) {
        perror("malloc failed");
        return NULL;
    }
    l->totalCount = 0;
    l->head = NULL;
    l->name = strdup(path);
    return l;
}

List** initializeArray () {
    List **allFiles = malloc(10 * sizeof(List*));

    if(allFiles == NULL) {
        perror("malloc failed");
        return NULL;
    }

    return allFiles;
}

    // doubling the size of the array for more storage
List** lengthenArray (List **allFiles, int* capacity) {
    *capacity = (*capacity) * 2;
    
    //reallocating by doing the number of slots * 8 bytes (size of a pointer)
    List **temp = realloc(allFiles, (*capacity) * sizeof(List*));

    if(allFiles == NULL) {
        perror("realloc failed");
        return allFiles;
    }
    return temp;
}

Node* initializeNode (List* l, const char* word) {
    Node* n = malloc(sizeof(Node));

    if(n == NULL) {
        return NULL;
    }
    n->data = strdup(word);
    n->counter = 0;
    n->mean = 0;
    n->seen = 0;
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

void clearList (List** allFiles, int fileCount) {

    int counter = 0;
    while(counter < fileCount) {
        List* temp = allFiles[counter];

        Node* ptr = temp->head;
        Node* next;

        while(ptr != NULL) {
            next = ptr->next;
            free(temp->name); //frees path name
            free(ptr->data); //frees the word
            free(ptr); //frees the node
            ptr = next;
        }
        free(temp);

        counter++;
    }
    free(allFiles);
}