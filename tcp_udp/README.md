## TCP UDP SERVER

### TCP

#### 单客户端简单实现

* server.c
* tcp_server.c

#### 多客户端实现

##### 多进程(fork)

* sever_muti_fork.c

##### 非阻塞(fcntl)

* sever_muti_nblock.c

##### SELECT 机制

* sever_muti_select.c

##### EPOLL 机制(Linux Only)

* sever_muti_epoll_lt.c
* sever_muti_epoll_et.c

##### Kqueue 机制(macOS Only)

* sever_muti_kqueue.c

#### TCP Proxy (socket transfer and splice with zero copy)

* tcp_proxy.c
* sever_muti_select_splice.c (select splice 会导致400ms左右的select延迟，未找到原因)

### Zero Copy In C

> 想要使用Linux下的splice函数，想要在文件头加上 #define _GNU_SOURCE

* [Zero Copy](https://www.linuxjournal.com/article/6345)
* [Zero Copy VS IP Forward](https://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.34.9915&rep=rep1&type=pdf)
* [sockmap-tcp-splicing-of-the-future](https://blog.cloudflare.com/sockmap-tcp-splicing-of-the-future/)

### 在docker 上进行 idea remote调试

> 某些场景下，有些lib仅仅是Linux支持的，需要在Linux上运行或者debug，通过调整图中的ToolChains，可以选择在不同的环境下运行调试

#### 支持gcc，rsync等指令的docker创建

[创建测试容器](https://blog.jetbrains.com/clion/2020/01/using-docker-with-clion/#getting-docker)

```shell
 docker build -t clion/remote-c-env:1.1 -f Dockerfile .
 docker run -it -d --cap-add sys_ptrace -p127.0.0.1:2222:22 -p127.0.0.1:8088:8080 --name clion_remote_env clion/remote-c-env:1.1
 ssh-keygen -f "$HOME/.ssh/known_hosts" -R "[localhost]:2222"
 ssh-keygen -f "$HOME/.ssh/known_hosts" -R "[127.0.0.1]:2222"
```

#### 配置CLion Remote Env

[CLion Remote Run/Debug](https://www.jetbrains.com/help/clion/remote-projects-support.html#WorkWithRemote)
![toolchain](./images/toolchain.png)
![cmake](./images/cmake.png)
