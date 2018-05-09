DNS服务器将域名转化为IP地址,若DNS服务器无法解析,则会询问其他DNS服务器

`ping www.xxx.com`可查看IP地址

`nslookup server`可查看计算机默认DNS服务器地址

利用域名获取IP地址的函数:
```
#include<netdb.h>

struct hostent* gethostname(const char* hostname)

struct hostent
{
    char* h_name;//official name
    char** h_aliasea;//alias list
    int h_addrtype;//host address type
    int h_length;//address length
    char** h_addr_list;//address list,这里char*是为了兼容IPv4和IPv6
}
```

利用IP地址获取域名

```
struct hostent* gethostbyaddr(const char* addr,socklen_t len,int family)
//len IPv4为4,IPv6为16
//family Ipv4为AF_INET,IPv6为AF_INET6
```