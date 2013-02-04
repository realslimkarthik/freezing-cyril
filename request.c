#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<netinet/in.h>
#include<string.h>

int main(int argc, char* argv[]) {
	if(argc != 3) {
		printf("usage: ./<outfile name> <shared file> <destination ip address>\n");
	return 0;
	}
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(8000);
	inet_pton(AF_INET, argv[2], &server.sin_addr);
	
	connect(sock, (struct sockaddr *)&server, sizeof(struct sockaddr));
	printf("Connected\n");
	int siz = strlen(argv[1]);
	write(sock, (char *)&siz,sizeof(int));
	write(sock, argv[1], strlen(argv[1])*sizeof(char));
	FILE *f;
	char *fName = strcat("new_",argv[1]);
	f = fopen(fName, "w");
	//f = fopen("abc.html", "w");
	char line[100];
	int test = 1;
	
	while(test) {
		test = read(sock, (char *)&line, sizeof(line));
		printf("%s\n", line);
		fprintf(f, "%s", line);
	}
	fclose(f);
	close(sock);
	return 0;
}
