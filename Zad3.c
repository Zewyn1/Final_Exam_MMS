#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
//input N and M signed ints, from the following N lines read input ROW char string, the line number and M amount of ints separated by spaces, in the last row input a file name to write the output
 int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    char *row;
    row = (char *) malloc(sizeof(char) * N);
    int *col;
    col = (int *) malloc(sizeof(int) * M);
    int i, j;
    for (i = 0; i < N; i++) {
        scanf("%s", row);
        for (j = 0; j < M; j++) {
            scanf("%d", &col[j]);
        }
        printf("%s\n", row);
        for (j = 0; j < M; j++) {
            printf("%d ", col[j]);
        }
        printf("\n");
    }
    char *file;
    file = (char *) malloc(sizeof(char) * N);
    scanf("%s", file);
    int fd;
    fd = open(file, O_WRONLY | O_CREAT, 0644);
    write(fd, row, N);
    write(fd, col, M);
    close(fd);
    free(row);
    free(col);
    return 0;
}
