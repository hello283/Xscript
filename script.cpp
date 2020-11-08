#include "src/env.h"

/*int main(int argc , const char **argv){
  map<string,string> args;
  for (size_t i = 0; i < argc; i++){
    string s=argv[i];
    vector<string> sp = CodeSplit(s,'=');
    args[sp[0]] = (sp.size() <= 1) ? sp[0] : sp[1];
  }

  try{
    string expr = Format(EasyFiles::ReadFile("./test/test.xs0"));
    cout << expr << endl;
    ScriptResult scr = Script(expr);
  }catch(Error::SyntaxError syx){
    syx.what();
  }catch(Error::TypeError tpx){
    tpx.what();
  }
}*/

int main(int argc , const char **argv){
  //cout << "Xscript IDLE\nXscript Core:" << CoreVersion() << getCompiler() << getVer() << " on " << OSType() << "\nPowered by Xiaokang0010\n";
  //cout << "Root addres: " << now_scope << endl;
  init_env(&root_scope);
  while(true){
    try{
      string expr = Format(EasyFiles::ReadFile("./test/test.xs0"));
      //Script(expr);
      ScriptResult scr = Script(expr);
      #ifdef __SCRIPT_DEBUG
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
      #endif
    }catch(Error::SyntaxError syx){
      syx.what();
    }catch(Error::TypeError tpx){
      tpx.what();
    }
    break;
  }
}
