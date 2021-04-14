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
  int serv_fd;
  struct sockaddr_in serv_addr;
  int opt = 1;

  char buffer[MAX];

  // socket create and verification
  serv_fd = socket(PF_INET, SOCK_STREAM, 0);
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

  fd_set readers, copy_readers;
  int fd_max, fd_num;
  struct timeval timeout;

  FD_ZERO(&readers);//初始化清空socket集合
  FD_SET(serv_fd, &readers);
  fd_max = serv_fd;

  while (1) {
    copy_readers = readers;
    timeout.tv_sec = 5;
    timeout.tv_usec = 5000;
    //无限循环调用select 监视可读事件
    if ((fd_num = select(fd_max + 1, &copy_readers, 0, 0, &timeout)) == -1) {
      perror("select error");
      break;
    }
    if (fd_num == 0) {//没有变动的socket
      continue;
    }

    for (int fd = 0; fd < fd_max + 1; fd++) {

      if (FD_ISSET(fd, &copy_readers)) {
        struct sockaddr_in cli_addr;
        int len = sizeof(cli_addr);
        if (fd == serv_fd) { //serv_fd变动,代表有新客户端连接
          int cli_fd = accept(serv_fd, (struct sockaddr *) &cli_addr, (socklen_t *) &len);
          printf("Received connect from %s:%d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
          FD_SET(cli_fd, &readers);
          if (fd_max < cli_fd) {
            fd_max = cli_fd;
          }
        } else {
          //获取远端socket地址，
          getpeername(fd, (struct sockaddr *) &cli_addr, (socklen_t *) &len);
          memset(buffer, 0, sizeof(buffer));
          int n = read(fd, buffer, MAX);
          if (n == -1) {
            continue;
          } else if (n == 0) {
            close(fd);
            printf("Connection close from %s:%d\n",
                   inet_ntoa(cli_addr.sin_addr),
                   ntohs(cli_addr.sin_port));
            FD_CLR(fd, &readers);
          } else {
            printf("[%s:%d] Length:%d, Data:%s\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), n, buffer);
            send(fd, buffer, strlen(buffer), 0);
          }
        }
      }
    }
    // After chatting close the socket
  }

}
