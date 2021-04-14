#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>

#define PORT     6060
#define MAXLINE 1024

int main() {
  int sockfd;
  char buffer[MAXLINE];
  char *hello = "Hello from server!";
  struct sockaddr_in servaddr, cliaddr;

  // Creating socket file descriptor
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }

  bzero(&servaddr, sizeof(servaddr));
  bzero(&cliaddr, sizeof(cliaddr));
  // Filling server information
  servaddr.sin_family = AF_INET; // IPv4
  servaddr.sin_addr.s_addr = INADDR_ANY;
  servaddr.sin_port = htons(PORT);

  // Bind the socket with the server address
  if (bind(sockfd, (const struct sockaddr *) &servaddr,
           sizeof(servaddr)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  } else
    printf("Socket successfully binded..\n");

  int len, n;
  len = sizeof(cliaddr);  //len is value/resuslt

  n = recvfrom(sockfd, (char *) buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *) &cliaddr, &len);

  buffer[n] = '\0';
  printf("Client : %s\n", buffer);

  sendto(sockfd, hello, strlen(hello), MSG_RST, (const struct sockaddr *) &cliaddr,
         len);

  printf("Hello message sent.\n");

}