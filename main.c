// tirei o types dos headers e coloquei
#include "leitor.c"
#include "exibidor.c"

// ferramenta de debug
#define printaU2(objeto) printf("%x \n", objeto);
#define printaU4(objeto) printf("%x \n", objeto);
#define printaU8(objeto) printf("%lx \n", objeto);



int main(void){

    // Lendo o arquivo .CLASS
    char path[] = "zoo.class";
    FILE *fd = fopen(path, "rb");

    // Declarando o ponteiro do tipo ClassFile (struct) - Aqui temos que alocar um espaço na memoria do tamanho de classfile e fazer um casting
    ClassFile *cf = (ClassFile *) malloc(sizeof(ClassFile));

    class_reader(fd, cf);
    // exibir_cp_info(cf);

    // printf("\n tag: %d \n\n", cf->constant_pool[20].tag);
    // printf("\n class index: %d \n", cf->constant_pool[1].constant_type_union.Methodref_info.class_index );
    // printf("\n name and type: %d \n", cf->constant_pool[1].constant_type_union.Methodref_info.name_and_type_index );
        


    // printf("\n class index: %d \n", cf->constant_pool[24].constant_type_union.Class_info.name_index);
















    // aqui podemos colocar tudo em uma funcao:

    // // Lendo o magic
    // cf->magic = u4Read(fd);
    // printaU4(cf->magic);

    // // Lendo minor_version
    // cf->minor_version = u2Read(fd);
    // printf("%d \n",cf->minor_version);

    // // Lendo major_version
    // cf->major_version = u2Read(fd);
    // printf("%d \n",cf->major_version);

    // // Lendo constant_pool_count
    // cf->constant_pool_count = u2Read(fd);
    // printf("%d \n",cf->constant_pool_count);

    
    // ----------------------------------------------------------------------------------------------- //
    
    // LENDO O CONSTANT POOL
    
    // criando espaco na memoria para todas as constantes -> constant_pool_count
    // ps: sempre criar uma copia do ponteiro para acessar as nossas constant pools
    // cf->constant_pool = (cp_info *) malloc((cf->constant_pool_count) * (sizeof(cp_info)));

    //Iterar constant_pool_count vezes e ir lendo os bytes 
    // Os indices válidos são 1 até constant_pool_count - 1 
    // for(int cp_index = 1; cp_index < cf->constant_pool_count; cp_index++){

    //     // pegamos o cf->constant_pool que é um ponteiro pegamos o valor [cp_index] dele e pegamos com & o endereço daquele valor. 
    //     // Atenção -> Na função, precisamos de um ponteiro que aponte para uma estrutura cp_info, dessa maneira, passamos um endereço para um estrutura cp_info assim -> &cf->constant_pool[cp_index]
    //     // No caso do cp_index, passamos seu endereço para que possamos mudar quando o conteudo for do tipo double ou long.
    //     read_cp_info(fd, &cf->constant_pool[cp_index], &cp_index);

    // };

    // exibindo constant pool

    // // printar a tag
    // u1 tag = u1Read(fd);
    // printf("%d \n",tag);

    // printar o primeiro tipo do pool  
    // cp_info primeiro = cf->constant_pool[1];
    // printf("%d tag\n", primeiro.tag);
    // printf("%d \n", primeiro.constant_type_union.Utf8.length);
    // // for(int i = 0; i < primeiro.constant_type_union.Utf8.length; i++){
    // //     printf("%d  \n", primeiro.constant_type_union.Utf8.bytes[i]);
    // // }
    
    // printf("%d \n" ,cf->constant_pool[3].tag);
    // printf("%c \n",cf->constant_pool[cf->constant_pool[3].constant_type_union.String.string_index].constant_type_union.Utf8.bytes[0]);
    


    // exibir_cp_info(cf);


    // Lendo cp_info
    // Lendo acess_flags
    // Lendo this_class
    // Lendo super_class
    // Lendo interface_count
    // Lendo interfaces
    // Lendo fields_count
    // Lendo fields
    // Lendo methods_count
    // Lendo methods
    // Lendo atributes_count
    // Lendo atributes

    return 0;
}