#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

#define MAX 1024
#define CLIENT_MAX_SIZE 128
#define PORT 8080
/*
 * epoll_create() 创建epoll监听socket
 * epoll_ctl()注册,删除,修改监听
 * epoll_wait() 等待事件触发函数
 *
 * LT(level-trigger) 水平触发
 * epoll的默认工作方式,在这个模式下,只要监听的socket有可读/可写状态,都将返回该socket,例如:
 * 当客户端给tcp服务器发送一个数据时,这个client_socket将会是可读的,调用epoll_wait函数将会返回该client_socket,
 * 如果服务器不做处理,这个client_socket将会是一直可读的,下次调用epoll_wait函数将会继续返回client_socket
 */
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

  struct epoll_event event;
  struct epoll_event wait_event_arr[CLIENT_MAX_SIZE];
  int epoll_fd = epoll_create(10);//创建epoll句柄,里面的参数10没有意义

  if (epoll_fd == -1) {
    perror("Create EPOLL FD FAIL");
    exit(EXIT_FAILURE);
  }

  event.events = EPOLLIN;//可读事件
  event.data.fd = serv_fd;//server_socket
  int result = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, serv_fd, &event);

  if (result == -1) {
    perror("EPOLL register fail");
    exit(EXIT_FAILURE);
  }

  while (1) {
    result = epoll_wait(epoll_fd, wait_event_arr, CLIENT_MAX_SIZE, -1);//阻塞
    if (result <= 0) {
      continue;
    }

    for (int i = 0; i < result; i++) {
      int fd = wait_event_arr[i].data.fd;
      struct sockaddr_in cli_addr;
      int len = sizeof(cli_addr);
      if (serv_fd == fd && EPOLLIN == wait_event_arr[i].events & EPOLLIN) {
        int cli_fd = accept(serv_fd, (struct sockaddr *) &cli_addr, (socklen_t *) &len);
        printf("Received connect from %s:%d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
        event.data.fd = cli_fd;
        event.events = EPOLLIN; //可读或错误
        result = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, cli_fd, &event);
        if (result == -1) {
          perror("EPOLL register fail");
          exit(EXIT_FAILURE);
        }
      }

      if ((wait_event_arr[i].events & EPOLLIN) || (wait_event_arr[i].events & EPOLLERR)) {
        //获取远端socket地址，
        getpeername(fd, (struct sockaddr *) &cli_addr, (socklen_t *) &len);
        memset(buffer, 0, sizeof(buffer));
        int n = read(fd, buffer, MAX);
        if (n == -1) {
          continue;
        } else if (n == 0) {
          close(fd);
          event.data.fd = fd;
          epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, &event);
          printf("Connection close from %s:%d\n",
                 inet_ntoa(cli_addr.sin_addr),
                 ntohs(cli_addr.sin_port));
        } else {
          printf("[%s:%d] Length:%d, Data:%s\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), n, buffer);
          send(fd, buffer, strlen(buffer), 0);
        }
      }
    }
  }

}
