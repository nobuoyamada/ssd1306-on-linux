#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>

#define SET_CONTRAST_IOCTL _IOW('d', 1, int)
#define SET_INVERSE_IOCTL _IOW('d', 2, int)
#define SHOW_TIME_IOCTL _IOW('d', 3, int)
#define CLEAR_DISPLAY_IOCTL _IOW('d', 4, int)

struct time_info { 
    int tm_year; 
    int tm_mon; 
    int tm_mday; 
    int tm_hour; 
    int tm_min; 
    int tm_sec;
};

struct time_info getCurrentTime(void){
    time_t current_time;
    struct tm *local_time;
    struct time_info time_kernel;

    time(&current_time);
    local_time = localtime(&current_time);

    time_kernel.tm_year = local_time->tm_year + 1900;
    time_kernel.tm_mon = local_time->tm_mon + 1;
    time_kernel.tm_mday = local_time->tm_mday;
    time_kernel.tm_hour = local_time->tm_hour;
    time_kernel.tm_min = local_time->tm_min;
    time_kernel.tm_sec = local_time->tm_sec;

    return time_kernel;
}
int main() {

    int fd;
    struct time_info time_kernel;
    int value;
    char buffer[10];

	if ((fd = open("/dev/ssd1306temp", O_RDWR)) < 0){
        perror("open");
        return 1;
    }
    // printf("fd opend\n");

    while(1) {
        lseek(fd, 0, SEEK_SET);
        read(fd, buffer, sizeof(buffer)-1);
        value = atoi(buffer);
        // printf("value: %d\n",value);
        if(value==1){
            time_kernel = getCurrentTime();
            if (ioctl(fd, SHOW_TIME_IOCTL, &time_kernel) < 0) {
                perror("time_ioctl");
                close(fd);
                return 1;
            }
        }
        else if(value==2){
            break;
        }
        else{
            if (ioctl(fd, CLEAR_DISPLAY_IOCTL, &time_kernel) < 0) {
                perror("time_ioctl");
                close(fd);
                return 1;
            }            
        }
        //printf("ioctl executed %d times\n", i + 1);
        usleep(100000); // 1秒待機
    }

	if (close(fd) != 0){
        perror("close");
        return 1;
    }

	return 0;
}