#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <stdint.h>

#define printaEndereco(ponteiro) printf("%p \n", ponteiro);
#define printa32bits(objeto) printf("%x \n", objeto);
#define printa64bits(objeto) printf("%lx \n", objeto);

// 1 char = 1 byte = 8bits

int main(void){
    char path[] = "hello_world.class";

    FILE *fd = fopen(path, "rb");

    // aqui temos o endereço inicial do ponteiro
    printf("%p \n", fd);


    int64_t toReturn;

    // CA  FE  BA  BE
    // fd

    //           F    E
    // 0000 0000 0000 0000


    toReturn = getc(fd);
    for (int x= 0 ; x < 7; x ++){
        toReturn = toReturn << 8 | getc(fd);
        printaEndereco(fd);
    }
    printf("%lx \n", toReturn);

    
    // char x[100]; 
    // x[0] = getc(stdin);
    // printf("%c", x[0]);
    // printf("%c", x[1]);
    // printf("%c", x[2]);


}