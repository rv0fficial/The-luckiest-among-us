#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>
#include<netdb.h>
#include<netinet/in.h>


void gameFunction(int connfd_4_c1,int connfd_4_c2,int connfd_4_c3){
	
	
	int 		c1_points=0,c2_points=0,c3_points=0,size=sizeof(int32_t);
	int32_t 	c1_conv_points,c2_conv_points,c3_conv_points;
	char 		buf[100];

	FILE 		*fp;	//log prt
	fp = fopen("output.txt","w");//log prt

	while(1){

		sleep(1);
		write(connfd_4_c1,"The lucky ones get the sum first",100); //strlen(message)
		if(read(connfd_4_c1,&c1_conv_points,size)<0)
			printf("Read Error from Player 1");
		c1_points+=ntohl(c1_conv_points);	
		snprintf(buf, 100, "Your Score is :: %d |Player 2 Score is :: %d |Player 3 Score is :: %d\n\n", c1_points, c2_points,c3_points);
		write(connfd_4_c1,buf,100);
		
		if(c1_points>=20){
			fputc(c1_points,fp);//log prt
			write(connfd_4_c1,"\xE2\x99\xA3 You won this round. \xE2\x99\xA3",100);
			write(connfd_4_c2,"Game over: You lost this round",100);
			write(connfd_4_c3,"Game over: You lost this round",100);
			fclose(fp);	//log prt
			break;
		}

		sleep(2);
		write(connfd_4_c2,"The lucky ones get the sum first",100);
		if(read(connfd_4_c2,&c2_conv_points,size)<0)
			printf("Read Error from Player 2");
		c2_points+=ntohl(c2_conv_points);
		snprintf(buf, 100, "Your Score is :: %d |Player 1 Score is :: %d |Player 3 Score is :: %d\n\n", c2_points, c1_points,c3_points);
		write(connfd_4_c2,buf,100);
		
		if(c2_points>=20){
			fputc(c2_points,fp);//log prt
			write(connfd_4_c2,"\xE2\x99\xA3 You won this round. \xE2\x99\xA3",100);
			write(connfd_4_c1,"Game over: You lost this round",100);
			write(connfd_4_c3,"Game over: You lost this round",100);
			fclose(fp);	//log prt
			break;
		}

		sleep(3);
		write(connfd_4_c3,"The lucky ones get the sum first",100);
		if(read(connfd_4_c3,&c3_conv_points,size)<0)
			printf("Read Error from Player 3");
		c3_points+=ntohl(c3_conv_points);
		snprintf(buf, 100, "Your Score is :: %d |Player 1 Score is :: %d |Player 2 Score is :: %d\n\n",c3_points, c1_points, c2_points);
		write(connfd_4_c3,buf,100);
		
		if(c3_points>=20){
			fputc(c3_points,fp);//log prt
			write(connfd_4_c3,"\xE2\x99\xA3 You won this round. \xE2\x99\xA3",100);
			write(connfd_4_c2,"Game over: You lost this round",100);
			write(connfd_4_c1,"Game over: You lost this round",100);
			fclose(fp);	//log prt
			break;
		}
		
	}

	close(connfd_4_c1);
	close(connfd_4_c2);
	close(connfd_4_c3);
}



int main(int argc){
	char *myTime;
	int listenfd, connfd_4_c1, connfd_4_c2, connfd_4_c3; //SERV_TCP_PORT = 55555;
	socklen_t len;
	struct sockaddr_in servaddr;
	int points;
	int32_t conv_points;
	int size = sizeof(conv_points);
	
	/*if(argc != 1){
		fprintf(stderr,"Call model: %s <Port#>\n",argv[0]);
		exit(0);
	}*/

	if((listenfd = socket(AF_INET, SOCK_STREAM, 0))<0){
		fprintf(stderr, "[-] Could not create socket\n");
		exit(1);
	}
	else{
		fprintf(stderr, "[+] Socket Created\n"); 
	}

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

//no need of sscanf function to get port number as a input.
	//sscanf(argv[1], "%d", &SERV_TCP_PORT);

	servaddr.sin_port = htons(55555);
	bind(listenfd, (struct sockaddr *) &servaddr,sizeof(servaddr));
	
	if(listen(listenfd, 6) == 0){
		printf("[+]Listening...\n");
	}else{
		printf("[-]Error in binding.\n");
	}

		printf("///////////// \xE2\x99\xA0 Welcome to the GAME SERVER \xE2\x99\xA0 /////////////\n");

	while(1){

		connfd_4_c1 = accept(listenfd,(struct sockaddr*)NULL, NULL);//not keeping track of client infromation
		write(connfd_4_c1,"Waiting for player 2 & 3 to join...",100);

		connfd_4_c2 = accept(listenfd,(struct sockaddr*)NULL, NULL);//not keeping track of client infromation
		write(connfd_4_c1,"Player 2 joined... | Please wait...",100);
		write(connfd_4_c2,"Player 1 already joined... | Waiting for player 3 to join...",100);

		connfd_4_c3 = accept(listenfd,(struct sockaddr*)NULL, NULL);//not keeping track of client infromation
		write(connfd_4_c1,"Player 3 joined... | Please wait...",100);
		write(connfd_4_c2,"Player 3 joined... | Please wait...",100);
		write(connfd_4_c3,"Player 1 & 2 already joined... | Game is Starting...",100);

		printf("[+] Incoming game request from user\n");
		
		if(fork()==0)
			gameFunction(connfd_4_c1,connfd_4_c2,connfd_4_c3);
		
	}
}

