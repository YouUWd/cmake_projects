
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <arpa/inet.h>
#include <netdb.h>
int main() {
  struct sockaddr_in ad;
  char *host = "www.baidu.com";
  int sock;
  // assign IP, PORT
  ad.sin_family = AF_INET;

  unsigned long ia = inet_addr(host);
  if (ia != INADDR_NONE)
    memcpy(&ad.sin_addr, &ia, sizeof(ia));
  else {
    struct hostent *hp = gethostbyname(host);
    if (hp == NULL)
      return -1;
    memcpy(&ad.sin_addr, hp->h_addr, hp->h_length);
  }
  ad.sin_port = htons(80);

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
    return sock;
  if (connect(sock, (struct sockaddr *) &ad, sizeof(ad)) < 0)
    return -1;

  printf("sock=%d\n", sock);
  char request[1024];

  strcpy(request, "GET / HTTP/1.1\r\n");

//  strcat(request, "Host: www.baidu.com\r\n");
  strcat(request, "Connection: close\r\n");
//  strcat(request, "Accept: */*\r\n");
//  strcat(request, "User-Agent: C-Client\r\n");

  strcat(request, "\r\n");//这个是必须的

  int len = write(sock, request, strlen(request));
  printf("len=%d\n", len);
  char buff[1024];
  while (1) {
    int reads = read(sock, buff, 1024);
    printf("reads=%d\n", reads);
    if (reads == 0)
      break;
    printf("%s\n", buff);
    memset(buff, 0, sizeof(buff));
  }

}