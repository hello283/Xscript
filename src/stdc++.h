#pragma once
#include<cassert>
#include<cctype>
#include<cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>

using namespace std;

string EmptyStr(){
    return "";
}

#if defined __WIN32
#include <io.h>

void GetFileNames(string path,vector<string>& filenames)
{
	path += (path[path.length() - 1] == '/') ? "*" : "/*"; // directory path
    intptr_t handle;
    _finddata_t findData;

    handle = _findfirst(path.data(), &findData);    // 查找目录中的第一个文件
    if (handle == -1)
    {
        cout << "Failed to find first file!\n";
        return;
    }

    do
    {

        if (EmptyStr() + findData.name != "." && EmptyStr() + findData.name != ".." ){
            cout << findData.name << endl;
            filenames.push_back( findData.name );
        }
    } while (_findnext(handle, &findData) == 0);    // 查找目录中的下一个文件

    _findclose(handle);    // 关闭搜索句柄
	return;
}

#else
#include <sys/types.h>
#include <dirent.h>

void GetFileNames(string path,vector<string>& filenames)
{
    DIR *pDir;
    struct dirent* ptr;
    if(!(pDir = opendir(path.c_str())))
        return;
    while((ptr = readdir(pDir))!=0) {
        if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0)
            filenames.push_back(ptr->d_name);
    }
    closedir(pDir);
}


#endif

std::string FloatToStr(float num){
    std::ostringstream oss;
	oss << num;
	std::string str(oss.str());
	return str;
}