#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include "linkedList.h"
#include "tokenizer.h"

int main (int argc, char* argv[]) {
    if(argc < 2 ) {
        printf("Usage: %s <directory_path>\n", argv[0]);
        return 1;
    }

    int capacity = 10;
    int fileCount = 0;

    //Setting up my glorious Master Array
    List ** allFiles = initializeArray();

    //runs through directories and files to get to the lowest files
    //Then reads said files and writes them to the master allfiles
    paceDirectories(argv[1], &allFiles, &fileCount, &capacity);

    if(fileCount < 2) {
        printf("Error: Found %d .txt files. Need at least 2 for comparison.\n", fileCount);
        clearList(allFiles, fileCount); //cleans array out prematurely.
        return 1;
    }
    //runs through all files and compares all words
    //also grabs the means from like-words
    wfd(allFiles, fileCount);

    //runs the comparison loops to get the JSD
    looper(allFiles, fileCount);

    //Final cleanup and frees everything
    clearList(allFiles, fileCount);

    return 0;

}