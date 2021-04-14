#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr
// Function designed for chat between client and server.
void func(int sockfd) {
  printf("Enter String To sever :");
  char buff[MAX];
  int n;
  while (1) {
    bzero(buff, MAX);
    n = 0;
    while ((buff[n++] = getchar()) != '\n');
    write(sockfd, buff, sizeof(buff));
    // if msg contains "Exit" then server exit and chat ended.
    if (strncmp("exit", buff, 4) == 0) {
      printf("Client Exit...\n");
      break;
    }

    bzero(buff, MAX);
    read(sockfd, buff, sizeof(buff));
    // print buffer which contains the client contents
    printf("From Server: %s\t To sever : ", buff);
    if (strncmp("exit", buff, 4) == 0) {
      printf("Server Exit...\n");
      break;
    }

  }
}

int main() {
  int sockfd;
  struct sockaddr_in servaddr;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    printf("socket creation failed...\n");
    exit(0);
  } else
    printf("Socket successfully created..\n");
  bzero(&servaddr, sizeof(servaddr));

  // assign IP, PORT
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  servaddr.sin_port = htons(PORT);
  // connect the client socket to server socket
  if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) != 0) {
    printf("connection with the server failed...\n");
    exit(0);
  } else
    printf("connected to the server..\n");

  // function for chat
  func(sockfd);

  // close the socket
  close(sockfd);
}