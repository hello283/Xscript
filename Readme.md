# Xscript —— 一个简单的脚本语言

## 这玩意是个啥?
### 好吧，这是一个支持类继承，加载外部库，拥有stdlib，<s>而且没有人用的</s>脚本语言。
> Tips: 例程可以在test文件夹里面找到

## 给程序员看的
如果你想为Xscript作出贡献，您可以修复以下Bug,或增加新功能.
### Bugs:
> 函数没有callstack<br>
> for产生的变量不会收回<br>

### Todo:
> 完善stdlib: 增加substr函数，加入指针，完成数组<br>
> **修复bug!!!!!!!!**<bt>

## 已实现功能
- class
- function
- for
- while
- var
- const

## 注意

在正常使用时，你必须把`src/const.h`里的`#define __SCRIPT_DEBUG`去掉<br>
这个是用来查看调试输出的！<br>

## About

[Xiaokang00010](https://github.com/xiaokang00010)<br>
[Fox-Awa DevTeam](https://github.com/Fox-Awa)