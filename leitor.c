#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leitor_exibidor.h"


// file reader
FILE* fopen(const char* filename, const char* mode); 


// read u1 (8bits)
static u1 u1Read(FILE *fd){
    u1 toReturn = getc(fd);
    return toReturn;
};
// read u2 (16bits)
static u2 u2Read(FILE *fd){
    u2 toReturn = getc(fd);
    toReturn = (toReturn << 8 | getc(fd));
    return toReturn ;
};
// read u4 (32bits)
static u4 u4Read(FILE *fd){
    u4 toReturn = getc(fd);
    for(int i = 0; i < 3; i++){
        toReturn = (toReturn << 8 | getc(fd));
    }
    return toReturn ;
};
// read u8 (64bits)
static u8 u8Read(FILE *fd){
    u8 toReturn = getc(fd);
    for(int i = 0; i < 7; i++){
        toReturn = (toReturn << 8 | getc(fd));
    }
    return toReturn;
};







