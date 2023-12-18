#include<stdio.h>
#include<stdlib.h>
#include<netdb.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<time.h>
#include<string.h>


int main(int argc, char **argv){
	char 		message[100];
	int 		sockfd, SERV_TCP_PORT = 55555;
	socklen_t 	len;
	struct 		sockaddr_in servAdd;
	int 		rand_num;
	int32_t 	point;
	int 		size=sizeof(point);
	long int 	ss=0;


	char 			name[10];	
	//int 			i=0;
	//int			sockfd, n;
	char			buff[4096];
	//char			recvline[MAXLINE + 1];
	//char 			msg[MAXLINE]="";
	//struct sockaddr_in	servaddr;



	if(argc != 3){
		printf("Call model:%s <IP> <Port#>\n",argv[0]);
		exit(0);
	}

	if ((sockfd=socket(AF_INET,SOCK_STREAM,0))<0){
		fprintf(stderr, "[-] Cannot create socket\n");
		exit(1);
	}
	else
	{
		fprintf(stderr, "[+] Socket Created\n");
	}
	
	servAdd.sin_family = AF_INET;
	sscanf(argv[2], "%d", &SERV_TCP_PORT);
	servAdd.sin_port = htons(SERV_TCP_PORT);
	if(inet_pton(AF_INET, argv[1], &servAdd.sin_addr) < 0){
		fprintf(stderr, " inet_pton() has failed\n");
		exit(2);
	}

	if(connect(sockfd, (struct sockaddr *) &servAdd, sizeof(servAdd))<0){
		fprintf(stderr, "connect() failed, exiting\n");
		exit(3);
	}


/*
	printf("Enter name: ");
	fgets(name,10,stdin);
	name[strcspn(name,"\n")]=0;
	snprintf(buff, sizeof(buff), "%s Joined\n",name);
	write(sockfd, buff, strlen(buff));
*/


	while(1){
		if (read(sockfd, message, sizeof(message))<0){ // sizeof(message)
			fprintf(stderr, "read() error\n");
			exit(0);
		}
		printf("%s\n",message);
		if(!strcmp(message,"The lucky ones get the sum first")){
			rand_num = (int) time(&ss)%6+1;
			printf("-------------\xE2\x99\xA0 Your lucky number: %d \xE2\x99\xA0------------\n",rand_num);
			point=htonl(rand_num);
			write(sockfd,&point,size);
		}
	}
	exit(0);
}
