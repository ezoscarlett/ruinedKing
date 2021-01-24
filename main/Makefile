SRC=main.c \
	helloworld.c

OBJ_FILES := $(patsubst %.c,  %.o, $(SRC) )

#$(info "objfiles ="$(OBJ_FILES))
all:helloworld

%.o : %.c
	gcc -c $< -o $@ $(CFLAGS)
helloworld:$(OBJ_FILES)
	$(CC) -o helloworld $(OBJ_FILES)  $(CFLAGS)
clean:
	rm -rf helloworld
	rm -rf *.o
