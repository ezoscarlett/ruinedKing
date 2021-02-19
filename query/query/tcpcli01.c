#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <netdb.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
	int					sockfd;
	struct sockaddr_in	servaddr;
	char line[8];
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
    while(1){
        printf("Input the number you want to search: ");
        int n_read = read(0, line, sizeof(line));
        if(n_read < 0)
        {
        	printf("Input error");
        	return -1;
        }
        if(strlen(line)==0)
            continue;
        if(line[0] == 'q')
            break;
        int num = atoi(line);
        if(num == 0)
        	printf("Invalid Query Number");
        	//Start the loop again
        write(sockfd,line,8);
    }

    close(sockfd);
	//str_cli(stdin, sockfd);		/* do it all */

	return 0;
}
