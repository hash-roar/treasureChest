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


	
	
