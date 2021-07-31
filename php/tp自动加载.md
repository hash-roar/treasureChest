## thinkphp加载类流程
#### 大型项目中命名空间是必不可少的,但是引用命名空间并不意味着对应的文件被引入,需要我们自己引入.因此使用到了php的类自动加载机制.每当用到一个未定义的类,都会调用sql____autoload____resister 注册的函数,因此只需要在注册的函数中实现类的加载就行.
#### 命名空间的定义与文件夹目录结构相同时,只需将对应的类名及命名空间经过字符串方法处理后,返回类文件在tp工程目录中的实际位置并include加载,就能实现框架的类的自动加载.

### PHP 运行流程

Apache 收到用户的 HTTP 请求

这个请求是以 .php 结尾或者是一个不存在的路径（.htaccess 会将其转发到 index.php）

Apache 的 mod_php 会启动一个新的 PHP 进程（PHP 解释器），读取 HTTP 请求的 URL 中的那个 .php 文件或者 index.php

被读取进 PHP 解释器的字符串被按照 PHP 的语法进行解析。为了方便理解，我们将这些经过解析的字符串所生成的 context（上下文）命名为 Matrix

然后 PHP 解释器会根据从 Matrix 中解析出的特定 PHP 语句（如 require）载入其他 PHP 文件，并将其内容以字符串的形式加入 Matrix

最终 Matrix 变成一个数万行代码的巨型上下文（为了便于理解可以想象成巨长的代码文件字符串），PHP 解释器会按照 PHP 语法执行 Matrix，进行数据库连接、网络请求、文件读写等操作

每一次的 echo 都会被写入到输出缓冲区，最终这个巨长的代码字符串被执行完毕，PHP 进程退出内存

缓冲区中就是要发给用户的 HTTP response，其实就是一堆字符串，只不过它遵守 HTML 规范，可以被浏览器解析。这一堆字符串被 Apache 发送回用户的浏览器，浏览器渲染，用户看到内容

命名空间从始至终就是一个“内部伪概念”，只是用于解决类和变量的命名冲突，从来就跟实际文件结构没有半毛钱的关系。让大家疑惑的其实是自动加载，当它和命名空间混杂在一起的时候，就不容易理解了。命名空间从来就是一个纯 PHP 内部的概念，你可以把整个 Laravel 框架的所有文件合并成一个巨大的 PHP 文件，取消自动加载，除了性能会损失一些，功能不会受到任何影响，命名空间依旧运转良好。

### psr4

 PSR4 是关于由文件路径 自动载入 对应类的相关规范，
本规范是可互操作的，可以作为任一自动载入规范的补充，其中包括 [PSR-0]()，此外，
 PSR 4还包括自动载入的类对应的文件存放路径规范。

草案还是规定了自动加载器应该如何处理错误。具体来说，它禁止抛出异常和错误，主要有这两方面考虑：

PHP 中自动加载器设计是可堆叠的，如果一个自动加载器不能加载，则其他的仍有机会继续加载。若有其中一个自动加载器发生错误此过程将不会进行下去；

class_exists() 和 interface_exists() 允许『在尝试自动加载后仍然找不到类』的存在，一个用例是：若自动加载器抛出异常将使得 class_exists() 不可用，从互操作性的角度来看这是无法接受的。自动加载器在找不到类的情况下最好通过日志记录提供附加的调试信息，日志可以使用 PSR-3 兼容日志记录或类似的方案。

### 自动加载函数

在了解这个函数之前先来看另一个函数：__autoload。

自动加载的原理，就是在我们new一个class的时候，PHP系统如果找不到你这个类，就会去自动调用本文件中的__autoload($class_name)方法，我们new的这个class_name 就成为这个方法的参数。所以我们就可以在这个方法中根据我们需要new class_name的各种判断和划分就去require对应的路径类文件，从而实现自动加载。
####  spl_autoload_register的使用

当我们去new一个找不到的class时，PHP就会去自动调用sql_autoload_resister注册的函数，这个函数通过它的参数传进去：sql_autoload_resister($param) 这个参数可以有多种形式：

	sql_autoload_resister('load_function'); //函数名
	sql_autoload_resister(array('load_object', 'load_function')); //类和静态方法
	sql_autoload_resister('load_object::load_function'); //类和方法的静态调用
	
	//php 5.3之后，也可以像这样支持匿名函数了。
	spl_autoload_register(function($className){
	    if (is_file('./lib/' . $className . '.php')) {
	        require './lib/' . $className . '.php';
	    }
	});

####  多个spl_autoload_register的使用

spl_autoload_register是可以多次重复使用的，这一点正是解决了__autoload的短板，那么如果一个页面有多个，执行顺序是按照注册的顺序，一个一个往下找，如果找到了就停止。


