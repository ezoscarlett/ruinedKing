#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <stdlib.h>
#include <arpa/inet.h>
int main(int argc, char **argv)
{
	int					sockfd;
	struct sockaddr_in	servaddr;
	if (argc != 3){
		printf("usage: tcpcli <IPaddress> port");
        return 0;
    }
    unsigned short serv_port = atoi(argv[2]);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(serv_port);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    
    write(sockfd,"hello",5);
    close(sockfd);
	//str_cli(stdin, sockfd);		/* do it all */

	return 0;
}
