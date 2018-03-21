
 - 一个网络版本的计算器
 
   * 客户端向服务器发送一个表达式
   * 服务器处理表达式,并向客户端返回结果
   * 客户端通过标准输出将结果打印出来

客户端:

![](https://github.com/nullcanon/Network-programming-linux-/blob/master/chapter5/clnt.png)

服务器端:

![](https://github.com/nullcanon/Network-programming-linux-/blob/master/chapter5/serv.png)

**遇到的问题**

read()函数并不处理'\n'
