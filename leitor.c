#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leitor.h"
#include "exibidor.h"

// Funçoes que iremos utilizar para a leitura dos arquivos


// file reader
// FILE* fopen(const char* filename, const char* mode); 


// ----------------- LEITOR DE BYTES -------------------------------- //

// funcoes que retornam u bytes.
// read u1 (8bits) getc -> return e fd++
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

// ----------------- ATTRIBUTE -------------------------------- //
// aqui já passamos o attribute info em questão
void read_attribute(FILE *fd, attribute_info *attr_info, u2 attr_count, cp_info *cp){

    for(int i = 0; i < 2; i++){

        attr_info->attribute_name_index = u2Read(fd);
        attr_info->attribute_lenght = u2Read(fd);

        printf("%s", Utf8_decoder(&cp[attr_info->attribute_name_index]));


        // agora vamos trabalhar com a union
        // switch (attr_info->attribute_lenght)
        // {
        // case /* constant-expression */:
        //     /* code */
        //     break;
        
        // default:
        //     break;
        // }

    }; 
};


// ----------------- METHODS -------------------------------- //


// ----------------- FIELDS -------------------------------- //
// represent all fields, both class variables and instance variables

void read_fields(FILE *fd, ClassFile *cf){
    // alocando ESPAÇO para o cp_info
    cf->fields = (field_info *) malloc(cf->fields_count * sizeof(field_info));
    
    // alocar em memória os fields
    for(int i = 0; i < cf->fields_count; i++){
        // lendo flags
        cf->fields[i].acess_flags = u2Read(fd);
        
        // lendo name_index
        cf->fields[i].name_index = u2Read(fd);
        
        // lendo descriptor_index
        cf->fields[i].descriptor_index = u2Read(fd);
        
        // lendo attributes_count
        cf->fields[i].attributes_count = u2Read(fd);

        // alocando o espaço para os attributes do field
        cf->fields[i].attributes = (attribute_info *) malloc(cf->fields[i].attributes_count * sizeof(attribute_info));

        // lendo field attributes
        read_attribute(fd, cf->fields[i].attributes, cf->fields[i].attributes_count, cf->constant_pool);
    };
};


// ----------------- CONSTANT POOL -------------------------------- //

// Lendo as tags
// no Constant Pool temos os Cp_infos que dependem da tag para fazermos a alocacao

/* exemplo de atribuicao com base na tag
cp_info teste;
teste.tag = 10;
teste.constant_type.Methodref_info.name_index = 20; 
teste.constant_type.testando = 10; 
*/

// para double e integer "If a CONSTANT_Long_info or CONSTANT_Double_info structure is the item in the constant_pool table at index n, then the next usable item in the pool is located at index n+2. The constant_pool index n+1 must be valid but is considered unusable."

// switch do cp info -> aqui com base na tag que o constant pool object tiver teremos que decidir que tipo de estrurura iremos ler

// passar o endereco do ponteiro

// -------------------------- read cp info ----------------------------------- //
void read_cp_info(FILE *fd, ClassFile *cf){
    
    // alocando ESPAÇO para o cp_info na memória e endereçando no ponteiro constant_pool.
    cf->constant_pool = (cp_info *) malloc(cf->constant_pool_count * sizeof(cp_info));
    
    for(int cp_index = 1; cp_index < cf->constant_pool_count; cp_index++){


        cp_info *cp_info = &cf->constant_pool[cp_index];

        cp_info->tag = u1Read(fd);

        // pegar a tag e com base no seu número, selecionar a estrutura.
        u1 tag = cp_info->tag;

        // perguntar pro ladeira a outra alternativa para realizar isso.
        switch(tag){
            case(CONSTANT_Class_info):
                cp_info->constant_type_union.Class_info.name_index = u2Read(fd); 
                break;

            case(CONSTANT_Fieldref_info):
                cp_info->constant_type_union.Fieldref_info.class_index = u2Read(fd);
                cp_info->constant_type_union.Fieldref_info.name_and_type_index = u2Read(fd);
                break;
                
            case(CONSTANT_Methodref_info):
                cp_info->constant_type_union.Methodref_info.class_index = u2Read(fd);
                cp_info->constant_type_union.Methodref_info.name_and_type_index = u2Read(fd);
                break;
                
            case(CONSTANT_InterfaceMethodref_info):
                cp_info->constant_type_union.InterfaceMethodref_info.class_index = u2Read(fd);
                cp_info->constant_type_union.InterfaceMethodref_info.name_and_type_index = u2Read(fd);
                break;
                
            case(CONSTANT_String_info):
                cp_info->constant_type_union.String.string_index = u2Read(fd);
                break;

            case(CONSTANT_Integer_info):
                // IEEE 754 floating-point single format  
                cp_info->constant_type_union.Float.bytes = u4Read(fd);
                break;
            
            case(CONSTANT_Float_info):
                // IEEE 754 floating-point single format 
                // na hora de representar tem que utilizar -> result of the mathematical expression s · m · 2e-150. 
                cp_info->constant_type_union.Float.bytes = u4Read(fd);
                break;

            case(CONSTANT_Long_info):
                // pular o indice? SIM
                cp_index++;
                // também tem toda uma técnica na hora de representar
                cp_info->constant_type_union.Long.high_bytes = u4Read(fd);
                cp_info->constant_type_union.Long.low_bytes = u4Read(fd);
                break;

            case(CONSTANT_Double_info):
                // pular o indice? SIM
                cp_index++;
                // também tem toda uma técnica na hora de representar
                cp_info->constant_type_union.Double.high_bytes = u4Read(fd);
                cp_info->constant_type_union.Double.low_bytes = u4Read(fd);
                break;
            
            case(CONSTANT_NameAndType_info):
                cp_info->constant_type_union.NameAndType.name_index = u2Read(fd);
                cp_info->constant_type_union.NameAndType.descriptor_index = u2Read(fd);
                break;
            
            //erro aqui  
            case(CONSTANT_Utf8_info):
                //the number of bytes in the bytes array (not the length of the resulting string) 
                cp_info->constant_type_union.Utf8.length = u2Read(fd);

                u2 lenght = cp_info->constant_type_union.Utf8.length;

                //bytes é um ponteiro para um array de lenght bytes -> alocando espaco e memoria para os bytes
                cp_info->constant_type_union.Utf8.bytes = (u1 *) malloc(lenght * sizeof(u1));
                
                // iterar dentro do do (0 até lenght - 1)
                for(int i = 0; i < lenght; i++){
                    cp_info->constant_type_union.Utf8.bytes[i] = u1Read(fd);
                }
                break;

            default:
                break;
        }
    };
};   



// -------------------------- .CLASS READING ----------------------------------- //

void class_reader(FILE *fd, ClassFile *cf){

    // Lendo o magic
    cf->magic = u4Read(fd);
    printf("Magic: %d \n",cf->minor_version);
    
    // Lendo minor_version
    cf->minor_version = u2Read(fd);
    printf("Minor_version: %d \n",cf->minor_version);

    // Lendo major_version
    cf->major_version = u2Read(fd);
    printf("Major_version: %d \n",cf->major_version);

    // Lendo constant_pool_count
    cf->constant_pool_count = u2Read(fd);
    printf("Constant pool count: %d \n \n",cf->constant_pool_count);

    // lendo o cp
    read_cp_info(fd, cf);

    // lendo acess flags
    cf->access_flags = u2Read(fd);
    
    // lendo this_class
    cf->this_class = u2Read(fd);
    
    // lendo super_class
    cf->super_class = u2Read(fd);

    // lendo interfaces count 
    cf->interfaces_count = u2Read(fd);    

    // alocando em memória o interfaces count
    cf->interfaces = (u2*) malloc(cf->interfaces_count * sizeof(u2));

    // preenchendo o vetor de interfaces
    for (int i = 0; i < cf->interfaces_count; i++){
        cf->interfaces[i] = u2Read(fd);
    };

    // lendo fields count 
    cf->fields_count = u2Read(fd);

    // lendo os FIELDS
    read_fields(fd, cf);





};



