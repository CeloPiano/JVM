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
    class_exibitor(cf);
    return 0;
}