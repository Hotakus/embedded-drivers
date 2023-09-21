//
// Created by hotakus on 9/15/23.
//

#ifndef HELLO_HELLO_H
#define HELLO_HELLO_H

#include "common_inc/imx6ull/common_inc.h"
#include "../common_inc/hello_typedefs.h"

typedef struct hello_handle_t {
    void (*init)(void);
    void (*exit)(void);



    void (*write)(const char *buf);
    struct hello_t * (*read)(void);
} hello_handle_t;


#endif //HELLO_HELLO_H
