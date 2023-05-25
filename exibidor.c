#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exibidor.h"


// print u1 em hexadecimal
// void exibir_u1_hexa(u1 estrutura){
//     printf("%x \n", estrutura);
// }


// essa função vai retornar um vetor de char
// pegar o cp info em questão usar o lenght para iterar e "concatenar" a string 
char* Utf8_decoder(cp_info *cp_info_pointer){
    
    // pegar o tamanho
    u1 length = cp_info_pointer->constant_type_union.Utf8.length;
    
    // alocando espaço em memória para a string
    char* string = (char *) malloc((length) * sizeof(char)); 

    // alimentando a string com os caracteres?
    for(int i = 0; i < length; i++){
        // pegar o byte em questão e transfomar para char 
        u1 byte = cp_info_pointer->constant_type_union.Utf8.bytes[i];
        *(string+i*sizeof(char)) = (char) byte;
        // precisa de casting, não. 1 char -> 1 byte em C
        // string[i] = byte; 
    };

    return string;
}




// exibir o cp_info
// iremos precisar de um ponteiro para o classfile 
void exibir_cp_info(ClassFile *classFile){
    
    // pegar o contador de constant pool
    int cp_info_count = classFile->constant_pool_count;

    // pegar o endereço do constant pool salvo e colocar no ponteiro constantPool.
    cp_info *constantPool = classFile->constant_pool;
    
    printf("Constant Pool \n");

    // iterar nos constant pools e ir printando com base em cada um de (1 até cp_count - 1) 
    for(int i = 1; i < 2; i++){

        // constantPoolItem é um ponteiro que aponta para a cp em questão
        // aqui pegamos no &constantPool[i] o endereço do cp_info localizado nessa posição
        // cp_info *constantPoolItem = &constantPool[i];

        // imprimir o indice do constant pool
        printf("[%d] ", i);
        // primeiro byte é o tag 
        printf("Tag: %d \n", constantPool[i].tag);

        // agora temos o restante que depende do tag, aplicar um SWITCH
        // para cada estrutura, agora temos que realizar os devidos prints
        switch(constantPool[i].tag){
            
            case(CONSTANT_Class_info):
                // colocar o cp_info aqui?
                u1 class_name_index = constantPool[i].constant_type_union.Class_info.name_index;
                // aqui pegamos o index para acessar a constante utf_8 para a nossa função
                printf("Class name: cp_info #%d <%s>\n", class_name_index, Utf8_decoder(&constantPool[class_name_index]));
                break;

            case(CONSTANT_Fieldref_info):
                
                u1 fieldref_class_index = constantPool[i].constant_type_union.Fieldref_info.class_index;
                printf("Class name: cp_info #%d <%s>\n", fieldref_class_index, Utf8_decoder(&constantPool[fieldref_class_index]));
                
                u1 fieldref_name_and_type_index = constantPool[i].constant_type_union.Fieldref_info.name_and_type_index;
                printf("Name and type: cp_info #%d <%s>\n", fieldref_name_and_type_index, Utf8_decoder(&constantPool[fieldref_name_and_type_index]));

                break;
                
            case(CONSTANT_Methodref_info):

                u1 methodref_class_index = constantPool[i].constant_type_union.Methodref_info.class_index;
                
                // meio confuso, tem outras formas de implementar
                // aqui o class_index aponta para uma classe no constant poll e depois essa class_info aponta para um utf8.
                
                printf("Class name: cp_info #%d <%s>\n", methodref_class_index, Utf8_decoder(&constantPool[constantPool[methodref_class_index].constant_type_union.Class_info.name_index]));
                
                // u1 methodref_name_and_type_index = constantPool[i].constant_type_union.Methodref_info.name_and_type_index;
                // printf("Name and type: cp_info #%d <%s>\n", methodref_name_and_type_index, Utf8_decoder(&constantPool[methodref_name_and_type_index]));
                
                break;
                
            // case(CONSTANT_InterfaceMethodref_info):
            //     cp_info_pointer->constant_type_union.InterfaceMethodref_info.class_index = u2Read(fd);
            //     cp_info_pointer->constant_type_union.InterfaceMethodref_info.name_and_type_index = u2Read(fd);
            //     break;
                
            // case(CONSTANT_String_info):
            //     cp_info_pointer->constant_type_union.String.string_index = u2Read(fd);
            //     break;

            // case(CONSTANT_Integer_info):
            //     // IEEE 754 floating-point single format  
            //     cp_info_pointer->constant_type_union.Float.bytes = u4Read(fd);
            //     break;
            
            // case(CONSTANT_Float_info):
            //     // IEEE 754 floating-point single format 
            //     // na hora de representar tem que utilizar -> result of the mathematical expression s · m · 2e-150. 
            //     cp_info_pointer->constant_type_union.Float.bytes = u4Read(fd);
            //     break;

            // case(CONSTANT_Long_info):
            //     // pular o indice? SIM
            //     *cp_index++;
            //     // também tem toda uma técnica na hora de representar
            //     cp_info_pointer->constant_type_union.Long.high_bytes = u4Read(fd);
            //     cp_info_pointer->constant_type_union.Long.low_bytes = u4Read(fd);
            //     break;

            // case(CONSTANT_Double_info):
            //     // pular o indice? SIM
            //     *cp_index++;
            //     // também tem toda uma técnica na hora de representar
            //     cp_info_pointer->constant_type_union.Double.high_bytes = u4Read(fd);
            //     cp_info_pointer->constant_type_union.Double.low_bytes = u4Read(fd);
            //     break;
            
            // case(CONSTANT_NameAndType_info):
            //     cp_info_pointer->constant_type_union.NameAndType.name_index = u2Read(fd);
            //     cp_info_pointer->constant_type_union.NameAndType.descriptor_index = u2Read(fd);
            //     break;
            
            // case(CONSTANT_Utf8_info):
            //     //the number of bytes in the bytes array (not the length of the resulting string) 
            //     cp_info_pointer->constant_type_union.Utf8.length = u2Read(fd);

            //     u2 lenght = cp_info_pointer->constant_type_union.Utf8.length;

            //     //bytes é um ponteiro para um array de lenght bytes -> alocando espaco e memoria para os bytes
            //     u1 *bytes = (u1 *) malloc(lenght * sizeof(u1));
            //     break;

            default:
                break;


        };

    }

}
