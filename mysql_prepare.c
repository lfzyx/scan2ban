//
//  mysql_prepare.c
//  ipblack
//
//  Created by lfzyx on 15/7/22.
//  Copyright (c) 2015年 lfzyx. All rights reserved.
//

#include "mysql_prepare.h"


const char *UPDATEcount = "update list set count = count + 1 where ipaddress = ?";
const char *UPDATEweightstatuscountremove = "update list set weight = weight + 1, status = 1, count = 0, removetime = date_add(now(), interval weight*weight day) where ipaddress = ?";
const char *INSERTip = "INSERT INTO list (ipaddress,createtime,updatetime) VALUES (?,now(),now())";
const char *SELECTip = "SELECT count, updatetime from list where ipaddress = ?";
const char *CLEANcount = "update list set count = 0 where ipaddress = ?";



MYSQL_STMT *insert_ip_time;
MYSQL_STMT *update_ip_count;
MYSQL_STMT *select_ip;
MYSQL_STMT *update_weight_status;
MYSQL_STMT *clean_ip_count;

int mysql_prepare()
{
    extern MYSQL *conn;
    
    insert_ip_time = mysql_stmt_init(conn);
    update_ip_count = mysql_stmt_init(conn);
    select_ip = mysql_stmt_init(conn);
    update_weight_status = mysql_stmt_init(conn);
    clean_ip_count = mysql_stmt_init(conn);
    
    
    mysql_stmt_prepare(insert_ip_time, INSERTip, strlen(INSERTip));
    mysql_stmt_prepare(update_ip_count, UPDATEcount, strlen(UPDATEcount));
    mysql_stmt_prepare(select_ip, SELECTip, strlen(SELECTip));
    mysql_stmt_prepare(update_weight_status, UPDATEweightstatuscountremove, strlen(UPDATEweightstatuscountremove));
    mysql_stmt_prepare(clean_ip_count, CLEANcount, strlen(CLEANcount));
    return 0;
}

