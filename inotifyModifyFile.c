#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/inotify.h>
const size_t MAX_buff = sizeof(struct inotify_event)+4096;
int main(int argc, const char * argv[])
{
    int fd;
    uint32_t  modifyfile;
    char buffer[MAX_buff];
    ssize_t numRead;
    fd = inotify_init();
    modifyfile = inotify_add_watch(fd, "/usr/local/share/waukeen_new/logs/localhost_access_log/localhost_access_log.2015-07-20.txt",  IN_MODIFY);
    for(;;)
    {
        read(fd, buffer,MAX_buff);
        struct inotify_event *event = (struct inotify_event *) buffer;
        if (event->mask & IN_MODIFY)
        {
            printf("MODIFY file:localhost_access_log.2015-07-20.txt\n");
        }
    }
    
}