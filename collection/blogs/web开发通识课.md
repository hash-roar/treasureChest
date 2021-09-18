---
title: web开发通识课
date: 2021-09-17 21:17:44
tags:
  - web开发
categories:
  - [术,web开发]
---

## 前言

鉴于很多one echor还对web开发一无所知,甚至网上也没找到好的web开发通识教程.现写一点,以待后来者补充更改,留作one echo教学用

本文为web开发通识课第一篇,上水课时写的,有点粗糙.

小白阅读本文,建议先通读全文大概理解,感觉自己行了再开始实操,因本文中涉及到服务器配置,这些都是后面才讲的.

## web开发

### 总论

​	听人说了很久,可曾想过到底什么是web开发,怎样才能搭建网站?

#### 从浏览器说起

下面我将讲诉当你在浏览器中点击一个链接时,一个页面怎么呈现在你眼前的

那我们直接开始吧

以我的博客举例,在浏览器中输入 网址点击回车

![image-20210917213053976](image-20210917213053976.png)

![image-20210917213118359](image-20210917213118359.png)



一个漂亮的网页呈现了

这其中经历的过程:

1. 浏览器向服务器发送一个请求
2. 服务器返回一个html文件
3. html文件描述了网站的内容结构.但是只有html文件的网站是很丑的,因此很多html文件会引用其他修饰的资源(比如css文件,图片资源)
4. 对于这些引用的资源,浏览器接着发送请求,获得文件,将这些文件渲染进网页中,此时变得到完整的网页(大概)

好了,现在你已经明白浏览器都在干什么了,你当然也注意到,浏览器是向服务器请求资源.那么服务器的用途也就呼之欲出了.回应浏览器的请求(比如,浏览器想要图片,服务器就把图片传给它,想要css文件,那就传css文件给它(这么看来服务器可真是个老好人))

服务器当然不只处理这些静态资源,还有许多功能呢,后面再聊.



**你现在已经有点了解了,但感觉啥也不懂,那现在我以编写一个微型网站为例,向你展示web开发的流程.**

这个网站只有一个功能,用户输入名字和密码,前端将数据传给后端,后端判断密码是否正确,再把结果返回给前端

### 前端

刚才你已经看到浏览器的作用,前端做的,就是编写html文件等,编写那些需要与用户交互的页面,并负责把用户输入的数据传给后端,并根据后端传回的数据将合适的效果呈现在用户面前.

![查看源图像](v2-ea14325ee79f60d878d1b412d1e2a76d_r.jpg)



**我们直接开始吧!**

在我相信读者已经有一点html基础的情况下,我们开始编写html文件

> index.html文件

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>page for one echor</title>
</head>
<body>
    <!-- 输入表单,获取用户信息 -->    
    <form action="resolve_data.php" method="post"> <!-- action指定表单数据提交到哪里,method表示提交方式-->
        <label for="">name:</label>
        <input type="text" placeholder="name"><!-- 名字表单,类型为普通文本,输入框提示词为"name"-->
        <label for="">password:</label>
        <input type="password" placeholder="name" ><!-- 密码表单,类型为密码类型,输入框提示词为"name"-->
        <button type="submit">提交</button> <!-- 提交按钮,类型为submit,点击时表单数据将提交到后端" -->
    </form>
</body>
</html>
```

将html文件放在服务器上,在浏览器输入相应地址打开文件

或者在文件夹中找到刚才写的html文件,鼠标双击即可用默认浏览器打开

以第一种方式为例,**打开的效果**:

![image-20210918194425547](image-20210918194425547.png)

这个时候,你就可以在框里输入信息,点击提交.

到这个时候,前端的任务就完成了,数据已经交后端了

### 后端

前文提到,表单中的form标签中有一个  **action="resolve_data.php"**  ,这段代码的含义就代表着将表单数据提交给与html文件同目录下的  **resolve_data.php** 文件,服务器接受到这个发送的数据,**交给这个php文件执行**  

![image-20210918200217011](image-20210918200217011.png)



我们现在的任务就是编写一个php文件,接受传过来的数据,并判断密码是否正确并返回结果.(现在我假设读者已经有点php基础=_=.)

那我们直接开始

#### 第一尝试

打印一下传进来的数据

> resolve_data.php文件

```php
<?php  //每个php文件都以这个开头哦!
    var_dump($_POST); //var_dump表示打印变量, $_POST表示传递过来的post数据
```

![image-20210918201135642](image-20210918201135642.png)



我们在前端页面输入 **test**  **1234**  点击提交,这时提交的数据已经到了后端,屏幕上应该能打印出数据吧.试一试!



![image-20210918201429909](image-20210918201429909.png)



可以看到,打印出的$_POST是个空数组,为什么前端数据没传过来呢?



直接告诉你吧,因为前端编写的html文件有问题,在上面的html代码中

```html
<input type="text" placeholder="name"><!-- 名字表单,类型为普通文本,输入框提示词为"name"-->
   
<input type="password" placeholder="name" ><!-- 密码表单,类型为密码类型,输入框提示词为"name"-->
```

试想一下,服务器传上来的数据都没有标识,那个数据代表着什么?这些后端都不知道,因此浏览器直接没有把数据传过去.

了解到这些我们只要为每一个 **input** 命名就行了,修改一下html代码

> index.html 文件

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>page for one echor</title>
</head>
<body>
    <form action="resolve_data.php" method="post">
        <label for="">name:</label>
        <input type="text" placeholder="name" name="name"> <!-- 就是在input标签中加入name属性,标识不同数据 -->
        <label for="">password:</label>
        <input type="password" placeholder="name" name="password">
        <button type="submit">提交</button>
    </form>
</body>
</html>
```

#### 再次尝试

![image-20210918202426260](image-20210918202426260.png)

点击

![image-20210918202443483](image-20210918202443483.png)

可以看到,php脚本已经获得用户传上来的数据,获取到数据了,剩下的就简单了.

我们直接编写完整的php文件

> resolve_data.php 文件

```php
<?php

$name = $_POST["name"];
$password = $_POST["password"]; //将数据存储在变量中

//判断用户名 密码是否正确

if($password == "123"){
    echo  "
    <html>
    <head><title>com from webServer</title></head>
    <body>
        <h1>密码正确</h1>
    </body>
    </html>
    ";
}
else{
    echo  "
    <html>
    <head><title>com from webServer</title></head>
    <body>
        <h1>密码错误</h1>
    </body></html>
    ";
}
//根据不同情况返回一个html格式的字符串,会被浏览器解析成html文件
```

#### 最终效果

![image-20210918203759261](image-20210918203759261.png)

![image-20210918203809864](image-20210918203809864.png)



## 结语

到这里,你已经明白了前端与后端的交互.你可以在html中编写更多功能,用css文件美化前端界面

对于后端,你可能已经注意到,关于密码的判断是写死的.假如用户要改密码,难道程序员还要去改代码吗?当然不会,这就要涉及到数据库了,将用户名密码储存在数据库中,需要的时候直接取出来就行了.修改数据就不用改代码了.你也可以尝试着完善.

骚年,web开发的世界还有很多东西,开始努力吧.



