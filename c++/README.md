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
	const对象只能访问const成员函数,而非const对象可以访问任意的成员函数,包括const成员函数: