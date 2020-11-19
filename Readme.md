# Xscript —— 一个简单的脚本语言

## 这玩意是个啥?
### 好吧，这是一个支持类继承，加载外部库，拥有stdlib，<s>而且没有人用的</s>脚本语言。
> Tips: 例程可以在test文件夹里面找到

## 给程序员看的
如果你想为Xscript作出贡献，您可以修复以下Bug,或增加新功能.
### Bugs:
> 函数没有callstack<br>

### Todo:
> 完善stdlib: 增加substr函数<br>
> **修复bug!!!!!!!!**<bt>

### 目录结构:
```bash

├── build
│   ├── idle
│   ├── idle.dSYM
│   │   └── Contents
│   │       ├── Info.plist
│   │       └── Resources
│   │           └── DWARF
│   │               └── idle
│   ├── idle.exe
│   ├── include
│   │   ├── lib
│   │   │   ├── array
│   │   │   ├── array.cpp
│   │   │   ├── array.exe
│   │   │   ├── Makefile
│   │   │   ├── Makefile.cross
│   │   │   ├── stdlib
│   │   │   ├── stdlib.cpp
│   │   │   └── stdlib.exe
│   │   └── stdlib.xs0
│   ├── script
│   ├── script.dSYM
│   │   └── Contents
│   │       ├── Info.plist
│   │       └── Resources
│   │           └── DWARF
│   │               └── script
│   ├── script.exe
│   └── test
│       ├── a
│       ├── a.cpp
│       └── test.xs0
├── build.tar
├── directory.txt
├── idle.cpp
├── idle.dSYM
│   └── Contents
│       ├── Info.plist
│       └── Resources
│           └── DWARF
│               └── idle
├── main.dSYM
│   └── Contents
│       ├── Info.plist
│       └── Resources
│           └── DWARF
│               └── main
├── make_all.sh
├── Makefile.unix-like
├── Makefile.win
├── Makefile.wincross
├── Readme-english.html
├── Readme-english.md
├── Readme_files
│   └── katex.min.css
├── Readme.html
├── Readme.md
├── sample
│   ├── first.xs0
│   └── testfile.idle
├── script.cpp
├── script.dSYM
│   └── Contents
│       ├── Info.plist
│       └── Resources
│           └── DWARF
│               └── script
└── src
    ├── const.h
    ├── dlfcn.h
    ├── env.h
    ├── error.h
    ├── script.h
    ├── stdc++.h
    ├── type.h
    └── words.h

27 directories, 49 files

```

## 已实现功能
- class
- function
- for
- while
- var
- const
- Array

## 注意

在正常使用时，你必须把`src/const.h`里的`#define __SCRIPT_DEBUG`去掉<br>
这个是用来查看调试输出的！<br>

## About

[Xiaokang00010](https://github.com/xiaokang00010)<br>
[Fox-Awa DevTeam](https://github.com/Fox-Awa)