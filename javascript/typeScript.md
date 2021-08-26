# typescript

## 简介

**JavaScript的超集**

**编译生成js**



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

```

