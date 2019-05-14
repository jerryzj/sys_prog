CC = clang
CFLAG =-D_GNU_SOURCE -shared -ldl -fPIC
SRC = malloc_count.c 
OBJ = libmcount.so 

all:
	$(CC) $(CFLAG) -o $(OBJ) $(SRC)
test:
	LD_PRELOAD=$(PWD)/$(OBJ) ls
clean:
	rm $(OBJ)
