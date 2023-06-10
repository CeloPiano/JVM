#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exibidor.h"

char * accFlag_decoder(u2);
const char* bytecode_to_opcode_string(value_to_opcode);
int bytecode_group(u1);
void bytecode_print( u1*, int *, int, cp_info *);

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

char *class_decoder(cp_info *cp, u2 classIndex) {
    u2 UTF8index = cp[classIndex].constant_type_union.Class_info.name_index;
    char *className = Utf8_decoder(&cp[UTF8index]);
    return className;
}

float float_decoder (u4 bytes) {
    float value;
    memcpy(&value, &bytes, sizeof(float));
    return value;
}

long long int long_decoder (u8 highBytes, u8 lowBytes) {
    long long int value = (highBytes << 32) | lowBytes;
    return value;
}

double double_decoder (u8 high_bytes, u8 low_bytes) {
    u8 bytes = (high_bytes << 32) | low_bytes;
    double value;
    memcpy(&value, &bytes, sizeof(double));
    return value;
}

// ----------------------------- CONSTANTVALUE -------------------------------------

void constantValue_type_exibitor(cp_info *cp, ClassFile *cf) {
    switch (cp->tag)
    {
    case (CONSTANT_Long_info): {
        printf("<%lld>\n\n", long_decoder(cp->constant_type_union.Long.high_bytes, cp->constant_type_union.Long.low_bytes));
    }
        break;
    case (CONSTANT_Float_info): {
        printf("<%f>\n\n", float_decoder(cp->constant_type_union.Float.bytes));
    }
        break;
    case (CONSTANT_Double_info): {
        printf("<%lf>\n\n", double_decoder(cp->constant_type_union.Double.high_bytes, cp->constant_type_union.Double.low_bytes));
    }
        break;
    case (CONSTANT_Integer_info): {
        printf("<%d>\n\n", cp->constant_type_union.Integer.bytes);
    }
        break;
    case (CONSTANT_String_info): {
        u2 index = cp->constant_type_union.String.string_index;
        printf("<%s>\n\n", Utf8_decoder(&cf->constant_pool[index]));
    }
        break;
    }
}

void constantValue_exibitor(attribute_info *attribute, ClassFile *cf) {
    u2 constantValue_index = attribute->attribute_info_union.constantvalue_index;
    printf("\tSpecific info:\n");
    printf("\tConstant value index: cp_info #%d ", constantValue_index);
    constantValue_type_exibitor(&cf->constant_pool[constantValue_index], cf);
}


// ----------------------------- CODE -------------------------------------
void code_exibitor(attribute_info *attribute, ClassFile *cf){
    
    // MISC    
    printf("\n\tMISC: \n\n");
    printf("\tMaximum stack size: %d \n",attribute->attribute_info_union.code_attribute.max_stack);
    printf("\tMaximum local variables: %d \n",attribute->attribute_info_union.code_attribute.max_locals);
    printf("\tMaximum code length: %d \n\n",attribute->attribute_info_union.code_attribute.code_lenght);

    // code mnermonicos!
    
    // iterar para cada byte
    // for(int i = 0; i < attribute->attribute_info_union.code_attribute.code_lenght; i++){
        
    //     u1 bytecode = attribute->attribute_info_union.code_attribute.code[i];
    //     // printf("\t%d %s   ",i , bytecode_to_opcode_string(bytecode));
    //     // printf("HEXA %x \n", bytecode);
        
    //     // pegar o grupo
    //     int group = bytecode_group(bytecode);

    //     printf("esse é o grupo %d \n", group);
        
    //     // printar com base no grupo
    //     bytecode_print(attribute->attribute_info_union.code_attribute.code, &i, group, cf->constant_pool);

    // };
    
    printf("\n");

    attributes_exibitor(attribute->attribute_info_union.code_attribute.attributes, attribute->attribute_info_union.code_attribute.attribute_count, cf);

};



// -------------------------- EXCEPTIONS ---------------------- 

void exceptions_exibitor(attribute_info *attribute, ClassFile *cf) {
    u2 length = attribute->attribute_info_union.exceptions_attribute.number_of_exceptions;
    cp_info *cp = cf->constant_pool;
    printf("\tSpecific info:\n");

    for (int i = 0; i < length; i++) {
        u2 exception_index = attribute->attribute_info_union.exceptions_attribute.exception_index_table[i];
        printf("\tNúmero: %d - Exception: cp_info #%d <%s>\n", i, exception_index, class_decoder(cp, exception_index));
    }

    printf("\n");
}

// -------------------------- INNERCLASSES ---------------------- 

void innerClasses_exibitor(attribute_info *attribute, ClassFile *cf) {
    u2 length = attribute->attribute_info_union.innerClasses_attribute.number_of_classes;
    cp_info *cp = cf->constant_pool;
    printf("\tSpecific info:\n");
    
    for (int i = 0; i < length; i++) {
        inner_classes *inner_class = &attribute->attribute_info_union.innerClasses_attribute.inner_classes[i];
        printf("\tNúmero: %d - Inner Class: cp_info #%d <%s> - Outer Class: cp_info #%d <%s> - Inner Name: cp_info #%d <%s> - Access Flags: 0x%x [%s]\n", i, inner_class->inner_class_info_index, class_decoder(cp, inner_class->inner_class_info_index), inner_class->outer_class_info_index, class_decoder(cp, inner_class->outer_class_info_index), inner_class->inner_name_index, Utf8_decoder(&cp[inner_class->inner_name_index]), inner_class->inner_class_access_flags, accFlag_decoder(inner_class->inner_class_access_flags));
    }

    printf("\n");
}

// -------------------------- LINENUMBERTABLE ---------------------- 

void lineNumberTable_exibitor(attribute_info *attribute, ClassFile *cf) {
    u2 length = attribute->attribute_info_union.lineNumberTable_attribute.line_number_table_length;
    printf("\tSpecific info:\n");

    for (int i = 0; i < length; i++) {
        line_number_table *line_number_table = &attribute->attribute_info_union.lineNumberTable_attribute.line_number_table[i];
        printf("\tNúmero: %d - Start PC: %d - Line Number: %d\n", i, line_number_table->start_pc, line_number_table->line_number);
    }

    printf("\n");
}
// -------------------------- LOCALVARIABLETABLE ---------------------- 

void localVariableTable_exibitor(attribute_info *attribute, ClassFile *cf) {
    u2 length = attribute->attribute_info_union.localVariableTable_attribute.local_variable_table_length;
    cp_info *cp = cf->constant_pool;
    printf("\tSpecific info:\n");
    
    for (int i = 0; i < length; i++) {
        local_variable_table *local_variable_table = &attribute->attribute_info_union.localVariableTable_attribute.local_variable_table[i];
        printf("\tNúmero: %d - Start PC: %d - Length: %d - Name Index: cp_info #%d <%s> - Descriptor Index: cp_info #%d <%s> - Index: %d\n", i, local_variable_table->start_pc, local_variable_table->length, local_variable_table->name_index, Utf8_decoder(&cp[local_variable_table->name_index]), local_variable_table->descriptor_index, Utf8_decoder(&cp[local_variable_table->descriptor_index]), local_variable_table->index);
        if (!strcmp(Utf8_decoder(&cp[local_variable_table->descriptor_index]), "J") || !strcmp(Utf8_decoder(&cp[local_variable_table->descriptor_index]), "D")) {
            i++;
        }
    }

    printf("\n");
}


// ----------------------------- ATTRIBUTES -------------------------------------

void attributes_exibitor(attribute_info *attributes, u2 attributes_count, ClassFile * cf){
    for (int i = 0; i < attributes_count; i++) {
        attribute_info *attr = &attributes[i];
        u2 length = attr->attribute_lenght;
        u2 name_index = attr->attribute_name_index;
        printf("\tAttribute[%d]\n", i);
        printf("\tAttribute name index: cp_info #%d <%s> \n", name_index, Utf8_decoder(&cf->constant_pool[name_index]));
        printf("\tAttribute length: %d\n", length);

        char * name = Utf8_decoder(&cf->constant_pool[name_index]);
        // usar o code length aqui não faz sentido porque não é pra printar um code para cada length.
        // entramos na função e com base no bytecode vamos ter que tomar nossas decisões do que fazer
        if (!strcmp(name, "ConstantValue"))
        {
            constantValue_exibitor(attr, cf);
        }
        else if (!strcmp(name, "Code"))
        {
            code_exibitor(attr, cf);
        }
        else if (!strcmp(name, "Exceptions"))
        {
            exceptions_exibitor(attr, cf);
        }
        else if (!strcmp(name, "InnerClasses"))
        {
            innerClasses_exibitor(attr, cf);
        }
        else if (!strcmp(name, "LineNumberTable"))
        {
            lineNumberTable_exibitor(attr, cf);
        }
        else if (!strcmp(name, "LocalVariableTable"))
        {
            localVariableTable_exibitor(attr, cf);
        } else {
            printf("\n");
        }
    }
};

// ----------------------------- FIELDS -------------------------------------

void fields_exibitor(ClassFile *cf) {
    u2 fields_count = cf->fields_count;
    printf("Início Fields\n\n");
    for (int i = 0; i < fields_count; i++) {
        field_info *field = &cf->fields[i];
        cp_info *cp = cf->constant_pool;
        printf("Field[%d]\n", i);
        printf("Name: cp_info #%d %s\n", field->name_index, Utf8_decoder(&cp[field->name_index]));
        printf("Descriptor: cp_info #%d <%s>\n", field->descriptor_index, Utf8_decoder(&cp[field->descriptor_index]));
        printf("Access flags: 0x%x [%s]\n\n", field->acess_flags, accFlag_decoder(field->acess_flags));
        attributes_exibitor(field->attributes, field->attributes_count, cf);
    }
    printf("Fim Fields\n\n");
}

// ----------------------------- METHODS -------------------------------------

void methods_exibitor(ClassFile *cf){

    u2 methods_count = cf->methods_count;

    printf("Início Methods:\n\n");

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
        printf("Acess Flags: 0x%x [%s] \n\n", method->acess_flags, accFlag_decoder(method->acess_flags));

        // attributes
        attributes_exibitor(method->attributes, method->attributes_count, cf);
    };

    printf("Fim Methods\n\n");

};


char * accFlag_decoder(u2 accFlag) {
    char *flagName = (char *) malloc(64 * sizeof(char));
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

    if (strlen(flagName) > 0) {
        flagName[strlen(flagName) - 1] = '\0';
    }

    return flagName;
}

void interfaces_exibitor (ClassFile *cf) {
    u2 interfaces_count = cf->interfaces_count;
    printf("Início Interfaces: \n \n");
    for (int i = 0; i < interfaces_count; i++) {
        u2 interface = cf->interfaces[i];
        printf("Interface[%d]\n", i);
        printf("Class name: cp_info #%d <%s> \n\n", interface, class_decoder(cf->constant_pool, interface));
    }
    printf("Fim Interfaces \n\n");
}

// exibir o cp_info
// iremos precisar de um ponteiro para o classfile 
void cp_info_exibitor(ClassFile *classFile){
    
    // pegar o contador de constant pool
    int cp_info_count = classFile->constant_pool_count;

    // pegar o endereço do constant pool salvo e colocar no ponteiro constantPool.
    cp_info *constantPool = classFile->constant_pool;
    
    printf("\nInício Constant Pool \n \n");

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

            case(0) :
                {
                printf("(large numeric continued)\n\n");
                }
                break;
            case(CONSTANT_Class_info):
                { 
                u2 class_name_index = constantPool[i].constant_type_union.Class_info.name_index;
                // aqui pegamos o index para acessar a constante utf_8 para a nossa função
                printf("Class name: cp_info #%d <%s>\n\n", class_name_index, Utf8_decoder(&constantPool[class_name_index]));
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
                printf("%s>\n\n", Utf8_decoder(&constantPool[constantPool[fieldref_name_and_type_index].constant_type_union.NameAndType.descriptor_index]));
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
                printf("%s> \n\n", Utf8_decoder(&constantPool[constantPool[methodref_name_and_type_index].constant_type_union.NameAndType.descriptor_index]));
                
                }
                break;
                

            case(CONSTANT_InterfaceMethodref_info): 
                {
                u2 interface_index = constantPool[i].constant_type_union.InterfaceMethodref_info.class_index;
                u2 name_and_type_index = constantPool[i].constant_type_union.InterfaceMethodref_info.name_and_type_index;

                printf("Interface name: cp_info #%d <%s>\n", interface_index, Utf8_decoder(&constantPool[interface_index]));
                printf("Name and type: cp_info #%d <%s>\n\n", name_and_type_index, Utf8_decoder(&constantPool[name_and_type_index]));
                }
                break;
                
            case(CONSTANT_String_info):
            {

                u1 string_info_index = constantPool[i].constant_type_union.String.string_index;
                printf("String: cp_info #%d <%s> \n\n", string_info_index ,Utf8_decoder(&constantPool[string_info_index]));

            }
                break;

            case(CONSTANT_Integer_info): 
            {
                u4 bytes = constantPool[i].constant_type_union.Integer.bytes;
                printf("Integer value: %d\n\n", bytes);
            }
                break;
            
            case(CONSTANT_Float_info):
            {
                u4 bytes = constantPool[i].constant_type_union.Float.bytes;
                printf("Float value: %f\n\n", float_decoder(bytes));
            }   
                break;

            case(CONSTANT_Long_info): 
            {
                u8 high_bytes = constantPool[i].constant_type_union.Long.high_bytes;
                u8 low_bytes = constantPool[i].constant_type_union.Long.low_bytes;
                printf("Long value: %lld\n\n", long_decoder(high_bytes, low_bytes));
            }
                break;

            case(CONSTANT_Double_info): 
            {
                u8 high_bytes = constantPool[i].constant_type_union.Double.high_bytes;
                u8 low_bytes = constantPool[i].constant_type_union.Double.low_bytes;
                printf("Double value: %lf\n\n", double_decoder(high_bytes, low_bytes));
            }
                break;
            
            case(CONSTANT_NameAndType_info):{

                u2 name_index = constantPool[i].constant_type_union.NameAndType.name_index;
                u2 descriptor_index = constantPool[i].constant_type_union.NameAndType.descriptor_index;

                printf("Name: cp_info #%d %s \n", name_index, Utf8_decoder(&constantPool[name_index]));
                printf("Descriptor: cp_info #%d %s\n\n", descriptor_index, Utf8_decoder(&constantPool[descriptor_index]));
            }
                break;
            
            case(CONSTANT_Utf8_info):
            {   
                // lenght of byte array?
                printf("lenght of Byte array: %d \n", constantPool[i].constant_type_union.Utf8.length);
                // lenght of string?
                printf("lenght of string: %d \n", constantPool[i].constant_type_union.Utf8.length);
                // String
                printf("String: %s \n\n", Utf8_decoder(&constantPool[i]));
            }   
                break;

            default:
                printf("\n");
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
    printf("Access flags: 0x%x [%s] \n", cf->access_flags, accFlag_decoder(cf->access_flags));

    // Exibição this class 
    printf("This class: #%d <%s> \n", cf->this_class, class_decoder(cf->constant_pool, cf->this_class));

    // Exibição super class
    printf("Super class: #%d <%s> \n", cf->super_class, class_decoder(cf->constant_pool, cf->super_class));

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
    interfaces_exibitor(cf);

    // Exibição fields
    fields_exibitor(cf);

    // Exibição methods
    methods_exibitor(cf);
    
    // Exibição attributes
    printf("Início attributes\n\n");
    attributes_exibitor(cf->attributes, cf->attributes_count, cf);
    printf("\nFim attributes\n\n");

}


// -------------------------- CODE NAME ---------------------- 
// função que pega o nome baseado no opcode.
const char* bytecode_to_opcode_string(value_to_opcode op)
{
    switch (op)
    {

    case    nop:                      return "nop";       
    case    aconst_null:              return "aconst_null";               
    case    iconst_m1:                return "iconst_m1";             
    case    iconst_0:                 return "iconst_0";            

    case    iconst_1:                 return "iconst_1";            
    case    iconst_2:                 return "iconst_2";            
    case    iconst_3:                 return "iconst_3";            
    case    iconst_4:                 return "iconst_4";            

    case    iconst_5:                 return "iconst_5";            
    case    lconst_0:                 return "lconst_0";            
    case    lconst_1:                 return "lconst_1";            
    case    fconst_0:                 return "fconst_0";            

    case    fconst_1:                 return "fconst_1";            
    case    fconst_2:                 return "fconst_2";            
    case    dconst_0:                 return "dconst_0";            
    case    dconst_1:                 return "dconst_1";            

    case    bipush:                   return "bipush";          
    case    sipush:                   return "sipush";          
    case    ldc:                      return "ldc";       
    case    ldc_w:                    return "ldc_w";         
    case    ldc2_w:                   return "ldc2_w";          

    case    iload:                    return "iload";         
    case    lload:                    return "lload";         
    case    fload:                    return "fload";         
    case    dload:                    return "dload";         
    case    aload:                    return "aload";         

    case    iload_0:                  return "iload_0";           
    case    iload_1:                  return "iload_1";           
    case    iload_2:                  return "iload_2";           
    case    iload_3:                  return "iload_3";           
    case    lload_0:                  return "lload_0";           

    case    lload_1:                  return "lload_1";           
    case    lload_2:                  return "lload_2";           
    case    lload_3:                  return "lload_3";           
    case    fload_0:                  return "fload_0";           
    case    fload_1:                  return "fload_1";           

    case    fload_2:                  return "fload_2";           
    case    fload_3:                  return "fload_3";           
    case    dload_0:                  return "dload_0";           
    case    dload_1:                  return "dload_1";           
    case    dload_2:                  return "dload_2";           

    case    dload_3:                  return "dload_3";           
    case    aload_0:                  return "aload_0";           
    case    aload_1:                  return "aload_1";           
    case    aload_2:                  return "aload_2";           
    case    aload_3:                  return "aload_3";           

    case    iaload:                   return "iaload";          
    case    laload:                   return "laload";          
    case    faload:                   return "faload";          
    case    daload:                   return "daload";          
    case    aaload:                   return "aaload";          
    case    baload:                   return "baload";          

    case    caload:                   return "caload";          
    case    saload:                   return "saload";          
    case    istore:                   return "istore";          
    case    lstore:                   return "lstore";          
    case    fstore:                   return "fstore";          
    case    dstore:                   return "dstore";          

    case    astore:                   return "astore";          
    case    istore_0:                 return "istore_0";            
    case    istore_1:                 return "istore_1";            
    case    istore_2:                 return "istore_2";            
    case    istore_3:                 return "istore_3";            

    case    lstore_0:                 return "lstore_0";            
    case    lstore_1:                 return "lstore_1";            
    case    lstore_2:                 return "lstore_2";            
    case    lstore_3:                 return "lstore_3";            
    case    fstore_0:                 return "fstore_0";            

    case    fstore_1:                 return "fstore_1";            
    case    fstore_2:                 return "fstore_2";            
    case    fstore_3:                 return "fstore_3";            
    case    dstore_0:                 return "dstore_0";            
    case    dstore_1:                 return "dstore_1";            

    case    dstore_2:                 return "dstore_2";            
    case    dstore_3:                 return "dstore_3";            
    case    astore_0:                 return "astore_0";            
    case    astore_1:                 return "astore_1";            
    case    astore_2:                 return "astore_2";            

    case    astore_3:                 return "astore_3";            
    case    iastore:                  return "iastore";           
    case    lastore:                  return "lastore";           
    case    fastore:                  return "fastore";           
    case    dastore:                  return "dastore";           

    case    aastore:                  return "aastore";           
    case    bastore:                  return "bastore";           
    case    castore:                  return "castore";           
    case    sastore:                  return "sastore";           
    case    pop:                      return "pop";       
    case    pop2:                     return "pop2";        

    case    dup:                      return "dup";       
    case    dup_x1:                   return "dup_x1";          
    case    dup_x2:                   return "dup_x2";          
    case    dup2:                     return "dup2";        
    case    dup2_x1:                  return "dup2_x1";           
    case    dup2_x2:                  return "dup2_x2";           
    case    swap:                     return "swap";        

    case    iadd:                     return "iadd";        
    case    ladd:                     return "ladd";        
    case    fadd:                     return "fadd";        
    case    dadd:                     return "dadd";        
    case    isub:                     return "isub";        
    case    lsub:                     return "lsub";        
    case    fsub:                     return "fsub";        
    case    dsub:                     return "dsub";        

    case    imul:                     return "imul";        
    case    lmul:                     return "lmul";        
    case    fmul:                     return "fmul";        
    case    dmul:                     return "dmul";        
    case    idiv:                     return "idiv";        
    case    inst_ldiv:                return "inst_ldiv";             
    case    fdiv:                     return "fdiv";        
    case    ddiv:                     return "ddiv";        

    case    irem:                     return "irem";        
    case    lrem:                     return "lrem";        
    case    frem:                     return "frem";        
    case    inst_drem:                return "inst_drem";             
    case    ineg:                     return "ineg";        
    case    lneg:                     return "lneg";        
    case    fneg:                     return "fneg";        
    case    dneg:                     return "dneg";        

    case    ishl:                     return "ishl";        
    case    lshl:                     return "lshl";        
    case    ishr:                     return "ishr";        
    case    lshr:                     return "lshr";        
    case    iushr:                    return "iushr";         
    case    lushr:                    return "lushr";         
    case    iand:                     return "iand";        
    case    land:                     return "land";        

    case    ior:                      return "ior";       
    case    lor:                      return "lor";       
    case    ixor:                     return "ixor";        
    case    lxor:                     return "lxor";        
    case    iinc:                     return "iinc";        
    case    i2l:                      return "i2l";       
    case    i2f:                      return "i2f";       
    case    i2d:                      return "i2d";       
    case    l2i:                      return "l2i";       

    case    l2f:                      return "l2f";       
    case    l2d:                      return "l2d";       
    case    f2i:                      return "f2i";       
    case    f2l:                      return "f2l";       
    case    f2d:                      return "f2d";       
    case    d2i:                      return "d2i";       
    case    d2l:                      return "d2l";       
    case    d2f:                      return "d2f";       
    case    i2b:                      return "i2b";       
    case    i2c:                      return "i2c";       
    case    i2s:                      return "i2s";       
    case    lcmp:                     return "lcmp";        
    case    fcmpl:                    return "fcmpl";         
    case    fcmpg:                    return "fcmpg";         
    case    dcmpl:                    return "dcmpl";         
    case    dcmpg:                    return "dcmpg";         
    case    ifeq:                     return "ifeq";        

    case    ifne:                     return "ifne";        
    case    iflt:                     return "iflt";        
    case    ifge:                     return "ifge";        
    case    ifgt:                     return "ifgt";        
    case    ifle:                     return "ifle";        
    case    if_icmpeq:                return "if_icmpeq";             
    case    if_icmpne:                return "if_icmpne";             

    case    if_icmplt:                return "if_icmplt";             
    case    if_icmpge:                return "if_icmpge";             
    case    if_icmpgt:                return "if_icmpgt";             
    case    if_icmple:                return "if_icmple";             
    case    if_acmpeq:                return "if_acmpeq";             

    case    if_acmpne:                return "if_acmpne";             
    case    inst_goto:                return "inst_goto";             
    case    jsr:                      return "jsr";       
    case    ret:                      return "ret";       
    case    tableswitch:              return "tableswitch";               

    case    lookupswitch:             return "lookupswitch";                
    case    ireturn:                  return "ireturn";           
    case    lreturn:                  return "lreturn";           
    case    freturn:                  return "freturn";           
    case    dreturn:                  return "dreturn";           

    case    areturn:                  return "areturn";           
    case    inst_return:              return "inst_return";               
    case    getstatic:                return "getstatic";             
    case    putstatic:                return "putstatic";             
    case    getfield:                 return "getfield";            

    case    putfield:                 return "putfield";            
    case    invokevirtual:            return "invokevirtual";                 
    case    invokespecial:            return "invokespecial";                 
    case    invokestatic:             return "invokestatic";                

    case    invokeinterface:          return "invokeinterface";               
    case    invokedynamic:            return "invokedynamic";                   
    case    new:                      return "new";            
    case    newarray:                 return "newarray";            
    case    anewarray:                return "anewarray";             

    case    arraylength:              return "arraylength";               
    case    athrow:                   return "athrow";          
    case    checkcast:                return "checkcast";             
    case    instanceof:               return "instanceof";

    case    monitorenter:             return "monitorenter";                
    case    monitorexit:              return "monitorexit";               
    case    wide:                     return "wide";        
    case    multianewarray:           return "multianewarray";                  
    case    ifnull:                   return "ifnull";          

    case    ifnonnull:                return "ifnonnull";             
    case    goto_w:                   return "goto_w";          
    case    jsr_w:                    return "jsr_w";         
        }

    return "Unknown op";
}

// -------------------------- CODE GROUP ---------------------- 
int bytecode_group(u1 bytecode){


    switch(bytecode){

        // começando pelas de index number
        case aload:
        case astore:
        case dload:
        case dstore:
        case fload:
        case fstore:
        case iload:
        case istore:
        case lload:
        case lstore:
        case ret: return 1;

        // index pool
        case ldc: return 11;

        default:
            return 0;
    }


};


// -------------------------- GROUP PRINT ---------------------- 
// baseado nos grupos iremos printar os codes
void bytecode_print( u1* code_array, int *index, int bytecode_group, cp_info *constant_pool){
    
    switch(bytecode_group){

        // 1 byte:
        
        // index number group (1):
        case(1):
            // printando bytecode
            printf("%s ", bytecode_to_opcode_string(code_array[*index]));
            
            ++(*index);
            
            // printando o número
            printf("%d \n", code_array[*index]);


        // index cp_info group (1.1):
        case(11):
            // printando
            printf("%s ", bytecode_to_opcode_string(code_array[*index]));

            ++(*index);

            int pool_index = *index;
            // printando o cp_info
            // aqui o pool_index aponta -> CONSTANT_String_info
            printf("#%d %s\n", pool_index, Utf8_decoder(&constant_pool[constant_pool[pool_index].constant_type_union.String.string_index]));


        // noarguments group 
        case(0):
            printf("%s \n", bytecode_to_opcode_string(code_array[*index]));

    };


};

