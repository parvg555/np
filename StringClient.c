#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#define MAX 80
#define PORT 8888
#define SA struct sockaddr
void func(int sockfd)
{
char buff[MAX];
printf("Press any key to see menu.....\n");
for(;;){
int n=0;
getchar();
bzero(buff, sizeof(buff));
printf("\nChoose an operation from the following\n(a)String sorting\n(b)String comparison\n(c)String copy\n(d)String insertion\n(e)deletion from a particular location\n:");
scanf("%c",&buff[0]);


if(buff[0]=='a')
{
	printf("Enter String to Sort: ");
	scanf("%s",&buff[1]);
}

if(buff[0]=='b')
{
	printf("Enter first String: ");
	scanf("%s",&buff[1]);
	buff[strlen(buff)]='#';
	printf("Enter second String: ");
	scanf("%s",&buff[strlen(buff)]);
	
}

if(buff[0]=='c')
{
	printf("Enter String to Copy:");
	scanf("%s",&buff[1]);
	//write(sockfd, buff, sizeof(buff));//send the message to server
   
}

if(buff[0]=='d')
{
	printf("Enter first String: ");
	scanf("%s",&buff[1]);
	buff[strlen(buff)]='#';
	printf("Enter second String to insert: ");
	scanf("%s",&buff[strlen(buff)]);
	buff[strlen(buff)]='#';
	printf("Enter index to insert: ");
	scanf("%s",&buff[strlen(buff)]);
}


write(sockfd, buff, sizeof(buff));//send the message to server
read(sockfd, buff, sizeof(buff)); //reading the message recived from server
printf("\nFrom Server : %s", buff);
}

/*if ((strncmp(buff, "exit", 4)) == 0) {
printf("Client Exit...\n");
close(sockfd);
break;
}*/

}
int main()
{
int sockfd, connfd;
struct sockaddr_in servaddr, cli;
// socket create and varification
sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd == -1) {
printf("socket creation failed...\n");
exit(0);
}
else
printf("Socket successfully created..\n");
bzero(&servaddr, sizeof(servaddr));
// assign IP, PORT
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
servaddr.sin_port = htons(PORT);
// connect the client socket to server socket
if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
printf("connection with the server failed...\n");
exit(0);
}
else
printf("connected to the server..\n");
// function for chat
func(sockfd);
// close the socket
close(sockfd);
}