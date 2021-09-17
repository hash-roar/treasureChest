---
title: yaml文件
date: 2021-09-8 20:5:30
tags: 
  - web开发 
categories: 
  - [术,web开发]

---

# yaml文件

## 1-yaml文件介绍

> YAML 语言（发音 /ˈjæməl/ ）的设计目标，就是方便人类读写。它实质上是一种通用的数据串行化格式。
>
> 其让人最容易上手的特色是巧妙避开各种封闭符号，如：引号、各种括号等，这些符号在嵌套结构中会变得复杂而难以辨认。

**一种适合于程序间交换数据**,**及配置文件编写的文件格式**

### 实例1

```yaml
languages:
  - Ruby
  - Perl
  - Python 
websites:
  YAML: yaml.org 
  Ruby: ruby-lang.org 
  Python: python.org 
  Perl: use.perl.org
```

转换为json文件变成:

```json
{ 
  languages: [ 'Ruby', 'Perl', 'Python'],
  websites: {
    YAML: 'yaml.org',
    Ruby: 'ruby-lang.org',
    Python: 'python.org',
    Perl: 'use.perl.org' 
  } 
}
```

### 实例2

```yaml
name: John Smith 
age:  37 
spouse: 
    name: Jane Smith 
    age:  25 
children: 
    -   name: Jimmy Smith 
        age:  15 
    -   name: Jenny Smith 
        age   12
```

> 解析成php

```php
<?php
$john = array(
    'name' => 'John Smith',
    'age' => 37,
    'spouse' => array(
        'name' => 'Jane Smith',
        'age' => 25
    ),
    'children' => array(
        0 => array(
            'name' => 'Jimmy Smith',
            'age' => 5
        ),
        1 => array(
            'name' => 'Jenny Smith',
            'age' => 3
        )
    )
);
```

> 看完这两个实例你已经大概明白yaml写法了,接下来只需再详细了解一下规则即可

## 2-基本语法

> - 大小写敏感
> - 使用缩进表示层级关系
> - 缩进不允许使用tab，只允许空格
> - 缩进的空格数不重要，只要相同层级的元素左对齐即可
> - '#'表示注释

### 2-1 数据类型

YAML 支持以下几种数据类型：

#### 2-1-1对象

> 对象：键值对的集合，又称为映射（mapping）/ 哈希（hashes） / 字典（dictionary）

用相同缩进表示相同层级,

**使用 “:”（冒号） + 空格表示单个键值对**:

```yaml
name: 
  - subname1: value
  - subname2: value  
```

**使用"{}"表示一个键值表**:

```yaml
name: {subname1: value, subname2:value}
```



#### 2-1-2数组

> 数组：一组按次序排列的值，又称为序列（sequence） / 列表（list）

**使用“-”（横线） + 单个空格表示单个列表项**:

```yaml
name:
 - value1
 - value2
```

**使用 "[]"(中括号) 表示列表**

```yaml
name: [value1, value2]
```

解析成json

```json
{
  "name":["value1","value2"]
}
```



#### 2-1-3纯量

纯量（scalars）：单个的、不可再分的值. 包括:**字符串,布尔值.整数,浮点数,Null,时间,日期**

