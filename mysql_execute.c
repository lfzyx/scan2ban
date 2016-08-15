//
//  mysql_execute.c
//  ipblack
//
//  Created by lfzyx on 15/7/24.
//  Copyright (c) 2015年 lfzyx. All rights reserved.
//

#include "mysql_execute.h"

int mysql_execute()
{
    extern MYSQL_STMT *insert_ip_time;
    extern MYSQL_STMT *update_ip_count;
    extern MYSQL_STMT *select_ip;
    extern MYSQL_STMT *update_weight_status;
    extern MYSQL_STMT *clean_ip_count;
    extern MYSQL_BIND ip[1];
    extern MYSQL_BIND count[2];
    extern int rescount;
    extern MYSQL_TIME ts;

    /**
     bind input data for the parameter markers in the SQL statement
     **/
    mysql_stmt_bind_param(insert_ip_time, ip);
    mysql_stmt_bind_param(update_ip_count, ip);
    mysql_stmt_bind_param(update_weight_status, ip);
    mysql_stmt_bind_param(select_ip, ip);
    mysql_stmt_bind_param(clean_ip_count, ip);
    mysql_stmt_bind_result(select_ip, count);
    
    
    if (mysql_stmt_execute(select_ip))
    {
        fprintf(stderr, " %s\n", mysql_stmt_error(select_ip));
        fprintf(stderr, " mysql_stmt_execute(), failed\n");
        exit(0);
    }
    
    if (mysql_stmt_store_result(select_ip))
    {
        fprintf(stderr, " mysql_stmt_store_result() failed/n");
        fprintf(stderr, " %s\n", mysql_stmt_error(select_ip));
        exit(0);
    }
    
    /**
     Determine whether there is IP in result, if not ,execute insert IP.
     **/
    if  (mysql_stmt_num_rows(select_ip))
    {
        mysql_stmt_fetch(select_ip);
        
        struct tm *mysql_time = localtime(&(time_t){time(NULL)});
        
        mysql_time->tm_year = ts.year-1900;
        mysql_time->tm_mon = ts.month-1;
        mysql_time->tm_mday= ts.day;
        mysql_time->tm_hour = ts.hour;
        mysql_time->tm_min = ts.minute;
        mysql_time->tm_sec = ts.second;
        
        /**
         Count of the IP more than 5, and time interval less than 60s, will update weight, else clean the count of the ip.
         Count of the IP less than 5, and time interval less than 60s, will update count, else clean the count of the ip.
         **/
        if(rescount>=5 )
        {
            if(time(NULL)-mktime(mysql_time)<60)
            {
                mysql_stmt_execute(update_weight_status);
            }
            else
            {
                mysql_stmt_execute(clean_ip_count);
                mysql_stmt_execute(update_ip_count);
            }
        }
        else
        {
            if (time(NULL)-mktime(mysql_time)<60)
            {
                mysql_stmt_execute(update_ip_count);
            }
            else
            {
                mysql_stmt_execute(clean_ip_count);
                mysql_stmt_execute(update_ip_count);
            }
        }
    }
    else
    {
        mysql_stmt_execute(insert_ip_time);
    }
    
    mysql_stmt_free_result(insert_ip_time);
    mysql_stmt_free_result(update_ip_count);
    mysql_stmt_free_result(select_ip);
    mysql_stmt_free_result(update_weight_status);
    
    return 0;
}