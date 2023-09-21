//
// Created by hotakus on 9/21/23.
//

#ifndef HELLO_MODULE_IOCTL_CMDS_H
#define HELLO_MODULE_IOCTL_CMDS_H

#include <linux/ioctl.h>

#define HELLO_IOCTL_TYPE            'c'
#define HELLO_IOCTL_CMD_INIT        _IO(HELLO_IOCTL_TYPE, 0)
#define HELLO_IOCTL_CMD_GREET       _IOW(HELLO_IOCTL_TYPE, 1, int)

#endif //HELLO_MODULE_IOCTL_CMDS_H
