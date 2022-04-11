#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
 int main() {
  int fd[4];
  int sum[4];
  int i,j;
  for(i=0;i<4;i++)
  {
    fd[i]=open("file",O_RDONLY);
    read(fd[i],&sum[i],4);
  }
  for(i=0;i<4;i++)
  {
    close(fd[i]);
  }
  for(i=0;i<4;i++)
  {
    for(j=i+1;j<4;j++)
    {
      sum[i]+=sum[j];
    }
  }
  printf("%d\n",sum[0]);
  return 0;
}
