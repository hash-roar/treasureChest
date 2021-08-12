# c++
### const
1 常量在不同文件里使用:

	//extern_file1.cpp
	extern const int ext=12;
	#include<iostream>
	extern const int ext;
	int main(){
	 std::cout<<ext<<std::endl;
	}

2 指针与常量:

	const char * a; //指向const对象的指针或者说指向	常量的指针。
	char const * a; //同上
	char * const a; //指向类型对象的const指针。或者	说常指针、const指针。
	const char * const a; //指向const对象的const指针。

3 函数const

		const int* func2();指针指向的内容不变
		int *const func2();指针不可变
		void func(char *dst, const char *src);参数指针所指内容不可变
		void func(const A &a);防止a被修改

4 类与const


	对于类中的const成员变量必须通过初始化列表进行初始化
	const对象只能访问const成员函数,而非const对象可以访问任意的成员函数,包括const成员函数;
	
### static

#### 静态变量
1函数中静态变量:当变量声明为static时，空间将在程序的生命周期内分配。即使多次调用该函数，静态变量的空间也只分配一次，前一次调用中的变量值通过下一次函数调用传递。这对于在C / C ++或需要存储先前函数状态的任何其他应用程序非常有用。

2类中的静态变量:由于声明为static的变量只被初始化一次，因为它们在单独的静态存储中分配了空间，因此类中的静态变量**由对象共享。**对于不同的对象，不能有相同静态变量的多个副本。也是因为这个原因，静态变量不能使用构造函数初始化。
因此，类中的静态变量应由用户使用类外的类名和范围解析运算符显式初始化

#### 静态成员
1类对象为静态:就像变量一样，对象也在声明为static时具有范围，直到程序的生命周期。

2类中的静态函数:就像类中的静态数据成员或静态变量一样，静态成员函数也不依赖于类的对象。我们被允许使用对象和'.'来调用静态成员函数。但建议使用类名和范围解析运算符调用静态成员。


###  this
this作用域是在类内部，当在类的非静态成员函数中访问类的非静态成员的时候，编译器会自动将对象本身的地址作为一个隐含参数传递给函数。也就是说，即使你没有写上this指针，编译器在编译的时候也是加上this的，它作为非静态成员函数的隐含形参，对各成员的访问均通过this进行。
	
### inline

内联是以代码膨胀(复制)为代价，仅仅省去了函数调用的开销，从而提高函数的执行效率。

	/**
 	* 编译器对 inline 函数的处理步骤
 	* 将 inline 函数体复制到 inline 函数调用点处；
	 * 为所用 inline 函数中的局部变量分配内存空间；
 	* 将 inline 函数的的输入参数和返回值映射到调用	方法的局部变量空间中；
 	* 如果 inline 函数有多个返回点，将其转变为 	inline 函数代码块末尾的分支（使用 GOTO）。
 	*/

 ###  sizeof
 
 空类的大小为1字节
 
一个类中，虚函数本身、成员函数（包括静态与非静态）和静态数据成员都是不占用类对象的存储空间。

对于包含虚函数的类，不管有多少个虚函数，只有一个虚指针,vptr的大小。

普通继承，派生类继承了所有基类的函数与成员，要按照字节对齐来计算大小

虚函数继承，不管是单继承还是多继承，都是继承了基类的vptr。(32位操作系统4字节，64位操作系统 8字节)！虚继承,继承基类的vptr。
 
 ## 类与对象
 
 ### 构造函数
 
       classname(){}; 
       拷贝构造函数
       classname (const classname & name){}
       classname name();会被认为成一个函数声明
       calssname name = classname(arg)   ;后者为临时对象,下一行释放
       作为函数参数值传递,调用拷贝构造函数.
       作为函数返回值,返回一个新的对象.
       定义有参构造,不再提供默认构造
       定义拷贝构造,不在提供构造.
 
 ####  初始化列表
 
 	classname (int a,int b):A(a),B(b){
 	
 	}
 #### 类对象做成员
 
 	初始化时先构造本类成员.
 	析构时先析构本类
 
 #### 静态
 
 	静态变量:所有对象共有'
 	编译阶段分配
 	类内声明,类外初始化
 	静态函数:所有类共享,静态成员函数访问静态变量.
 
 #### 对象大小
 
 	空对象占用1字节.(编译器用来区分空对象
 	非空对象:内存对齐
 	静态成员函数不属于类
 
 #### this
 
 	指向调用的对象
 	返回对象本身:*this  (链式调用)
 
 #### 空指针调用函数
 
 	calssname * name = NULL;
 	name->fun()   函数里不访问成员时可以.
 
 #### const常函数,常对象
 
 	void func() const {};  原理:改变this的值,使成为 const classname * const  this
 	加mutable 在常函数 中可以修改
 	const calssname name  namk不可修改
 	常对象只能调用常函数
 
 
 
 ### 友元
 
 	friend  void func();
 	friend  classname;
 	friend   classname::func()
 	
 ### 运算符重载
 
 	成员函数重载及全局重载
 	void operator + (arg){   return}
 	全局重载<<
 	ostream & operator << (ostream & cout,a ){
 	return cout;}
 	重载 ++
 	前置 
 	classname & operator++()
 	{ return *this}
 	后置 
 	classname & operator++(int)
 	{ return *this}
	占位参数区分前后置. 
 	
 	
 ### 继承
 
 	class name : public parentClass
 	公共继承,
 	保护继承,到子类全部为保护及私有
 	私有继承,全部私有
 	父类中所有非静态成员都会被继承
 
 #### 构造与析构
 
 	父类构造->子类构造->子类析构->父类构造
 
 #### 同名函数
 
 	classname.parentname::name    访问父类成员属性
 	子类会隐藏父类同名成员函数
 	静态:
 	classname:parentname:name
 	
 #### 多继承
 
 	利用虚继承解决菱形继承问题
 	calssname : virtual classname
 	
 ### 多态
 派生类.虚函数
 
 	virtual void func(){}虚函数,地址晚绑定
 	继承,子类重写父类虚函数
 	使用:类指针或者引用执行子类对象
 	原理:父类中存在一个虚函数(表)指针
 	虚函数表:记录虚函数地址
 	子类重写父类虚函数;
 	子类虚函数表内部会被替换成子类虚函数表
 
 #### 纯虚函数和抽象类
 
 	抽象类:无法实例化,子类必须重写虚函数否则还是抽象类
 	纯虚函数:irtual void func()= 0;
 
 #### 虚构和纯虚析构
 
 	解决父类释放子类资源
 	~virtual classname();
 	纯虚析构: virtual ~calaname()= 0 ;
 
 
 ###文件操作

	头文件<fstream>
	 fd.open("1.txt",ios::in);
	    if(!fd.is_open())
	    {
	        cout<<"文件打开失败"<<endl;
	        return 0 ;
	    }
	    char buffer[1024] = {0};
	    while (fd>>buffer)
	    {
	        cout<<buffer<<endl;
	    }
	   2:
	    while (fd.getline(buffer,sizeof(buffer)))
	    {
	        cout<<buffer<<endl;
	    }
	    3:
	     string buffer;
	    while (getline(fd,buffer))
	    {
	        cout<<buffer<<endl;
	    }
	    二进制写入:
	    fd.write(const char * p,length)
	    读:
	    fd.read(char * buffer,length)

### 泛型 模板
#### 函数模板

	Templete<typename T>
	func()
	显示指定类型
	func<int>();
	自动推导必须推出一致的数据类型
	推出数据类型才能使用函数
	普通函数会发生隐式类型转化
	函数模板用显示指定参数类型会发生类型转换

#### 普通函数与模板函数同名

	优先调用普通函数
	可用空模板强制调用函数模板
	函数模板可以重载
	函数模板有更好的匹配,优先函数模板
	模板特殊重载
	templete<> bool func(int a,int b
	
####类模板

	
