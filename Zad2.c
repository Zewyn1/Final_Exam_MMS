#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

//read 4 byte integers from binary files which names are given in the command line, sum the integers and print the result, use different processes to read the files and use the parent process to print the result
int main(int argc, char *argv[])
{
    int i, sum = 0, fd, n;
    char buf[4];
    if (argc < 2)
    {
        printf("Usage: %s file1 file2 file3 ...\n", argv[0]);
        exit(1);
    }
    for (i = 1; i < argc; i++)
    {
        fd = open(argv[i], O_RDONLY);
        if (fd == -1)
        {
            perror("open");
            exit(1);
        }
        while ((n = read(fd, buf, 4)) > 0)
        {
            sum += *(int *)buf;
        }
        close(fd);
    }
    printf("sum = %d\n", sum);
    return 0;
}
