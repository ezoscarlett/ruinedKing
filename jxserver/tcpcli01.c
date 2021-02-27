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

int is_begin_with(const char *str1,char *str2)
{
    if(str1 == NULL || str2 == NULL)
        return -1;
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    if((len1 < len2) ||  (len1 == 0 || len2 == 0))
        return -1;
    char *p = str2;
    int i = 0;
    while(*p != '\0')
    {
        if(*p != str1[i])
            return 0;
        p++;
        i++;
    }
    return 1;
}

int is_valid_get(char *command)
{
    if(is_begin_with(command, "get"))
    {
    	if(strtok(command, " ") != NULL)
    	{
    		if(strtok(command, " ") != NULL)
    		{
    			if(strtok(command, " ") != NULL)
    			{
    				return 1;
    			}
    		}
    	}
    }
    return 0;
}

int retrieve_file(int fd, char *local_saving_name)
{
	char recv_buf[1024];
	int recv_size;
    read(fd, &recv_size, 4);
    FILE *new_file_fp = NULL;
    new_file_fp = fopen(local_saving_name, "w");
    if(new_file_fp == NULL){
        perror("can't create file ");
        return 0;
    }
    while(recv_size)
    {
    	int read_size = recv_size;
    	if(recv_size > 1024)
    		read_size = 1024;
    	if(readn(fd, recv_buf, recv_size) != read_size)
    	{
    		break;
    		printf("Error while reading target file\n");
    	}
    	recv_size -= read_size;
    	int n = writen(fileno(new_file_fp), recv_buf, read_size);
        printf("write %d,%d bytes to file\n",read_size,n);
    }
    fclose(new_file_fp);
	return 0;
}

int retrieve_dir(int fd)
{
	return 0;
}

int retrieve_help(int fd)
{
	int msg_size;
	read(fd, &msg_size, 4);
	char* msg = malloc(sizeof(char) * msg_size);
	int n = readn(fd, msg, msg_size);
    printf("write %d,%d bytes to file\n",msg_size,n);
    return 0;
}

int main(int argc, char **argv)
{
	int sockfd, command_len;
	struct sockaddr_in servaddr;
	char command[1024];
	char *local_saving_name;
    unsigned char req_type, response_type;
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
    	printf("> ");
        int n_read = read(0, command, sizeof(command));
        if(n_read < 0)
        {
        	printf("Failed to capture input\n");
        	return -1;
        }
        command[n_read] = 0;
        command_len = strlen(command);
        if(strlen(command) == 1)
            continue;
        if(command[command_len-1] == '\n')
        	command[command_len-1] = 0;
        if(command[0] == 'q')
            break;
        printf("filename: %s\n", command);

        if (is_valid_get(command) == 1)
        {
        	req_type = 6;
        	local_saving_name = strtok(command, " ");
        	local_saving_name = strtok(command, " ");
        	local_saving_name = strtok(command, " ");
        }
        else if (strcmp(command, "ls") == 0)
        	req_type = 2;
        else if (strcmp(command, "help") == 0)
        	req_type = 7;
        else
        {
        	printf("Invalid command\n");
        	continue;
        }
        write(sockfd, &req_type, 1);
        command_len = strlen(command);
        write(sockfd, &command_len, 4);
        write(sockfd, &command, command_len);
        read(sockfd, &response_type, 1);

        switch((int)response_type){
        case 7:
        	retrieve_file(sockfd, local_saving_name);
        	break;
        case 3:
        	retrieve_dir(sockfd);
        	break;
        case 8:
        	retrieve_help(sockfd);
        	break;
        }
    }
    close(sockfd);
	//str_cli(stdin, sockfd);		/* do it all */
	return 0;
}
