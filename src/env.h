#include "./script.h"
using namespace std;


#ifdef _WIN32
  #ifdef _WIN64
    string OSType(){return "Windows64";}
  #else
    string OSType(){return "Windows32";}
  #endif
#endif

#ifdef __linux__
#include <sys/utsname.h>
string OSType(){
  struct utsname u;
  uname(&u);
  string s = "linux/";
  s+=u.machine;
  return s;
}
#endif

#ifdef __APPLE__
  string OSType(){return "macOS";}
#endif

std::string ver_string(int a, int b, int c) {
  std::ostringstream ss;
  ss << a << '.' << b << '.' << c;
  return ss.str();
}
string getVer() {
      std::string true_cxx =
      #ifdef __clang__
        "clang++";
      #else
        "g++";
      #endif

      std::string true_cxx_ver =
      #ifdef __clang__
        ver_string(__clang_major__, __clang_minor__, __clang_patchlevel__);
      #else
        ver_string(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
      #endif
      return true_cxx_ver;

}

string getCompiler() {
      std::string true_cxx =
      #ifdef __clang__
        "clang++";
      #else
        "g++";
      #endif

      
      return true_cxx;

}

void init_env(Type* root){
    Type temp(root);
    #if defined(_WIN32)
    temp.type = _var;
    temp.vtype = _str;
    temp.mod = _const;
    temp.content = "WIN32";
    root->node["os"] = temp;
    #endif
    #if defined(_WIN64)
    temp.type = _var;
    temp.vtype = _str;
    temp.mod = _const;
    temp.content = "WIN64";
    root->node["os"] = temp;
    #endif
    #if defined(__linux__)
    temp.type = _var;
    temp.vtype = _str;
    temp.mod = _const;
    temp.content = "linux";
    root->node["os"] = temp;
    #endif
    #if defined(__APPLE__)
    temp.type = _var;
    temp.vtype = _str;
    temp.mod = _const;
    temp.content = "macOS";
    root->node["os"] = temp;
    #endif
    temp.type = _var;
    temp.vtype = _str;
    temp.mod = _const;
    temp.content = getCompiler();
    root->node["compiler"] = temp;
    temp.type = _var;
    temp.vtype = _str;
    temp.mod = _const;
    temp.content = getVer();
    root->node["compiler_version"] = temp;
    temp.type = _var;
    temp.vtype = _str;
    temp.mod = _const;
    temp.content = CoreVersion();
    root->node["core_ver"] = temp;
}