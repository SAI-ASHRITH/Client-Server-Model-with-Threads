#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<pthread.h>

struct sockaddr_in serv;
struct sockaddr_in cli;
int pid;


void myHandler(int a){
	int loc;
	waitpid(pid,&loc,WUNTRACED);
}

void mH(void * par)
{
	char buf[10];
	int dsfd=*((int*)(par));
	recv(dsfd,buf,9,0);
	printf("Message: %s\n",buf);
	send(dsfd,"Msg Rcvd",8,0);
	exit(0);
}


int main()
{
	signal(SIGCHLD,myHandler);
	char buf[10];
	int csfd= socket(AF_INET,SOCK_STREAM,0);
	serv.sin_family=AF_INET;
	serv.sin_port=htons(4005);
	serv.sin_addr.s_addr=htonl(INADDR_ANY);

	bind(csfd,(struct sockaddr*)&serv,sizeof(struct sockaddr_in));

	listen(csfd,6);
	int size;
	
	pthread_t pt;

	for(;;)
	{		
	
		int dsfd=accept(csfd,(struct sockaddr*)&cli,&size);

		pthread_create(&pt,NULL,(void *)mH,(void *)&dsfd);

		/*pid = fork();
		
		
		
		if(pid==0)
		{
			recv(dsfd,&buf,9,0);
			printf("Message: %s\n",buf);
			//printf("port=%d",cli.sin_port);
			//printf("ip=%u",cli.sin_addr.s_addr);
			send(dsfd,"Msg Rcvd",8,0);
			exit(0);
		}
		else if (pid>0)
		{
			close(dsfd);
		}*/
	}
	
}
