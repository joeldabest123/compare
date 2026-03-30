#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include "linkedList.h"
#include "tokenizer.h"

//need a function that:
//1. collects each list sent in from paceDirectories
//2. stores data within an array for usage
//3. frees/wipes the contents of linked list, sends it back
//4. functions in math use said contents for getting means and doing math stuff 
//5. stonks

//static double 

void wfd(List* words, int total) {
    Node* ptr = words->head;
    double adder;
    for(int i = 0; i < total; i++) {
        ptr->counter = ptr->counter / total;
        adder = adder + ptr->counter;
        ptr = ptr->next;
    }
    if(round(adder) == 1) {
        looper(words);
    } else {
        perror("words adding error");
    }
}

//void looper(List* words, )

void jsd(List* words) {
    double fileFreq = 0;

}
