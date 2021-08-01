####


### index.php

加载base.php完成更多事情(在这其中完成类的自动加载等事情)

Container::get('app')->run()->send();
获取容器中的app实例并开始运行应用

### app.php
完成应用初始化及相关参数绑定


	1在index.php中得到的容器中app实例调用app中方法,绑定一些环境变量等,然后用得到的新的app实例替换容器中实例
	2在$this->env中,由于没有此方法,会走到_get()方法,运行make()方法返回env实例
	
#### init函数

两次定位模块目录,都进行加载扩展文件,加载公共文件,加载助手函数中间件等操作,因此在application和application\index目录下都可定义中间件等

#### routeTnit函数

	if (is_dir($this->routePath)) {
	            $files = glob($this->routePath . '*.php');
	            foreach ($files as $file) {
	                $rules = include $file;
	                if (is_array($rules)) {
	                    $this->route->import($rules);
	                }
	            }
	        }

遍历加载route目录下所有文件一起加载

### route
定义路由
route::get()
通过容器得到route实例,调用get方法调用rule方法,调用routegroup实例方法

### routeItem

对路由进行正则及字符串处理


