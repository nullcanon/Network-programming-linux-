/*************************************************************************
	> File Name: tcp_client.c
	> Author: jack
	> Mail: hansheng.jiayou@qq.com 
	> Created Time: 2018-03-20 14:47:45
 ************************************************************************/



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

    char buf[1024] = {0};
    ssize_t read_size = read(0,buf,sizeof(buf)-1);
    if(read_size < 0)
    {
        perror("read");
        exit(1);
    }
    else
    {
        read_size = '\0';
        write(sock,buf,strlen(buf));
    }

    if(read(sock,buf,sizeof(buf)-1) < 0)
    {
        perror("read");
        exit(1);
    }
    else
    {
        printf("result from server:%s\n",buf);
    }    
    close(sock);
    return 0;
}
