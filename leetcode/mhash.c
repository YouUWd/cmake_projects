#include <stdio.h>
#include <stdlib.h>
#include <libc.h>

struct node {
    int k, v;
    struct node *next;
};

struct map {
    int size;
    struct node *data;
};

void put(struct map m, int k, int v) {
    int idx = k % m.size;
    struct node n = m.data[idx];
    struct node *p = n.next;
    while (p != NULL) {
        p = &n.next;
    }
    n.k = k;
    n.v = v;
}


int main() {
    struct node n;
    n.k = 1;
    n.v = 2;
    struct node n1;
    n1.k = 3;
    n1.v = 4;
    n.next = &n1;
    printf("%d %d\n", n.k, n.v);
    printf("%d %d\n", n.next->k, n.next->v);


    struct map m;
    m.size = 10;
    m.data = malloc(sizeof(struct node) * m.size);
    for (int i = 0; i < m.size; ++i) {
        m.data[i].next = NULL;
    }
    put(m, 1, 2);
    put(m, 1, 2);

    return 0;
}