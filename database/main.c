#include <stdio.h>
#include <mysql.h>

void Create(MYSQL *conn) {
  if (mysql_query(conn, "create database if not exists d1")) {
    perror("create database fail");
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(EXIT_FAILURE);
  }
  if (mysql_query(conn, "create table if not exists d1.t1 (id int,name varchar(16))")) {
    perror("create table fail");
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(EXIT_FAILURE);
  }
}

void Insert(MYSQL *conn) {
  if (mysql_query(conn, "insert into d1.t1 values (1,'a'),(2,'b')")) {
    perror("insert table fail");
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(EXIT_FAILURE);
  }
}

void Result(MYSQL *conn) {
  mysql_query(conn, "SELECT * from d1.t1");
  MYSQL_RES *result;
  MYSQL_FIELD *field;
  MYSQL_ROW row = NULL;
  result = mysql_store_result(conn);
  int fieldCount = mysql_field_count(conn);

  while (field = mysql_fetch_field(result)) {
    printf("| ");
    printf("%s ", field->name);
  }
  printf("|\n");
  if (result) {
    while ((row = mysql_fetch_row(result)) != NULL) {
      for (int i = 0; i < fieldCount; i++) {
        printf("| ");
        printf("%s ", row[i]);
      }
      printf("|\n");
    }
  }

}

void Update(MYSQL *conn) {
  if (mysql_query(conn, "update d1.t1 set name = 'A' where id = 1")) {
    fprintf(stdout, "%s\n", mysql_error(conn));
  }
}

void Delete(MYSQL *conn) {
  if (mysql_query(conn, "delete from d1.t1 where id = 2")) {
    fprintf(stdout, "%s\n", mysql_error(conn));
  }
}

void Drop(MYSQL *conn) {
  if (mysql_query(conn, "drop database if exists d1")) {
    fprintf(stdout, "%s\n", mysql_error(conn));
  }
}
int main() {
  MYSQL conn;
  mysql_init(&conn);
  mysql_real_connect(&conn, "127.0.0.1", "root", "pass", NULL, 33060, NULL, 0);
  Drop(&conn);
  Create(&conn);
  Insert(&conn);
  Result(&conn);
  Update(&conn);
  Result(&conn);
  Delete(&conn);
  Result(&conn);
  return 0;
}
