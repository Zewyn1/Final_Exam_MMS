#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

#define read_file NULL

int sum_file();

//read 4 byte integers from binary files which names are given in the command line, sum the integers and print the result, use pthreads to read the files and use the main process to print the result
int main(){
    int fd1, fd2, fd3, fd4, sum;
    char *filename1, *filename2, *filename3, *filename4;
    pthread_t thread1, thread2, thread3, thread4;

    filename1 = (char*)malloc(sizeof(char)*100);
    filename2 = (char*)malloc(sizeof(char)*100);
    filename3 = (char*)malloc(sizeof(char)*100);
    filename4 = (char*)malloc(sizeof(char)*100);

    filename1 = strcpy(filename1, "file1.bin");
    filename2 = strcpy(filename2, "file2.bin");
    filename3 = strcpy(filename3, "file3.bin");
    filename4 = strcpy(filename4, "file4.bin");

    fd1 = open(filename1, O_RDONLY);
    fd2 = open(filename2, O_RDONLY);
    fd3 = open(filename3, O_RDONLY);
    fd4 = open(filename4, O_RDONLY);

    pthread_create(&thread1, NULL, read_file, (void*)fd1);
    pthread_create(&thread2, NULL, read_file, (void*)fd2);
    pthread_create(&thread3, NULL, read_file, (void*)fd3);
    pthread_create(&thread4, NULL, read_file, (void*)fd4);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);

    sum = sum_file();
    printf("%d\n", sum);

    return 0;
}

int sum_file() {
    int fd, sum = 0;
    char *buffer;
    buffer = (char*)malloc(sizeof(char)*4);
    fd = open("file1.bin", O_RDONLY);
    read(fd, buffer, 4);
    sum += *(int*)buffer;
    close(fd);
    fd = open("file2.bin", O_RDONLY);
    read(fd, buffer, 4);
    sum += *(int*)buffer;
    close(fd);
    fd = open("file3.bin", O_RDONLY);
    read(fd, buffer, 4);
    sum += *(int*)buffer;
    close(fd);
    fd = open("file4.bin", O_RDONLY);
    read(fd, buffer, 4);
    sum += *(int*)buffer;
    close(fd);
    return sum;
}
