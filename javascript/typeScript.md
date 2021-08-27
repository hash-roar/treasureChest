# typescript

## 简介

**JavaScript的超集** **编译生成js**

## 基础

### 类型声明

原生js

```javascript
let a;
a=10;
```

ts

```typescript
let a:number;
a= "hello"; //error
let b:string;
b = "hahha";//ok
b =12;//error
声明时赋值:
let a:string = "hahha";
赋值时自动类型推导:
let b = false;
b =12;//error
也可用字面量:
let q :"male"|"female";
```

ts函数:

```typescript
function sum(a:number,b:number){
	return a+b;
}
```

#### 类型

| 类型    | 解释                                                       |
| ------- | ---------------------------------------------------------- |
| number  | 0                                                          |
| string  | haha                                                       |
| any     | 任何值:1,"haha",true(不指定类型就是any,可以赋值给其它类型) |
| unknown | 任何值:只能让其他给自己赋值                                |
| void    | 空值                                                       |
| never   | 没有值                                                     |
| object  | 对象                                                       |
| []      | 数组                                                       |
| tuple   | 固定长度数组                                               |
| enum    | 枚举                                                       |
| &       | 同时满足                                                   |

```typescript
 类型断言(告诉解析器的实际类型):
let s = e as string;
s = <string>e;
对象类型:
//[propName:string]:any表示任意类型属性
let b :{name:string,[propName:string]:any};
b= {age:12};//error
函数类型:
let d :(a:number,b:number)=>number;
d= function(n1,n2):number{
    return "haha";
}//error 类型错误
数组:
let e:string[];
e = ['a','b'];
元组:
let h:[string,number];
h = ["heel",12];//ok
h = ["heel","daa"];//error
枚举:
enum Gender{
    male = 0,
    female =1
};
let i:{name:string,gender:Gender};
i ={
    name:"a",
    gender:Gender.male
};
类型别名:
type mytype = string;
```

### 编译

#### 自动编译文件

tsc ./1.js -w 监听文件变化并编译

创建tsconfig.json文件,运行tsc -w,会监视整个目录

#### 配置文件

```typescript
{
	"include":["./src/**/*"],//定义那些文件需要编译 **表示任意目录,*表示任意文件
	"exclude":["./src/static/**/*"],//定义排除在外的(有默认值)
     "files":[],//列出一个个文件
     "extends":[],//继承
     "compilerOptions":{
         "target":"ES6",//编译版本
         "module":"ES6"|"commonjs",//模块化解决规范
         "lib":["dom"],//库
         "outDir":"./dist",//dist目录
         "outFile":"merge.js",//合并文件名字
         "allowJs":true,//允许js文件
         "checkJs":false,//检查js代码规范
         "removeComments":true,//去掉注释
         "noEmit":false,//不生成目标文件
         "noEmitOnError":true,//不生成目标文件当有错误时
         "alwaysStrict":false,//严格模式(有模块时默认开启)
         "noImplicitAny":false,//隐式any
         "noImplicitThis":false,//不允许不明确this类型,
         "strictNullChecks":false,//严格检查空值
         "strict":false,//严格检查总打开
     }
}
```

### webpack配置

webpack.config.js

```javascript
const path = require("path");

module.exports= {
    entry:"indexPath",
    output:{
        path:"outPath",
        filename:"bundle.js"
    }
    module:{
    	rules:[
			{
    			test:/\.ts$/,
    			use:'te-loader'
    			exclude:/noe-modules/
			}
    	]
    }
}
```

package.js

```javascript
{
  "name": "javascript",
  "version": "1.0.0",
  "description": "[数据类型](https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Data_structures)",
  "main": "index.js",
  "scripts": {
    "test": "echo \"Error: no test specified\" && exit 1",
    "build":"webpack",//指定构建工具
  },
  "keywords": [],
  "author": "",
  "license": "ISC"
}
```

**webpack.config.js深入**

npm i html-webpack-piugin

```javascript
{
	plugins:[
		new HTMLWebpackPlugin({
			title:"title"
		}),
		
	]
}
```

## 面向对象

#### 类

```typescript
class className{
    name1:number = 12;
	static name:string = "value";//静态属性
    readonly name3:number = "value";//只读属性
    constructor(var1,var2){
        this.name1 = var1;
        this.name2 = var2;//this表示当前对象
    }//构造函数
    func(){
        log("hello");
    }//普通方法
    static func2(){
        log("static");
    }//静态方法
    
}

const obj = new className();

```

#### 继承

```typescript
class classParent{
	name_p1:number ;
	constructor(var1){
		this.name_p1 = var1;
	}
}
class classSon extends classParent{
    name_s1:number;
    constructor(){
        
    }
    //子类会覆盖父类方法
    //子类的构造函数需调用父类构造函数
}
```

#### super

```typescript
class c1{
	func(){
	 
	}
}
class c2 extends c1{
	func(){
	super.func();//调用父类方法
	}
}

```

#### 抽像类

```typescript
abstract class c1{
   abstract	func(){
	 
	}//抽象方法必须被重写
}//抽象类,不能创建对象
class c2 extends c1{
	func(){
	super.func();//调用父类方法
	}
}

```

#### 接口

**用来定义类结构**



```typescript
interface myinter{
	name:string;
}//接口中所有方法只用抽象方法
class c1 implements myinter{
    
}
```

#### 成员作用域

和c++类似

```typescript
public name1:string ;
private namw2:number;
class c{
    constructor(public name:string){
        
    }//构造函数中定义属性
}
```

#### 泛型

c++模板

```typescript
function fn<T> (a:T):T{
	return a;
}
function fn<T extends interfaceName>:T(){
    
}//必须是inter接口的实现类
fn<string>("hahah");
```

