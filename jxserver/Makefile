CC=gcc
#CFLAGS=-Wall -Werror -Wno-error=unused-variable -g
CLIENT_SRC=tcpcli01.c
SERVER_SRC=tcpserv01.c

CLIENT_OBJ_FILES := $(patsubst %.c,  %.o, $(CLIENT_SRC) )
SERVER_OBJ_FILES := $(patsubst %.c,  %.o, $(SERVER_SRC) )
CLIENT_OBJS_D := $(patsubst %.c,%.d,$(CLIENT_SRC))
SERVER_OBJS_D := $(patsubst %.c,%.d,$(SERVER_SRC))

.PHONY : all clean

#$(info "objfiles ="$(OBJ_FILES))
all:client server

%.o : %.c 
	$(CC) $(CFLAGS)  -MM -MT $@ -MF $(patsubst %.o, %.d, $@) $<
	$(CC) -c -o $@  $(CFLAGS) $<
#	$(CC) -MMD -MP $(CFLAGS) -c $< -o $@ $(patsubst %.o, %.d, $@)
client:$(CLIENT_OBJ_FILES)
	$(CC)  $(CFLAGS) -o client $(CLIENT_OBJ_FILES)
server:$(SERVER_OBJ_FILES)
	$(CC)  $(CFLAGS) -o server $(SERVER_OBJ_FILES)
clean:
	rm -rf client server
	rm -rf *.o *.d
-include  $(CLIENT_OBJS_D)
-include  $(SERVER_OBJS_D)
