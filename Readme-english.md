# Xscript —— A simple script language

## What the fuck is this??
### Well,This is an support class extends，load share library，has stdlib，<s>no people used</s>'s Script Language.
> Tips: samples for developers can found at test directory

## For developer
If you want to contribute Xscript,you can fix these Bug or add new features.
### Bugs:
> function doesn't have callstack<br>

### Todo:
> perfect the stdlib: Add substr function<br>
> **fix bugs!!!!!!!!**<bt>

### Directory Struct:
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

## Finish features
- class
- function
- for
- while
- var
- const
- Array

## PLEASE ATTENTION

For user，you must delete `#define __SCRIPT_DEBUG` from `src/const.h`<br>
This is for developers to view debug output!<br>

## About us

[Xiaokang00010](https://github.com/xiaokang00010)<br>
[Fox-Awa DevTeam](https://github.com/Fox-Awa)