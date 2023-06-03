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
        *(string+i) =  byte;
    };

    return string;
}

char * accFlag_decoder(u2 accFlag) {
    char *flagName = (char *) malloc(11 * sizeof(char));

    switch (accFlag) {
        case 0x0001:
            strcat(flagName, "Public");
            break;
        case 0x0010:
            strcat(flagName, "Final");
            break;
        case 0x0020:
            strcat(flagName, "Super");
            break;
        case 0x0200:
            strcat(flagName, "Interface");
            break;
        case 0x0400:
            strcat(flagName, "Abstract");
            break;
        case 0x1000:
            strcat(flagName, "Synthetic");
            break;
        case 0x2000:
            strcat(flagName, "Annotation");
            break;
        case 0x4000:
            strcat(flagName, "Enum");
            break;
        default:
            strcat(flagName, "Erro");
    }

    return flagName;
}

char *class_decoder(cp_info *cp, int classIndex) {
    int UTF8index = cp[classIndex].constant_type_union.Class_info.name_index;
    char *className = Utf8_decoder(&cp[UTF8index]);
    return className;
}

// exibir o cp_info
// iremos precisar de um ponteiro para o classfile 
void exibir_cp_info(ClassFile *classFile){
    
    // pegar o contador de constant pool
    int cp_info_count = classFile->constant_pool_count;

    // pegar o endereço do constant pool salvo e colocar no ponteiro constantPool.
    cp_info *constantPool = classFile->constant_pool;
    
    printf("Constant Pool \n \n");

    // iterar nos constant pools e ir printando com base em cada um de (1 até cp_count - 1) 
    for(int i = 1; i < cp_info_count; i++){
    // printf("\n debug indice = %d \n\n", methodref_class_index);

        // constantPoolItem é um ponteiro que aponta para a cp em questão
        // aqui pegamos no &constantPool[i] o endereço do cp_info localizado nessa posição
        // cp_info *constantPoolItem = &constantPool[i];

        // imprimir o indice do constant pool
        printf("[0%d] - ", i);
        // primeiro byte é o tag 
        printf("Tag: %d \n", constantPool[i].tag);
        // agora temos o restante que depende do tag, aplicar um SWITCH
        // para cada estrutura, agora temos que realizar os devidos prints
        switch(constantPool[i].tag){
            
            case(CONSTANT_Class_info):
                { 
                    u2 class_name_index = constantPool[i].constant_type_union.Class_info.name_index;
                    // aqui pegamos o index para acessar a constante utf_8 para a nossa função
                    printf("Class name: cp_info #%d <%s>\n", class_name_index, Utf8_decoder(&constantPool[class_name_index]));
                }
                break;

            case(CONSTANT_Fieldref_info):
                {
                    
                u1 fieldref_class_index = constantPool[i].constant_type_union.Fieldref_info.class_index;
                u1 fieldref_name_and_type_index = constantPool[i].constant_type_union.Fieldref_info.name_and_type_index;
                
                // meio confuso, tem outras formas de implementar
                // aqui o class_index aponta para uma classe no constant poll e depois essa class_info aponta para um utf8.
                
                // printando o class name
                printf("Class name: cp_info #%d <%s>\n", fieldref_class_index, Utf8_decoder(&constantPool[constantPool[fieldref_class_index].constant_type_union.Class_info.name_index]));
                
                // printando o name and type
                // name
                printf("Name and type: cp_info #%d <%s : ",  fieldref_name_and_type_index, Utf8_decoder(&constantPool[constantPool[fieldref_name_and_type_index].constant_type_union.NameAndType.name_index]));

                // descriptor
                printf("%s>\n \n", Utf8_decoder(&constantPool[constantPool[fieldref_name_and_type_index].constant_type_union.NameAndType.descriptor_index]));
                }
                
                break;
                
            case(CONSTANT_Methodref_info):
                {

                u1 methodref_class_index = constantPool[i].constant_type_union.Methodref_info.class_index;
                u1 methodref_name_and_type_index = constantPool[i].constant_type_union.Methodref_info.name_and_type_index;
                
                // meio confuso, tem outras formas de implementar
                // aqui o class_index aponta para uma classe no constant poll e depois essa class_info aponta para um utf8.
                
                // printando o class name
                printf("Class name: cp_info #%d <%s>\n", methodref_class_index, Utf8_decoder(&constantPool[constantPool[methodref_class_index].constant_type_union.Class_info.name_index]));
                
                // printando o name and type

                // name
                printf("Name and type: cp_info #%d <%s : ",  methodref_name_and_type_index, Utf8_decoder(&constantPool[constantPool[methodref_name_and_type_index].constant_type_union.NameAndType.name_index]));

                // descriptor
                printf("%s> \n \n", Utf8_decoder(&constantPool[constantPool[methodref_name_and_type_index].constant_type_union.NameAndType.descriptor_index]));
                
                }
                break;
                

            // case(CONSTANT_InterfaceMethodref_info): {
            //     cp_info_pointer->constant_type_union.InterfaceMethodref_info.class_index = u2Read(fd);
            //     cp_info_pointer->constant_type_union.InterfaceMethodref_info.name_and_type_index = u2Read(fd);
            //     }
            //     break;
                
            case(CONSTANT_String_info):
            {

                u1 string_info_index = constantPool[i].constant_type_union.String.string_index;

                printf("String: cp_info #%d <%s> \n \n", string_info_index ,Utf8_decoder(&constantPool[string_info_index]));

            }
                break;

            // case(CONSTANT_Integer_info):
            //     // IEEE 754 floating-point single format  
            //     cp_info_pointer->constant_type_union.Float.bytes = u4Read(fd);
            //     break;
            
            case(CONSTANT_Float_info):
                {

            
                }   
                break;

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
            
            case(CONSTANT_Utf8_info):
            {   
                // lenght of byte array?
                printf("lenght of Byte array: %d", constantPool[i].constant_type_union.Utf8.length);
                // lenght of string?
                printf("lenght of string: %d", constantPool[i].constant_type_union.Utf8.length);
                // String
                printf("String: %s \n \n", Utf8_decoder(&constantPool[i]));
            }   
                break;

            default:
                break;


        };

    }

}

void class_exhibitor(ClassFile *cf) {
    // Exibição magic number
    printf("Magic: %d \n", cf->minor_version);

    // Exibição minor version
    printf("Minor version: %d \n", cf->minor_version);

    // Exibição major version
    printf("Major version: %d \n", cf->major_version);

    // Exibição constant pool
    printf("Constant pool size: %d \n", cf->constant_pool_count);
    exibir_cp_info(cf);

    // Exibição access flags
    printf("Access flags: %s \n", accFlag_decoder(cf->access_flags));
    printf("Access flags: %d \n", cf->access_flags);

    // Exibição this class 
    printf("This class: #%d %s \n", cf->this_class, class_decoder(cf->constant_pool, cf->this_class));

    // Exibição super class
    printf("Super class: #%d %s \n", cf->super_class, class_decoder(cf->constant_pool, cf->super_class));

    // Exibição 

}