#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>

#define MAX 1024
#define CLIENT_MAX_SIZE 128
#define PORT 8080
/*
 * epoll_create() 创建epoll监听socket
 * epoll_ctl()注册,删除,修改监听
 * epoll_wait() 等待事件触发函数
 *
 * ET(edge-trigger) 边缘触发
 * 通过注册监听增加EPOLLET参数可将模式转换成边缘触发,
 * 在et模式下,socket触发的多个事件只会返回一次,必须一次性全部处理,例如:
 * server_socket 有10个待处理的新连接,在epoll_wait函数返回后,必须循环读取accept直到没有数据可读
 * 由于必须一直循环读取,所以当accept没有数据可读时,必须是非阻塞模式,否则会阻塞
 */

/*
 * 由于必须一直循环读取,所以当accept没有数据可读时,必须是非阻塞模式,否则会阻塞
 */
int set_non_block(int socket) {
  int flags = fcntl(socket, F_GETFL, 0);
  flags |= O_NONBLOCK;
  return fcntl(socket, F_SETFL, flags);
}

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
  set_non_block(serv_fd);

  struct epoll_event event;
  struct epoll_event wait_event_arr[CLIENT_MAX_SIZE];
  int epoll_fd = epoll_create(10);//创建epoll句柄,里面的参数10没有意义

  if (epoll_fd == -1) {
    perror("Create EPOLL FD FAIL");
    exit(EXIT_FAILURE);
  }

  event.events = EPOLLIN | EPOLLET; //注册可读事件 + ET模式
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
        while (1) {
          int cli_fd = accept(serv_fd, (struct sockaddr *) &cli_addr, (socklen_t *) &len);
          if (cli_fd == -1) {
            break;
          }
          printf("Received connect from %s:%d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
          event.data.fd = cli_fd;
          event.events = EPOLLIN | EPOLLET; //可读或错误 + ET模式
          result = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, cli_fd, &event);
          if (result == -1) {
            perror("EPOLL register fail");
            exit(EXIT_FAILURE);
          }
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
