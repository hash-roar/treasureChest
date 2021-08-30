# 基础

#### .pro文件

```properties
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets 
#兼容版本4


CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
```

#### main.cpp

```c++
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    //应用程序对象
    QApplication a(argc, argv);
    //窗口对象
    MainWindow w;
    //显示窗口
    w.show();
    //阻塞函数,程序进入循环
    return a.exec();
}

```

## 窗口

### 窗口类

#### QWidget

所有窗口基类

#### QDialog

```c++
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog_test1.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
   //非模态
   ui->setupUi(this);
   Dialog_test1 * dlg = new Dialog_test1();
   dlg->show();
   //模态
   dlg->exec();//阻塞
}

MainWindow::~MainWindow()
{
    delete ui;
}


```

#### QMainWindow

具有工具栏菜单栏

### 坐标

以左上角为原点,向向右向下增长

以父窗口为根据

```c++
move(int x,int y)//移动

setFixedSize(int weigth,int height)//大小

```

### 内存回收机制

必须QObject类子类或简介子类,

维护了一个对象树,父节点释放时会释放所有子类

```c++
//构造函数指定父对象

//函数指定父对象
```

## 工具

### 日志类

```c++
#include<QDebug>

qDebug()<<"somthing"<<1000;

```

### 输出到控制台

config文件

```c++
conig += console
```

### 类型

#### 字符串类型

QByteArray

```c++
与char*转换
char* QByteArray::data()
    

```

QString

两者区别

前者内部是普通char* ,计算的长度就是字符长度.后者是处理过的,转换为utf8编码

### QVariant

包装基础函数类型,作为接口

```c++
//
QVariant q();
q.setValue();

//对自定义类型处理
Q_DECLARE_METATYPE();
//流程
Q_DECLARE_METATYPE(myType)
myType t();
////封装1
QVaruant v;
v.setValue(t);
////封装2
QVaruant v = QVaruant::fromValue(t);
//取出数据
if(v.canConvert<MyType>())
    Mytype tem = v.value<myType>
```

### 坐标类

#### QPoint

点

#### QLine

```c++
构造
(qpoint 1,qpoin 2)//
(x1,y1,x2,y2)//

//平移
    void translate(qpoint &offset)
    void translate(int dx,int dy)
    QLine translated()
//比较
    //== 起点终点相同
```

Qsize

长度和宽度

#### QRect

矩形类

### 时间类

QDate

日期

```c++
QDate::getCurrentTime()//当前日期,静态函数
qDate q = QDate::getCurrentTime();
QString  = q.toString("YYYY-MM-dd");
```

#### QTime

#### QDAteTime

### 信号槽

观察者模式,监听事件

#### connect

注册信号处理者





