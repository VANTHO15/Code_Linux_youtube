#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// FIFO file path
#define FIFO_FILE   "./myfifo"
#define BUFF_SIZE   1024

int main(int argc, char const *argv[])
{   
    char buff[BUFF_SIZE];
    int fd;

    // mkfifo(<pathname>, <permission>)
    mkfifo(FIFO_FILE, 0666);


    while (1) {
        // Write first
        printf("Message to comsumer : "); fflush(stdin);       
        fgets(buff, BUFF_SIZE, stdin);

        fd = open(FIFO_FILE, O_WRONLY);
        write(fd, buff, strlen(buff) +1);
        close(fd);

    }


    return 0;
}
