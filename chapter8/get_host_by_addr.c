#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<sys/socket.h>
#include<string.h>


int main(int argc,char* argv[])
{
    if(argc != 2)
    {
        printf("Usage : %s <IP>\n",argv[0]);
        exit(1);
    }

    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
    addr.sin_addr.s_addr = inet_addr(argv[1]);

    struct hostent* host = gethostbyaddr((char*)&addr.sin_addr,4,AF_INET);
    if(!host)
    {
        perror("get host by name");
        exit(1);
    }
    
    printf("official name: %s\n",host->h_name);
    
    int i = 0;
    while(host->h_aliases[i] != NULL)
    {
        printf("Aliases %d:%s\n",i+1,host->h_aliases[i]);
        ++i;
    }

    printf("Address type:%s\n",(host->h_addrtype==AF_INET)?"AF_INET":"AF_INET6");

    i = 0;
    while(host->h_addr_list[i] != NULL)
    {
        printf("IP addr %d:%s\n",i+1,inet_ntoa(*(struct in_addr*)host->h_addr_list[i]));
        ++i;
    }



    return 0;
}
