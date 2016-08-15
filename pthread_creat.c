//
//  pthread_creat.c
//  ipblack
//
//  Created by lfzyx on 15/7/22.
//  Copyright (c) 2015年 lfzyx. All rights reserved.
//

#include "pthread_creat.h"

void *creat_file(void* args)
{
    while(1)
    {
        sleep(5);
        printf("THIS IS creat\n");
    }
}