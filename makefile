OBJ := $(patsubst %.c,%.o, $(wildcard *.c))

./a.out : $(OBJ)
	gcc $(OBJ)

clean :
	rm *.o