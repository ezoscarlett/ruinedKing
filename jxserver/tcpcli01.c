#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <netdb.h>
#include <stdlib.h>
#include <stddef.h>
#include <arpa/inet.h>
#include "readn.h"
#include "writen.h"

int main(int argc, char **argv)
{
	int sockfd;
	struct sockaddr_in servaddr;
	char file_name[1024];
	char recv_buf[1024];
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

	int ret = connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	if(ret < 0)
	{
		perror("Binding failed:");
	}
    while(1){
    	printf("Input File Name: \n");
        int n_read = read(0, file_name, sizeof(file_name));
        if(n_read < 0)
        {
        	printf("Failed to capture input\n");
        	return -1;
        }
        file_name[n_read] = 0;
        name_len = strlen(file_name);
        if(strlen(file_name) == 1)
            continue;
        if(file_name[name_len-1] == '\n')
        	file_name[name_len-1] = 0;
        if(file_name[0] == 'q')
            break;
        printf("filename: %s\n", file_name);

        unsigned char type = 1;
        write(sockfd, &type, 1);
        name_len = strlen(file_name);
        write(sockfd, &name_len, 4);
        write(sockfd, &file_name, name_len);
        int recv_size;
        read(sockfd, &type, 1);
        read(sockfd, &recv_size, 4);
        FILE *new_file_fp = NULL;
        new_file_fp = fopen("report_recv.txt", O_CREAT);
        if(new_file_fp == NULL){
            perror("can't create file ");
            return 0;
        }
        while(recv_size)
        {
        	int read_size = recv_size;
        	if(recv_size > 1024)
        		read_size = 1024;
        	if(readn(sockfd, recv_buf, recv_size) != read_size)
        	{
        		break;
        		printf("Error while reading target file\n");
        	}
        	recv_size -= read_size;
        	int n = writen(fileno(new_file_fp), recv_buf, read_size);
            printf("write %d,%d bytes to file\n",read_size,n);
        }
        fclose(new_file_fp);
    }
    close(sockfd);
	//str_cli(stdin, sockfd);		/* do it all */
	return 0;
}
