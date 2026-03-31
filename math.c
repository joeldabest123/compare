#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include "linkedList.h"
#include "tokenizer.h"
#include "math.h"

//Compares results and sorts in descending order
int compareResults(const void* a, const void* b) {
    JSDResult* resA = (JSDResult*)a;
    JSDResult* resB = (JSDResult*)b;

    return (resB->combinedCount - resA->combinedCount);
}

//Determines the jsd from 2 given files at a time
JSDResult jsd(List* file1, List* file2) {

    Node* ptr1 = file1->head;
    Node* ptr2 = file2->head;
    char* key;
    char* searchVal;

    double totalJSD = 0;

    while(ptr1 != NULL) { //runs until file1 runs out of words
        key = ptr1->data;
        int found = 0;

        while(ptr2 != NULL) { //runs until file2 runs out of words
            searchVal = ptr2->data;
            if(strcmp(key, searchVal) == 0) {
                found = 1;
                ptr2->seen = 1;
                
                double p = ptr1->mean; //calculates mean frequency here
                double q = ptr2->mean;

                double m = 0.5 * (p + q);

                double firstTerm = 0.5 * (p * log2(p / m)); //calculates KLD from here
                double secondTerm = 0.5 * (q * log2(q / m));
                totalJSD += (firstTerm + secondTerm);
                break;
            }
            ptr2 = ptr2->next;
        }

        if(found == 0) { //if a word from first file isn't found in second, runs process
            totalJSD += 0.5 * (ptr1->mean * log2(2.0));
        }
        ptr1 = ptr1->next;
        ptr2 = file2->head;

    }

    ptr2 = file2->head;

    while(ptr2 != NULL) { //runs opposite process to check all file2 words not in first list
   
        if(ptr2->seen == 0) {          
            totalJSD += 0.5 * (ptr2->mean * log2(2.0));
        } else {
            ptr2->seen = 0;
        }
        
        ptr2 = ptr2->next;

    }
    totalJSD = sqrt(totalJSD);

    JSDResult res;
    res.distance = totalJSD;
    res.name1 = file1->name;
    res.name2 = file2->name;
    res.combinedCount = file1->totalCount + file2->totalCount;
    return res;
}

//loops through all possible file combos
void looper(List** allFiles, int fileCount) {
    int numPairs = (fileCount * (fileCount - 1)) / 2;
    JSDResult* results = malloc(sizeof(JSDResult) * numPairs); //gets JSDResult type from jsd
    int k = 0;

    // Gathers all comparisons
    for(int i = 0; i < fileCount; i++) {
        for(int j = i + 1; j < fileCount; j++) {
            results[k] = jsd(allFiles[i], allFiles[j]);
            k++;
        }
    }

    // Sort the array using qsort and whatnot
    qsort(results, numPairs, sizeof(JSDResult), compareResults);

    //prints sorted table
    for(int i = 0; i < numPairs; i++) {
        printf("%.5f %s %s\n", results[i].distance, results[i].name1, results[i].name2);
    }

    free(results); //frees the results from jsd
}

//finds the mean frequency from all files
void wfd(List** allFiles, int fileCount) {
    for(int i = 0; i < fileCount; i++) {
        List* currList = allFiles[i];
        Node* ptr = currList->head;
        double adder = 0;
    
        while(ptr != NULL) {
            ptr->mean = ptr->counter / (double) currList->totalCount; //sticks mean frequency into mean slot
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