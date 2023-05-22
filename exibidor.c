#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "exibidor.h"

exibir_u1_hexa(estrutura){
    printf("%x \n", estrutura);
}


// exibir o cp_info
// iremos precisar de um ponteiro para o classfile 
void exibir_cp_info(ClassFile *classFile){
    
    // pegar o contador de constant pool
    int cp_info_count = classFile->constant_pool_count;

    // pegar o endereço do constant pool salvo e colocar no ponteiro constantPool.
    cp_info *constantPool = classFile->constant_pool;
    
    printf("Constant Pool \n");

    // iterar nos constant pools e ir printando com base em cada um de (1 até count - 1) 
    for(int i = 1; i < cp_info_count; i++){
        cp_info constantPoolItem = constatPool[i];

        // primeiro byte é o tag 
        exibir_u1_hexa(constantPoolItem.tag);


        // agora temos o restante que depende do tag, aplicar um SWITCH

        switch(tag){

            case(CONSTANT_Class_info)


        };

    }

}
