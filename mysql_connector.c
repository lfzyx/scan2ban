//
//  mysql_connector.c
//  ipblack
//
//  Created by lfzyx on 15/7/22.
//  Copyright (c) 2015年 lfzyx. All rights reserved.
//


#include "mysql_connector.h"
#include "config.h"

MYSQL *conn=NULL;

int mysql_connector()
{
    const char *mysql_connector_path = "/Users/lfzyx/ipblack/config/mysql_connector.conf";
    const char *host = readconfig(mysql_connector_path, "host");
    const char *database = readconfig(mysql_connector_path, "database");
    const char *username = readconfig(mysql_connector_path, "username");
    const char *passwd = readconfig(mysql_connector_path, "passwd");

    
    if((conn = mysql_init(NULL))==NULL)
    {
        printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        exit(1);
    }
    if (mysql_real_connect(conn, host, username, passwd, database, 0, 0 ,0)==NULL)
    {
        printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        exit(1);
    }
    
    return 0;

}