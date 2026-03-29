#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include "tokenizer.h"
#include "linkedList.h"


//something like if addToCount == -1, insert new Node

//reads from file, then calls add to count. 


void paceDirectories(const char *path) {
    DIR* d = opendir(path);

    if(d == NULL) {
        perror("Error opening Directory");
        return;
    }

    struct dirent* entry = readdir(d);
    int bufferCount = 0;
    char* fileName;

    while(entry != NULL) {

        fileName = entry->d_name;
        if(strcmp(fileName, ".") == 0 || strcmp(fileName, "..") == 0) {
            entry = readdir(d);
            continue;
        }

        char* fullPath = bufferBuilder(path, entry);
        struct stat st;

        stat(fullPath, &st);
        if(S_ISREG(st.st_mode)) {
            int entryLength = strlen(fileName);
            if(entryLength >= 4) {
                char* suffix = fileName + (entryLength - 4);

                if(strcmp(suffix, ".txt") == 0) {
                    tokenize(fullPath);
                };
            }
        } else {
            if (S_ISDIR(st.st_mode)) {
                paceDirectories(fullPath);
            }
        }

        free(fullPath);
        entry = readdir(d);

    }

    closedir(d);
}

char* bufferBuilder(const char *path, struct dirent* entry) {
    int bufferCount = 0;
    char* fileName = entry->d_name;

    bufferCount = strlen(path) + 1 + strlen(fileName) + 1;

    char * tempBuffer = malloc(bufferCount);
    snprintf(tempBuffer, bufferCount, "%s/%s", path, fileName);
    
    return tempBuffer;
}

void tokenize(const char *file) {
    int fd = open(file, O_RDONLY);

    if(fd == -1) {
        perror("Error opening file");
        return;
    }

    while()

    if()

    close(file);
}

//int fd = open(path, O_RDONLY);