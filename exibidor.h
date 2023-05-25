/**
 * @file leitor_exibidor.h
 * @author Marcelo Piano
 * @author Aluno 2
 * @author Aluno 3
 * @author Aluno 4
 * @author Aluno 5
 * @brief Arquivo com as funções utilizadas no exibidor.
 * @details Declaração das funções de exibição.
 */


// #include "types.h"
#ifndef EXIBIDORH
#define EXIBIDORH
#endif

/// @brief Função que exibe os bytes em ascii que estão alocados no espaço de memória Bytes 
/// @param cp_info_pointer Ponteiro que aponta para o cp_info que representa um Utf8
char* Utf8_decoder(cp_info * cp_info_pointer);

/// @brief Função que exibe o cp info com base no ponteiro que aponta para os cp_infos alocados 
/// @param classFile Ponteiro que aponta para o classfile em questão
void exibir_cp_info(ClassFile *classFile);

