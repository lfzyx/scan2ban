//
//  pthread_modify.c
//  ipblack
//
//  Created by lfzyx on 15/7/22.
//  Copyright (c) 2015年 lfzyx. All rights reserved.
//

#include "pthread_modify.h"
void *modify_file(void* args)
{
    while(1)
    {
        sleep(3);
        printf("THIS IS modify\n");
    }
}