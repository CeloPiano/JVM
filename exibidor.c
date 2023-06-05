#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exibidor.h"


char * accFlag_decoder(u2);

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


// ----------------------------- METHODS -------------------------------------
void code_exibitor(attribute_info *attribute, ClassFile *cf){
    
    // printar THE CODE

    
    printf("\nMISC: \n\n");
    printf("Maximum stack size: %d \n",attribute->attribute_info_union.code_attribute.max_stack);
    printf("Maximum local variables: %d \n",attribute->attribute_info_union.code_attribute.max_locals);
    printf("Maximum code length: %d \n",attribute->attribute_info_union.code_attribute.code_lenght);


    

    // vetor de code 
    
    

};




// ----------------------------- METHODS -------------------------------------

void attributes_exibitor(attribute_info *attribute, ClassFile * cf){

    // pegar o tamanho
    u2 length = attribute->attribute_lenght;

    // pegar o name index
    u2 name_index = attribute->attribute_name_index;
    
    printf("Attribute name index: cp_info#%d <%s> \n", name_index, Utf8_decoder(&cf->constant_pool[name_index]));

    printf("Attribute length:  %d\n", length);

    char * name = Utf8_decoder(&cf->constant_pool[name_index]);


    // usar o code length aqui não faz sentido porque não é pra printar um code para cada length.
    // entramos na função e com base no bytecode vamos ter que tomar nossas decisões do que fazer

    if(!strcmp(name, "Code")){
        code_exibitor(attribute, cf);
    };


};








// ----------------------------- METHODS -------------------------------------

void methods_exibitor(ClassFile *cf){

    u2 methods_count = cf->methods_count;

    printf("Início Methods: \n \n");

    // iterar em cada method
    for (int i = 0; i < methods_count; i++){
            
        // pegar o method
        method_info *method = &cf->methods[i]; 
        
        printf("Method[%d]\n", i);

        //name
        printf("Name: cp_info #%d <%s> \n", method->name_index, Utf8_decoder(&cf->constant_pool[method->name_index])); 

        // discriptor 
        printf("Descriptor: cp_info #%d <%s> \n", method->descriptor_index, Utf8_decoder(&cf->constant_pool[method->descriptor_index]));
        
        // acess flags
        printf("Acess Flags: %x [%s] \n", method->acess_flags, accFlag_decoder(method->acess_flags));

        // attributes
        attributes_exibitor(method->attributes, cf);



        printf("\n");

    };

printf("Fim Methods \n \n");

};


char * accFlag_decoder(u2 accFlag) {
    char *flagName = (char *) malloc(128 * sizeof(char));
    if (accFlag & 0x0001) {
        strcat(flagName, "public ");
    }if (accFlag & 0x0002) {
        strcat(flagName, "private ");
    }if (accFlag & 0x0004) {
        strcat(flagName, "protected ");
    }if (accFlag & 0x0008) {
        strcat(flagName, "static ");
    } if (accFlag & 0x0010) {
        strcat(flagName, "final ");
    } if (accFlag & 0x0020) {
        strcat(flagName, "super ");
    } if (accFlag & 0x0200) {
        strcat(flagName, "interface ");
    } if (accFlag & 0x0400) {
        strcat(flagName, "abstract ");
    } if (accFlag & 0x1000) {
        strcat(flagName, "synthetic ");
    } if (accFlag & 0x2000) {
        strcat(flagName, "annotation ");
    } if (accFlag & 0x4000) {
        strcat(flagName, "enum ");
    }

    return flagName;
}

char *class_decoder(cp_info *cp, int classIndex) {
    int UTF8index = cp[classIndex].constant_type_union.Class_info.name_index;
    char *className = Utf8_decoder(&cp[UTF8index]);
    return className;
}

void interfaces_exibitor (u2 *interfaces, int interfacesCount, cp_info *cp) {
    if (interfacesCount != 0) {
        printf("Início Interfaces: \n \n");
        for (int i = 0; i < interfacesCount; i++) {
            printf("[0%d] - ", i);
            printf("Class name: #%d <%s> \n", interfaces[i], class_decoder(cp, interfaces[i]));
        }
        printf("\nFim Interfaces \n \n");
    }
}

// exibir o cp_info
// iremos precisar de um ponteiro para o classfile 
void cp_info_exibitor(ClassFile *classFile){
    
    // pegar o contador de constant pool
    int cp_info_count = classFile->constant_pool_count;

    // pegar o endereço do constant pool salvo e colocar no ponteiro constantPool.
    cp_info *constantPool = classFile->constant_pool;
    
    printf("Início Constant Pool \n \n");

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
                printf("lenght of Byte array: %d \n", constantPool[i].constant_type_union.Utf8.length);
                // lenght of string?
                printf("lenght of string: %d \n", constantPool[i].constant_type_union.Utf8.length);
                // String
                printf("String: %s \n \n", Utf8_decoder(&constantPool[i]));
            }   
                break;

            default:
                break;
        };
    }

    printf("Fim Constant Pool \n \n");

}

void class_exibitor(ClassFile *cf) {
    // Exibição magic number
    printf("Magic: %d \n", cf->minor_version);

    // Exibição minor version
    printf("Minor version: %d \n", cf->minor_version);

    // Exibição major version
    printf("Major version: %d \n", cf->major_version);

    // Exibição constant pool size
    printf("Constant Pool Count: %d \n", cf->constant_pool_count);

    // Exibição access flags
    printf("Access flags: %s \n", accFlag_decoder(cf->access_flags));

    // Exibição this class 
    printf("This class: #%d %s \n", cf->this_class, class_decoder(cf->constant_pool, cf->this_class));

    // Exibição super class
    printf("Super class: #%d %s \n", cf->super_class, class_decoder(cf->constant_pool, cf->super_class));

    // Exibição interfaces count
    printf("Interfaces count: %d\n", cf->interfaces_count);

    // Exibição fields count 
    printf("Fields count: %d \n", cf->fields_count);

    // Exibição methods count
    printf("Methods count: %d \n", cf->methods_count);

    // Exibição attributes count
    printf("Attributes count: %d \n", cf->attributes_count);

    // Exibição constant pool
    cp_info_exibitor(cf);
    
    // Exibição interfaces
    interfaces_exibitor(cf->interfaces, cf->interfaces_count, cf->constant_pool);



    // exibição dos methods
    methods_exibitor(cf);
    


}