#include<bits/stdc++.h>
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h> 
#include <arpa/inet.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/time.h> 
#define MAX 1025
#define SA struct sockaddr

using namespace std;

char buff[MAX] = "u";
int msg[10] = {0,0,0,0,0,0,0,0,0,0};
int g = 0;

struct client{
	int port;
	char user[MAX];
	char pass[MAX];
	char nick[MAX];
	char real[MAX];
} SC[10];

struct group{ 
   char name[20];
   char key[20];
   char topic[100];
   int users[10]; 
}; 

int receive(int sockfd, int port) { 
	int front_flag = 0, back_flag = 0, channel_available = 0, user_available = 0;;
	int i, c, x = 0;
	char buff1[MAX], reply[MAX], choice;
	char group_name[10], k[10] = "e";
	FILE *infile, *outfile; 
	struct group g[3]; 
	struct client cli[20];		 
	bzero(buff1, MAX); 
	read(sockfd, buff1, sizeof(buff1)); 
	for(i = 0; i < 4; i++){
		x += (buff1[i]-'0');
		x *= 10;
	}

	c = buff1[3] - '0';
	int c_port = x/10;
 	cout << "port " << c_port << endl;
 	if(buff1[i] == 'P' && buff1[i+2] == 'R') choice = 'A';
 	else if(buff1[i] == 'N' && buff1[i+1] == 'A') choice = 'B';
 	else choice = buff1[i]; 
 	//i++;
	printf("\t---- From client: %s ----\n", buff1); 


	switch(choice){
		case 'P':{
		 	i+=5;
		    
  	    	FILE *infile; 
			struct client cli[20]; 
			x = 0;
			infile = fopen ("users.txt", "r+"); 
			if (infile == NULL) 
			{ 
				fprintf(stderr, "\nError opening file\n"); 
				exit (1); 
			}
			while(fread(&cli[x], sizeof(struct client), 1, infile) && cli[x].port && cli[x].port != c_port) {
				// printf ("port = %d password = %s username = %s Nickname = %s realname = %s\n", cli[x].port, cli[x].pass, cli[x].user, cli[x].nick, cli[x].real);
				x++;
			}
			int	j = 0;
 		    while(buff1[i] != ':'){
 		    	cli[x].pass[j] = buff1[i];
		    	j++; i++;
		    }
		    cli[x].pass[j] = '\0';
			cli[x].port = c_port;
			cout << "Password " << cli[x].pass << endl;   
			//cout << "Port " << cli[x].port << endl;   
			fclose (infile); 

  		    FILE *outfile;    
		    outfile = fopen ("users.txt", "r+"); 
		    if (outfile == NULL) 
		    { 
		       fprintf(stderr, "\nError opend file\n"); 
		       exit (1); 
		    } 
		    for(x = 0; x < 10; x++){
		    	 fwrite (&cli[x], sizeof(struct client), 1, outfile); 
		    }
		    if(fwrite != 0) 
		    	; 
		     else
		        printf("error writing file !\n"); 
		    fclose (outfile); 

		    x = 0;
			infile = fopen ("users.txt", "r+"); 
			if (infile == NULL) 
			{ 
				fprintf(stderr, "\nError opening file\n"); 
				exit (1); 
			}
			while(fread(&cli[x], sizeof(struct client), 1, infile)) {
				printf ("Port = %d Pass = %s User = %s Nick = %s Real = %s\n", cli[x].port, cli[x].pass, cli[x].user, cli[x].nick, cli[x].real);
				x++;
			}
			fclose (infile); 

		    cout << "Password set successfully - port " << c_port << endl;	    		    
			bzero(reply, MAX); 
			reply[0] = 'O';
			reply[1] = 'K';
			reply[2] = '\0';
			bzero(group_name, sizeof(group_name));
			bzero(buff1, MAX); 
			write(sockfd, reply, sizeof(reply)); 
			bzero(reply, sizeof(reply)); 
			return 0; 
		}

		case 'N':{
			int pass_available = 0;
		 	i+=5, x = 0;
		    
  	    	struct client cli[20]; 
			FILE *infile; 
			infile = fopen ("users.txt", "r+"); 
			if (infile == NULL) 
			{ 
				fprintf(stderr, "\nError opening file\n"); 
				exit (1); 
			}
			while(fread(&cli[x], sizeof(struct client), 1, infile)) {
				// printf ("port = %d password = %s username = %s Nickname = %s realname = %s\n", cli[x].port, cli[x].pass, cli[x].user, cli[x].nick, cli[x].real);
				if(cli[x].port == c_port && cli[x].pass != ""){
					pass_available = 1;
					int j = 0;
		 		    while(buff1[i] != ':'){
		 		    	cli[x].nick[j] = buff1[i];
				    	j++; i++;
				    }
				    cli[x].nick[j] = '\0';
					cout << "nick " << cli[x].nick << endl;   
				}
				x++;
			}
			if(!pass_available){
				char error[20] = {"ERR_SETPASSFIRST"};
				cout << error << endl;
				write(sockfd, error, sizeof(error)); 
				bzero(group_name, sizeof(group_name));
				bzero(error, sizeof(error)); 
				return 0;
			}
			fclose (infile); 
		
			FILE *outfile; 
  		    outfile = fopen ("users.txt", "r+"); 
		    if (outfile == NULL) 
		    { 
		       fprintf(stderr, "\nError opend file\n"); 
		       exit (1); 
		    } 
		    for(x = 0; x < 10; x++){
		    	 fwrite (&cli[x], sizeof(struct client), 1, outfile); 
		    }
		    if(fwrite != 0) 
		    	; 
		     else
		        printf("error writing file !\n"); 
		    fclose (outfile); 

		    x = 0;
			infile = fopen ("users.txt", "r+"); 
			if (infile == NULL) 
			{ 
				fprintf(stderr, "\nError opening file\n"); 
				exit (1); 
			}
			while(fread(&cli[x], sizeof(struct client), 1, infile)) {
				printf ("Port = %d Pass = %s User = %s Nick = %s Real = %s\n", cli[x].port, cli[x].pass, cli[x].user, cli[x].nick, cli[x].real);
				x++;
			}
			fclose (infile); 

		    cout << "Nickname set successfully"  << endl;	    		    
			bzero(reply, MAX); 
			reply[0] = 'O';
			reply[1] = 'K';
			reply[2] = '\0';

			bzero(buff1, MAX); 
			bzero(group_name, sizeof(group_name));
			write(sockfd, reply, sizeof(reply)); 
			bzero(reply, sizeof(reply)); 
			return 0; 
		}

		case 'U':{
			int nick_available = 0;
		 	i+=5, x = 0;		    
  	    	struct client cli[20]; 
			FILE *infile; 
			infile = fopen ("users.txt", "r+"); 
			if (infile == NULL) 
			{ 
				fprintf(stderr, "\nError opening file\n"); 
				exit (1); 
			}
			while(fread(&cli[x], sizeof(struct client), 1, infile)) {
				// printf ("port = %d password = %s username = %s Nickname = %s realname = %s\n", cli[x].port, cli[x].pass, cli[x].user, cli[x].nick, cli[x].real);
				if(cli[x].port == c_port && (string)cli[x].nick != ""){
					//cout << "." << cli[x].nick << "." << endl;
					nick_available = 1;
					int j = 0;
		 		    while(buff1[i] != ' '){
		 		    	cli[x].user[j] = buff1[i];
				    	j++; i++;
				    }
				    cli[x].user[j] = '\0';
					cout << "user " << cli[x].user << endl;   
				
				    i+=5; // finishes reading hostname... no need to store.. hostname is port and it is already stored in sc[].port
				    i+=6; // finishes reading servername... no need to store.. hostname is server's port and it is already stored in argv[1]
				    i++; // reading : before realname

					j = 0;
		 		    while(buff1[i] != ':'){
		 		    	cli[x].real[j] = buff1[i];
				    	j++; i++;
				    }
				    cli[x].real[j] = '\0';
					cout << "real " << cli[x].real << endl;   
				}
				x++;
			}
			if(!nick_available){
				char error[20] = {"ERR_SETNICKFIRST"};
				cout << error << endl;
				write(sockfd, error, sizeof(error)); 
				bzero(group_name, sizeof(group_name));
				bzero(error, sizeof(error)); 
				return 0;
			}
			fclose (infile); 
		
			FILE *outfile; 
  		    outfile = fopen ("users.txt", "r+"); 
		    if (outfile == NULL) 
		    { 
		       fprintf(stderr, "\nError opend file\n"); 
		       exit (1); 
		    } 
		    for(x = 0; x < 10; x++){
		    	 fwrite (&cli[x], sizeof(struct client), 1, outfile); 
		    }
		    if(fwrite != 0) 
		    	; 
		     else
		        printf("error writing file !\n"); 
		    fclose (outfile); 

		    x = 0;
			infile = fopen ("users.txt", "r+"); 
			if (infile == NULL) 
			{ 
				fprintf(stderr, "\nError opening file\n"); 
				exit (1); 
			}
			while(fread(&cli[x], sizeof(struct client), 1, infile)) {
				printf ("Port = %d Pass = %s User = %s Nick = %s Real = %s\n", cli[x].port, cli[x].pass, cli[x].user, cli[x].nick, cli[x].real);
				x++;
			}
			fclose (infile); 

		    cout << "Username set successfully"  << endl;	    		    
			bzero(reply, MAX); 
			reply[0] = 'O';
			reply[1] = 'K';
			reply[2] = '\0';

			bzero(buff1, MAX); 
			write(sockfd, reply, sizeof(reply)); 
			bzero(group_name, sizeof(group_name));
			bzero(reply, sizeof(reply)); 
			return 0; 
		}

		case 'J':{
		 	i+=6; // reading space and # before channel name
		 	x = 0;
		    while(buff1[i] != ':' && buff1[i] != ' '){
		    	group_name[x] = buff1[i];
		    	// cout << buff1[i] << endl;
		    	x++; i++;
		    }
		    group_name[x] = '\0';i++;
		    // cout << "group_name ." << group_name <<"." << endl;
		    x = 0;
		    while(buff1[i] != ':' && buff1[i] != ' '){
		    	k[x] = buff1[i];
		    	x++; i++;
		    }
		    k[i] = '\0';i++;
		    // cout << "key " << k << endl;
		    
  	    	FILE *infile; 
			struct group g[3]; 
			i = 0, x = 0;
			
			infile = fopen ("data.txt", "r+"); 
			if (infile == NULL) 
			{ 
				fprintf(stderr, "\nError opening file\n"); 
				exit (1); 
			}
			while(fread(&g[x], sizeof(struct group), 1, infile)) {
				
				// printf ("name = %s key = %s topic = %s", g[x].name, g[x].key, g[x].topic);

				for(i = 0; i < 10 && g[x].users[i] ; i++){
					// cout << g[x].users[i] << '\t';
				} 

				if((string)(g[x].name) == (string)(group_name)){
					channel_available = 1;
					// cout << "in\n";
					if((string)(g[x].key) == (string)(k)){
						// cout << "key verified\n";
						g[x].users[i] = c_port;
					}else if((string)k == (string)("e")){
					// cout << "else if\n";
						
						char error[20] = {"ERR_NEEDMOREPARAMS"};
						cout << error << endl;
						write(sockfd, error, sizeof(error)); 
						bzero(group_name, sizeof(group_name));
						bzero(error, sizeof(error)); 
						return 0;
					}else{
					// cout << "else\n";
						char error[40] = {"ERR_BADCHANNELKEY"};
						cout << error << endl;
						write(sockfd, error, sizeof(error)); 
						bzero(group_name, sizeof(group_name));
						bzero(error, sizeof(error)); 
						return 0;	
					}
				}
				x++;
				cout << endl;
			}
			if(!channel_available){
				char error[40] = {"ERR_NOSUCHCHANNEL"};
				cout << error << endl;
				write(sockfd, error, sizeof(error)); 
				bzero(group_name, sizeof(group_name));
				bzero(error, sizeof(error)); 
				return 0;	
			}

			fclose (infile); 

  		    FILE *outfile;    
		    outfile = fopen ("data.txt", "r+"); 
		    if (outfile == NULL) 
		    { 
		       fprintf(stderr, "\nError opend file\n"); 
		       exit (1); 
		    } 
		    for(x = 0; x < 3; x++){
		    	 fwrite (&g[x], sizeof(struct group), 1, outfile); 
		    }
		    if(fwrite != 0) 
		    	; 
		     else
		        printf("error writing file !\n"); 
		    fclose (outfile); 


			infile = fopen ("data.txt", "r+"); 
			if (infile == NULL) 
			{ 
				fprintf(stderr, "\nError opening file\n"); 
				exit (1); 
			} 
			x = 0;	
			while(fread(&g[x], sizeof(struct group), 1, infile)) {
				
				printf ("name = %s key = %s topic = %s", g[x].name, g[x].key, g[x].topic);
			
				for(i = 0; i < 10 ; i++){
					if(!g[x].users[i]) continue;
					cout << g[x].users[i] << '\t';
				} 
				x++;
				cout << endl;
			}
			fclose (infile);

		    cout << "Joined grp - port " << c_port << endl;	    		    
			bzero(reply, MAX); 
			reply[0] = 'O';
			reply[1] = 'K';
			reply[2] = '\0';

			bzero(buff1, MAX); 
			write(sockfd, reply, sizeof(reply)); 
			bzero(group_name, sizeof(group_name));
			bzero(reply, sizeof(reply)); 
			return 0; 
		}

		case 'A':{ // PART
		 	i+=6; // reading space and # before channel name
		 	x = 0;

		    while(buff1[i] != ':' && buff1[i] != ' '){
		    	group_name[x] = buff1[i];
		    	// cout << buff1[i] << endl;
		    	x++; i++;
		    }
		    group_name[x] = '\0';i++;
		    // cout << "group_name ." << group_name <<"." << endl;
	    	i = 0, x = 0;
			FILE *infile; 
			infile = fopen ("data.txt", "r+"); 
			if (infile == NULL) 
			{ 
				fprintf(stderr, "\nError opening file\n"); 
				exit (1); 
			}
			struct group g[3];
			while(fread(&g[x], sizeof(struct group), 1, infile)) {
				// printf ("name = %s key = %s topic = %s", g[x].name, g[x].key, g[x].topic);
				if((string)(g[x].name) == (string)(group_name)){
					channel_available = 1;
				}
				for(i = 0; i < 10; i++){ 
					if(!g[x].users[i]) continue;
					if((g[x].users[i] == c_port) && (string)(g[x].name) == (string)(group_name)){
						// cout << "User verified\n";
						user_available = 1;
						g[x].users[i] = 0; // user is removed from the list	
						// cout << "user removed successfully ";
					}
					// cout << g[x].users[i] << '\t';
				} 

				x++;
				cout << endl;
			}
			if(!channel_available){
				char error[40] = {"ERR_NOSUCHCHANNEL"};
				cout << error << endl;
				write(sockfd, error, sizeof(error)); 
				bzero(group_name, sizeof(group_name));
				bzero(error, sizeof(error)); 
				return 0;	
			}
			if(!user_available){
				char error[40] = {"ERR_NOSUCHUSER"};
				cout << error << endl;
				write(sockfd, error, sizeof(error)); 
				bzero(group_name, sizeof(group_name));
				bzero(error, sizeof(error)); 
				return 0;	
			}

			fclose (infile); 

  		    outfile = fopen ("data.txt", "r+"); 
		    if (outfile == NULL) 
		    { 
		       fprintf(stderr, "\nError opend file\n"); 
		       exit (1); 
		    } 
		    for(x = 0; x < 3; x++){
		    	 fwrite (&g[x], sizeof(struct group), 1, outfile); 
		    }
		    if(fwrite != 0) 
		    	; 
		     else
		        printf("error writing file !\n"); 
		    fclose (outfile); 


			infile = fopen ("data.txt", "r+"); 
			if (infile == NULL) 
			{ 
				fprintf(stderr, "\nError opening file\n"); 
				exit (1); 
			} 
			x = 0;	
			while(fread(&g[x], sizeof(struct group), 1, infile)) {
				printf ("name = %s key = %s ", g[x].name, g[x].key);
				for(i = 0; i < 10 ; i++){
					if(!g[x].users[i]) continue;
					cout << g[x].users[i] << '\t';
				} 
				x++;
				cout << endl;
			}
			fclose (infile);

		    cout << "removed user - port " << c_port << endl;	    		    
			bzero(reply, MAX); 
			reply[0] = 'O';
			reply[1] = 'K';
			reply[2] = '\0';

			bzero(buff1, MAX); 
			write(sockfd, reply, sizeof(reply)); 
			bzero(group_name, sizeof(group_name));
			bzero(reply, sizeof(reply)); 
			return 0; 
		}

		case 'T':{
		 	i+=7; // command is read, reading space and # before channel name, starting of group name
		 	x = 0;
		    while(buff1[i] != ':' && buff1[i] != ' '){
		    	group_name[x] = buff1[i];
		    	x++; i++;
		    }
		    if(buff1[i] == ':'){
			    x = 0;				
				infile = fopen ("data.txt", "r+"); 
				if (infile == NULL) 
				{ 
					fprintf(stderr, "\nError opening file\n"); 
					exit (1); 
				}
				while(fread(&g[x], sizeof(struct group), 1, infile)) {
					for(i = 0; i < 10; i++){ if(!g[x].users[i]) continue;
					} 
					if((string)(g[x].name) == (string)(group_name)){
						channel_available = 1;
						cout << "Topic : " << g[x].topic << endl;
						bzero(buff1, MAX); 
						write(sockfd, g[x].topic, sizeof(g[x].topic)); 
						bzero(group_name, sizeof(group_name));
						bzero(g[x].topic, sizeof(g[x].topic)); 
						return 0; 
					}
					x++;
					cout << endl;
				}
				if(!channel_available){
					char error[40] = {"ERR_NOSUCHCHANNEL"};
					cout << error << endl;
					write(sockfd, error, sizeof(error)); 
					bzero(group_name, sizeof(group_name));
					bzero(error, sizeof(error)); 
					return 0;	
				}
				fclose (infile); 
		    }else if(buff1[i] == ' '){
				i++;
				infile = fopen ("data.txt", "r+"); 
				if (infile == NULL) 
				{ 
					fprintf(stderr, "\nError opening file\n"); 
					exit (1); 
				}
				x = 0;
				while(fread(&g[x], sizeof(struct group), 1, infile)) {	
					int j = 0;			
					if((string)(g[x].name) == (string)(group_name)){
						channel_available = 1;
						while(buff1[i] != ':'){
							g[x].topic[j] = buff1[i];
							j++; i++;
						}g[x].topic[j] = '\0'; i++;
						cout << "New topic set successfully " << g[x].topic << endl;
					}
					x++;
					cout << endl;
				}

	  		    outfile = fopen ("data.txt", "r+"); 
			    if (outfile == NULL) 
			    { 
			       fprintf(stderr, "\nError opend file\n"); 
			       exit (1); 
			    } 
			    for(x = 0; x < 3; x++){
			    	 fwrite (&g[x], sizeof(struct group), 1, outfile); 
			    }
			    if(fwrite != 0) 
			       printf("contents to file written successfully !\n"); 
			    else
			       printf("error writing file !\n"); 
			    fclose (outfile); 


				infile = fopen ("data.txt", "r+"); 
				if (infile == NULL) 
				{ 
					fprintf(stderr, "\nError opening file\n"); 
					exit (1); 
				} 
				x = 0;	
				while(fread(&g[x], sizeof(struct group), 1, infile)) {
					printf ("name = %s key = %s topic = %s\n", g[x].name, g[x].key, g[x].topic);
					for(i = 0; i < 10 ; i++){
						if(!g[x].users[i]) continue;
						cout << g[x].users[i] << '\t';
					} 
				x++;
					cout << endl;
				}
				fclose (infile);
		    }		    
			char response[MAX] = "New topic is set";
			bzero(buff1, MAX); 
			write(sockfd, response, sizeof(response)); 
			bzero(group_name, sizeof(group_name));
			bzero(response, sizeof(response)); 
			return 0; 
		}

		case '#':{
		 	int i3 = 0; 
			i = 0, x = 0;
		 	
		    while(buff1[i] != '#'){
		    	buff[i3] = buff1[i];
		    	// cout << buff1[i] << endl;
		    	i3++; i++;
		    }i++;
		    while(buff1[i] != ' '){
		    	group_name[x] = buff1[i];
		    	// cout << buff1[i] << endl;
		    	x++; i++;
		    }i++;
		    group_name[x] = '\0';
		    // cout << "group_name ." << group_name <<"." << endl;

			while(buff1[i] != ':'){
		    	buff[i3] = buff1[i];
		    	// cout << buff1[i] << endl;
		    	i3++; i++;
		    }i++;
		    buff[i3] = '-'; i3++;

			infile = fopen ("data.txt", "r+"); 
			if (infile == NULL) 
			{ 
				fprintf(stderr, "\nError opening file\n"); 
				exit (1); 
			}
			struct group g[3];
			int flag = 0; x = 0; 
			while(fread(&g[x], sizeof(struct group), 1, infile)) {
				// printf ("name = %s key = %s topic = %s", g[x].name, g[x].key, g[x].topic);
				if((string)(g[x].name) == (string)(group_name)) channel_available = 1;
				for(i = 0; i < 10; i++){
					// cout << g[x].users[i] << '\t';
					if(!g[x].users[i]) continue;
					if((g[x].users[i] == c_port) && (string)(g[x].name) == (string)(group_name)){
						int j = 0;
						// cout << "User verified\n";
						user_available = 1;
						for(int i1 = 0; i1 < 10; i1++){ if(!g[x].users[i1] || g[x].users[i1] == c_port) continue;
							int temp = g[x].users[i1];
							int val = ((temp/1000) * 10000);
							if(val == port){
								msg[j] = temp;
								j++;
							}else{
								if(val < port) back_flag = 1;
					    		if(val > port) front_flag = 1;
					    		flag = 1;
					    	}
							buff[i3] = (temp/1000) + '0';
							i3++;
							buff[i3] = (temp%10) + '0';
							i3++;
							buff[i3] = '-';
							i3++;
						}
					    if(flag){
					    	if(front_flag) msg[9] = port+10000;
					    	if(back_flag) msg[8] = port-10000;
					    	printf("msg8 msg9 %d %d\n", msg[8], msg[9]);
					    }
						buff[i3] = ':'; i3++; buff[i3] = '\0';
						cout << buff << endl;
						bzero(buff1, MAX); 
						bzero(group_name, sizeof(group_name)); 	
						bzero(reply, MAX); 
						reply[0] = '2';
						reply[1] = '0';
						reply[2] = '0';
						reply[3] = '\0';
						write(sockfd, reply, sizeof(reply)); 
						bzero(reply, sizeof(reply));
						return 1;
					}
				}
				x++;
				cout << endl;
			}
			if(!channel_available){
				char error[40] = {"ERR_NOSUCHCHANNEL"};
				cout << error << endl;
				write(sockfd, error, sizeof(error)); 
				bzero(group_name, sizeof(group_name));
				bzero(error, sizeof(error)); 
				return 0;	
			}
			if(!user_available){
				char error[40] = {"ERR_NOSUCHUSER"};
				cout << error << endl;
				write(sockfd, error, sizeof(error)); 
				bzero(group_name, sizeof(group_name));
				bzero(error, sizeof(error)); 
				return 0;	
			}
			fclose (infile); 
		}

		case 'B':{ // NAMES
		 	// cout << i << buff1[i] << endl;
		 	i+=5; // command is read
		 	x = 0;

		 	map<int, string> mp;   
  	    	struct client cli[20]; 
			FILE *infile; 
			infile = fopen ("users.txt", "r+"); 
			if (infile == NULL) 
			{ 
				fprintf(stderr, "\nError opening file\n"); 
				exit (1); 
			}
			while(fread(&cli[x], sizeof(struct client), 1, infile)) {
				// printf ("port = %d password = %s username = %s Nickname = %s realname = %s\n", cli[x].port, cli[x].pass, cli[x].user, cli[x].nick, cli[x].real);
				mp[cli[x].port] = (string)cli[x].nick;
				// cout <<"map val " << mp[cli[x].port] << endl;
				x++;
			}
			fclose (infile); 

		 	if(buff1[i] == ':'){
			    x = 0;				
				infile = fopen ("data.txt", "r+"); 
				if (infile == NULL) 
				{ 
					fprintf(stderr, "\nError opening file\n"); 
					exit (1); 
				}
				int k = 0;
				bzero(reply, sizeof(reply)); 
				while(fread(&g[x], sizeof(struct group), 1, infile)) {
					// printf ("name = %s key = %s topic = %s ", g[x].name, g[x].key, g[x].topic);
					// for(i = 0; i < 10; i++){ if(!g[x].users[i]) continue;
					// cout << g[x].users[i] << '\t';
					// }
					int j = 0;
					reply[k] = '*'; k++;
					while(g[x].name[j]){
						reply[k] = g[x].name[j];
						k++; j++;
					}reply[k] = '*'; k++; reply[k] = '\n'; k++;
					for(i = 0; i < 10; i++){ 
						if(!g[x].users[i]) continue;
						int u = g[x].users[i];
						j = 0;
						string s = mp[u];
			 			// cout << s <<"." << s[j] <<"." << u << endl;
						while(s != "" && s[j] != '\0' && u){
							reply[k] = s[j];
							k++; j++;
						}
						if(s != "" && u){ reply[k] = '\t'; k++;}
					}
					reply[k] = '\n'; k++;
					x++;
					cout << endl;
				}
				cout << "Names : " << reply << endl;
				bzero(buff1, MAX); 
				write(sockfd, reply, sizeof(reply)); 
				bzero(group_name, sizeof(group_name));
				bzero(reply, sizeof(reply)); 
				return 0; 

		 	}else if(buff1[i] == ' ' && buff1[i+1] == '#'){
	 			i+=2;  
	 			x = 0;
	 		    while(buff1[i] != ':'){
			    	group_name[x] = buff1[i];
			    	x++; i++;
			    }
			    group_name[x] = '\0';
			    // cout << "Group name " << group_name << endl;   

			    x = 0;				
				infile = fopen ("data.txt", "r+"); 
				if (infile == NULL) 
				{ 
					fprintf(stderr, "\nError opening file\n"); 
					exit (1); 
				}
				while(fread(&g[x], sizeof(struct group), 1, infile)) {
					// printf ("name = %s key = %s topic = %s ", g[x].name, g[x].key, g[x].topic);
				
					for(i = 0; i < 10; i++){
						if(!g[x].users[i]) continue;
						// cout << g[x].users[i] << '\t';
					} 
					if((string)(g[x].name) == (string)(group_name)){
						channel_available = 1;
						// cout << "in\n";
						int k = 0;
						bzero(reply, sizeof(reply)); 
						for(i = 0; i < 10; i++){ if(!g[x].users[i]) continue;
							// cout << g[x].users[i] << '\n';
							int u = g[x].users[i];
							int j = 0;
							string s = mp[u];
							while(s != "" && s[j] != '\0' && u){
								reply[k] = s[j];
								k++; j++;
							}
							if(s != "" && u){reply[k] = '\n'; k++;}
						} 
						cout << "Names : " << reply << endl;
						bzero(buff1, MAX); 
						write(sockfd, reply, sizeof(reply)); 
						bzero(group_name, sizeof(group_name));
						bzero(reply, sizeof(reply)); 
						return 0; 
					}
					x++;
					cout << endl;
				}
				if(!channel_available){
					char error[40] = {"ERR_NOSUCHCHANNEL"};
					cout << error << endl;
					write(sockfd, error, sizeof(error)); 
					bzero(group_name, sizeof(group_name));
					bzero(error, sizeof(error)); 
					return 0;	
				}
				fclose (infile);
		 	}
		}
		case 'L':{ // LIST
		 	// cout << i << buff1[i] << endl;
		 	i+=4; // command is read
		 	x = 0;

		 	if(buff1[i] == ':'){
			    x = 0;				
				infile = fopen ("data.txt", "r+"); 
				if (infile == NULL) 
				{ 
					fprintf(stderr, "\nError opening file\n"); 
					exit (1); 
				}
				int k = 0;
				bzero(reply, sizeof(reply)); 
				while(fread(&g[x], sizeof(struct group), 1, infile)) {
					int j = 0;
					reply[k] = '*'; k++;
					while(g[x].name[j]){
						reply[k] = g[x].name[j];
						k++; j++;
					}reply[k] = '*'; k++; reply[k] = '\t'; k++;
					j = 0;
					while(g[x].topic[j]){
						reply[k] = g[x].topic[j];
						k++; j++;
					}reply[k] = '\n'; k++;
					x++;
					cout << endl;
				}
				cout << "List : " << reply << endl;
				bzero(buff1, MAX); 
				write(sockfd, reply, sizeof(reply)); 
				bzero(group_name, sizeof(group_name));
				bzero(reply, sizeof(reply)); 
				return 0; 

		 	}else if(buff1[i] == ' ' && buff1[i+1] == '#'){
	 			i+=2;  
	 			x = 0;
	 		    while(buff1[i] != ':'){
			    	group_name[x] = buff1[i];
			    	x++; i++;
			    }
			    group_name[x] = '\0';
			    x = 0;				
				infile = fopen ("data.txt", "r+"); 
				if (infile == NULL) 
				{ 
					fprintf(stderr, "\nError opening file\n"); 
					exit (1); 
				}
				while(fread(&g[x], sizeof(struct group), 1, infile)) {
					if((string)(g[x].name) == (string)(group_name)){
						channel_available = 1;
						int k = 0, j = 0;
						bzero(reply, sizeof(reply)); 
						while(g[x].topic[j]){
							reply[k] = g[x].topic[j];
							k++; j++;
						}reply[k] = '\n'; k++;
						cout << "List : " << reply << endl;
						bzero(buff1, MAX); 
						write(sockfd, reply, sizeof(reply)); 
						bzero(group_name, sizeof(group_name));
						bzero(reply, sizeof(reply)); 
						return 0; 
					}
					x++;
					cout << endl;
				}
				if(!channel_available){
					char error[40] = {"ERR_NOSUCHCHANNEL"};
					cout << error << endl;
					write(sockfd, error, sizeof(error)); 
					bzero(group_name, sizeof(group_name));
					bzero(error, sizeof(error)); 
					return 0;	
				}
				fclose (infile);
		 	}
		}
	}

	printf("\t---- From client: %s ----\n", buff1); 
	
    int  j = 0, flag = 0;

    for(i = 0; buff1[i]; i++){
    	if(buff1[i] != '-') buff[i] = buff1[i];
    	else break;
    }
    x = i;
    i++;
    for(;buff1[i] != ':'; i++){
    	if(buff1[i] == '-') continue;
    	int val = (buff1[i] - '0') * 10000;
    	if(val == port){
			msg[j] = (val/10) + (buff1[i+1] - '0');	
			j++;

    	}
    	else{
			if(val < port) back_flag = 1;
    		if(val > port) front_flag = 1;
    		buff[x] = '-';
    		buff[x+1] = buff1[i];
    		buff[x+2] = buff1[i+1];
    		x+=3;
    		flag = 1;
    	}
    	i++;
    } i++;
    buff[x] = ':'; x++; buff[x] = '\0';
    
    if(flag){
    	if(front_flag) msg[9] = port+10000;
    	if(back_flag) msg[8] = port-10000;
    	printf("msg8 msg9 %d %d\n", msg[8], msg[9]);
    }

    
	bzero(buff1, MAX); 
	bzero(group_name, sizeof(group_name)); 	
	bzero(k, sizeof(k)); 

	bzero(reply, MAX); 
	reply[0] = '2';
	reply[1] = '0';
	reply[2] = '0';
	reply[3] = '\0';
	write(sockfd, reply, sizeof(reply)); 
	bzero(reply, sizeof(reply));

	return 1;
} 

int reception(int port){
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
		printf("Server listening..\n"); 
	len = sizeof(cli); 

	connfd = accept(sockfd, (SA*)&cli, &len); 
		
	if (connfd < 0) { 
		printf("server acccept failed...\n"); 
		exit(0); 
	} 
	
	int ret = receive(connfd, port); 
	close(sockfd); 
	return ret;
}

int transmission(char* bufft, int port_num){
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
	servaddr.sin_port = htons(port_num); 

	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
		printf("connection with the server failed... port_num : %d\n", port_num); 
		return 1; 
	} 
	
	write(sockfd, bufft, strlen(bufft)+1); 
	bzero(bufft, sizeof(bufft)); 
	read(sockfd, bufft, sizeof(bufft)); 
	printf("From Server : %s\n", bufft); 

	close(sockfd);
	return 0; 
}

int main(int argc , char *argv[]) { 
	int port = atoi(argv[1]);
	char data[MAX];
	while(1){
		int transmission_flag = reception(port);
		printf("\n switching to Transmission mode ......\n");
		for(int i = 0; i < 10 && transmission_flag ; i++){
			if((!msg[i])) continue;
			for(int j = 0; buff[j]; j++) data[j] = buff[j];
			for(int k = 1, repeat = 1; k <= 4 && repeat; k++){
				printf("sending to client - port : %d\n", msg[i]);
				repeat = transmission(data, msg[i]);
				if(repeat){
					printf("Sleep for 5 seconds before transmitting again\n");
					sleep(5);
				}	
			}		    
			bzero(data, sizeof(data));
		}

		bzero(buff, sizeof(buff));
		bzero(msg, sizeof(msg)); 
		printf("\n switching to reception mode ......\n");
	}
	return 0; 
} 
