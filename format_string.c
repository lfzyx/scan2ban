//
//  format_string.c
//  ipblack
//
//  Created by lfzyx on 15/7/22.
//  Copyright (c) 2015年 lfzyx. All rights reserved.
//

#include "format_string.h"
#include "mysql_prepare.h"
#include "mysql_execute.h"


const char *file = "/Users/lfzyx/Downloads/localhost_access_log.2015-07-22.txt";
const int MAX_READ = 1024;

MYSQL_BIND ip[1];
MYSQL_BIND count[2];
int rescount;
MYSQL_TIME ts;

int format_string()
{
    extern MYSQL *conn;
    extern MYSQL_STMT *insert_ip_time;
    extern MYSQL_STMT *update_ip_count;
    extern MYSQL_STMT *select_ip;
    extern MYSQL_STMT *update_weight_status;
    extern MYSQL_STMT *clean_ip_count;

    char *call = (char*)malloc(MAX_READ*sizeof(char));
    if (call == NULL )
    {
        printf("Out of memory");
        exit(0);
    }
    
    FILE *fp;
    if ((fp = fopen(file,"r"))==NULL)
    {
        printf("Can't open the file");
        exit(-1);
    }
    
    /**
     read string from fp , then get the IP address which cause 404 , store into database. Note: the fgets will modify the file offset.
     **/
    while(fgets(call, MAX_READ, fp)>0)
    {
        char* pos = strstr(call, " 404 ");
        if(pos)
        {
            *(strchr(call, ' '))='\0';

            memset(ip, 0, sizeof(ip));
            ip[0].buffer_type = MYSQL_TYPE_VAR_STRING;
            ip[0].buffer= (char *)call;
            ip[0].buffer_length= strlen(call);
            
            memset(count, 0, sizeof(count));
            count[0].buffer_type = MYSQL_TYPE_LONG;
            count[0].buffer= &rescount;
            count[1].buffer_type= MYSQL_TYPE_TIMESTAMP;
            count[1].buffer = &ts;
            
            mysql_execute();
        }

    }
    free(call);
    fclose(fp);
    mysql_stmt_close(insert_ip_time);
    mysql_stmt_close(update_ip_count);
    mysql_stmt_close(select_ip);
    mysql_stmt_close(update_weight_status);
    mysql_stmt_close(clean_ip_count);
    mysql_close(conn);
    printf("runtime=%lu\n", clock()/CLK_TCK);
    
    return 0;
}