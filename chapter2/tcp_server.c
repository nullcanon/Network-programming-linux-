/*************************************************************************
	> File Name: tcp_server.c
	> Author: jack
	> Mail: hansheng.jiayou@qq.com 
	> Created Time: 2018-03-20 13:08:34
 ************************************************************************/

#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<string.h>

int main(int argc, const char *argv[])
{
    //创建一个等待连接请求的服务器

    const char* buf = "hello";

    if(argc != 2)
    {
        printf("%s:参数错误\n",argv[0]);
        exit(1);
    }

    int serv_sockfd = socket(PF_INET,SOCK_STREAM,0);
    if(serv_sockfd == -1)
    {
        perror("socket");
        exit(1);
    }
    //分配本地地址
    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = PF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    //进行端口和地址的绑定
    if(bind(serv_sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) == -1)
    {
        perror("bind");
        exit(1);
    }

    //使套接字变为被动连接
    if(listen(serv_sockfd,5) == -1)
    {
        perror("listen");
        exit(1);
    }

    //阻塞的从列表中取出连接请求
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    int clnt_sockfd = accept(serv_sockfd,(struct sockaddr*)&clnt_addr,&clnt_addr_size);
    if(clnt_sockfd == -1)
    {
        perror("accept");
        exit(1);
    }

    write(clnt_sockfd,buf,strlen(buf));
    close(serv_sockfd);
    close(clnt_sockfd);
    return 0;
}
