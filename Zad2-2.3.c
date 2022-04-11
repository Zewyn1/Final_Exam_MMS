#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <omp.h>
int main(){
    int sum = 0;
    int fd[4];
    int i;
    int num;
    char *filename[4] = {"file1.bin", "file2.bin", "file3.bin", "file4.bin"};
    for(i = 0; i < 4; i++){
        fd[i] = open(filename[i], O_RDONLY);
        if(fd[i] == -1){
            printf("Error opening file %s\n", filename[i]);
            exit(1);
        }
    }
    #pragma omp parallel for private(num)
    for(i = 0; i < 4; i++){
        read(fd[i], &num, sizeof(int));
        sum += num;
    }
    printf("Sum: %d\n", sum);
    return 0;
}
