#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>

struct sockaddr_in serv;

int main()
{
		
	char msg[10];

	int csfd= socket(AF_INET,SOCK_STREAM,0);
	serv.sin_family=AF_INET;
	serv.sin_port=htons(4005);
	serv.sin_addr.s_addr=htonl(INADDR_ANY);

	connect(csfd,(struct sockaddr*)&serv,sizeof(struct sockaddr_in));
	send(csfd,"qwertyui",9,0);
	recv(csfd,msg,9,0);
	printf("%s",msg);

}
