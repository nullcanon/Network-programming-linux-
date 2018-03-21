/*************************************************************************
	> File Name: udp_server.c
	> Author: jack
	> Mail: hansheng.jiayou@qq.com 
	> Created Time: 2018-03-21 19:06:30
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, const char *argv[])
{
    if(argc != 2)
    {
        printf("参数错误\n");
        exit(1);
    }

    int serv_sockfd = socket(PF_INET,SOCK_DGRAM,0);
    if(serv_sockfd == -1)
    {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) == -1)
    {
        perror("bind");
        exit(1);
    }

    int str_len;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;
    char buf[1024] = {0};

    while(1)
    {
        clnt_addr_size = sizeof(clnt_addr); 
        str_len = recvfrom(serv_sockfd,buf,sizeof(buf)-1,0,
                (struct sockaddr*)&clnt_addr,&clnt_addr_size);
        buf[str_len] = '\0';
        sendto(serv_sockfd,buf,str_len,0,(struct sockaddr*)&clnt_addr,clnt_addr_size);
    }
    close(serv_sockfd);
    return 0;
}
