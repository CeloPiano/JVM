/**
 * @file leitor_exibidor.h
 * @author Marcelo Piano
 * @author Aluno 2
 * @author Aluno 3
 * @author Aluno 4
 * @author Aluno 5
 * @brief Arquivo com as funções utilizadas no leitor exibidor
 * @details Declaração das funções de leitura de diversos campos e atributos.
 */

#include <stdint.h>

// definindo os tamanhos
typedef int8_t u1;
typedef int16_t u2;
typedef int32_t u4;
typedef int64_t u8;

// Funções de leitura de 8, 16, 32 e 64 bits

/// @brief lê o tipo de dado u1
static u1 u1Read();

/// @brief lê o tipo de dado u2
static u2 u2Read();

/// @brief lê o tipo de dado u4
static u4 u4Read();

/// @brief lê o tipo de dado u8
static u8 u8Read();


/// @brief Struct que define classfile
typedef struct Classfile
{
    u4 magic;
    u2 minor_version;
    u2 major_version;
    u2 constant_pool_count;
    cp_info *constant_pool;
    u2 access_flags;
    u2 this_class;
    u2 super_class;
    u2 interfaces_count;
    u2 *interfaces; //aqui temos um array com os indices apontando para o constant poll
    u2 fields_count;
    // field_info *fields;
    u2 methods_count;
    // method_info *methods;
    u2 attributes_count;
    // attribute_info *attributes;

} Classfile;


/// @brief Struct cp_info
typedef struct cp_info{
    u1 tag;

    union constant_type{
        struct{
            u2 name_index;
        } Class;

        struct{
            u2 class_index;
            u2 name_and_type_index;
        } Fieldref;

        struct{
            u2 class_index;
            u2 name_and_type_index;
        } Methodref;
        
        struct{
            u2 class_index;
            u2 name_and_type_index;
        } InterfaceMethodref;
        
        struct{
            u2 name_index;
            u2 descriptor_index;
        } NameAndType;
        
        struct{
            u2 length;          //indica o número de bytes no array bytes (embaixo) pode ser 1, 2 ou 3 bytes
            u1 *bytes;
            // u1 *bytes = (u1 *) malloc(lenght * sizeof(u1));     //aqui criamos um espaço de memória do tamanho do problema. (u1 tem 1 bit)
        } Utf8;
        
        struct{
            u2 string_index;
        } String;
        
        struct{
            u4 bytes;
        } Integer;
        
        struct{
            u4 bytes;
        } Float;
        
        struct{
            u4 high_bytes;
            u4 low_bytes;
        } Long;
        
        struct{
            u4 high_bytes;
            u4 low_bytes;
        } Double;

    } constant_type_union;

} cp_info;



/// @brief Struct Field info

typedef struct field_info{
    u2 acess_flags; 
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    // attribute_info attributes[attributes_count];
}



