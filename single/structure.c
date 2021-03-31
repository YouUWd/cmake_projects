
#include <stdio.h>
#include <string.h>
struct Book {
  int id;
  char name[128];

} book = {1, "ABC"};

struct S1 {
  int id;
  char name[128];
};

struct {
  int id;
  char name[128];
} s1;

struct S2 {
} s2;

struct S1 t1, t2[2], *t3;

typedef struct {
  int id;
  char name[128];
} s3;

s3 u1, u2, *u3;

struct Complex {
  char string[100];
  struct S1 s1;
};
//========================链表========================
struct Node {
  char string[100];
  struct Node *next_node;
};
//=====================相互持有变量=====================
struct B;    //对结构体B进行不完整声明

//结构体A中包含指向结构体B的指针
struct A {
  struct B *partner;
  //other members;
};

//结构体B中包含指向结构体A的指针，在A声明完后，B也随之进行声明
struct B {
  struct A *partner;
  //other members;
};

struct Message {
  int seq: 2;
  int id: 4;
  unsigned int length: 8;
  char data[128];
};

void printBookStruct(struct Book book);
void printBookStruct(struct Book book) {
  printf("Book id : %d\n", book.id);
  printf("Book name : %s\n", book.name);
}
void printBook(struct Book *book);
void printBook(struct Book *book) {
  printf("Book id : %d\n", book->id);
  printf("Book name : %s\n", book->name);
}

int main(void) {
  printBookStruct(book);
  printBook(&book);

  printf("==========================\n");
  struct Book book;
  book.id = 2;
  strcpy(book.name, "C Program");
  printBookStruct(book);
  printBook(&book);
  printf("==========================\n");

  struct Book *p = &book;
  printBook(&book);
  printBook(p);
  printf("==========================\n");
  printf("Book %d %s\n", p->id, p->name);
  printf("Book %d %s\n", book.id, book.name);
  printf("==========================\n");
  struct Message message;

  for (int i = 0; i < 32; ++i) {
    message.seq = i;
    message.id = i;
    message.length = i;
    strcpy(message.data, "OK");
    printf("%d,%d,%d,%s\n", message.seq, message.id, message.length, message.data);
  }
  printf("==========================\n");
  message.seq = 0;
  message.id = 1;
  message.length = 2;
  strcpy(message.data, "OK");
  printf("%d,%d,%d,%s\n", message.seq, message.id, message.length, message.data);

  struct Message *pt = &message;
  pt->seq = 1;
  pt->id &= 3;
  pt->length |= 1;
  printf("%d,%d,%d,%s\n", message.seq, message.id, message.length, message.data);

  s3 s_3;
  s_3.id = 1;
  strcpy(s_3.name, "Jack");
  printf("S3 %d %s\n", s_3.id, s_3.name);
  return 0;
}