#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <netdb.h>
#include <stddef.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "readn.h"
#include "writen.h"

int process(void* fd)
{
	return 0;
}

int main(int argc, char **argv)
{
	int	listenfd, connfd;
	pid_t childpid;
	socklen_t clilen;
	unsigned char type;
	int name_len;
	int target_file;
	int target_size;
    char file_name[1024];
    char target_buf[1024];
    struct stat buf;
	struct sockaddr_in	cliaddr, servaddr;
	if (argc != 2){
		printf("usage: tcpsrv port");
        return 0;
    }
    
    unsigned short serv_port = atoi(argv[1]);
	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_port        = htons(serv_port);

	bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	listen(listenfd, 5);

	for ( ; ; ) {
		clilen = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
        printf("accept a connect from %s\n",inet_ntoa(cliaddr.sin_addr));
        int n = read(connfd, &type, 1);
        if(n == 0)
            close(connfd);
        if(n < 0)
            close(connfd);

        n = read(connfd, &name_len, 4);
        if(n == 0)
            close(connfd);
        if(n < 0)
            close(connfd);

        n = read(connfd,file_name,name_len);
        if(n == 0)
            close(connfd);
        if(n < 0)
            close(connfd);
        file_name[n] = 0;

        printf("File name: %s\n",file_name);
        printf("File name length: %d\n", name_len);
        target_file = open(file_name, O_RDONLY);
        fstat(target_file, &buf);
        target_size = buf.st_size;
        unsigned char type = 7;
        write(connfd, &type, 1);
        write(connfd, &target_size, 4);
        while(target_size)
        {
        	int read_size = target_size;
        	if(target_size > 1024)
        		read_size = 1024;
        	if(readn(target_file, target_buf, read_size) != read_size)
        	{
        		break;
        		printf("Error while reading target file\n");
        	}
        	target_size -= read_size;
        	writen(connfd, target_buf, read_size);
        }


//        str_echo(connfd);	/* process the request */
        //TODO: Pack as a single 'process' function
	}
}
