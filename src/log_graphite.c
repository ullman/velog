/*
Copyright (C) 2020  Philip Freeman <elektron@halo.nu>
License: GPL Version 3
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "log_graphite.h"

#define MAX_PATH_SIZE 100
#define MAX_MSG_SIZE 130

static int sockfd = 0;
static struct sockaddr_in serv_addr;

int init_graphite(char *host, int port)
{
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("socket");
		return 1;
	}

	memset(&serv_addr, '\0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);

	if(inet_pton(AF_INET, host, &serv_addr.sin_addr) != 1) {
		perror("inet_pton");
		return 1;
	}

	if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
		perror("connect");
		return 1;
	}

	return 0;
}

void close_graphite()
{
	if (sockfd != -1) {
		close(sockfd);
		sockfd = -1;
	}
}

void log_graphite(char* path_in, float value, unsigned long ts)
{
	char path[MAX_PATH_SIZE];
	char message[MAX_MSG_SIZE];
	int n;

	snprintf(path, MAX_PATH_SIZE, "%s", path_in);

	snprintf(message, MAX_MSG_SIZE, "%s %.2f %lu\n", path, value, ts);

	n = write(sockfd, message, strlen(message));
	if (n < 0) {
		 perror("write");
		 exit(1);
	}
}
