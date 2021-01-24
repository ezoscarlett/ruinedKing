CC=gcc
CFLAGS=-Wall -Werror
SRC=main.c \
	helloworld.c

OBJ_FILES := $(patsubst %.c,  %.o, $(SRC) )
OBJS_D := $(patsubst %.c,%.d,$(SRC))

-include  $(OBJS_D)
.PHONY : all clean

#$(info "objfiles ="$(OBJ_FILES))
all:helloworld

%.o : %.c 
	$(CC) $(CFLAGS)  -MM -MT $@ -MF $(patsubst %.o, %.d, $@) $<
	$(CC) -c -o $@  $(CFLAGS) $<
#	$(CC) -MMD -MP $(CFLAGS) -c $< -o $@ $(patsubst %.o, %.d, $@)
helloworld:$(OBJ_FILES)
	$(CC)  $(CFLAGS) -o helloworld $(OBJ_FILES)
clean:
	rm -rf helloworld
	rm -rf *.o *.d
