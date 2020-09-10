# cmake_projects
c语言的一些样例工程，基于cmake



## 单目录工程

sample1

```shell
# tree sample1
sample1
├── CMakeLists.txt
├── include
│   └── hello.h
└── src
    ├── CMakeLists.txt
    ├── hello.c
    └── tsar.c
```

## 多目录工程

sample2

```shell
# tree sample2
sample2
├── CMakeLists.txt
└── src
    ├── CMakeLists.txt
    ├── hello
    │   ├── CMakeLists.txt
    │   ├── hello.c
    │   └── hello.h
    ├── main.c
    └── world
        ├── CMakeLists.txt
        ├── world.c
        └── world.h
```



## 动态库和静态库的构建和使用

sample3

```shell
# tree sample3
sample3
├── CMakeLists.txt
├── include
├── src
│   ├── CMakeLists.txt
│   ├── hello
│   │   ├── hello.c
│   │   └── hello.h
│   └── world
│       ├── world.c
│       └── world.h
└── test
    ├── CMakeLists.txt
    └── test.c
```




# 参考文档
[参考](https://www.jianshu.com/p/8df5b2aba316)
