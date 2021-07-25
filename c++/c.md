##


#### 枚举

	enum colors{red,yellow,colorNum}; 从左到右分别为0,1,.....
	小技巧:用colorNum作为color的总颜色数

### 结构

	struct date{
	int month;
	int day;
	int year;
	}
	初始化:
	struct date today={12,23,2021}
	struct date today={,23,2021}未给定的初始化为0
	stru1 = (struct date){3,5,2021}强制类型转换
	stru1 = stru2 结构赋值
	作为函数参数:
	fun(struct date d){} 会创建一个新变量d
	fun(struct date * p){}传入指针
	嵌套的结构:
	struct pointer{
	int x;
	int y;
	}p1;
	struct rectangle{
	struct pointer p1;
	struct pointer p2
}r1;调用:r1.p1.x
	


###
	