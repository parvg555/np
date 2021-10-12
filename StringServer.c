#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 80
#define PORT 8888
#define SA struct sockaddr

void func(int sockfd)
{
char buff[MAX];
int n,len,i,j,k,a,val;
char s1[3][20];
char temp;
// infinite loop 

for (;;) {
    bzero(buff, MAX); // set buff with null values
	for(i=0;i<3;i++)
		bzero(s1[i],sizeof(s1[i]));

// read the message from client and copy it in buffer
n = read(sockfd, buff, sizeof(buff));
if(n==-1)
exit(0);
else
	printf("\nFrom client(%d): %s:",n,buff);

len = strlen(buff);
j=0;
k=0;
for(i=1;i<len;i++)
{
 if(buff[i]=='#')
 {
	 j++;
	 k=0;
 }	
  else{
	  s1[j][k]=buff[i];
	  k++;
  }
  	  
}//end for

switch(buff[0])
{
	case 'a':
	for(i=0;i<strlen(s1[0])-1;i++)
	{
		for(j=i+1;j<strlen(s1[0]);j++)
		{
			if(s1[0][j]<s1[0][i])
			{
				temp = s1[0][j];
				s1[0][j]=s1[0][i];
				s1[0][i]=temp;
			}
		}
	}
	strcpy(buff,s1[0]);
	break;

    case 'b':
	a = strcmp(s1[0],s1[1]);
	if(a==0)
		strcpy(buff,"Strings are Same");
	else
		strcpy(buff,"Strings are different");
	break;
 
    case 'c':
	strcpy(buff,s1[0]);
	break;

    case 'd':
	val = atoi(s1[2]);
	if(val > strlen(s1[0]))
		strcpy(buff, "Unable to insert, Out of index");
	else
	{
		strcpy(s1[0]+val,s1[1]);
		strcpy(buff,s1[0]);
	}
	break;	
	
	default:
	strcpy(buff,"Incorrect Option ");
}//end switch

for(i=0;i<4;i++)
{
	printf("\n%s",s1[i]);
}
    write(sockfd, buff, sizeof(buff));
	//sendto
// if msg contains "Exit" then server exit and chat ended.
 /*  if (strncmp("exit", buff, 4) == 0) {
    printf("Server Exit...\n");
   break;
   }*/
}
close(sockfd);
}



// Driver function
int main()
{
int sockfd, connfd, len;
struct sockaddr_in servaddr, cli;


// socket create and verification
sockfd = socket(AF_INET, SOCK_STREAM, 0);
//sockfd = socket(AF_INET, SOCK_DGRAM, 0);
if (sockfd == -1) {
printf("socket creation failed...\n");
exit(0);
}
else
printf("Socket successfully created..\n");



bzero(&servaddr, sizeof(servaddr));
// assign IP, PORT
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
servaddr.sin_port = htons(PORT);



// Binding newly created socket to given IP and verification
if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
printf("socket bind failed...\n");
exit(0);
}
else
printf("Socket successfully binded..\n");
// Now server is ready to listen and verification
if ((listen(sockfd, 5)) != 0) {
printf("Listen failed...\n");
exit(0);
}
else
printf("Server listening..\n");
len = sizeof(cli);



// Accept the data packet from client and verification
connfd = accept(sockfd, (SA*)&cli, &len);
if (connfd < 0) {
printf("server acccept failed...\n");
exit(0);
}
else{
printf("server acccept the client...\n");

// Function for chatting between client and server
func(connfd);
//func(sockfd)
}
// After chatting close the socket
close(sockfd);
}