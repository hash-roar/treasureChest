# nginx配置

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
	
### 多个webapp配置



