//
//  scan2ban
//
//  Created by lfzyx on 15/10/29.
//  Copyright (c) 2015年 lfzyx. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_READ = 1024;

int main(int argc, const char * argv[])
{
    char line[MAX_READ];
    FILE *fp;
    
    if ((fp = fopen("/tmp/localhost_access_log.2015-09-22.txt","r"))==NULL)
    {
        fprintf(stderr, "Can't open the file \n");
        exit(1);
    }
    
    /**
     read string from open file , then get the IP address which cause 404. Note: the fgets will modify the file offset.
     **/
    while(fgets(line, MAX_READ, fp)>0)
    {
        char* temp = strstr(line, " 404 ");
        if(temp)
        {
            *(strchr(line, ' '))='\0';
            printf("%s\n",line);
            
        }
    }
    return 0;
}
