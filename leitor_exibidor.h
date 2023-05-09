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

// sempre que tiver um INDEX é um indice do constant pool

// definindo os tamanhos

/// @brief Tipo u1 - 8bits
typedef int8_t u1;

/// @brief Tipo u2 - 16bits
typedef int16_t u2;

/// @brief Tipo u4 - 32bits
typedef int32_t u4;

/// @brief Tipo u8 - 64bits
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


/// @brief Struct Attribute info

typedef struct attribute_info{
    u2 attribute_name_index;
    u4 attribute_lenght;
    u1 info[attribute_lenght];
}


/// @brief Struct do Method

typedef struct field_info{
    u2 acess_flags; 
    u2 name_index;          //aqui nesse caso pode ser <init>, <clinit> ou um nome valido para o metodo
    u2 descriptor_index;            
    u2 attributes_count;
    attribute_info attributes**;  //aqui acessamos o atribute info utilizando o count para acessar uma estrutura de atribute info

/// @brief Struct do Field

typedef struct field_info{
    u2 acess_flags; 
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info attributes**;  //aqui acessamos o atribute info utilizando o count
}

/// @brief Struct cp_info
typedef struct cp_info{
    u1 tag;

    union constant_type{
        struct{
            u2 name_index;
        } Class_info;

        struct{
            u2 class_index;
            u2 name_and_type_index;
        } Fieldref_info;

        struct{
            u2 class_index;
            u2 name_and_type_index;
        } Methodref_info;
        
        struct{
            u2 class_index;
            u2 name_and_type_index;
        } InterfaceMethodref_info;
        
        struct{
            u2 name_index;
            u2 descriptor_index;
        } NameAndType;
        
        struct{
            u2 length;          //indica o número de bytes no array bytes (embaixo) pode ser 1, 2 ou 3 bytes
            u1 *bytes;          // quando formos alocar os bytes levamos em conta o numero de byts aqui é um array
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



/// @brief Struct que define o ClassFile
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

