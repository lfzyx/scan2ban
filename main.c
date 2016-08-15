//
//  ipblack
//
//  Created by lfzyx on 15/5/29.
//  Copyright (c) 2015年 lfzyx. All rights reserved.
//

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "pthread_creat.h"
#include "pthread_modify.h"
#include "mysql_connector.h"
#include "mysql_prepare.h"
#include "format_string.h"
#include "mysql_execute.h"


int main(int argc, const char * argv[])
{
    pthread_t pid1, pid2;
    pthread_create(&pid1, NULL, &modify_file, NULL);
    pthread_create(&pid2, NULL, &creat_file, NULL);
    mysql_connector();
    mysql_prepare();
    format_string();
    //pthread_join(pid1, NULL);
    //pthread_join(pid2, NULL);
    int n= 0;
    while (1)
    {
        
        sleep(2);
        n++;
        printf("n=%d\n",n);
        if (n>2)
        {
            pthread_cancel(pid1);
        }
    }
    
    return 0;
}