**代码说明**
 - 通过网络编程实现进程间的通信
  * 创建一个服务器程序-该程序阻塞的接收客户端的消息
* 创建一个客户端程序-该程序在访问服务器后得到服务器的回应
* 此代码为了验证"面向连接的套接字传输的数据不存在边界",具体表现形式为read函数可以调用多次

**相关函数**

socket()函数


  * int socket(int domain, int type, int protocol);

	* 这个函数建立一个协议族为domain,协议类型为type,协议编号为protocol的套接字文件描述符

		* 调用成功,返回文件描述符
		* 失败返回-1

listen()函数
 * int listen(int sockfd, int backlog)

	* listen函数一般在调用bind之后-调用accept之前调用,它使主动连接套接口变为被动套接口,使得一个进程可以接受其他进程的请求,从而成为一个服务器进程,在TCP服务器编程中,listen函数把进程变为一个服务器,并指定相应的套接字变为被动连接
	* 参数

		* sockfd-由socket函数返回,
		* backlog-backlog告诉内核使用这个数作为进程空间里队列的上限
	* 返回

		* 成功0,失败-1

bind()函数
 * int bind(int sockfd, const struct sockaddr *my_addr, socklen_t addrlen);

	* 在建立套接字文件描述符成功后,需要对套接字进行地址和端口绑定,才能进行数据的接受和发送操作
	* 此函数将长度为addlen的struct sockadd类型的参数my_addr与sockfd绑定在一起,将scokfd绑定到某个端口上,如果使用connect()函数则没有绑定的必要
	* 参数

		* sockfd是用socket()函数创建的文件描述符
		* my_addr是指向一个结构为sockaddr参数的指针

			* sockaddr包含了地址,端口和ip地址的信息
			* 在进行地址绑定的时候,需要将地质结构中的IP地址,端口,类型等结构struct sockaddr中的域进行设置之后才能进行绑定,这样进行绑定后才能将套接字文件描述符与地址等接合在一起
		* addrlen是my_addr结构的长度,可以设置成sizeof(struct sockaddr)
	* 返回值

		* 绑定成功,返回0
		* 失败,返回-1
		* 错误,返回错误值

accept()函数
 * int accept(int sockfd, struct sockaddr*addr,socklen_t*addrlen); 

	* 函数由TCP服务器调用,用于从已完成连接队列返回下一个已完成连接,如果已完成连接队列为空,那么进程被投入睡眠
	* 参数

		* sockfd
		* addr和addrlen用来返回已连接的对端进程(客户端)的协议地址,如果我们对客户端的协议不感兴趣,可以把这两个参数置空指针
	* 返回

		* 成功返回非负描述符
		* 错误返回1

connect()函数
 - int connect (int sockfd,struct sockaddr * serv_addr,int addrlen);
  * connect函数通常用于客户端建立tcp连接。
  * 参数：
  
  	* sockfd：标识一个套接字。
  	* serv_addr：套接字s想要连接的主机地址和端口号。
  	* addrlen：name缓冲区的长度。
* 返回值：
	* 成功则返回0，失败返回-1，

**运行方法**
 - ./tcp_client 127.0.0.1 9190
 - ./tcp_server 9190

**遇到问题**
 - 在进程结束后重新运行时会提示" Address already in use"
	 * 解决方法:
	 * [Linux 套接字编程中的 5 个隐患](https://www.ibm.com/developerworks/cn/linux/l-sockpit/)
	 * 参考以上的隐患3
   
  **总结**
   - 面向连接的套接字
     * 套接字必须一一对应
     * 可靠地
     * 按序传输
     * 基于字节


 - 面向消息套接字
 	* 不可靠
 	* 不按序
 	* 以高速传输为目的
     
