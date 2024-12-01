#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include "digitRenderer/digitRenderer.h"

int main(int argc, char *argv[]) { 
    int fd; 
    int contrast; 
    if (argc != 2) { 
        fprintf(stderr, "Usage: %s <contrast_value>\n", argv[0]); 
        return 1; 
    } 
    contrast = atoi(argv[1]); 
    if (contrast < 0 || contrast > 255) { 
        fprintf(stderr, "Error: contrast value must be between 0 and 255.\n"); 
        return 1;
    }

	if ((fd = open("/dev/ssd1306temp", O_RDWR)) < 0){
        perror("open");
        return 1;
    }

	if (ioctl(fd, SET_INVERSE_IOCTL, &contrast) < 0){
        perror("contrast_ioctl");
        close(fd);
        return 1;
    }

	if (close(fd) != 0){
        perror("close");
        return 1;
    }

	return 0;
}
