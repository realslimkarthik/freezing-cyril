#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>

int main(int argc, char* argv[]) {
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	struct hostent *hp;
	char line[100];
	struct sockaddr_in client, server;
	server.sin_family = AF_INET;
	server.sin_port = htons(8000);
	server.sin_addr.s_addr = INADDR_ANY;
	bind(sock, (struct sockaddr *)&server, sizeof(struct sockaddr));
	listen(sock, 0);
	printf("listening\n");
	int len = sizeof(struct sockaddr);
	while(1) {
	int conn = accept(sock, (struct sockaddr *)&client, &len);
	printf("Connection accepted\n");
	printf("Request received from: ");
	hp = gethostbyaddr((char*)&client, sizeof(client), AF_INET);
	printf("%s\n", hp->h_name);
	int size;
	read(conn, (char*)&size, sizeof(int));
	read(conn, (char*)&line, (size)*sizeof(char));
	line[size]='\0';
	printf("%s\n", line);
	FILE *f = fopen(line, "r");
	memset(line,0,100*sizeof(char));
	while(fgets(line, 90, f)) {
		write(conn, line, 100*sizeof(char));
		memset(line,0,100*sizeof(char));
	}
	
	fclose(f);
	close(conn);
	}
	close(sock);
	return 0;
}
