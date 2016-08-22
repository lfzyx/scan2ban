#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/inotify.h>
const size_t MAX_buff = sizeof(struct inotify_event)+4096;
int main(int argc, const char * argv[])
{
    int fd;
    uint32_t  creatfile;
    char buffer[MAX_buff];
    ssize_t numRead;
    fd = inotify_init();
    creatfile = inotify_add_watch(fd, "/usr/local/share/waukeen_new/logs/localhost_access_log", IN_CREATE | IN_ONLYDIR);
    for(;;)
    {
        read(fd, buffer,MAX_buff);
        struct inotify_event *event = (struct inotify_event *) buffer;
        if (event->mask & IN_CREATE)
        {
            printf("CREATEfile:%s\n",event->name);
        }
    }
    
}