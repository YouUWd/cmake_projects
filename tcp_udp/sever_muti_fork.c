#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX 1024
#define PORT 8080

int main() {
  int serv_fd, cli_fd, len;
  struct sockaddr_in serv_addr, cli_addr;
  int opt = 1, status = 0;;

  char buffer[MAX];

  // socket create and verification
  serv_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (serv_fd == -1) {
    perror("socket creation failed...");
    exit(EXIT_FAILURE);
  } else
    printf("Socket successfully created %d..\n", serv_fd);

  // Forcefully attaching socket to the port 8080
  if (setsockopt(serv_fd, SOL_SOCKET, SO_REUSEPORT,
                 &opt, sizeof(opt))) {
    perror("set sock opt fail...");
    exit(EXIT_FAILURE);
  }
  // assign IP, PORT
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(PORT);

  // Binding newly created socket to given IP and verification
  if ((bind(serv_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr))) != 0) {
    perror("socket bind failed...");
    exit(EXIT_FAILURE);
  }

  // Now server is ready to listen and verification
  if ((listen(serv_fd, 5)) != 0) {
    perror("Listen failed...");
    exit(EXIT_FAILURE);
  } else
    printf("Server Listening:%d\n", PORT);

  // Accept the data packet from client and verification
  printf("Server %s:%d\n", inet_ntoa(serv_addr.sin_addr), ntohs(serv_addr.sin_port));

  len = sizeof(cli_addr);
  while (1) {
    cli_fd = accept(serv_fd, (struct sockaddr *) &cli_addr, (socklen_t *) &len);
    if (cli_fd < 0) {
      perror("server accept failed...");
      exit(EXIT_FAILURE);
    }
    printf("Received packet from %s:%d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));

    pid_t pid = fork();
    if (pid > 0) {
      close(cli_fd);
    } else if (pid == 0) {
      while (1) {
        memset(buffer, 0, sizeof(buffer));
        int n = read(cli_fd, buffer, MAX);
        if (n == 0) {
          close(cli_fd);
          printf("Connection close from %s:%d\n",
                 inet_ntoa(cli_addr.sin_addr),
                 ntohs(cli_addr.sin_port));
          cli_fd = 0;
          exit(1);
        } else {
          printf("[%s:%d] Length:%d, Data:%s\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), n, buffer);
          send(cli_fd, buffer, strlen(buffer), 0);
        }
      }
    }

    // After chatting close the socket


  }

}