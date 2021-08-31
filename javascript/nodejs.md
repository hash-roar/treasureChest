# nodejs

## 模块化

### require

引入外部文件,node中每个文件在函数中执行

```javascript
require(path);

let md = require(path);

//暴露变量

```

### 文件模块

全局对象global,作用类似于windows

全局对象都挂载在global

```javascript
a = 10;
global.a //10
```

执行文件时,模块代码包装在函数中

```javascript
function(exports,require,module(模块本身),__filename,__dirname){
//code//
    //exports==module.exports
}

//暴露对象

```

### 包

#### 结构

```JavaScript
package.json//描述文件
bin //二进制文件
lib//js代码
doc//文档
test//单元测试
```

#### package.json

包的说明书

```
{
	"name":[
	{
	
	}
	],
	"dependencies":{}//依赖
	"devdependencies":{}//依赖
	...
}
```

### npm

包管理器

```
npm search name //搜索包
```

