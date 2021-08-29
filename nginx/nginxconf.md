# nginx配置

### [nginx可视化配置](https://www.nginxwebui.cn/news.html)
### [关于nginx中$fastcgi_script_name与$request_name区别](https://qastack.cn/server/465607/nginx-document-rootfastcgi-script-name-vs-request-filename)

### 配置结构

	# 这里是一些配置
	...
	http {
	  # 这里是一些配置
	  ...
	  # 这部分可能存在于/etc/nginx/conf.d/目录下
	  upstream {
	
	  }
	  server {
	    listen 8080;
	    root /data/up1;
	
	    location / {
	    }
	  }
	  server {
	    listen 80;
	    root /data/up2;
	
	    location / {
	    }
	  }
	  这里是一些配置
	  ...
	}
	
	mail {
	}
### location正则



### nginx搭建文件服务器
修改conf文件

	server {
	  listen 80; 
	  server_name myServerNamne; # 自己PC的ip或者服务器的域名
	  charset utf-8; # 避免中文乱码 
	  root /www/static; # 存放文件的目录 
	  location / { 
	    autoindex on; # 索引 
	    autoindex_exact_size on; # 显示文件大小 
	    autoindex_localtime on; # 显示文件时间 
	  }
	}

### nginx配置虚拟主机

	server{
	server_name a.ttlsa.com;
	listen 80;
	root /data/site/a.ttlsa.com;
	access_log /data/logs/nginx/a.ttlsa.com-access.log main;
	location /{}
	}
	server{
	server_name b.ttlsa.com;
	listen 80;
	root /data/site/b.ttlsa.com;
	access_log /data/logs/nginx/b.ttlsa.com-access.log main;
	location /{}
	}

配置讲解

server{}：配置虚拟主机必须有这个段。

server_name：虚拟主机的域名，可以写多个域名，类似于别名，比如说你可以配置成server_name b.ttlsa.com c.ttlsa.com d.ttlsa.com，这样的话，访问任何一个域名，内容都是一样的

listen 80，监听 ip 和端口，这边仅仅只有端口，表示当前服务器所有 ip 的 80 端口，如果只想监听 127.0.0.1的 80，写法如下：listen 127.0.0.1:80

root /data/site/b.ttlsa.com：站点根目录，你网站文件存放的地方。注：站点目录和域名尽量一样，养成一个
好习惯

access_log /data/logs/nginx/b.ttlsa.com-access.log main：访问日志
##### 改变location中得uri

	alias path  例如:
	location  ~ ^/data/(.+\.(html|php))$ {
	alias /location/$1)
	}
##### 改变错误页面
提供一个思路

	error_page 404 /404.html
	当服务器找不到文件时自动转到/404.html,此时在location块加上:
	location /404.html{
	root /uri/errorpages/}
	就能自动匹配

### nginx+php环境

nginx与php交互使用fastcgi协议,但是windows下php-cgi.exe有以下缺点

1. 配置文件 php.ini 修改后无法平滑重载，需要重新启动 php-cgi 进程；
2. Windows 下 php-cgi 默认处理 500 个请求后就自动退出（PHP_FCGI_MAX_REQUESTS）；
3. 如果因为其他原因造成 php-cgi 进程崩溃，就无法处理后续请求了

linux 下用php-fpm这个PHP FastCGI管理器,提供了更好的PHP进程管理方式，可以有效控制内存和进程、可以平滑重载PHP配置.但是在windows下只能用一用spawn-CGI进程管理器..

将php-cgi-spawner.exe下载到php.exe同级目录,ps中运行

	.\php-cgi-spawner.exe "php-cgi.exe -c php.ini" 9000 4+16
	# 令 PHP FastCGI 处理程序监听在 9000 端口上
	# 至少开启 4 个 php-cgi 进程，高负载时最多可以开到 16 个

配置location块:

	location ~ [^/]\.php(/|$) {
	        # 从 URI 中分离出 $fastcgi_script_name 和 $fastcgi_path_info 的值
	        # 不推荐使用 php.ini 中的 cgi.fix_pathinfo 选项，这可能会造成安全隐患
	        fastcgi_split_path_info  ^(.+?\.php)(/.*)$;
	        fastcgi_param  PATH_INFO  $fastcgi_path_info;
	
	        # 当请求的 .php 文件不存在时直接返回 404
	        # 不然交给 PHP 处理的话那边就会返回 No input file specified.
	        if (!-f $document_root$fastcgi_script_name) {
	            return 404;
	        }
	
	        fastcgi_pass   127.0.0.1:9000;
	        fastcgi_index  index.php;
	        # 自带的配置文件，里面设置了一大堆 CGI 协议中的变量
	        include        fastcgi.conf;
	    }

### nginx+thinkphp5配置
通过重写uri实现

	nginx 的rewrite规则
	1 任何重写规则的第一部分都是一个正则表达式
	可以使用括号来捕获，后续可以根据位置来将其引用，位置变量值取决于捕获正则表达式中的顺序，$1 引用第一
	个括号中的值，$2 引用第二个括号中的值，以此类推。如：
	
	^/images/([a-z]{2})/([a-z0-9]{5})/(.*)\.(png|jpg|gif)$
	
	$1 是两个小写字母组成的字符串，$2 是由小写字母和 0 到 9 的数字组成的 5 个字符的字符串，$3 将是个文件名，
	$4 是 png、jpg、gif 中的其中一个。
	
	2 重写规则的第二部分是 URI
	请求被改写。该 URI 可能包含正则表达式中的捕获的位置参数或这个级别下的 nginx 任何配置变量。如：
	/data?file=$3.$4
	如果这个 URI 不匹配 nginx 配置的任何 location，那么将给客户端返回 301(永久重定向)或 302(临时重定向)的状
	态码来表示重定向类型。该状态码可以通过第三个参数来明确指定。
	3 重写规则的第三部分
	第三部分也就是尾部的标记(flag)。 last 标记将导致重写后的 URI 搜索匹配 nginx 的其他 location，最多可循
	环 10 次

# nginx实践

## 解决跨域

```nginx
add_header  Acess-Control-Allow-Origin  域名;(*表示所有)
add_header Acess-Control-Allow-Methods  GET,POST;
```

## 资源防盗链

```nginx
对于某些静态资源:
http{
    server{
        location ~ .*\.(png|jpg|gif)${
            valid_referers none blocked 正则;
            if($invalid_referer){
                return 403;
            }
            root images/;
        }
    }
}
```

## 变量与日志

### 内置变量

| args            | 参数          |
| --------------- | ------------- |
| host            | server_name   |
| document_uri    | url           |
| document_root   | location root |
| content_length  |               |
| content_type    |               |
| http_cookie     |               |
| remote_addr     |               |
| remote_port     |               |
| server_protocol |               |
| request_method  |               |

### 日志格式

```nginx
log_format main '$remote_addr  -  $request  - $status - Request'
```



## 重写

### 语法

```nginx
set $variable value #设置变量
location {
    set $name tom;
    set $age 18;
    default_type text/plain;
    return 200 $name=$age;
}

#if语句
if(condition){
    
}#condition  为空或为不成立
#正则
if($args ~ (正则) ){
    
}# ~区分大小写  ~*不区分大小写
#字符串中有"}"或";"加引号
if(!-f $request_filename)
{
    #文件不存在进入此块
}

#break语句
#终止当前作用域
#终止当前匹配

#return 
return status [text];
return url;#302跳转


#rewrite
location /rewrite{
    rewrite ^/rewrite/url\w*$ http://www.baidu.com;
    rewrite ^/rewrite/url(\w*)$ /$1;
    
}
##flag
#last 重写后重新匹配
#break 在本块中处理
#permanent 永久重定向

#rewrite_log
```

### 实践

```nginx
#域名跳转
location /{
    rewrite  ^(.*) http://www.yuming.com$1;
    
}

#域名镜像
#将某个模块重写到其他域名
location /a{
    rewrite ^/user(.*)$ http://yuming$1;
}

#独立域名

#目录加/
server_name_in_redirect 

#目录合并

```

## 代理

### 正向代理

```nginx
resolver ip;#dns
location /{
    proxy_pass 域名;
}
```

### 反向代理

```nginx
#proxy_pass
location / {
    proxy_pass yuming;
}
#yuming 会把地址拼接上
#yuming/ 直接访问yuming/

#proxy_set_header

#proxy_redirect
proxy_redirect value rplacement;

#实践

```

## 安全

