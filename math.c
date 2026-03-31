#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include "linkedList.h"
#include "tokenizer.h"

void jsd(List* file1, List* file2) {

    Node* ptr1 = file1->head;
    Node* ptr2 = file2->head;
    char* key;
    char* searchVal;

    double totalJSD = 0;

    while(ptr1 != NULL) {
        key = ptr1->data;
        int found = 0;

        while(ptr2 != NULL) {
            searchVal = ptr2->data;
            if(strcmp(key, searchVal) == 0) {
                found = 1;
                ptr2->seen = 1;
                
                double p = ptr1->mean;
                double q = ptr2->mean;

                double m = 0.5 * (p + q);

                double firstTerm = (p * log(p / m));
                double secondTerm = (q * log(q / m));
                totalJSD += (firstTerm + secondTerm);
                break;
            }
            ptr2 = ptr2->next;
        }

        if(found == 0) {
            totalJSD += (ptr1->mean * log(2));
        }
        ptr1 = ptr1->next;
        ptr2 = file2->head;

    }

    ptr2 = file2->head;

    while(ptr2 != NULL) {
   
        if(ptr2->seen == 0) {          
            totalJSD += (ptr2->mean * log(2));
        } else {
            ptr2->seen = 0;
        }
        
        ptr2 = ptr2->next;

    }
    totalJSD = sqrt(totalJSD * 0.5);

    print("%.5f %s %s\n", totalJSD, file1->name, file2->name);
}

void looper(List** allFiles, int fileCount) {
    for(int i = 0; i < fileCount; i++) {
        for(int j = i + 1; j < fileCount; j++) {
            jsd(allFiles[i], allFiles[j]);
        }
    }
}

void wfd(List** allFiles, int fileCount) {
    for(int i = 0; i < fileCount; i++) {
        List* currList = allFiles[i];
        Node* ptr = currList->head;
        double adder = 0;
    
        while(ptr != NULL) {
            ptr->mean = ptr->counter / (double) currList->totalCount;
            adder = adder + ptr->mean;
            ptr = ptr->next;
        }
        if(round(adder) == 1) {
        } else {
            perror("words adding error");
        }
        adder = 0;
    }
}