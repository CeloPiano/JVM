#include "leitor.c"

// ferramenta de debug
#define printaU2(objeto) printf("%x \n", objeto);
#define printaU4(objeto) printf("%x \n", objeto);
#define printaU8(objeto) printf("%lx \n", objeto);



int main(void){

    // Lendo o arquivo .CLASS
    char path[] = "hello_world.class";
    FILE *fd = fopen(path, "rb");

    // Declarando o ponteiro do tipo ClassFile (struct) - Aqui temos que alocar um espaço na memoria do tamanho de classfile e fazer um casting
    Classfile *cf = (Classfile *) malloc(sizeof(Classfile));

    // Lendo o magic
    cf->magic = u4Read(fd);
    printaU4(cf->magic);

    // Lendo minor_version
    cf->minor_version = u2Read(fd);
    printf("%d \n",cf->minor_version);

    // Lendo major_version
    cf->major_version = u2Read(fd);
    printf("%d \n",cf->major_version);

    // Lendo constant_pool_count
    cf->constant_pool_count = u2Read(fd);
    printf("%d \n",cf->constant_pool_count);

    
    
    // ------------------------------------------------ //
    
    // LENDO O CONSTANT POOL
    
    // criando espaco na memoria para todas as constantes -> constant_pool_count - 1
    // ps: sempre criar uma copia do ponteiro para acessar as nossas constant pools
    cp_info *cp_pointer = (cp_info *) malloc((cf->constant_pool_count - 1) * (sizeof(cp_info)));

    //Iterar constant_pool_count vezes e ir lendo os bytes 

    // printar a tag
    u1 tag = u1Read(fd);
    printf("%d \n",tag);
    




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