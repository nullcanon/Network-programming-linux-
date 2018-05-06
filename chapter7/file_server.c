#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>

// 向客户端传送文件
// 传送完成后使用shutdown函数对输出流进行半关闭
// ,这样向客户端传输了EOF,客户端就知道了文件传输完成
// 最后依然可以接收数据
int main(int argc,char* argv[])
{
    int serv_sd,clnt_sd;
    FILE* fp;
    char buf[1024];
    int read_cnt;

    struct sockaddr_in serv_adr,clnt_adr;
    socklen_t clnt_adr_sz;

    if(argc != 2)
    {
        printf("%s参数错误!\n",argv[0]);
        exit(1);
    }

    fp = fopen("file_server.c","rb");
    serv_sd = socket(PF_INET,SOCK_STREAM,0);

    memset(&serv_adr,0,sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    bind(serv_sd,(struct sockaddr*)&serv_adr,sizeof(serv_adr));
    listen(serv_sd,5);

    clnt_adr_sz = sizeof(clnt_adr);
    clnt_sd = accept(serv_sd,(struct sockaddr*)&clnt_adr,&clnt_adr_sz);

    while(1)
    {
        read_cnt = fread((void*)buf,1,1024,fp);
        if(read_cnt < 1024)
        {
            write(clnt_sd,buf,read_cnt);
            break;
        }
        write(clnt_sd,buf,1024);
    }
    shutdown(clnt_sd,SHUT_WR);
    read(clnt_sd,buf,1024);
    printf("msg from client:%s\n",buf);
    fclose(fp);
    close(clnt_sd);
    close(serv_sd);

    return 0;
}
