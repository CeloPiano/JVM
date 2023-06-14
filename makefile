TARGET = exec
FLAGS = -std=c99 
COMMON = utf8.c
LEITORES = leitor.c
EXIBIDORES = exibidor.c

all:
	gcc $(FLAGS) $(LEITORES) $(EXIBIDORES) $(COMMON) main.c -o $(TARGET)

clean:
	rm -f $(TARGET)