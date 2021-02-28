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
#include <dirent.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <pthread.h>
#include "readn.h"
#include "writen.h"

int transfer_file(int fd, char *file_name)
{
    int target_file;
    int target_size;
    char target_buf[1024];
    struct stat buf;
	target_file = open(file_name, O_RDONLY);
	fstat(target_file, &buf);
	target_size = buf.st_size;
	unsigned char response_req_type = 7;
	write(fd, &response_req_type, 1);
	write(fd, &target_size, 4);
	while (target_size) {
		int read_size = target_size;
		if (target_size > 1024)
			read_size = 1024;
		if (readn(target_file, target_buf, read_size) != read_size) {
			printf("Error while reading target file\n");
			break;
		}
		target_size -= read_size;
		int n = writen(fd, target_buf, read_size);
		printf("write %d,%d bytes to fd\n", read_size, n);
	}
	return 0;
}

int list_dir(int fd)
{
	int dir_size = 0;
	DIR *dp;
	struct dirent *dirp;
	char *dirname = ".";
	//char *dir_ret;
	unsigned char response_req_type = 3;
	write(fd, &response_req_type, 1);
	if((dp = opendir(dirname)) == NULL)
	{
		printf("Failed to read directory\n");
		return -1;
	}
	while((dirp = readdir(dp)) != NULL)
	{
		dirp = readdir(dp);
		printf("d_name : %s\n", dirp->d_name);
		dir_size += 1;
	}
	closedir(dp);

	return 0;
}

void help_msg(int fd)
{
	unsigned char response = 8;
	char* help_msg = "Enter \"ls\" to display all server directories\n"
			"Enter \"get target_name local_saving_name\" to retrieve file, example: get a.txt b.txt\n"
			"Enter \"q\" to quit the program\n";
	int msg_size = strlen(help_msg);
	write(fd, &response, 1);
	write(fd, &msg_size, 4);
	int n = writen(fd, help_msg, msg_size);
	printf("write %d,%d bytes to fd\n", msg_size, n);
}

void* process(void *arg)
{
    int fd = *((int *)arg);
    unsigned char req_type;
    int command_len;
    char command[1024];
    char *file_name;

	while(1) {
		int n = read(fd, &req_type, 1);
		//
		if (n == 0 || n < 0)
			break;

		n = read(fd, &command_len, 4);
		if (n == 0 || n < 0)
			break;

		n = read(fd, command, command_len);
		if (n == 0 || n < 0)
			break;
		command[n] = 0;
		switch(req_type)
		{
		case 6:
			file_name = strtok(command, " ");
			file_name = strtok(NULL, " ");
			transfer_file(fd, file_name);
			break;
		case 2:
			list_dir(fd);
			break;
		case 7:
			help_msg(fd);
			break;
		}
	}
    printf("connect lost\n");
    close(fd);
    return NULL;
}

int main(int argc, char **argv) {
	int listenfd, connfd;
	socklen_t clilen, err;
	;
	struct sockaddr_in cliaddr, servaddr;
	pthread_t ntid;
	//void *process_ret;
	if (argc != 2) {
		printf("usage: tcpsrv port");
		return 0;
	}

	unsigned short serv_port = atoi(argv[1]);
	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(serv_port);

	int bindnum = bind(listenfd, (struct sockaddr*) &servaddr,
			sizeof(servaddr));
	if (bindnum < 0) {
		printf("Binding failed\n");
		return -1;
	}
	listen(listenfd, 5);

	for (;;) {
		clilen = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr*) &cliaddr, &clilen);
		printf("accept a connect from %s\n", inet_ntoa(cliaddr.sin_addr));
		err = pthread_create(&ntid, NULL, process, &connfd);
		if(err != 0)
			perror("Creating thread failed");
#if 0
		pthread_join(ntid, &process_ret);
		if (*((int *)process_ret) < 0)
			perror("Server processing error, terminating");
		close(connfd);
		break;

#endif
	}
}
