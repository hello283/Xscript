# Xscript —— 一个简单的脚本语言

## 基本语法

### 一段例程
```
package First;
import("__Xscript_Include__/stdlib.xs0",std);

const First = class{
  const Main = function(){
    print("Hello,World!");
    return 0;
  };
};

```
这段程序的作用就是创建一个主类，并在主类的Main方法里输出Hello,World

读完这段程序，相信你也知道了，**这个是一种类似于ECMAScript的语法**.<s>pyjvcpp</s>

## IDLE
```     
Xscript IDLE
Xscript Core:beta0_1 clang++:11.0.3 on macOS
Powered by Xiaokang0010
Root addres: 0x10da72618
>>> var a=1+1

>>> a
2
>>> a=1+2*2

>>> a
5
>>> a=1+1+4+514

>>> a
520
>>> exit
```
这是一段IDLE运行的打印结果<br>
`RootAddres`->主空间的内存地址，常用于调试<br>
`Core:beta0_1`->当前Xscript核心版本号<br>
`clang++/g++`->在编译时所使用的clang/gcc版本号<br>
`macOS/Linux/Windows32/Windows64`->编译平台<br>

## 注意

在正常使用时，你必须把`src/const.h`里的`#define __SCRIPT_DEBUG`去掉<br>
这个是用来查看调试输出的！<br>

## TODO
如果你是程序猿，你可以尝试修复或添加一些功能:<br>
- 为eval方法添加括号支持
- 加入for,while等循环
- 为词法分析器增加==,<=,>=,!=,>,<等支持  <font color="green">已完成</font>
- 为eval方法加入逻辑判断  <font color="green">已完成</font>

## About

[Xiaokang00010](https://github.com/xiaokang00010)<br>
[Fox-Awa DevTeam](https://github.com/Fox-Awa)