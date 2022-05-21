#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include<sys/ioctl.h>

#define WR_VALUE _IOW(10,0x01,int32_t *)
#define RD_VALUE _IOR(10,0x02,int32_t *)

int main() {
    int fd;
    int32_t value = 0, number = 0;
    printf("*********************************\n");
    printf("\nOpening Driver\n");
    fd = open("/dev/urandom", O_RDWR);
    if (fd < 0) {
        printf("Cannot open device file...\n");
        return 0;
    }

    number = 8;
    printf("Writing Value %d to Driver %d\n", number, value);
    int ret = ioctl(fd, WR_VALUE, &number);
    printf("write ret %d\n", ret);
    perror("write fail");

    printf("Reading Value from Driver\n");
    ret = ioctl(fd, RD_VALUE, &value);
    printf("read ret %d\n", ret);
    perror("read fail");
    printf("Value is %d\n", value);

    printf("Closing Driver\n");
    close(fd);
}