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




char* bufferBuilder(const char *path, struct dirent* entry) {
    int bufferCount = 0;
    char* fileName = entry->d_name;

    bufferCount = strlen(path) + 1 + strlen(fileName) + 1;

    char * tempBuffer = malloc(bufferCount);
    snprintf(tempBuffer, bufferCount, "%s/%s", path, fileName);
    
    return tempBuffer;
}


void buffToList(char* buffer, long fileSize, List* words) {

    int start = 0;
    int end = 0;
    char* word;

    while(buffer[start] == ' ') {
        start++;
    }

    for(int end = 0; end < fileSize; end++) {
        if((buffer[end]) == ' ' || buffer[end] == '\0') {
            buffer[end] = '\0';
            if (end > start) {
                word = malloc(end + 1 - start);
                strncpy(word, &buffer[start], end - start);
                word[end - start] = '\0';
                insert(words, word);
            }
                start = end + 1;

            while(start < fileSize && buffer[start] == ' ') {
                start++;
            }
            end = start - 1;
            
        }
        
    }
}

void tokenize(const char *file, long fileSize, List* words) {
    int fd = open(file, O_RDONLY);
    char val;
    char* buffer = malloc(fileSize + 1);

    if(fd == -1) {
        perror("Error opening file");
        return;
    }

    int check = read(fd, buffer, fileSize);
    buffer[fileSize] = '\0';

    if(check == -1) {
        perror("tokenizing error");
        return;
    }

    buffToList(buffer, fileSize, words);

    free(buffer);
    close(fd);
}


void paceDirectories(const char *path, List* words) {
    DIR* d = opendir(path);

    if(d == NULL) {
        perror("Error opening Directory");
        return;
    }

    struct dirent* entry;
    char* fileName;

    while((entry = readdir(d)) != NULL) {


        fileName = entry->d_name;
        if(strcmp(fileName, ".") == 0 || strcmp(fileName, "..") == 0) {
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
                    tokenize(fullPath, st.st_size, words);
                };
            }
        } else {
            if (S_ISDIR(st.st_mode)) {
                paceDirectories(fullPath, words);
            }
        }

        free(fullPath);

    }

    closedir(d);
}