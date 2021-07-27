## JavaScript基础
### 数据类型
[数据类型](https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Data_structures)

1.null 与 undefined 的不同点：当检测 null 或 undefined 时，注意相等（==）与全等（===）两个操作符的区别 ，前者会执行类型转换

	typeof null        // "object" (因为一些以前的原因而不是'null')
	typeof undefined   // "undefined"
	null === undefined // false
	null  == undefined // true
	null === null // true
	null == null // true
	!null //true
	isNaN(1 + null) // false
	isNaN(1 + undefined) // true
	
2.symbol

一个具有数据类型 “symbol” 的值可以被称为 “符号类型值”。在 JavaScript 运行时环境中，一个符号类型值可以通过调用函数 Symbol() 创建，这个函数动态地生成了一个匿名，唯一的值。Symbol类型唯一合理的用法是用变量存储 symbol的值，然后使用存储的值创建对象属性。以下示例使用"var"创建一个变量来保存 symbol。

	var  myPrivateMethod  = Symbol();
	this[myPrivateMethod] = function() {...};

当一个 symbol 类型的值在属性赋值语句中被用作标识符，该属性（像这个 symbol 一样）是匿名的；并且是不可枚举的。因为这个属性是不可枚举的，它不会在循环结构 “for( ... in ...)” 中作为成员出现，也因为这个属性是匿名的，它同样不会出现在 “Object.getOwnPropertyNames()” 的返回数组里。这个属性可以通过创建时的原始 symbol 值访问到，或者通过遍历 “Object.getOwnPropertySymbols()” 返回的数组。在之前的代码示例中，通过保存在变量 myPrivateMethod的值可以访问到对象属性。

3.原型,原型链
每个函数都有一个 prototype 属性，函数的 prototype 属性指向了一个对象，这个对象正是调用该构造函数而创建的实例的原型

每一个JavaScript对象(null除外)在创建的时候就会与之关联另一个对象，这个对象就是我们所说的原型，每一个对象都会从原型"继承"属性。

每个原型都有一个 constructor 属性指向关联的构造函数
![prototype原型链.png](http://ww1.sinaimg.cn/large/007b6ma2ly1gsvny154vhj30ge0el0ts.jpg)

### 作用域

作用域是指程序源代码中定义变量的区域。

作用域规定了如何查找变量，也就是确定当前执行代码对变量的访问权限。

JavaScript 采用词法作用域(lexical scoping)，也就是静态作用域。

	var value = 1;
	
	function foo() {
	    console.log(value);
	}
	
	function bar() {
	    var value = 2;
	    foo();
	}
	
	bar();
执行 foo 函数，先从 foo 函数内部查找是否有局部变量 value，如果没有，就根据书写的位置，查找上面一层的代码，也就是 value 等于 1，所以结果会打印 1。

在进入执行上下文时，首先会处理函数声明，其次会处理变量声明，如果变量名称跟已经声明的形式参数或函数相同，则变量声明不会干扰已经存在的这类属性。