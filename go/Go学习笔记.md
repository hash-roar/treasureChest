# Go学习笔记

## 基础

### 包

1. **如果对一个包进行更改或重新编译，所有引用了这个包的客户端程序都必须全部重新编译。**

### 类型

1. Go 中不允许不同类型之间的混合使用，但是对于常量的类型限制非常少

### 函数

```go
func FunctionName (a typea, b typeb) (t1 type1, t2 type2)
```

### 常量

```go
const (
    Monday, Tuesday, Wednesday = 1, 2, 3
    Thursday, Friday, Saturday = 4, 5, 6
)
```

### 变量

1. 变量的命名规则遵循骆驼命名法，即首个单词小写，每个新单词的首字母大写，例如：`numShips` 和 `startDate`。

2. 全局变量希望能够被外部包所使用，则需要将首个单词的首字母也大写

3. 在函数体内声明局部变量时，应使用简短声明语法 `:=`,只能被用在函数体内

4. ```go
   a, b, c := 5, 7, "abc"
   ```

   连续声明赋值

### 运算符

#### ==

1. Go 对于值之间的比较有非常严格的限制，只有两个类型相同的值才可以进行比较，如果值的类型是接口（interface，第 11 章），它们也必须都实现了相同的接口。如果其中一个值是常量，那么另外一个值的类型必须和该常量类型相兼容的。如果以上条件都不满足，则其中一个值的类型必须在被转换为和另外一个值的类型相同之后才可以进行比较。

2. 对于布尔值而言，好的命名能够很好地提升代码的可读性。例如以 `is` 或者 `Is` 开头的 `isSorted`、`isFinished`、`isVisible`

#### 字符类型

1. 严格来说，这并不是 Go 语言的一个类型，字符只是整数的特殊用例。`byte` 类型是 `uint8` 的别名，对于只占用 1 个字节的传统 ASCII 编码的字符来说，完全没有问题

#### 字符串

1. Go 支持以下 2 种形式的字面值：

**解释字符串**：

该类字符串使用双引号括起来，其中的相关的转义字符将被替换，这些转义字符包括：

- `\n`：换行符
- `\r`：回车符
- `\t`：tab 键
- `\u` 或 `\U`：Unicode 字符
- `\\`：反斜杠自身

非解释字符串：

该类字符串使用反引号括起来，支持换行，例如：

```go
`This is a raw string \n` 中的 `\n\` 会被原样输出。
```

2. `string` 类型的零值为长度为零的字符串，即空字符串 `""`。
3.  获取字符串中某个字节的地址的行为是非法的，例如：`&str[i]`



### 指针

1. 如：`pointer+2`，移动指针指向字符串的字节数或数组的某个位置）是不被允许的。

## 流程控制

### 测试多返回值函数的错误

```go
an, err := strconv.Atoi(orig)
    if err != nil {
        fmt.Printf("orig %s is not an integer - exiting with error\n", orig)
        return
    } 
```

**习惯用法:**

```go
if err := file.Chmod(0664); err != nil {
    fmt.Println(err)
    return err
}
```

### for

1. 基于计数器的迭代

```
 for i := 0; i < 5; i++ {
        fmt.Printf("This is the %d iteration\n", i)
    }
```

2.  for-range 结构

一般形式为：`for ix, val := range coll { }`。

要注意的是，`val` 始终为集合中对应索引的值拷贝，因此它一般只具有只读性质，对它所做的任何修改都不会影响到集合中原有的值

### goto

```go
func main() {
    i:=0
    HERE:
        print(i)
        i++
        if i==5 {
            return
        }
        goto HERE
}
```

## 函数

### 基础

1. 假设 f1 需要 3 个参数 `f1(a, b, c int)`，同时 f2 返回 3 个参数 `f2(a, b int) (int, int, int)`，就可以这样调用 f1：`f1(f2(a, b))`。
2. 在函数块里面，`return` 之后的语句都不会执行。如果一个函数需要返回值，那么这个函数里面的每一个代码分支（code-path）都要有 `return` 语句。
3. 在函数调用时，像切片（slice）、字典（map）、接口（interface）、通道（channel）这样的引用类型都是默认使用引用传递（即使没有显式的指出指针）。
4. 函数命名返回值

```go
func getX2AndX3_2(input int) (x2 int, x3 int) {
    x2 = 2 * input
    x3 = 3 * input
    // return x2, x3
    return
}
```

5. 空白符用来匹配一些不需要的值，然后丢弃掉

```go
i1, _, f1 = ThreeValues()
```

6. **变长参数,**如果函数的最后一个参数是采用 `...type` 的形式，那么这个函数就可以处理一个变长的参数，这个长度可以为 0，这样的函数称为变长函数。
7. 如果一个变长参数的类型没有被指定，则可以使用默认的空接口 `interface{}`，这样就可以接受任何类型的参数



#### defer

1. 关键字 defer 允许我们推迟到函数返回之前（或任意位置执行 `return` 语句之后）一刻才执行某个语句或函数
2. 当有多个 defer 行为被注册时，它们会以逆序执行（类似栈，即后进先出

### 闭包

1. 匿名函数

```
 g := func(i int) { fmt.Printf("%d ", i) } //此例子中只是为了演示匿名函数可分配不同的内存地址，在现实开发中，不应该把该部分信息放置到循环中。
        g(i)
```

2. 闭包函数保存并积累其中的变量的值，不管外部函数退出与否，它都能够继续操作外部函数中的局部变量。
3. 这些局部变量同样可以是参数，
4. 实例

```go
func MakeAddSuffix(suffix string) func(string) string {
    return func(name string) string {
        if !strings.HasSuffix(name, suffix) {
            return name + suffix
        }
        return name
    }
}
addBmp := MakeAddSuffix(".bmp")
addJpeg := MakeAddSuffix(".jpeg")
```

## 容器

### 数组

1. Go 语言中的数组是一种 **值类型**（不像 C/C++ 中是指向首元素的指针），所以可以通过 new() 来创建： var arr1 = new([5]int)。

   那么这种方式和 var arr2 [5]int 的区别是什么呢？arr1 的类型是 *[5]int，而 arr2 的类型是 [5]int。

2. 这样的结果就是当把一个数组赋值给另一个时，需要再做一次数组内存的拷贝操作

### 切片

#### 基础

1. 切片（slice）是对数组一个连续片段的引用（该数组我们称之为相关数组，通常是匿名的），所以切片是一个引用类型
2. 切片提供了计算容量的函数 `cap()` 可以测量切片最长可以达到多少：它等于切片从第一个元素开始，到相关数组末尾的元素个数。
3. 一个切片 s 可以这样扩展到它的大小上限：`s = s[:cap(s)]`，如果再扩大的话就会导致运行时错误
4. `arr1[:3]` 和 `arr1[0:3]` 相同，包含了从第一个到第三个元素（不包括第四个 / 不包含下标为三的元素）。
5. `s2 = s2[-1:]` 会导致编译错误。切片不能被重新分片以获取数组的前一个元素。
6. **绝对不要用指针指向 slice。切片本身已经是一个引用类型，所以它本身就是一个指针！！**
7. 创建一个 slice1，它不占用整个数组，而只是占用以 len 为个数个项，那么只要：`slice1 := make([]type, len, cap)`。
8. 实例

```go
make([]int, 50, 100)
new([100]int)[0:50]
//这俩个相同
```

#### new 和make区别

new (T) 为每个新的类型 T 分配一片内存，初始化为 0 并且返回类型为 * T 的内存地址：这种方法 返回一个指向类型为 T，值为 0 的地址的指针，它适用于值类型如数组和结构体（参见第 10 章）；它相当于 &T{}。
make(T) 返回一个类型为 T 的初始值，它只适用于 3 种内建的引用类型：切片、map 和 channel（参见第 8 章，第 13 章）。

#### 遍历

```go
for ix, value := range slice1 {
    ...
}
```

第一个返回值 ix 是数组或者切片的索引，第二个是在该索引位置的值

#### 实例

1. 假设 s 是一个字符串（本质上是一个字节数组），那么就可以直接通过 `c := []byte(s)` 来获取一个字节数组的切片 c

2. 在内存中，一个字符串实际上是一个双字结构，即一个指向实际数据的指针和记录字符串长度的整数（见图 7.4）。因为指针对用户来说是完全不可见，因此我们可以依旧把字符串看做是一个值类型，也就是一个字符数组。

3. 复制切片 a 的元素到新的切片 b 上：

   ```go
    b = make([]T, len(a))
    copy(b, a)
   ```

4. 为切片 a 扩展 j 个元素长度：`a = append(a, make([]T, j)...)`
5. 在索引 i 的位置插入切片 b 的所有元素：`a = append(a[:i], append(b, a[i:]...)...)`

### map

1. map 传递给函数的代价很小：在 32 位机器上占 4 个字节，64 位机器上占 8 个字节，无论实际上存储了多少数据。通过 key 在 map 中寻找值是很快的，比线性查找快得多，但是仍然比从数组和切片的索引中直接读取要慢 100 倍
2. 初始化

```go
mapLit = map[string]int{"one": 1, "two": 2}
mapCreated := make(map[string]float32)
mapAssigned = mapLit

mapCreated["key1"] = 4.5
mapCreated["key2"] = 3.14159
mapAssigned["two"] = 3
```

3. 如果你错误的使用 new () 分配了一个引用对象，你会获得一个空引用的指针，相当于声明了一个未初始化的变量并且取了它的地址
4. 用切片作为 map 的值:

```go
mp1 := make(map[int][]int)
mp2 := make(map[int]*[]int)
```

5. map 默认是无序的，不管是按照 key 还是按照 value 默认都不排序（详见第 8.3 节）。

   如果你想为 map 排序，需要将 key（或者 value）拷贝到一个切片，再对切片排序

## 结构体与方法

### 实例

```go

type struct1 struct {
    i1  int
    f1  float32
    str string
}

func main() {
    ms := new(struct1)
    ms.i1 = 10
    ms.f1 = 15.5
    ms.str= "Chris"

    fmt.Printf("The int is: %d\n", ms.i1)
    fmt.Printf("The float is: %f\n", ms.f1)
    fmt.Printf("The string is: %s\n", ms.str)
    fmt.Println(ms)
}
```

```go
 ms := &struct1{10, 15.5, "Chris"}
```

### 方法

1. 类型和作用在它上面定义的方法必须在同一个包里定义
2. 当一个匿名类型被内嵌在结构体中时，匿名类型的可见方法也同样被内嵌，这在效果上等同于外层类型 **继承** 了这些方法：**将父类型放在子类型中来实现亚型**。

## 接口和反射

### 接口

1. ```go
   type Namer interface {
       Method1(param_list) return_type
       Method2(param_list) return_type
       ...
   }
   ```

   2. 类型不需要显式声明它实现了某个接口：接口被隐式地实现。多个类型可以实现同一个接口。

      实现某个接口的类型（除了实现接口方法外）可以有其他的方法。

      一个类型可以实现多个接口。

      接口类型可以包含一个实例的引用， 该实例的类型实现了此接口（接口是动态类型）

   3. 接口变量里包含了接收者实例的值和指向对应方法表的指针。

   4. **类型断言:**

   5. **type-switch**:

   ```go
   switch t := areaIntf.(type) {
   case *Square:
       fmt.Printf("Type Square %T with value %v\n", t, t)
   case *Circle:
       fmt.Printf("Type Circle %T with value %v\n", t, t)
   case nil:
       fmt.Printf("nil value: nothing to check?\n")
   default:
       fmt.Printf("Unexpected type %T\n", t)
   }
   ```

   6. 你想将切片中的数据复制到一个空接口切片中,可惜不能这么做，编译时会出错.原因是它们俩在内存中的布局是不一样的必须使用 `for-range` 语句来一个一个显式地复制：

   ### 反射

   1. reflect.Type 和 reflect.Value 都有许多方法用于检查和操作它们。一个重要的例子是 Value 有一个 Type 方法返回 reflect.Value 的 Type。另一个是 Type 和 Value 都有 Kind 方法返回一个常量来表示类型：Uint、Float64、Slice 等等。同样 Value 有叫做 Int 和 Float 的方法可以获取存储在内部的值

   2. 函数通过传递一个 x 拷贝创建了 v，那么 v 的改变并不能更改原始的 x。要想 v 的更改能作用到 x，那就必须传递 x 的地址 v = reflect.ValueOf(&x)。

      通过 Type () 我们看到 v 现在的类型是 *float64 并且仍然是不可设置的。

      要想让其可设置我们需要使用 Elem() 函数，这间接的使用指针：v = v.Elem()

   3. 当一个类型包含（内嵌）另一个类型（实现了一个或多个接口）的指针时，这个类型就可以使用（另一个类型）所有的接口方法。

   

   ## io

   ### 读取

   1. 读取标准输入:

   Scanln 扫描来自标准输入的文本，将空格分隔的值依次存放到后续的参数内，直到碰到换行。Scanf 与其类似，除了 Scanf 的第一个参数用作格式字符串，用来决定如何读取。Sscan 和以 Sscan 开头的函数则是从字符串读取，除此之外，与 Scanf 相同

   

   2. 

   

   



