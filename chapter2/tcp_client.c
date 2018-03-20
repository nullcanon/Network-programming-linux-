/*************************************************************************
	> File Name: tcp_client.c
	> Author: jack
	> Mail: hansheng.jiayou@qq.com 
	> Created Time: 2018-03-20 14:47:45
 ************************************************************************/


//此程序的作用为验证-面向连接的套接字
//“传输的数组不存在边界”

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>

int main(int argc, const char *argv[])
{
    if(argc != 3)
    {
        printf("参数错误\n");
        exit(1);
    }

    int sock = socket(PF_INET,SOCK_STREAM,0);
    if(sock == -1)
    {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = PF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    //客户端创建tcp连接
    if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) == -1)
    {
        perror("connect");
        exit(1);
    }

    //多次读取
    int read_size = 0;
    int all_size = 0;
    char buf[1024] = {0};
    int i = 0;
    while(read_size = read(sock,&buf[i++],1))
    {
        if(read_size == -1)
        {
            perror("read");
            exit(1);
        }
        all_size += read_size;
    }
    printf("来自服务器的消息：%s\n",buf);
    printf("read函数调用的次数：%d\n",all_size);
    close(sock);
    return 0;
}
