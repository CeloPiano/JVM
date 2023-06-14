// tirei o types dos headers e coloquei
#include <stdio.h>
#include <stdlib.h>
#include "leitor.h"
#include "exibidor.h"

// ferramenta de debug
#define printaU2(objeto) printf("%x \n", objeto);
#define printaU4(objeto) printf("%x \n", objeto);
#define printaU8(objeto) printf("%lx \n", objeto);



int main(int argc, char* argv[]){
    // Lendo o arquivo .CLASS
    char *path;

    if(argc != 2){
        return 1;
    }

    // printf("%s\n", argv[1]);
    path = argv[1];  

    FILE *fd = fopen(path, "rb");
    // Declarando o ponteiro do tipo ClassFile (struct) - Aqui temos que alocar um espaço na memoria do tamanho de classfile e fazer um casting
    ClassFile *cf = (ClassFile *) malloc(sizeof(ClassFile));
    class_reader(fd, cf);
    class_exibitor(cf);
    return 0;
}


