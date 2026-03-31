#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <sys/stat.h>
#include "linkedList.h"
#include "tokenizer.h"
#include "math.h"

int main (int argc, char* argv[]) {
    if(argc < 2 ) {
        printf("Usage: %s <directory_path>\n", argv[0]);
        return 1;
    }

    int capacity = 10;
    int fileCount = 0;

    //Setting up my glorious Master Array
    List ** allFiles = initializeArray();

    //loops through all user inputs to take multiple arguments
    for (int i = 1; i < argc; i++) {
        struct stat arg_st;
        if(stat(argv[i], &arg_st) != 0) {
            perror("Error accessing arg");
            continue;
        }

        if (S_ISDIR(arg_st.st_mode)) {

            //runs through directories and files to get to the lowest files
            //Then reads said files and writes them to the master allfiles
            paceDirectories(argv[i], &allFiles, &fileCount, &capacity);
        } else if (S_ISREG(arg_st.st_mode)) {
            //checks if more space is needed for stuff in master array
            if(fileCount >= capacity) {
                allFiles = lengthenArray(allFiles, &capacity);
            }

            //initializes, tokenizes, and stores
            List* newList = initializeList(argv[i]);
            tokenize(argv[i], arg_st.st_size, newList);

            allFiles[fileCount] = newList;
            fileCount++;
        }
    }

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