#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>


#ifdef __linux__
#define do_copy spliced_copy
#else
#define do_copy std_copy
#endif

/*
 * Read from in and write to out without using user space buffers.
 * Directly splice using the pipe buffer.
 */
#ifdef __linux__

static int spliced_copy(int in_fd, int out_fd) {
    printf("spliced_copy...\n");

    int pipe_fd[2];
    pipe(pipe_fd);

    int err = -1;
    int bytes;
    while ((bytes = splice(in_fd, NULL, pipe_fd[1], NULL,
                           32768, SPLICE_F_MORE | SPLICE_F_MOVE)) > 0) {
        if (splice(pipe_fd[0], NULL, out_fd, NULL,
                   bytes, SPLICE_F_MORE | SPLICE_F_MOVE) != bytes) {
            perror("write:");
            goto out;
        }
    }
    printf("read bytes %d\n", bytes);
    err = 0;
    out:
    return err;
}

#else

static int std_copy(int in_fd, int out_fd) {
    printf("std_copy...\n");

    char buf[1024];

    int err = -1;
    int bytes;
    while ((bytes = read(in_fd, buf, sizeof(buf))) > 0) {
        if (write(out_fd, buf, bytes) != bytes) {
            perror("write:");
            goto out;
        }
    }
    printf("read bytes %d\n", bytes);
    err = 0;
    out:
    return err;
}

#endif

int main() {

    const char *ip = "0.0.0.0";
    int port = 8080;

    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    inet_pton(AF_INET, ip, &address.sin_addr);

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    int reuse = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    int ret = bind(sock, (struct sockaddr *) &address, sizeof(address));
    assert(ret != -1);

    ret = listen(sock, 5);
    assert(ret != -1);
    printf("Server Listening %s:%d\n", ip, port);

    struct sockaddr_in client;
    socklen_t cl = sizeof(client);

    int fd = accept(sock, (struct sockaddr *) &client, &cl);
    if (fd < 0) {
        printf("errno is: %s\n", strerror(errno));
    } else {
        do_copy(fd, fd);
        close(fd);
    }

    close(sock);

    return 0;
}