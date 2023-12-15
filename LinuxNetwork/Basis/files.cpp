#include <sys/types.h> //定义了一些基本数据类型 size_t,time_t
#include <sys/stat.h>  //这个头文件定义了文件状态的结构体和一些与文件状态相关的常量
#include <fcntl.h>     //File Control
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// int open(const char *path, int flags);
// 以_t结尾的数据类型->元数据类型(primitive)
void error_handling(const char *message);
int main(void)
{
    int fd;
    char buf[] = "Let's go!\n";
    fd = open("data.txt", O_CREAT | O_WRONLY | O_TRUNC);

    if (fd == -1)
        error_handling("open() error!");
    printf("file descriptor: %d \n", fd);

    if (write(fd, buf, sizeof(buf)) == -1)
        error_handling("write() error!");
    close(fd);
    return 0;
}
void error_handling(const char *message)
{
    fputs(message, stderr); // stderr标准错误流
    fputc('\n', stderr);
    exit(1);
}
