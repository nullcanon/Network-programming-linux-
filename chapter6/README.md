**说明**

一个udp通信的回显服务器/客户端程序

**相关函数**

 - sendto()函数
    * ssize_t sendto(int sock,void *buff,size_t nbytes,int flags,struct sockaddr* to , socklen_t addrlen);
    * 描述
        * 将数据由指定的socket传给对方主机
    * 参数     
		* sock-用于传输数据的UDP套接字文件描述符
		* buff-保存待传输数据的缓冲地址值
     	 * nbytes-待传输的数据长度,以字节为单位
		* flags-可选项参数,若没有,则传递0
		* to-存有目标地址信息的sockaddr结构体变量的地址值
		* addrlen-传递给参数to的地址值结构体变量长度
        
    * 返回值
        * 成功返回传输的字节数,失败返回-1

 - recvfrom()函数

    * ssize_t recvfrom(int sock,void* buff,size_t nbytes,int flags,struct sockaddr* from,socklen_t* addrlen)
	      * 本函数用于从（已连接）套接口上接收数据，并捕获数据发送源的地址。
    * 参数-和上一个函数一样
    * 返回值-和上一个函数一样
