#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
int
main(int argc, char **argv)
{
	int					listenfd, connfd;
	pid_t				childpid;
	socklen_t			clilen;
    char data[1024];
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
        int n = read(connfd,data,1024);
        if(n == 0)
            close(connfd);
        if(n < 0)
            close(connfd);
        data[n] = 0;
        printf("read %s from client \n",data);
//        str_echo(connfd);	/* process the request */
		close(connfd);			/* parent closes connected socket */
	}
}
