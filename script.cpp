#include "src/script.h"

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
        " clang++:";
      #else
        " g++:";
      #endif

      
      return true_cxx;

}

int main(int argc , const char **argv){
  map<string,string> args;
  for (size_t i = 0; i < argc; i++){
    string s=argv[i];
    vector<string> sp = CodeSplit(s,'=');
    args[sp[0]] = (sp.size() <= 1) ? sp[0] : sp[1];
  }
  
  try{
    string expr = EasyFiles::ReadFile(args["input"]);
    ScriptResult scr = Script(expr);
  }catch(Error::SyntaxError syx){
    syx.what();
  }catch(Error::TypeError tpx){
    tpx.what();
  }
}
