#define _GNU_SOURCE

#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define MAX 1024
#define PORT 6606
#define RS_ADDRESS "127.0.0.1"
#define RS_PORT 3306

#ifdef __linux__
#define proxy proxy_splice
#else
#define proxy proxy_socket
#endif

#ifdef __linux__
// Function forward to target.
void proxy_splice(int fd) {
    char buff[MAX];

    // remote client
    struct sockaddr_in _target;
    _target.sin_family = AF_INET;
    _target.sin_addr.s_addr = inet_addr(RS_ADDRESS);
    _target.sin_port = htons(RS_PORT);
    int fd_proxy = socket(PF_INET, SOCK_STREAM, 0);
    if (fd_proxy == -1) {
        perror("Proxy socket creation failed...");
        exit(0);
    } else {
        printf("Proxy socket successfully created..\n");
    }

    if (connect(fd_proxy, (struct sockaddr *) &_target, sizeof(struct sockaddr)) != 0) {
        perror("Proxy connect fail");
        return;
    }

    fd_set readers, copy_readers;
    FD_ZERO(&readers);
    FD_SET(fd, &readers);
    FD_SET(fd_proxy, &readers);

    int fd_max, fd_number;
    fd_max = fd > fd_proxy ? fd : fd_proxy;

    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    int pipe_fd[2];
    pipe(pipe_fd);

    int ret;
    while (1) {
        copy_readers = readers;
        fd_number = select(fd_max + 1, &copy_readers, NULL, NULL, &timeout);
        if (fd_number < 0)
            perror("select fail");
        if (fd_number == 0)
            continue;
        bzero(buff, MAX);
        if (FD_ISSET(fd, &copy_readers)) {
            ret = splice(fd, NULL, pipe_fd[1], NULL,
                         32768, SPLICE_F_MORE | SPLICE_F_MOVE);

            if (ret == 0) {
                close(fd);
                break;
            }

            ret = splice(pipe_fd[0], NULL, fd_proxy, NULL,
                         32768, SPLICE_F_MORE | SPLICE_F_MOVE);
            if (ret == 0) {
                close(fd_proxy);
                break;
            }

        }
        if (FD_ISSET(fd_proxy, &copy_readers)) {

            ret = splice(fd_proxy, NULL, pipe_fd[1], NULL,
                         32768, SPLICE_F_MORE | SPLICE_F_MOVE);
            if (ret == 0) {
                close(fd_proxy);
                break;
            }
            ret = splice(pipe_fd[0], NULL, fd, NULL,
                         32768, SPLICE_F_MORE | SPLICE_F_MOVE);
            if (ret == 0) {
                close(fd);
                break;
            }
        }
    }
}

#else

// Function forward to target by recv and send.
void proxy_socket(int fd) {
    char buff[MAX];

    // remote client
    struct sockaddr_in _target;
    _target.sin_family = AF_INET;
    _target.sin_addr.s_addr = inet_addr(RS_ADDRESS);
    _target.sin_port = htons(RS_PORT);
    int fd_proxy = socket(PF_INET, SOCK_STREAM, 0);
    if (fd_proxy == -1) {
        perror("Proxy socket creation failed...");
        exit(0);
    } else {
        printf("Proxy socket successfully created..\n");
    }

    if (connect(fd_proxy, (struct sockaddr *) &_target, sizeof(struct sockaddr)) != 0) {
        perror("Proxy connect fail");
        return;
    }

    fd_set readers, copy_readers;
    FD_ZERO(&readers);
    FD_SET(fd, &readers);
    FD_SET(fd_proxy, &readers);

    int fd_max, fd_number;
    fd_max = fd > fd_proxy ? fd : fd_proxy;

    struct timeval now;

    while (1) {
        copy_readers = readers;
        fd_number = select(fd_max + 1, &copy_readers, NULL, NULL, NULL);
        if (fd_number < 0)
            perror("select fail");
        if (fd_number == 0)
            continue;
        bzero(buff, MAX);
        if (FD_ISSET(fd, &copy_readers)) {
            int count = recv(fd, buff, MAX, 0);
            if (count == 0) {
                printf("close by client...");
                exit(1);
            }
            send(fd_proxy, buff, count, 0);
        }
        if (FD_ISSET(fd_proxy, &copy_readers)) {
            int count = recv(fd_proxy, buff, MAX, 0);
            if (count == 0) {
                printf("close by proxy_splice...");
                exit(1);
            }
            send(fd, buff, count, 0);
        }
    }
}

#endif

int main() {
    int serv_fd, cli_fd, len;
    struct sockaddr_in serv_addr, cli_addr;
    int opt = 1;


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
            proxy(cli_fd);
        }

        // After chatting close the socket
    }


}
