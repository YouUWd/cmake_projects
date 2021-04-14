#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/event.h>

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

  int kq = kqueue();
  struct kevent change_event[4], event[4];
  // Create event 'filter', these are the events we want to monitor.
  // Here we want to monitor: socket_listen_fd, for the events: EVFILT_READ  (when there is data to be read on the socket),
  // and perform the following actions on this kevent: EV_ADD and EV_ENABLE (add the event to the kqueue and enable it).
  EV_SET(change_event, serv_fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, 0);
  if (kevent(kq, change_event, 1, NULL, 0, NULL) == -1) {
    perror("kevent fail");
    exit(EXIT_FAILURE);
  }

  while (1) {
    // Check for new events, but do not register new events with the kqueue.
    // Hence the 2nd and 3rd arguments are NULL, 0.
    // Only handle 1 new event per iteration in the loop; 5th argument is 1.
    int active = kevent(kq, NULL, 0, event, 1, NULL);
    if (active == -1) {
      perror("kevent active fail");
      exit(EXIT_FAILURE);
    }
    for (int i = 0; i < active + 1; i++) {

      struct kevent ke = event[i];
      int fd = ke.ident;
      struct sockaddr_in cli_addr;
      int len = sizeof(cli_addr);

      if (fd == serv_fd) {
        int cli_fd = accept(serv_fd, (struct sockaddr *) &cli_addr, (socklen_t *) &len);
        printf("Received connect from %s:%d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
        EV_SET(change_event, cli_fd, EVFILT_READ, EV_ADD, 0, 0, NULL);
        int active = kevent(kq, change_event, 1, NULL, 0, NULL);
        if (active == -1) {
          perror("kevent change fail");
          exit(EXIT_FAILURE);
        }
      } else if (ke.flags & EV_EOF) {
        getpeername(fd, (struct sockaddr *) &cli_addr, (socklen_t *) &len);
        close(fd);
        printf("Connection close[EV_EOF] from %s:%d\n",
               inet_ntoa(cli_addr.sin_addr),
               ntohs(cli_addr.sin_port));
      } else if (ke.filter & EVFILT_READ) {
        //获取远端socket地址，
        getpeername(fd, (struct sockaddr *) &cli_addr, (socklen_t *) &len);
        memset(buffer, 0, sizeof(buffer));
        int n = read(fd, buffer, MAX);
        if (n == 0) {
          // 注册EV_EOF事件 或者直接close，二选一
          EV_SET(change_event, fd, EVFILT_READ, EV_EOF, 0, 0, NULL);
//          close(fd);
//          printf("Connection close[0] from %s:%d\n",
//                 inet_ntoa(cli_addr.sin_addr),
//                 ntohs(cli_addr.sin_port));
        } else {
          printf("[%s:%d] Length:%d, Data:%s\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), n, buffer);
          send(fd, buffer, strlen(buffer), 0);
        }
      }
    }
    // After chatting close the socket
  }

}
