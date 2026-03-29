#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include "tokenizer.h"

//something like if addToCount == -1, insert new Node

//reads from file, then calls add to count. 

void openFile(const char *file) {
    int fd = open(file, O_RDONLY);
    //

}


void paceDirectories(const char *path) {
    DIR* d = opendir(path);
    struct dirent* entry = readdir(d);
    int bufferCount = 0;
    char* fileName = entry->d_name;


    
    while(entry != NULL) {

        fileName = entry->d_name;
        
        if(strcmp(fileName, ".") == 0 || strcmp(fileName, "..") == 0) {
            entry = readdir(d);
            fileName = entry->d_name;
            continue;
        }

        int entryLength = strlen(fileName);

        char* suffix = fileName + (entryLength - 4);
        if(strcmp(suffix, ".txt") == 0) {
            char* fullPath = bufferBuilder(path, entry);

            struct stat st;

            stat(fullPath, &st);
            if(S_ISREG(st.st_mode)) {
                openFile(fullPath);
            } else {
                paceDirectories(fullPath);
            }
            
            free(fullPath);

        }
        entry = readdir(d);

    }

    close(d);
}

char* bufferBuilder(const char *path, struct dirent* entry) {
    int bufferCount = 0;
    char* fileName = entry->d_name;

    bufferCount = strlen(path) + 1 + strlen(fileName) + 1;

    char * tempBuffer = malloc(bufferCount);
    snprintf(tempBuffer, bufferCount, "%s/%s", path, fileName);
    
    return tempBuffer;
}

void tokenize(const char *path) {
    
}

//int fd = open(path, O_RDONLY);