#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <linux/videodev2.h>
#include <linux/uvcvideo.h>
#include <linux/usb/video.h>

#include <sys/ioctl.h>

static void parse_result(int result) {
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <on|off>\n", argv[0]);
        return -1;
    }
    __u8 setbuffer[256] = {
        0x01, // bNumEntries
        0x03, // bEndpointAddress
        0b001 // bmControlFlags
    };
    if (strcmp(argv[1], "on") == 0) {
        setbuffer[0] = 0x01; // bNumEntries
        setbuffer[1] = 0x03; // bEndpointAddress
        setbuffer[2] = 0x00; // bmControlFlags
              // Bit0: Authentication Disabled
              // Bit1: Authentication Alternative Frame Illumination
              // Bit2: Authentication Background Subtraction
              // Bit3-55: Reserved, set to zero
              // above bit map doesn't really work on XinPro, seems only 0x01
              // disables alternative frame other values will enable it
    }

    struct uvc_xu_control_query set_query = {
        .unit = 10,
        .selector = 0x06,   // MSXU_CONTROL_FACE_AUTHENTICATION
        .query = UVC_SET_CUR,
        .size = 9,
        .data = (__u8*)&setbuffer,
    };

    int result = 0;
    int fd = open("/dev/video2", O_WRONLY);

    result = ioctl(fd, UVCIOC_CTRL_QUERY, &set_query);
    if (result < 0) {
        printf("Error code: %d, errno: %d, error: %s\n", result, errno, strerror(errno));
        switch(errno) {
           case ENOMEM:
                printf("Not enough memory to perform the operation.\n");
                break;
           case EPERM:
                printf("Insufficient privileges (super user privileges are required).\n");
                break;
           case EINVAL:
                printf("No such UVC control.\n");
                break;
           case EOVERFLOW:
                printf("The requested offset and size would overflow the UVC control.\n");
                break;
           case EEXIST:
                printf("Mapping already exists.\n");
                break;
        }
        return -1;
    }

    close(fd);
    return 0;
}
