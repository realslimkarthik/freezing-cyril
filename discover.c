#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<math.h>
#include<sys/socket.h>

#define SENDPORT 8000
#define RECVPORT 8001

int appsock;

struct bname
{
	char cname[100];
};

int broadcast_cname(char* computername)
{
	struct bname new;
	struct sockaddr_in broad;
	int res;
	broad.sin_family = AF_INET;
	broad.sin_port = htons(SENDPORT);
	broad.sin_addr.s_addr = htonl(INADDR_BROADCAST);
	
	strcpy(new.cname,computername);
	res = sendto(appsock,(char *)&new,sizeof(new),0,(struct sockaddr *)&broad,sizeof(struct sockaddr));
	if(res < 0)
	{
		printf("\nsendto failed\n");
		return -1;
	}
	else
	{
		return 0;
	}
}

int startlisten()
{
	struct bname rdata;
	struct sockaddr_in client;
	int clientLength;
	int i = 0;
	while(i<10)
	{
	recvfrom(appsock,(char *)&rdata,sizeof(struct bname),0,(struct sockaddr*) &client, &clientLength);
	printf("\n%s connected\n",rdata.cname);
	i++;
	}
}

int main(int argc,char** argv)
{
	char* computername = argv[1];
	struct sockaddr_in comp;
	comp.sin_family = AF_INET;
	comp.sin_port = htons(RECVPORT);
	comp.sin_addr.s_addr = htonl(INADDR_ANY);
	appsock = socket(AF_INET,SOCK_DGRAM,0);
	int broadcastEnable=1;
	int ret=setsockopt(appsock, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));
	if(bind(appsock,(struct sockaddr *)&comp,sizeof(struct sockaddr)) == -1)
	{
		printf("Bind Failed\n");
	}
	else
	{
		broadcast_cname(computername);
		startlisten();
	}

	return 0;
}