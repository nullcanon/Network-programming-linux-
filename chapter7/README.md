优雅的断开连接

当两个主机进行通信时,通信一方调用close或closesocket函数断开连接时,会完全断开连接,这样显得不太优雅?

比如说主机A和B进行双向通信,A发送完数据调用close之后再也不能收到B的数据

当两个主机建立连接,每个主机拥有单独的输入流和输出流

shutdown函数可以关闭其中一个流

```
int shutdown(int sock,int howto);

//第二个参数:
SHUT_RD:断开输入流
SHUT_WR:断开输出流
SHUT_RDWR:同时断开I/O流

```
