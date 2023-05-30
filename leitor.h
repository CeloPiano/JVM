/**
 * @file leitor_exibidor.h
 * @author Marcelo Piano
 * @author Aluno 2
 * @author Aluno 3
 * @author Aluno 4
 * @author Aluno 5
 * @brief Arquivo com as funções utilizadas no leitor.
 * @details Declaração das funções de leitura.
 */
// #include "types.h"
#ifndef LEITORH
#define LEITORH
#endif

// sempre que tiver um INDEX é um indice do constant pool

// Funções de leitura de 8, 16, 32 e 64 bits

/// @brief lê o tipo de dado u1
/// @param  fd Ponteiro para Byte do arquivo .Class lido
static u1 u1Read(FILE * fd);

/// @brief lê o tipo de dado u2
/// @param  fd Ponteiro para Byte do arquivo .Class lido
static u2 u2Read(FILE * fd);

/// @brief lê o tipo de dado u4
/// @param  fd Ponteiro para Byte do arquivo .Class lido
static u4 u4Read(FILE * fd);

/// @brief lê o tipo de dado u8
/// @param  fd Ponteiro para Byte do arquivo .Class lido
static u8 u8Read(FILE * fd);


/// @brief Funçao que le o arquivo 
/// @param fd Ponteiro para Byte do arquivo .Class lido
/// @param cf Ponteiro para o Class File
void read_cp_info(FILE *,ClassFile *);

/// @brief Funçao que le o arquivo 
/// @param fd Ponteiro para Byte do arquivo .Class lido
/// @param cf Ponteiro para o Class File
void class_reader(FILE *,ClassFile *);

