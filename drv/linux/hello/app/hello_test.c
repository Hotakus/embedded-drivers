//
// Created by hotakus on 9/18/23.
//

#include "hello_test.h"
#include "hello_typedefs.h"
#include "ioctl_cmds.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <malloc.h>

int main(int argc, char **argv) {

    if (argc != 3) {
        printf("Parameter is wrong.\n");
        return -1;
    }

    char *dev_path = argv[1];
    char *dev_opt  = argv[2];
    char status = (strcmp(dev_opt, "on") == 0) ? 1 : 0;

    printf("Hello world\n");
    printf("Hello world\n");

    int fd = open(dev_path, O_RDWR);
    if (fd < 0) {
        printf("open %s error\n", dev_path);
        return -1;
    }

    hello_t ht;
    ht.age = 20;
    strcpy(ht.gender, "male");

    int res = ioctl(fd, HELLO_IOCTL_CMD_GREET, &ht);
    if (res) {
        printf("ioctl error\n");
        exit(-1);
    }

    while(1) {
        write(fd, &status, 1);
        status = !status;
        sleep(1);
    }


    close(fd);

    return 0;
}

