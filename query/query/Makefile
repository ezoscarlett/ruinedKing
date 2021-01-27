CC=gcc
CFLAGS=-Wall -Werror
SRC=query.c

OBJ_FILES := $(patsubst %.c,  %.o, $(SRC) )
OBJS_D := $(patsubst %.c,%.d,$(SRC))

.PHONY : all clean

#$(info "objfiles ="$(OBJ_FILES))
all:query

%.o : %.c 
	$(CC) $(CFLAGS)  -MM -MT $@ -MF $(patsubst %.o, %.d, $@) $<
	$(CC) -c -o $@  $(CFLAGS) $<
#	$(CC) -MMD -MP $(CFLAGS) -c $< -o $@ $(patsubst %.o, %.d, $@)
query:$(OBJ_FILES)
	$(CC)  $(CFLAGS) -o query $(OBJ_FILES)
clean:
	rm -rf query
	rm -rf *.o *.d
-include  $(OBJS_D)
