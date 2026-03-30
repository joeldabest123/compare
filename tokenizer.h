#ifndef TOKENIZER_H
#define TOKENIZER_H

char* bufferBuilder(const char *, struct dirent*);
void buffToList(char* , long , List* );
void tokenize(const char *, long , List* );
void paceDirectories(const char *, List* );



#endif