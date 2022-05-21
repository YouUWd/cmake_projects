#define _GNU_SOURCE

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <pthread.h>
#include <errno.h>
#include "log.h"

#define DEFAULT_SERVER_PORT (3306)
#define DEFAULT_REMOTE_PORT (33050)
#define DEFAULT_SERVER_ADDR "0.0.0.0"
#define DEFAULT_REMOTE_ADDR "127.0.0.1"
#define PROXY_MODE_NORMAL (1)
#define PROXY_MODE_SPLICE (2)

static struct test_options {
    int verbose;
    int server_port;
    int remote_port;
    int mode;
    char server_addr[40];
    char remote_addr[40];
} test_options = {
        .verbose = 0,
        .server_port = DEFAULT_SERVER_PORT,
        .remote_port = DEFAULT_REMOTE_PORT,
        .mode = PROXY_MODE_NORMAL,
        .server_addr = DEFAULT_SERVER_ADDR,
        .remote_addr = DEFAULT_REMOTE_ADDR,
};

struct pair {
    int r_fd;
    int w_fd;
};

#ifdef __linux__
#define do_copy do_copy_splice
#else
#define do_copy do_copy_normal
#endif

#ifdef __linux__

static int do_copy_splice(int r_fd, int w_fd, char *buf, size_t buf_size, int pipe_fd[2]) {
    int bytes = splice(r_fd, NULL, pipe_fd[1], NULL, buf_size, SPLICE_F_NONBLOCK | SPLICE_F_MOVE);
    if (bytes <= 0) {
        if (bytes < 0) {
            //if no data or sigint, retry
            if (errno == EAGAIN || errno == EINTR) {
                return 1;
            }
            perror("splice:");
        }
        return 0;
    }
    bytes = splice(pipe_fd[0], NULL, w_fd, NULL, bytes, SPLICE_F_NONBLOCK | SPLICE_F_MOVE);
    if (bytes <= 0) {
        if (bytes < 0) {
            if (errno == EAGAIN || errno == EINTR) {
                return 1;
            }
            perror("splice out:");
        }
        return 0;
    }
    return bytes;
}

#endif

static int do_copy_normal(int r_fd, int w_fd, char *buf, size_t buf_size, int unused_pipe[2]) {
    int r_bytes, w_bytes;
    (void) unused_pipe;
    r_bytes = read(r_fd, buf, buf_size);
    if (r_bytes <= 0) {
        if (errno == EINTR) {
            return 1;
        }
        return 0;
    }
    if ((w_bytes = write(w_fd, buf, r_bytes)) != r_bytes) {
        perror("write:");
        r_bytes = w_bytes;
    }
    return r_bytes;
}


static void *proxy_packet(void *arg) {
    struct pair *p = arg;
    int r_fd = p->r_fd, w_fd = p->w_fd;
    int mode = test_options.mode;
    int bytes;
    int err = -1;
    char buf[65536];
    static size_t buf_size = sizeof(buf);
    char *_buf = buf;
    int pipe_fds[2];
    int (*copy)(int r_fd, int w_fd, char *buf, size_t buf_size, int pipe_fd[2]) = do_copy_normal;
    if ((mode & PROXY_MODE_SPLICE)) {
        if (do_copy == do_copy_normal) {
            log_debug(test_options.verbose, "current os not support splice, will use do_copy_normal...");
        } else {
            _buf = NULL;
            if (pipe(pipe_fds) < 0) {
                perror("pipe splice:");
                goto out_close;
            }
            assert(fcntl(pipe_fds[0], F_SETFL, O_NONBLOCK | O_CLOEXEC) == 0);
            assert(fcntl(pipe_fds[1], F_SETFL, O_NONBLOCK | O_CLOEXEC) == 0);
            copy = do_copy;
            log_debug(test_options.verbose, "do_copy_splice...");
        }
    }
    for (;;) {
        bytes = copy(r_fd, w_fd, _buf, buf_size, pipe_fds);
        if (bytes <= 0) {
            err = bytes;
            goto out_close;
        }
    }
    out_close:
    log_debug(test_options.verbose, "close...");
    close(r_fd);
    close(w_fd);
    return (void *) (long) err;
}

static int do_proxy(const char *host, int port, int r_fd) {
    pthread_t thread[2];
    struct pair pair[2];
    int i;
    int w_fd;
    int err = -1;
    struct sockaddr_in addr;
    int rcv_buf = 1 << 20;
    int snd_buf = 1 << 20;
    memset(&addr, 0, sizeof(addr));
    addr.sin_addr.s_addr = inet_addr(host);
    addr.sin_port = htons(port);
    addr.sin_family = PF_INET;
    w_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    assert(w_fd >= 0);

    assert(setsockopt(w_fd, SOL_SOCKET, SO_RCVBUF, &rcv_buf, sizeof(rcv_buf)) == 0);
    assert(setsockopt(w_fd, SOL_SOCKET, SO_SNDBUF, &snd_buf, sizeof(snd_buf)) == 0);
    assert(setsockopt(r_fd, SOL_SOCKET, SO_RCVBUF, &rcv_buf, sizeof(rcv_buf)) == 0);
    assert(setsockopt(r_fd, SOL_SOCKET, SO_SNDBUF, &snd_buf, sizeof(snd_buf)) == 0);

    if (connect(w_fd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        perror("connect:");
        goto out_close;
    }
    //connect success, we can start the conn/proxy_splice
    pair[0].r_fd = r_fd;
    pair[0].w_fd = w_fd;

    assert(pthread_create(&thread[0], NULL, proxy_packet, &pair[0]) == 0);
    pair[1].r_fd = w_fd;
    pair[1].w_fd = r_fd;

    assert(pthread_create(&thread[1], NULL, proxy_packet, &pair[1]) == 0);
    for (i = 0; i < sizeof(thread) / sizeof(thread[0]); ++i) {
        pthread_join(thread[i], NULL);
    }
    err = 0;
    out_close:
    close(r_fd);
    close(w_fd);
    return err;
}

static int do_server(const char *server_addr, const int port,
                     const char *proxy_addr, const int proxy_port) {
    struct sockaddr_in server;
    int fd_server, fd_client, opt = 1;
    memset(&server, 0, sizeof(server));
    server.sin_family = PF_INET;
    server.sin_addr.s_addr = inet_addr(server_addr);
    server.sin_port = htons(port);
    if ((fd_server = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        perror("socket:");
        exit(EXIT_FAILURE);
    }
    assert(setsockopt(fd_server, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == 0);
    printf("Server [%s] listening on [%d]\n", server_addr, port);
    if (bind(fd_server, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("bind:");
        exit(EXIT_FAILURE);
    }
    if (listen(fd_server, 5) < 0) {
        perror("listen:");
        exit(EXIT_FAILURE);
    }
    for (;;) {
        socklen_t len = sizeof(server);
        fd_client = accept(fd_server, (struct sockaddr *) &server, &len);
        if (fd_client < 0) {
            perror("accept:");
            continue;
        }
        if (!fork()) {//pid==0,子进程
            close(fd_server);
            log_debug(test_options.verbose, "close(fd_server)");
            exit(do_proxy(proxy_addr, proxy_port, fd_client));
        }
        log_debug(test_options.verbose, "close(fd_client)");
        close(fd_client);//parent continues;
    }

}

static void usage(const char *prog) {
    const char *p = strrchr(prog, '/');
    if (p)
        ++p;
    else
        p = prog;
    log_error("Usage: %s -s <server_addr> -p <server_port> "
              "-r <remote_addr> -c <remote port> -z | enable splice mode  -v | verbose -h | this help\n", p);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
    int c;
    opterr = 0;
    while ((c = getopt(argc, argv, "s:p:r:c:zvh")) != EOF) {
        switch (c) {
            case 's':
                test_options.server_addr[0] = 0;
                strncat(test_options.server_addr, optarg, sizeof(test_options.server_addr) - 1);
                break;
            case 'r':
                test_options.remote_addr[0] = 0;
                strncat(test_options.remote_addr, optarg, sizeof(test_options.remote_addr) - 1);
                break;
            case 'p':
                test_options.server_port = atoi(optarg);
                break;
            case 'c':
                test_options.remote_port = atoi(optarg);
                break;
            case 'v':
                test_options.verbose = 1;
                break;
            case 'z':
                test_options.mode = PROXY_MODE_SPLICE;
                break;
            case 'h':
            case '?':
            default:
                usage(argv[0]);
        }
    }

    if (optind != argc) {
        usage(argv[0]);
    }
    return do_server(test_options.server_addr, test_options.server_port,
                     test_options.remote_addr, test_options.remote_port);
}
