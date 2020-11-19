#include <bits/stdc++.h>
#include <unistd.h>
#include <poll.h>
#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <arpa/inet.h>
#define MAX 1000 
#define SA struct sockaddr 

using namespace std;

void receive(int sockfd, int port) { 
	char last_digit = (port%10) + '0';
	char buff1[MAX], msg[MAX]; 
	bzero(buff1, MAX); 

	read(sockfd, buff1, sizeof(buff1)); 

	if(buff1[0] == 'O' && buff1[1] == 'K'){
		cout << buff1 << endl;
		return;
	}

	int i = 0;
	for(i = 0; buff1[i] != ':' && buff1[i] != '-'; i++){
		msg[i] = buff1[i];
	}
	msg[i] = '\0';

	printf("\t---------------------- From client: %s ----------------------\n", msg); 

	bzero(buff1, MAX); 
	bzero(msg, MAX);
	char reply[4];
	bzero(reply, MAX); 
	reply[0] = '2';
	reply[1] = '0';
	reply[2] = last_digit;
	reply[3] = '\0';
	write(sockfd, reply, sizeof(reply)); 
	bzero(reply, sizeof(reply)); 
	return;
} 

void reception(int port){
	int sockfd, connfd;
	socklen_t len; 
	struct sockaddr_in servaddr, cli; 

	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("socket creation failed...\n"); 
		exit(0); 
	} 
	bzero(&servaddr, sizeof(servaddr)); 

	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(port); 

	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
		printf("socket bind failed...\n"); 
		exit(0); 
	} 
	
	if ((listen(sockfd, 5)) != 0) { 
		printf("Listen failed...\n"); 
		exit(0); 
	} 
	else
		printf("Server listening - port : %d\n", port); 
	len = sizeof(cli); 


	fd_set rds;
	FD_ZERO(&rds);
	FD_SET(sockfd, &rds);

	struct timeval timeout;
	timeout.tv_sec = 7;
	timeout.tv_usec = 0;

	int res;
	if ((res = select(sockfd+1, &rds, NULL, NULL, &timeout)) <= 0)
	{
	    if (res < 0)
	        printf("select failed...\n"); 
	    else
	        printf("Time out...\n"); 
	    close(sockfd);
	    return; 
	}


	connfd = accept(sockfd, (SA*)&cli, &len); 
	if (connfd < 0) { 
		printf("server acccept failed...\n"); 
		exit(0); 
	} 
	
	receive(connfd, port); 
	close(sockfd); 
}

int transmission(char* buff, int port){
	int sockfd, connfd; 
	struct sockaddr_in servaddr, cli; 

	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("socket creation failed...\n"); 
		return 1;
	} 
	bzero(&servaddr, sizeof(servaddr)); 

	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	servaddr.sin_port = htons(port); 

	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
		printf("connection with the server failed...\n"); 
		return 1; 
	} 
	
	printf("-----%s-----\n", buff);

	write(sockfd, buff, strlen(buff)+1); 
	bzero(buff, sizeof(buff)); 
	char buff1[MAX];
	read(sockfd, buff1, sizeof(buff1)); 
	printf("Received successfully : \n%s\n", buff1); 

	close(sockfd);
	return 0; 
}

int main(int argc,char* argv[]) {  

    int port = atoi(argv[1]);
 
    int s_port = (port / 1000) * 10000;
    struct pollfd mypoll = { STDIN_FILENO, POLLIN|POLLPRI };
    char str[1000];
    char message[1000];
	while(1){
    	printf("Enter message to send :\n");
		if( poll(&mypoll, 1, 13000) )
	    {
	       	fgets(str, MAX, stdin); 
	        int x = 0;
	        for(x = 0; str[x] != '\n'; x++);
	        str[x] = ':';
   			x++;
 			cout <<"str " << str << endl;
	    	cout <<"argv[1] " << argv[1] << endl;
	    	bzero(message, sizeof(message));
	        strcat(message, argv[1]);
	    	cout <<"message " << message << endl;
	    	strcat(message, str);
    		cout <<"message and str " << message << endl;
	    	printf("%s\nswitching to Transmission mode ......\n", message);
			int repeat = 1, i=1;
			while(i <= 3 && repeat){
				repeat = transmission(message, s_port); i++;
				if(repeat) sleep(5);
			}		    
	    }
	    else
	    {
	    	printf("\nswitching to reception mode ......\n");
			reception(port);
	    }

	}
} 
