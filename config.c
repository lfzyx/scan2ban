//
//  config.c
//  ipblack
//
//  Created by lfzyx on 15/7/27.
//  Copyright (c) 2015年 lfzyx. All rights reserved.
//

#include "config.h"

const int MAX_REA = 1024;

char * readconfig( char const * configFile, char const * item)
{
    
    char buffer[MAX_REA] = {0};
    char *dest, *result;
    dest = (char*)malloc(MAX_REA*sizeof(char));
    if (dest == NULL )
    {
        printf("Out of memory");
        exit(0);
    }
    result = (char*)malloc(MAX_REA*sizeof(char));
    if (result == NULL )
    {
        printf("Out of memory");
        exit(0);
    }
    
    FILE * fp;
    if((fp = fopen(configFile, "r")) == NULL)
    {
        printf("Error! fopen configFile Error!\n");
        exit(-1);
    }

    while(fgets(buffer, MAX_REA, fp ) >0 )
    {
        buffer[strlen(buffer)-1] = '\0';
        if ( strncmp(item, buffer, strlen(item)) == 0 )
        {
            dest = strchr(buffer, ' ')+1;
            break;
        }
    }
    strncpy(result, dest, strlen(dest));
    return result;
}