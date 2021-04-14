#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int sockfd;
  int len;
  struct sockaddr_in address;
  int result;
  char ch[] = {'A', '\n'};

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr("127.0.0.1");
  address.sin_port = htons(8080);
  len = sizeof(address);
  result = connect(sockfd, (struct sockaddr *) &address, len);

  if (result == -1) {
    perror("oops: client1");
    exit(1);
  }
  write(sockfd, &ch, strlen(ch));

  char bufferRead[512];
  int size = read(sockfd, &bufferRead, 512);
  printf("size %d\n", size);

  printf("char from server = %s\n", bufferRead);
  close(sockfd);
  exit(0);

}
