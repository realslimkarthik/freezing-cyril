#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/types.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/in.h>
#include<pthread.h>

void serve(int sockfd, struct sockaddr_in this) {
	int connfd;
	char buff[1024], line[1024];
	while(1) {
		connfd = accept(sockfd, (struct sockaddr *)this, sizeof(this));
		read(connfd,(char *)&buff, sizeof(buff));
		close(connfd);
	}
}

void request(int sockfd, struct sockaddr_in other) {
	while(1) {
		printf("Enter the IP address to request file from: ");
		char buff[1024];
		scanf("%s", buff);
		inet_pton(AF_INET, addr, &other.sin_addr);
		connect(sock, (struct sockaddr *)other, sizeof(other));
		printf("Enter the file name: ");
		scanf("%s", buff);
	}
}

int main(int argc, char* argv[]) {
	int sock = socket(AF_inet, SOCK_STREAM, 0);
	if(sock == -1) {
		perror("Unable to create socket");
		exit(0);
	}

	pthread_t req, res;

	struct sockaddr_in this, other;

	this.sin_family = AF_INET;
	this.sin_addr.s_addr = INADDR_ANY;
	this.sin_port = htons(8000);

	other.sin_family = AF_INET;
	other.sin_port = htons(8000);
	
	bind(sock, (struct sockaddr *)this, sizeof(this));
	pthread_create(&req, 0, (void *)request, (void *)sock, (void *)other);
	pthread_create(&res, 0, (void *)serve, (void *)sock, (void *)this);

	return 0;
}
