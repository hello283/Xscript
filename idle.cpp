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
  cout << "Xscript IDLE\nXscript Core:" << CoreVersion() << getCompiler() << getVer() << " on " << OSType() << "\nPowered by Xiaokang0010\n";
  cout << "Root addres: " << now_scope << endl;
  while(true){
    #ifndef __WIN32
    cout << "\033[32m>>> \033[0m";
    #endif
    #ifdef __WIN32
    cout << ">>> ";
    #endif
    try{
      string expr;
      getline(cin,expr);
      //Script(expr);
      ScriptResult scr = Script(expr);
      if(scr.Content.vtype == _int){
        cout << stoi_(scr.Content.content) << endl;
      }else if(scr.Content.vtype == _str){
        cout << scr.Content.content << endl;
      }else if(scr.Content.vtype == _bol){
        Type iftrue(now_scope);iftrue.type = _var;iftrue.vtype = _bol;iftrue.content.resize(1);iftrue.content[0] = (char)1;
        //Type iffalse(now_scope);iffalse.type = _var;iffalse.vtype = _bol;iffalse.content.resize(1);iffalse.content[0] = (char)0;
        cout << (int)scr.Content.content[0] << endl;
      }else{
        cout << scr.Content.content << endl;
      }
    }catch(Error::SyntaxError syx){
      syx.what();
    }
  }
	//string a = Format(EasyFiles::ReadFile("./sample/first.xs0"));
	//cout << a;
	//vector<string> CodeArr = CodeSplit(a,';');
	/*for(int i = 0;i < CodeArr.size();i++){
		vector<word> a = WordParser(CodeArr[i]);
		for(int i=0;i<a.size();i++){
			cout << setw(8) << "Type:" << a[i].word_type << " Word: " << a[i].wd ;
		}
		cout << endl;
		//cout << CodeArr[i] << setw(4) << "";
	}
	cout << endl;*/
}
