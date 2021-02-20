#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <netdb.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
	int sockfd;
	struct sockaddr_in servaddr;
	char file_name[1024];
	int name_len;
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
    	printf("Input File Name: \n");
        int n_read = read(0, file_name, sizeof(file_name));
        if(n_read < 0)
        {
        	printf("Failed to capture input\n");
        	return -1;
        }
        if(strlen(file_name)==0)
            continue;
        if(file_name[0] == 'q')
            break;

        unsigned char type = 1;
        write(sockfd, &type, 1);
        name_len = strlen(file_name);
        write(sockfd, &name_len, 4);
        write(sockfd, &file_name, name_len);
    }
    close(sockfd);
	//str_cli(stdin, sockfd);		/* do it all */
	return 0;
}
