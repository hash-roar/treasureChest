# docker

## 常用命令

```bash
docker images#查看images
docker info #查案信息
docker --help #查看帮助
```

### 镜像命令

```bash
docker images
REPOSITORY(名字)    TAG(标签)       IMAGE ID(id)       CREATED(时间)         SIZE(大小)
hello-world         latest         d1165f221234        5 months ago          13.3kB

docker search name#搜索
docker pull name [:tag] #下载
########################################
Using default tag: latest#最近的版本
latest: Pulling from library/mysql
e1acddbe380c: Pull complete#分层下载
bed879327370: Pull complete
03285f80bafd: Pull complete
ccc17412a00a: Pull complete
1f556ecc09d1: Pull complete
adc5528e468d: Pull complete
1afc286d5d53: Pull complete
6c724a59adff: Pull complete
0f2345f8b0a3: Pull complete
c8461a25b23b: Pull complete
3adb49279bed: Pull complete
77f22cd6c363: Pull complete
Digest: sha256:d45561a65aba6edac77be36e0a53f0c1fba67b951cb728348522b671ad63f926#签名
Status: Downloaded newer image for mysql:latest
docker.io/library/mysql:latest#真实地址
###########################################

docker rm -f $(docker images -aq)#删除全部

```

### 容器命令

```bash
docker run --help #查看run命令
docker run --name="name" -d 后台 -it交互方式 -p指定端口(-p 主机端口:容器端口) -P随机端口

docker run -it centos /bin/bash #进入容器

docker ps -a #列出所有容器
docker ps -a -n
c-p+q #不停止退出
docker rm -f $(docker ps -aq)删除所有容器
docker ps -a -q | xargs docker rm

docker start id
docker restart id
docke stop id
docker kill id

#后台启动,如果没有前台服务,会自动停止

#进入容器
docker exec -it id #进入容器开启新终端
docker attach id#打开终端,正在执行当前代码

#拷贝
docker cp id:path path

```

### 日志

```
#查看日志
docker logs 

#查看进程
docker top  id

#查看信息
docker inspect

```



## 基础

### docker run原理

1. docker run
2. 有则运行,无则下载,在dockerhub上找
3. dockerhub 找不到
4. 返会错误

### 底层原理

client-server 系统,守护进程,通过socket访问,类似于一个小的linux服务器

dockerServer 介绍dockerclient命令

#### 快的原因

docker有更少的抽象层,用的主系统的内核

### 镜像

#### 得到镜像

1. 仓库下载
2. 从第三方下载
3. 自己制作

#### 分层文件系统

一层一层叠加,可以复用

#### 分层加载原理

boots->rootfs(系统级,精简的系统)

docker镜像默认只读,用户操作在新的一层(容器层)

### commit

docker commit -m=messge

## doker数据卷

### 容器间的数据共享

容器的持久化和同步

```shell
docker run -it -v(挂载)  dir:dir(local)

```

#### 具名挂载

#### 匿名挂载

```shell
-v path #
-v name:path#
docker volume 
var/lib/docker/volumes#在此文件中
```

## dockerFile

通过脚本生成镜像

```shell
vim dockerfile
####指令(大写) 参数
FROM centos
VOLUME ["volume1","volume2"] #匿名挂载,/var/lib/docker/volumes
CMD /bin/bash
######
docker build -f dcokerfile -t test1
```

#### 基础

关键字大写,从上到下,每个命令一层镜像

```bash
FROM  #基础镜像
MAINTAINER #基础镜像
RUN         #运行命令
ADD     #步骤,增加压缩包
WORKDIR #工作目录
VOLUME #挂载目录
EXPOSE #暴露端口
CMD #指定运行命令 CMD ["ls","-a"]
ENTRYPOINT #运行命令,可以追加命令
ONBUILD #构建完成后
COPY  #复制
ENV #环境变量

```

## docker网络

### 网络

> 实验

```bash
ip addr
docker0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc noqueue state UP group default
    link/ether 02:42:c1:ff:cf:0a brd ff:ff:ff:ff:ff:ff
    inet 172.17.0.1/16 brd 172.17.255.255 scope global docker0
       valid_lft forever preferred_lft forever
    inet6 fe80::42:c1ff:feff:cf0a/64 scope link
       valid_lft forever preferred_lft forever
ping 
```

> 原理

每个docker分配一个ip,网卡桥接模式,使用evth-pair技术(成对的虚拟设备接口)

docker中所有网络接口都是10m

### link

```shell
docker --link name1 name2 #通过服务名连接
```

> 原理:
>
> 通过修改host文件

### 自定义网络

```bash
docker network create --driver bridge --subnet 192.168.0.0/16 --gateway 192.168.0.1 mynet(name)#创建网络

docker run -d -P --name name_self --net mynet image_name#
#自定义网络中可以互相ping

```

### 网络联通

```
#connect,
#一个容器两个ip

docker network connect net_name Container_name
```





## 实践

### nginx

```bash
docker pull nginx
docker run -d --name nginx-01 -p port:port nnginx

curl localhost:port
#====>
<!DOCTYPE html>
<html>
<head>
<title>Welcome to nginx!</title>
<style>
    body {
        width: 35em;
        margin: 0 auto;
        font-family: Tahoma, Verdana, Arial, sans-serif;
    }
</style>
</head>
<body>
<h1>Welcome to nginx!</h1>
<p>If you see this page, the nginx web server is successfully installed and
working. Further configuration is required.</p>

<p>For online documentation and support please refer to
<a href="http://nginx.org/">nginx.org</a>.<br/>
Commercial support is available at
<a href="http://nginx.com/">nginx.com</a>.</p>

<p><em>Thank you for using nginx.</em></p>
</body>
</html>

##进入nginx
root@75431f18dc30:/# ls
bin   dev                  docker-entrypoint.sh  home  lib64  mnt  proc  run   srv  tmp  var
boot  docker-entrypoint.d  etc                   lib   media  opt  root  sbin  sys  usr
root@75431f18dc30:/# cd /etc/n
nginx/         nsswitch.conf
root@75431f18dc30:/# cd /etc/nginx/
root@75431f18dc30:/etc/nginx# ls
conf.d  fastcgi_params  mime.types  modules  nginx.conf  scgi_params  uwsgi_params
root@75431f18dc30:/etc/nginx# vim
bash: vim: command not found
root@75431f18dc30:/etc/nginx#    
```

### mysql

#### 数据持久化

```bash
docker pull mysql#获取

docker run -d(后台) -p 3301:3306 -v path:path -v -e MYSQL_ROOT_PAAWORD="" --name mysql0 mysql

```

#### 多个mysql数据同步

```bash
docker run -it --name docker01 --volums-from docker00 image_name
```

### 构建centos

99%镜像由sratch构建

> dockerfile

```dockerfile
FROM centos
MAINTAINER lf

ENV MYPATH /usr/local
WORKDIR $MYPATH
RUN yum -y install vim
RUN yum -y install net-tools

EXPOSE 80
CMD /bin/bash
```

> 构建

```bash
docker build -f dockerfile -t name
```

### tomcat镜像

> 准备文件

准备压缩包

> Dockerfile

```dockerfile
FROM centos
COPY readme.txt /usr/local/readme.txt
add name.tar.gz  /usr/local
RUN yum -y install vim
ENV MYPATH /usr/local
WORKDIR $MYPATH

ENV JAVA_HOME /usr/local/
ENV PATH $JAVA_HOME:$MYPATH

EXPOSE 8080
```

