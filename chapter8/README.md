DNS������������ת��ΪIP��ַ,��DNS�������޷�����,���ѯ������DNS������

`ping www.xxx.com`�ɲ鿴IP��ַ

`nslookup server`�ɲ鿴�����Ĭ��DNS��������ַ

����������ȡIP��ַ�ĺ���:
```
#include<netdb.h>

struct hostent* gethostname(const char* hostname)

struct hostent
{
    char* h_name;//official name
    char** h_aliasea;//alias list
    int h_addrtype;//host address type
    int h_length;//address length
    char** h_addr_list;//address list,����char*��Ϊ�˼���IPv4��IPv6
}
```

����IP��ַ��ȡ����

```
struct hostent* gethostbyaddr(const char* addr,socklen_t len,int family)
//len IPv4Ϊ4,IPv6Ϊ16
//family Ipv4ΪAF_INET,IPv6ΪAF_INET6
```