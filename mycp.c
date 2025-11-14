#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define NUM_ARGS 3
#define BUFF_SIZE 4096

int main(int argc, char *argv[])
{
    if (argc != NUM_ARGS) 
    {
        fprintf(stderr, "mycp requires exactly two arguments.\n");
        fprintf(stderr, "usage: mycp SOURCE DEST\n");
        return 1;
    }

    const char* source = argv[1];
    const char* dest = argv[2];

    int src_fd = open(source, O_RDONLY);
    if (src_fd < 0) {
        fprintf(stderr, "mycp: cannot open %s: %s\n", source, strerror(errno));
        return 1; 
    }

    int dest_fd = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd < 0) {
        fprintf(stderr, "mycp: cannot open %s: %s\n", dest, strerror(errno));
        close(src_fd);
        return 1; 
    }

    char buff[BUFF_SIZE];

    while (1) 
    {
        ssize_t n = read(src_fd, buff, BUFF_SIZE);
        
        if (n < 0) 
        {
            fprintf(stderr, "mycp: read error on %s: %s\n", source, strerror(errno));
            close(src_fd);
            close(dest_fd);
            return 1;
        }

        if (n == 0) break;  // EOF

        ssize_t written_bytes = write(dest_fd, buff, n);
        if (written_bytes != n)
        {
            fprintf(stderr, "mycp: write error on %s: %s\n", dest, strerror(errno));
            close(src_fd);
            close(dest_fd);
            return 1;
        }
    }

    close(src_fd);
    close(dest_fd);

    printf("mycp: successfully copied %s to %s\n", source, dest);
    return 0;
}
