/*************************************************************************
	> File Name: udp_client.c
	> Author: jack
	> Mail: hansheng.jiayou@qq.com 
	> Created Time: 2018-03-21 20:19:48
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
    if(argc != 3)
    {
        printf("参数错误\n");
        exit(1);
    }

    int sockfd = socket(PF_INET,SOCK_DGRAM,0);
    if(sockfd == -1 )
    {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    char buf[2048] = {0};
    int str_len;
    socklen_t addr_size;
    struct sockaddr_in from_addr;
    while(1)
    {
        fputs("输入消息（q退出）：",stdout);
        fgets(buf,sizeof(buf)-1,stdin);
        if(!strcmp(buf,"q\n") || !strcmp(buf,"Q\n"))
        {
            printf("退出成功\n");
            break;
        }
        sendto(sockfd,buf,strlen(buf),0,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
        addr_size = sizeof(from_addr);
        str_len = recvfrom(sockfd,buf,sizeof(buf)-1,0,
                (struct sockaddr*)&from_addr,&addr_size);

        buf[str_len] = '\0';
        printf("来自服务器的消息：%s\n",buf);
    }
    close(sockfd);
    return 0;
}
