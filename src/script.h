#include "stdc++.h"
#include "words.h"
#include "type.h"
#include "error.h"
#include "const.h"
#include "dlfcn.h"

using namespace std;

string pkgname = "";

string CoreVersion(){
  return "release1.1";
}

enum hantype{
  __lib,
  //__proc
};

struct handle{
  bool exist;
  hantype htype;
  int arg1;
  void* arg2;
  string arg3;
};

map<int,handle> handles;

size_t find(string str,char ch,int start = 0){
        int taowa = 0,taowa1 = 0;
        bool bkh = 0,xkh = 0,instr = 0;
        for(int i = start;i < str.length();i++){
            if(str[i] == '"')  instr = !instr;
            if(str[i] == '(' && !instr){
                taowa++;
                if(xkh == true)  {goto con;}
                xkh = true;
            }
            if(str[i] == ')' && !instr){
                taowa--;
            }
            if(str[i] == '{' && !instr){
                taowa1++;
                if(bkh == true)  {goto con;}
                bkh = true;
            }
            if(str[i] == '}' && !instr){
                taowa1--;
            }
            con:
            //cout << taowa << " " << taowa1 << endl;
            if(str[i] == ch && taowa == 0 && taowa1 == 0 && !instr){
                return i;
            }
        }
        return 18446744073709551615;
    }

namespace EasyFiles{
	class FileError{
		public:
		class CanNotOpenFile{
			public:
			void what(){
				cerr << "Can Not Open File!\n";
			}
		};
	};
	string ReadFile(string FileName){
		string ret;
		FILE* fd = fopen(FileName.data(),"r+");
    if(fd == NULL){
      cout << "Failed!:" << FileName << endl;
      throw EasyFiles::FileError::CanNotOpenFile();
    }else{
      for (char byte = 0; (byte = fgetc(fd)) != EOF ; ret += byte);
      return ret;
    }
	}

	string WriteFile(string FileName,string Output){
		fstream f1;
  	f1.open(FileName.data(),ios::out|ios::trunc|ios_base::out);
		if(!f1.is_open()){
      cout << "Failed:" << FileName << endl;
      throw FileError::CanNotOpenFile();
    }
		f1 << Output;
		f1.close();
		return Output;
	}
}

string&   replace_all(string&   str,const   string&   old_value,const   string&   new_value)
{
    while(true)   {
        string::size_type   pos(0);
        if(   (pos=str.find(old_value))!=string::npos   )
            str.replace(pos,old_value.length(),new_value);
        else   break;
    }
    return   str;
}

Type root_scope;
Type* now_scope = &root_scope;

enum resultT{
  _return=1,
  _lopbreak=2,
  _lopcontinue=3,
  _finally=3,
};

enum Script_{
	__SUCCESS__=1,
  __FAILED__=2
};

class ScriptResult{
  public:
  resultT res;
  Type Content;
  ScriptResult(){}
  ScriptResult(Script_ t){
	 if(t==__SUCCESS__){
		 Content.content+=(char)1;
		 Content.type = _var;
     Content.vtype = _bol;
		 res = _finally;
	 }else{
     Content.content+=(char)0;
		 Content.type = _var;
     Content.vtype = _bol;
		 res = _finally;
   }
  }
};

// 判断Type指针是否安全，若否，则使其安全
// 傻逼g++O2优化把这段程序优化成段错误了
bool checkSafe(Type* target){
  for(map<string,Type>::iterator iter=target->node.begin();iter != target->node.end();iter++){
    checkSafe(&iter->second);
    if(iter->second.parent != target){
      #ifdef __SCRIPT_DEBUG
      cout << "野指针:" << iter->second.parent << " " << target << endl;
      #endif
      iter->second.parent = target;
    }
    if(iter->second.name != iter->first)  iter->second.name = iter->first;
  }
}

// 变量
Type getTypeContent(string name){
  #ifdef __SCRIPT_DEBUG
  cout << "GET:" << name << endl;
  #endif
  if(name == ""){
    return Type();
  }
  checkSafe(&root_scope);
  //checkSafe(now_scope);
  TypeFinder tpf = getPath(name);
  Type global = root_scope.getNode(tpf);
  if(global.type != _not_exist) return global;
  Type thisScope = now_scope->getNode(tpf);
  if(thisScope.type != _not_exist) return thisScope;

  Type inThisParent = now_scope->parent->getNode(tpf);
    return inThisParent;
  
}

bool IsTypeExist(string name){
  checkSafe(&root_scope);
  TypeFinder tpf = getPath(name);
  if(now_scope->parent->isexist(tpf)){
    return true;
  }else if(now_scope->isexist(tpf)){
    return true;
  }else if(root_scope.isexist(tpf)){
    return true;
  }else{
    return false;
  }
}

Type *getTypeAddr(string name){
  Type unk;
  if(name == ""){
    return &unk;
  }
  checkSafe(&root_scope);
  //checkSafe(now_scope);
  TypeFinder tpf = getPath(name);
  Type *global = root_scope.getNodeAddr(tpf);
  if(global->type != _not_exist){
    return global;
  }
  Type *thisScope = now_scope->getNodeAddr(tpf);
  if(thisScope->type != _not_exist)  return thisScope;
  Type *inThisParent = now_scope->parent->getNodeAddr(tpf);
    return inThisParent;
}

bool setTypeContent(string name,Type write,bool inglobal = false){
  checkSafe(&root_scope);
  //checkSafe(now_scope);
  TypeFinder tpf = getPath(name);
  if(now_scope->parent->isexist(tpf)){
    return now_scope->parent->setNode(tpf,write);
  }
  if(inglobal)  return root_scope.setNode(tpf,write);
  return now_scope->setNode(tpf,write);
}

bool deleteType(string name){
  checkSafe(&root_scope);
  //checkSafe(now_scope);
  TypeFinder tpf = getPath(name);
  if(root_scope.isexist(tpf)){
    return now_scope->deletes(tpf);
  }
  else if(now_scope->parent->isexist(tpf)){
    return now_scope->parent->deletes(tpf);
  }else if(root_scope.isexist(tpf)){
    return root_scope.deletes(tpf);
  }else{
    return false;
  }
}

bool newTypeContent(string name,Type write,bool inglobal = false){
  checkSafe(&root_scope);
  checkSafe(now_scope);
  TypeFinder tpf = getPath(name);
  if(inglobal)  return root_scope.newNode(tpf,write);
  return now_scope->newNode(tpf,write);
}

// 代码分割
vector<string> CodeSplit(string toSplit,char spliter){
    vector<string> result;
    bool flag = false;
    int taowa = 0;
    string tmp;
    for(int i = 0;i < toSplit.length();i++){
        if(toSplit[i] == '"'){
        //cout << "There is a \"!Flag Coverted!\n";
        flag = !flag;
        //continue;
        }
        if(toSplit[i] == spliter){
            if(flag || (!flag && taowa != 0)){
                //cout<< "Here Is Flag!Continue!\n";
                goto con;
            }
            else{
                //cout << flag << endl;
                //cout << toSplit[i] << ": There Not Flags!Pushing to array!\n";
                result.push_back(tmp);
                tmp = "";
                continue;
            }
        }
        if(toSplit[i] == '{' && !flag){
            taowa++;
        }
        if(toSplit[i] == '}' && !flag){
            taowa--;
        }

        con:
        tmp += toSplit[i];
        if(i == toSplit.length() - 1){
            //cout << "There Is End Of Str!\n";
            result.push_back(tmp);
            tmp = "";
            continue;
        }
        /**/
    }
    return result;
}

// 代码格式化
string Format(string s){
  //replace_all(s,"\n","");
  string res;
  bool blank_in_start = true,str = false,descript=false;
  for(int i = 0;i < s.length();i++){
    // String
    if(s[i] == 13)  continue;
    if(s[i] == '"' && !descript)  str=!str;
    if(s[i-1] == '*' && s[i] == '/' && !str){
			if(descript){descript=false;continue;}
			//else throw Error::SyntaxError("InvalidSyntax");
		}else if(s[i] == '\n' && !str){
			if(descript){descript=false;}
		}
		if(descript && !str)  continue;
		if(s[i] == '/' && s[i+1] == '/' && !str){
			descript = true;
			continue;
		}else if(s[i] == '/' && s[i+1] == '*' && !str){
			descript = true;
			continue;
		}
    // 删行首空格
    if(s[i] == '\n' && !str){blank_in_start = true;continue;}
    if(blank_in_start){
      if(s[i] == ' '){
        continue;
      }else{
        blank_in_start = false;
      }
    } 

    // 优化空格,lz不会正则，别tm烦我
    if(s[i] == ' ' && !str){
      if(s[i+1] == '+' || s[i+1] == '-' || s[i+1] == '*' || s[i+1] == '/' || s[i+1] == '%' || s[i+1] == '='){
        continue;
      }
      if(s[i-1] == '+' || s[i-1] == '-' || s[i-1] == '*' || s[i-1] == '/' || s[i-1] == '%' || s[i-1] == '='){
        continue;
      }
    }
    res+=s[i];
  }
  return res;
}
ScriptResult Script(string expr);
ScriptResult Script(vector<word> wrd);

class ExprTree{
public:
  word oper;
  int operlevel = -1;
  Type content;
  vector<ExprTree> lr;
  ExprTree(){} // For default

  // Create Expr Tree
  ExprTree(vector<word> tokens){
    lr.resize(2);
    vector<word> token_buf;
    int brackets=0;
    for(int i = 0;i < tokens.size();i++){
      if(tokens[i].word_type == chr){
        if(tokens[i].wd == "("){
          brackets++;
        }else if(tokens[i].wd == ")"){
          brackets--;
          if(!brackets) token_buf.push_back(tokens[i]);
        }
        if((tokens[i].wd == "!=" || tokens[i].wd == "==" || tokens[i].wd == ">=" || tokens[i].wd == "<=" || tokens[i].wd == ">" || tokens[i].wd == "<") && brackets == 0){
          #ifdef __SCRIPT_DEBUG
          cout << "Operate Level:1" << tokens[i].wd << endl;
          #endif
          operlevel = 1;
          oper = tokens[i];
          lr[0] = ExprTree(token_buf);
          lr[1] = ExprTree(WordCollection(tokens,i+1));
          token_buf.clear();
          return;
        }else if((tokens[i].wd == "*" || tokens[i].wd == "/" || tokens[i].wd == "%") && brackets == 0){
          #ifdef __SCRIPT_DEBUG
          cout << "Operate Level:3\n";
          #endif
          operlevel = 3;
          oper = tokens[i];
          lr[0] = ExprTree(token_buf);
          lr[1] = ExprTree(WordCollection(tokens,i+1));
          token_buf.clear();
          return;
        }else if((tokens[i].wd == "+" || tokens[i].wd == "-") && brackets == 0){
          #ifdef __SCRIPT_DEBUG
          cout << "Operate Level:2\n";
          #endif
          operlevel = 2;
          oper = tokens[i];
          lr[0] = ExprTree(token_buf);
          lr[1] = ExprTree(WordCollection(tokens,i+1));
          token_buf.clear();
          return;
        }else{
          //throw Error::SyntaxError("Invalid Expr!");
        }
        if(brackets){
          token_buf.push_back(tokens[i]);
        }
      }else{
        token_buf.push_back(tokens[i]);
      }

      if(i + 1 == tokens.size()){
        // 死也没有运算符
        #ifdef __SCRIPT_DEBUG
        cout << "Token-buf:" << token_buf[0].wd << endl;
        #endif
        content = Script(token_buf).Content;
        operlevel = 0;
        break;
      }
    }
  }
};

Type CallFunction(Type *func,vector<Type> args);

Type eval(ExprTree expr){
  // 左右两端哪个大先算哪个
  Type left,right;
  #ifdef __SCRIPT_DEBUG
  cout << "Size:" << expr.lr.size() << "OperLevel:" << expr.operlevel << endl;
  #endif
  if(expr.operlevel == 0)  return expr.content;
  else if(expr.operlevel == -1) return Type();
  //cout << "there?";
  if((expr.lr[0].operlevel > expr.lr[1].operlevel) || (expr.lr[0].operlevel == expr.lr[1].operlevel)){
    left = eval(expr.lr[0]);
    right = eval(expr.lr[1]);
  }else{
    left = eval(expr.lr[1]);
    right = eval(expr.lr[0]);
  }
  if(expr.oper.wd == "=="){
    //cout << "我人傻掉==.\n";    
    if(left.isexist(getPath("__eq__"))){
      vector<Type> targs;
      targs.push_back(right);
      return CallFunction(&left.node["__eq__"],targs);
    }else if(right.isexist(getPath("__eq__"))){
      vector<Type> targs;
      targs.push_back(left);
      return CallFunction(&left.node["__eq__"],targs);
    }
    if(left.vtype != right.vtype) throw Error::SyntaxError("TypeError: '==' operation must be applied to the same type as both prototypes!");
    Type iftrue(now_scope);iftrue.type = _var;iftrue.vtype = _bol;iftrue.content.resize(1);iftrue.content[0] = (char)1;
    Type iffalse(now_scope);iffalse.type = _var;iffalse.vtype = _bol;iffalse.content.resize(1);iffalse.content[0] = (char)0;
    if(left.vtype == _int && right.vtype == _int){
      if(stoi_(left.content) == stoi_(right.content))  return iftrue;
      return iffalse;
    }else{
      if(left.content == right.content)  return iftrue;
      return iffalse;
    }
  }else if(expr.oper.wd == "!="){
    //cout << "我人傻掉!=.\n";
    if(left.isexist(getPath("__neq__"))){
      vector<Type> targs;
      targs.push_back(right);
      return CallFunction(&left.node["__neq__"],targs);
    }else if(right.isexist(getPath("__neq__"))){
      vector<Type> targs;
      targs.push_back(left);
      return CallFunction(&left.node["__neq__"],targs);
    }
    if(left.vtype != right.vtype) throw Error::SyntaxError("TypeError: '==' operation must be applied to the same type as both prototypes!");
    Type iftrue(now_scope);iftrue.type = _var;iftrue.vtype = _bol;iftrue.content.resize(1);iftrue.content[0] = (char)1;
    Type iffalse(now_scope);iffalse.type = _var;iffalse.vtype = _bol;iffalse.content.resize(1);iffalse.content[0] = (char)0;
    if(left.vtype == _int && right.vtype == _int){
      if(stoi_(left.content) != stoi_(right.content))  return iftrue;
      return iffalse;
    }else{
      if(left.content != right.content)  return iftrue;
      return iffalse;
    }
  }else if(expr.oper.wd == "<"){
    //cout << "我人傻掉<.\n";
    if(left.isexist(getPath("__min__"))){
      vector<Type> targs;
      targs.push_back(right);
      return CallFunction(&left.node["__min__"],targs);
    }else if(right.isexist(getPath("__min__"))){
      vector<Type> targs;
      targs.push_back(left);
      return CallFunction(&left.node["__min__"],targs);
    }
    if(left.vtype != right.vtype) throw Error::SyntaxError("TypeError: '==' operation must be applied to the same type as both prototypes!");
    Type iftrue(now_scope);iftrue.type = _var;iftrue.vtype = _bol;iftrue.content.resize(1);iftrue.content[0] = (char)1;
    Type iffalse(now_scope);iffalse.type = _var;iffalse.vtype = _bol;iffalse.content.resize(1);iffalse.content[0] = (char)0;
    if(left.vtype == _int && right.vtype == _int){
      if(stoi_(left.content) < stoi_(right.content))  return iftrue;
      return iffalse;
    }else{
      throw Error::SyntaxError("TypeError: '*' operation must apply on two int proto object!");
    }
  }else if(expr.oper.wd == ">"){
    //cout << "我人傻掉>.\n";
    if(left.isexist(getPath("__max__"))){
      vector<Type> targs;
      targs.push_back(right);
      return CallFunction(&left.node["__max__"],targs);
    }else if(right.isexist(getPath("__max__"))){
      vector<Type> targs;
      targs.push_back(left);
      return CallFunction(&left.node["__max__"],targs);
    }
    if(left.vtype != right.vtype) throw Error::SyntaxError("TypeError: '==' operation must be applied to the same type as both prototypes!");
    Type iftrue(now_scope);iftrue.type = _var;iftrue.vtype = _bol;iftrue.content.resize(1);iftrue.content[0] = (char)1;
    Type iffalse(now_scope);iffalse.type = _var;iffalse.vtype = _bol;iffalse.content.resize(1);iffalse.content[0] = (char)0;
    if(left.vtype == _int && right.vtype == _int){
      if(stoi_(left.content) > stoi_(right.content))  return iftrue;
      return iffalse;
    }else{
      throw Error::SyntaxError("TypeError: '*' operation must apply on two int proto object!");
    }
  }else if(expr.oper.wd == "<="){
    //cout << "我人傻掉<=.\n";
    if(left.isexist(getPath("__mineq__"))){
      vector<Type> targs;
      targs.push_back(right);
      return CallFunction(&left.node["__mineq__"],targs);
    }else if(right.isexist(getPath("__mineq__"))){
      vector<Type> targs;
      targs.push_back(left);
      return CallFunction(&left.node["__mineq__"],targs);
    }
    if(left.vtype != right.vtype) throw Error::SyntaxError("TypeError: '==' operation must be applied to the same type as both prototypes!");
    Type iftrue(now_scope);iftrue.type = _var;iftrue.vtype = _bol;iftrue.content.resize(1);iftrue.content[0] = (char)1;
    Type iffalse(now_scope);iffalse.type = _var;iffalse.vtype = _bol;iffalse.content.resize(1);iffalse.content[0] = (char)0;
    if(left.vtype == _int && right.vtype == _int){
      if(stoi_(left.content) <= stoi_(right.content))  return iftrue;
      return iffalse;
    }else{
      throw Error::SyntaxError("TypeError: '*' operation must apply on two int proto object!");
    }
  }else if(expr.oper.wd == ">="){
    //cout << "我人傻掉>=.\n";
    if(left.isexist(getPath("__maxeq__"))){
      vector<Type> targs;
      targs.push_back(right);
      return CallFunction(&left.node["__maxeq__"],targs);
    }else if(right.isexist(getPath("__maxeq__"))){
      vector<Type> targs;
      targs.push_back(left);
      return CallFunction(&left.node["__maxeq__"],targs);
    }
    if(left.vtype != right.vtype) throw Error::SyntaxError("TypeError: '==' operation must be applied to the same type as both prototypes!");
    Type iftrue(now_scope);iftrue.type = _var;iftrue.vtype = _bol;iftrue.content.resize(1);iftrue.content[0] = (char)1;
    Type iffalse(now_scope);iffalse.type = _var;iffalse.vtype = _bol;iffalse.content.resize(1);iffalse.content[0] = (char)0;
    if(left.vtype == _int && right.vtype == _int){
      if(stoi_(left.content) >= stoi_(right.content))  return iftrue;
      return iffalse;
    }else{
      throw Error::SyntaxError("TypeError: '*' operation must apply on two int proto object!");
    }
  }else if(expr.oper.wd == "*"){
    // check var proto
    //cout << "我人傻掉*.\n";
    if(left.isexist(getPath("__multiple__"))){
      vector<Type> targs;
      targs.push_back(right);
      return CallFunction(&left.node["__multiple__"],targs);
    }else if(right.isexist(getPath("__multiple__"))){
      vector<Type> targs;
      targs.push_back(left);
      return CallFunction(&left.node["__multiple__"],targs);
    }
    if(left.vtype != _int && right.vtype != _int) throw Error::SyntaxError("TypeError: '*' operation must apply on two int proto object!");
    left.content = itos(stoi_(left.content)*stoi_(right.content));
    return left;
  }else if(expr.oper.wd == "/"){
    // check var proto
    //cout << "我人傻掉/ \n";
    if(left.isexist(getPath("__div__"))){
      vector<Type> targs;
      targs.push_back(right);
      return CallFunction(&left.node["__div__"],targs);
    }else if(right.isexist(getPath("__div__"))){
      vector<Type> targs;
      targs.push_back(left);
      return CallFunction(&left.node["__div__"],targs);
    }
    if(left.vtype != _int && right.vtype != _int) throw Error::SyntaxError("TypeError: '/' operation must apply on two int proto object!");
    left.content = itos(stoi_(left.content)/stoi_(right.content));
    return left;
  }else if(expr.oper.wd == "%"){
    //cout << "我人傻掉%.\n";
    // check var proto
    if(left.isexist(getPath("__mod__"))){
      vector<Type> targs;
      targs.push_back(right);
      return CallFunction(&left.node["__mod__"],targs);
    }else if(right.isexist(getPath("__mod__"))){
      vector<Type> targs;
      targs.push_back(left);
      return CallFunction(&left.node["__mod__"],targs);
    }
    if(left.vtype != _int && right.vtype != _int) throw Error::SyntaxError("TypeError: '%' operation must apply on two int proto object!");
    left.content = itos(stoi_(left.content)%stoi_(right.content));
    return left;
  }else if(expr.oper.wd == "+"){
    if(left.isexist(getPath("__add__"))){
      vector<Type> targs;
      targs.push_back(right);
      return CallFunction(&left.node["__add__"],targs);
    }else if(right.isexist(getPath("__add__"))){
      vector<Type> targs;
      targs.push_back(left);
      return CallFunction(&left.node["__add__"],targs);
    }
    if(left.vtype == _int && right.vtype == _int){
      //cout << stoi_(left.content) << " " << stoi_(right.content) << endl;
      left.content = itos(stoi_(left.content)+stoi_(right.content));
      return left;
    }else if(left.vtype == _str && right.vtype == _str){
      right.content = left.content + right.content;
      return right;
    }else if(left.vtype == _str && right.vtype == _int){
      right.content = left.content + (char)(stoi_(right.content));
      return right;
    }else{
      //return left;
      throw Error::SyntaxError("TypeError: Unknown Operation for this type!");
    }
  }else if(expr.oper.wd == "-"){
    //cout << "我人傻掉-.\n";
    if(left.isexist(getPath("__sub__"))){
      vector<Type> targs;
      targs.push_back(right);
      return CallFunction(&left.node["__sub__"],targs);
    }else if(right.isexist(getPath("__sub__"))){
      vector<Type> targs;
      targs.push_back(left);
      return CallFunction(&left.node["__sub__"],targs);
    }
    if(left.vtype == _int && right.vtype == _int){
      left.content = itos(stoi_(left.content)-stoi_(right.content));
      return left;
    }else{
      throw Error::SyntaxError("TypeError: Unknown Operation for this type!");
    }
  }else{
    throw Error::SyntaxError("ScripterError: Please report this bug to github issues!");
  }
}

Type eval(vector<word> tokens){
  ExprTree expr(tokens);
  return eval(expr);
}

// 解释函数
Type CallFunction(Type *func,vector<Type> args){
  #ifdef __SCRIPT_DEBUG
	cout << now_scope << endl;
  #endif
  if((*func).vtype != _function){
    throw Error::TypeError((*func).name);
  }
  // 更改作用域
  Type func_local_scope(func->parent);
  Type* old_scope = now_scope;
  now_scope = &func_local_scope;
  // 参数定义
  for(int i = 0;i < (*func).args.size();i++){
    Script((*func).args[i]);
    // 获取参数名称
    size_t namepos = getWordPos((*func).args[i],chr,Text::ToString("="));
    if(namepos == WORD_NOTFOUND){
      namepos = (*func).args[i].size() - 1;
    }
    //cout << "Name: " << (*func).args[i][namepos].wd << endl;
    setTypeContent((*func).args[i][namepos].wd,args[i]);
  }
  #ifdef __SCRIPT_DEBUG
	cout << now_scope << endl;
  cout << "fromDLL: " << func->fromDLL << endl;
  #endif
  if(func->fromDLL != NULL){
    ScriptResult (*fromDym) (Type*,vector<Type>) = (ScriptResult (*)(Type*,vector<Type>))func->fromDLL;
    ScriptResult s = (*fromDym)(now_scope,args);
    now_scope = old_scope;
    return s.Content;
  }
  ScriptResult s = Script((*func).content);
  now_scope = old_scope;
  return s.Content;
}

Type CallFunction(Type *func,vector<word> call_line){
  #ifdef __SCRIPT_DEBUG
	cout << now_scope << endl;
  #endif
  if((*func).vtype != _function){
    throw Error::TypeError((*func).name);
  }
  call_line = WordCollection(call_line,getWordPos(call_line,chr,"(")+1,getWordPos(call_line,chr,")"));
  //cout << "Splited:" << WordSpliter(call_line,word(chr,",")).size() << endl;
  vector< vector<word> > carr = WordSpliter(call_line,word(chr,",")); //
  // 对参数进行处理
  vector<Type> tarr;
  for(int i = 0;i < carr.size();i++){
    tarr.push_back(Script(carr[i]).Content);
  }
  return CallFunction(func,tarr);
}

// 解释代码
ScriptResult Script(string expr);
ScriptResult Script(vector<word> wrd){
  ScriptResult scr;
  // 判断主语
  //cout << "Hey!" << wrd[0].wd << " " << wrd[0].word_type << endl;
  // 为了防止误判断，在wrd的大小大于1的情况下，不对变量进行解析
  // ++var;
  if(wrd[0].word_type == chr && (wrd[0].wd == "++" || wrd[0].wd == "--") ){
    vector<word> tmps;
    tmps.push_back(wrd[1]);
    tmps.push_back(word(chr,"="));
    tmps.push_back(wrd[1]);
    tmps.push_back(word(chr,(wrd[0].wd == "++") ? "+" : "-"));
    tmps.push_back(word(con,"1"));
    Script(tmps);
    Type s=getTypeContent(wrd[1].wd);
    scr.Content = s;
    scr.res = _finally;
    return scr;
  }
  if(wrd[0].word_type == nam && !iscmd(wrd[0].wd) && getTypeContent(wrd[0].wd).type != _not_exist){
    //cout << "我tm直接我™.\n";
    if(wrd.size() <= 1){
      scr.Content = getTypeContent(wrd[0].wd);
      scr.res = _finally;
      return scr;
    }else{
      //cout << "Expr Script!\n";
      // 当wrd的大小大于一时，会判断这是个表达式
      if(wrd[1].word_type == chr && wrd[1].wd == "="){
        string tname = wrd[0].wd;
        Type tContent = eval(WordCollection(wrd,2));
        if(!setTypeContent(tname,tContent))  throw Error::NotDefine(tname);
        return ScriptResult(__SUCCESS__);
      }else if(wrd[1].word_type == chr && (wrd[1].wd == "++" || wrd[1].wd == "--") ){
        Type s=getTypeContent(wrd[0].wd);
        vector<word> tmps;
        tmps.push_back(wrd[0]);
        tmps.push_back(word(chr,"="));
        tmps.push_back(wrd[0]);
        tmps.push_back(word(chr,(wrd[1].wd == "++") ? "+" : "-"));
        tmps.push_back(word(con,"1"));
        Script(tmps);
        scr.Content = s;
        scr.res = _finally;
        return scr;
      }else if(wrd[1].word_type == chr && (wrd[1].wd == "+=" || wrd[1].wd == "-=")){
        Type s=getTypeContent(wrd[0].wd);
        vector<word> tmps;
        tmps.push_back(wrd[0]);
        tmps.push_back(word(chr,"="));
        tmps.push_back(wrd[0]);
        if(wrd[1].wd == "+="){
          tmps.push_back(word(chr,"+"));
        }else{
          tmps.push_back(word(chr,"-"));
        }
        for(int i = 2;i < wrd.size();i++){
          tmps.push_back(wrd[i]);
        }
        Script(tmps);
        scr.Content = s;
        scr.res = _finally;
        return scr;
      }
      if(wrd[1].word_type == chr && wrd[1].wd == "("){
        //lalala
		    ScriptResult scs;
        scs.Content=CallFunction(getTypeAddr(wrd[0].wd),wrd);
		    scs.res = _finally;
		    //cout << "!" << endl;
		    return scs;
      }else{
        ScriptResult scs;
        scs.Content=eval(wrd);
        scs.res = _finally;
        return scs;
      }
    }
  }
  if(wrd[0].word_type == nam){
    if(wrd[0].wd == "class"){
      size_t rpos = getWordPos(wrd,chr,")");
      size_t block_pos = getWordPos(wrd,blo);
      if(block_pos == WORD_NOTFOUND){
        throw Error::SyntaxError("Invalid Syntax: Invalid Class Definition");
      }
      if(rpos == WORD_NOTFOUND || (rpos != WORD_NOTFOUND && wrd[rpos-1].wd == "(")){
        // No base class
        Type newclass(now_scope);
        newclass.type = _var;
        newclass.vtype = _str;
        newclass.name = "flag";
        newclass.parent = now_scope;

        Type* oldScope = now_scope;
        now_scope = &newclass;

        Script(wrd[block_pos].wd);

        now_scope = oldScope;
        newclass.type = _var;
        newclass.vtype = _str;
        newclass.content = "<Xscript_class>";
        scr.Content = newclass;
        scr.res = _finally;
        return scr;
      }else{
        Type baseclass = getTypeContent(wrd[rpos-1].wd);
        if(baseclass.type == _not_exist)  throw Error::NotDefine(wrd[rpos-1].wd);
        Type newclass = baseclass;
        newclass.parent = now_scope;

        Type* oldScope = now_scope;
        now_scope = &newclass;

        Script(wrd[block_pos].wd);

        now_scope = oldScope;
        newclass.type = _var;
        newclass.vtype = _str;
        newclass.content = "<Xscript_class>";
        scr.Content = newclass;
        scr.res = _finally;
        return scr;
      }
    }else if(wrd[0].wd == "package"){
      if(wrd[1].word_type != nam)  throw Error::SyntaxError("Invalid Syntax: Invalid Package Definition");
      pkgname = wrd[1].wd;
      scr = ScriptResult(__SUCCESS__);
      return scr;
    }else if(wrd[0].wd == "exit"){
      exit(0);
    }else if(wrd[0].wd == "if"){
      vector<word> expr = WordCollection(wrd,getWordPos(wrd,chr,"(")+1,getWordPos(wrd,chr,")"));
      size_t sz = getWordPos(wrd,chr,")") + 1;
      Type eval_res = eval(expr);
      Type iftrue(now_scope);iftrue.type = _var;iftrue.vtype = _bol;iftrue.content.resize(1);iftrue.content[0] = (char)1;
      if(eval_res.content == iftrue.content){
        ScriptResult ifr = Script(wrd[sz].wd);
        if(ifr.res != _finally)  return ifr;
      }else if(wrd.size() > sz && wrd[sz+1].wd == "else"){
        ScriptResult ifr = Script(WordCollection(wrd,sz+2));
        if(ifr.res != _finally)  return ifr;
      }
      scr = ScriptResult(__SUCCESS__);
      return scr;
    }else if(wrd[0].wd == "for"){
      Type for_scope(now_scope);
      Type* oldscope = now_scope;
      now_scope = &for_scope;
      vector<word> expr = WordCollection(wrd,getWordPos(wrd,chr,"(")+1,getWordPos(wrd,chr,")"));
      vector< vector<word> > exp = WordSpliter(expr,word(chr,","));
      ScriptResult scr1_ = Script(exp[0]);
      if(scr1_.res != _finally){
        now_scope = oldscope;
        return scr1_;
      }

      size_t sz = getWordPos(wrd,chr,")") + 1;
      Type iftrue(now_scope);iftrue.type = _var;iftrue.vtype = _bol;iftrue.content.resize(1);iftrue.content[0] = (char)1;
      while(eval(exp[1]).content[0] == 1){
        ScriptResult ifr = Script(wrd[sz].wd);
        ScriptResult scr2_ = Script(exp[2]);
        if(scr2_.res == _lopcontinue){
          continue;
        }else if(scr2_.res != _finally){
          now_scope = oldscope;
          return scr2_;
        }
        if(ifr.res != _finally){now_scope = oldscope;return ifr;}
      }
      now_scope = oldscope;
      scr = ScriptResult(__SUCCESS__);
      return scr;

    }else if(wrd[0].wd == "while"){
      Type for_scope(now_scope);
      Type* oldscope = now_scope;
      now_scope = &for_scope;
      vector<word> expr = WordCollection(wrd,getWordPos(wrd,chr,"(")+1,getWordPos(wrd,chr,")"));
      size_t sz = getWordPos(wrd,chr,")") + 1;
      Type iftrue(now_scope);iftrue.type = _var;iftrue.vtype = _bol;iftrue.content.resize(1);iftrue.content[0] = (char)1;
      //Type eval_res = eval(expr);
      //eval_res.content[0] = 1;
      //ScriptResult ifr = Script(wrd[sz].wd);
      do{
        //eval_res =
        ScriptResult ifr = Script(wrd[sz].wd);
        //if(eval_res.content[0] != 1)  break;
        if(ifr.res == _lopcontinue)  continue;
        if(ifr.res != _finally){now_scope = oldscope;return ifr;}
      }while(eval(expr).content[0] == 1);
      now_scope = oldscope;
      scr = ScriptResult(__SUCCESS__);
      return scr;
    }else if(wrd[0].wd == "execute"){
      vector<word> expr = WordCollection(wrd,getWordPos(wrd,chr,"(")+1,getWordPos(wrd,chr,")"));
      Type s = eval(expr);
      if(s.type == _not_exist || s.vtype != _str){
        return ScriptResult(__SUCCESS__);
      }else{
        return Script(s.content);
      }
    }else if(wrd[0].wd == "dlopen"){
      // Open Dymaic Library
      vector<word> expr = WordCollection(wrd,getWordPos(wrd,chr,"(")+1,getWordPos(wrd,chr,")"));
      //printf("%d",expr.size());
	    Type dlname = Script(expr).Content;
	    if(dlname.vtype != _str){
		    throw Error::TypeError("dlopen: TypeError");
	    }
      int fhandle = 0;
      while(handles[fhandle++].exist){};fhandle--;
      handles[fhandle].arg2 = dlopen(dlname.content.data(),RTLD_LAZY);
	    handles[fhandle].exist = true;
      scr.Content.content=itos(fhandle);
	    scr.Content.vtype=_int;
      scr.Content.type=_var;
      scr.res=_finally;

      return scr;
    }else if(wrd[0].wd == "dlclose"){
      // Close Dymaic Library
      vector<word> expr = WordCollection(wrd,getWordPos(wrd,chr,"(")+1,getWordPos(wrd,chr,")"));
	    Type dlname = eval(expr);
	    if(dlname.vtype != _int){
		    throw Error::TypeError("dlclose: TypeError");
	    }
      int fhandle = stoi_(dlname.content);
      handles[fhandle].exist = false;
      handles[fhandle].arg2=NULL;
      dlclose(handles[fhandle].arg2);
      scr.Content.content=itos(fhandle);
	    scr.Content.vtype=_int;
      scr.Content.type=_var;
      scr.res=_finally;

      return scr;
    }else if(wrd[0].wd == "getdl"){
      // Get dymaic library addres

      vector< vector<word> > expr = WordSpliter(WordCollection(wrd,getWordPos(wrd,chr,"(")+1,getWordPos(wrd,chr,")")),word(chr,","));
	    if(expr.size() <= 1){
  		  throw Error::SyntaxError("getdl : invalid call format");
	    }
	    Type dlhandle = eval(expr[0]);
      //printf();
	    if(dlhandle.vtype != _int){
        throw Error::TypeError("getdl: TypeError:" + to_string(dlhandle.vtype));
      }else if(stoi_(dlhandle.content) < 0){
        throw Error::TypeError("getdl: handle too small");
      }else if(!handles[stoi_(dlhandle.content)].exist){
        throw Error::TypeError("getdl: handle not exist");
      }else{
        scr.Content.vtype = _function;
        scr.Content.fromDLL = dlsym(handles[stoi_(dlhandle.content)].arg2,eval(expr[1]).content.data());
        scr.Content.type = _var;
        #ifdef __SCRIPT_DEBUG
        cout << "fromDLL:" << scr.Content.fromDLL << endl;
        #endif
      }
      return scr;
    }else if(wrd[0].wd == "return"){
      //Type evres
      //cout << "I still here!"<< wrd[1].wd <<"\n";
      scr.Content = eval(WordCollection(wrd,1));
      //cout << scr.Content.content << endl;
      //printf("EvalContent: %s\n",scr.Content.content);
      scr.res = _return;
      return scr;
    }else if(wrd[0].wd == "import"){
      vector< vector<word> > expr = WordSpliter(WordCollection(wrd,getWordPos(wrd,chr,"(")+1,getWordPos(wrd,chr,")")),word(chr,","));
      if(expr.size() != 1){
        throw Error::SyntaxError("import: invalid call format");
      }
      Type name = eval(expr[0]);
      return Script(EasyFiles::ReadFile(name.content));
    }else if(wrd[0].wd == "delete"){
      #ifdef __SCRIPT_DEBUG
      //cout << wrd.size() << endl;
      #endif
      if(getTypeContent(wrd[1].wd).type == _not_exist){
		    throw Error::SyntaxError("Var not exist!\n");
	    }else{
  		  deleteType(wrd[1].wd);
		    return ScriptResult(__SUCCESS__);
	    }
    }else if(wrd[0].wd == "function"){
      #ifdef __SCRIPT_DEBUG
	    cout << "Function" << endl;
      for(int i = 0;i < wrd.size();i++){
        cout << wrd[i].wd << " ";
      }
      cout << endl;
      #endif
      size_t rpos = getWordPos(wrd,chr,")");
      size_t block_pos = rpos+1;
      if(rpos == WORD_NOTFOUND){
        throw Error::SyntaxError("Invalid Syntax: Invalid Function Definition");
      }else{
        vector<word> args = WordCollection(wrd,getWordPos(wrd,chr,"(")+1,getWordPos(wrd,chr,")"));
        vector< vector<word> > argss = WordSpliter(args,word(chr,","));
        // 参数处理
        /*#ifdef __SCRIPT_DEBUG
        for(int i = 0;i < argss.size();i++){
          for (size_t j = 0; j < argss[i].size(); j++)
          {
            cout << "Args::" << argss[i][j].wd;
          }
          cout << endl;
        }
        #endif*/
		    ;
        scr.Content.args = argss;
        scr.Content.funcontent = wrd[block_pos];
        scr.Content.type = _var;
        scr.Content.vtype = _function;
        #ifdef __SCRIPT_DEBUG
        cout << scr.Content.vtype <<endl;
        #endif
        scr.Content.content = wrd[block_pos].wd;
        scr.res = _finally;
        return scr;
      }
      scr = ScriptResult(__SUCCESS__);
      return scr;
    }else if(wrd[0].wd == "const"){
      vector< vector<word> > arg_list = WordSpliter(wrd,word(chr,","),1);
      Type con;
      for (size_t i = 0; i < arg_list.size(); i++) {
        //if(arg_list[i][1].word_type != nam)  throw Error::SyntaxError("Invalid Syntax: Invalid Const Definition");
        if(arg_list[i][0].word_type != nam)  cout << "Invalid Syntax: Invalid Const Definition\n";
        string tname = arg_list[i][0].wd;
        #ifdef __SCRIPT_DEBUG
        cout << "Const Define Type: " << tname << endl;
        #endif
        //if(arg_list[i].size() > 2 && (arg_list[i][2].word_type != chr || arg_list[i][2].wd != "="))  throw Error::SyntaxError("Invalid Syntax");
        if(arg_list[i].size() > 2 && (arg_list[i][1].word_type != chr || arg_list[i][1].wd != "="))  cout << "Invalid Syntax!\n";
        if(arg_list[i].size() <= 2){
          //cout << "Var Not Inited!\n";
          con.parent = now_scope;
          //cout << "PARENT:" << con.parent << " " << now_scope << endl;
          con.mod = _const;
          con.name = tname;
          con.type = _var;
          if(!newTypeContent(tname,con)) throw Error::AlreadyExist(tname);
          continue;
        }
        con.parent = now_scope;
        con = eval(WordCollection(arg_list[i],2));
        con.parent = now_scope;
        //cout << "PARENT:" << con.parent << " " << now_scope << endl;
        con.name = tname;
        con.mod = _const;

        if(!newTypeContent(tname,con)) throw Error::AlreadyExist(tname);
        /*for(size_t j=0;j < arg_list[j].size();j++){
          cout << arg_list[i][j].wd << "  ";
        }
        cout << endl;*/
      }
      scr.res = _finally;
      scr.Content = con;
      return scr;
    //}
  }else if(wrd[0].wd == "var"){
      vector< vector<word> > arg_list = WordSpliter(wrd,word(chr,","),1);
      Type con;
      for (size_t i = 0; i < arg_list.size(); i++) {
        //if(arg_list[i][1].word_type != nam)  throw Error::SyntaxError("Invalid Syntax: Invalid Const Definition");
        if(arg_list[i][0].word_type != nam)  cout << "Invalid Syntax: Invalid Const Definition\n";
        string tname = arg_list[i][0].wd;
        #ifdef __SCRIPT_DEBUG
        cout << "Var Define Type: " << tname << endl;
        #endif
        //if(arg_list[i].size() > 2 && (arg_list[i][2].word_type != chr || arg_list[i][2].wd != "="))  throw Error::SyntaxError("Invalid Syntax");
        if(arg_list[i].size() > 2 && (arg_list[i][1].word_type != chr || arg_list[i][1].wd != "="))  cout << "Invalid Syntax!\n";
        if(arg_list[i].size() <= 2){
          #ifdef __SCRIPT_DEBUG
          cout << "Var Not Inited!\n";
          #endif
          con.parent = now_scope;
          //cout << "PARENT:" << con.parent << " " << now_scope << endl;
          con.name = tname;
          con.mod = _none;
          con.type = _var;
          if(!newTypeContent(tname,con)) throw Error::AlreadyExist(tname);
          continue;
        }
        con.parent = now_scope;
        con = eval(WordCollection(arg_list[i],2));
        con.parent = now_scope;
        //cout << "PARENT:" << con.parent << " " << now_scope << endl;
        con.name = tname;
        con.mod = _none;

        if(!newTypeContent(tname,con)) throw Error::AlreadyExist(tname);
        /*for(size_t j=0;j < arg_list[j].size();j++){
          cout << arg_list[i][j].wd << "  ";
        }
        cout << endl;*/
      }
      scr.res = _finally;
      scr.Content = con;
      return scr;
    }
  }else if(wrd[0].word_type == con){
    if(wrd.size() > 1){
      // When token-buf max then 1,then it is a expr.
      scr.Content = eval(wrd);
      scr.res = _finally;
      return scr;
    }
    #ifdef __SCRIPT_DEBUG
    cout << "Const: " << wrd[0].wd << endl;
    #endif
    if(wrd[0].wd[0] == '"'){
      wrd[0].wd.erase(wrd[0].wd.begin());
      //if(*(wrd[0].wd.end()) != '"')  throw Error::SyntaxError(Text::ToString("Invalid Syntax")+wrd[0].wd);
      //wrd[0].wd.erase(wrd[0].wd.end());
      scr.Content.content = wrd[0].wd.substr(0,wrd[0].wd.length() - 1);
      //cout << "Content: " << wrd[0].wd.substr(0,wrd[0].wd.length() - 1) << endl;
      scr.Content.vtype = _str;
      scr.Content.type = _var;
      scr.res = _finally;
      return scr;
    }else if(wrd[0].wd[0] >= 48 && wrd[0].wd[0] <= 57){
      //cout << "Const Int Defineion.\n";
      //cout << atoi(wrd[0].wd.data()) << endl;
      scr.Content.content = itos(atoi(wrd[0].wd.data()));
      //cout << "Message: " << scr.Content.content << endl;
      scr.Content.vtype = _int;
      scr.Content.type = _var;
      scr.res = _finally;
      return scr;
    }else if(wrd[0].wd == "true" || wrd[0].wd == "false"){
      scr.Content.content += (wrd[0].wd == "true" ) ? (char)1 : (char)0;
      scr.Content.vtype = _bol;
      scr.Content.type = _var;
      scr.res = _finally;
    }
  }
  return scr;
}

ScriptResult Script(string expr){
  ScriptResult scr;
  vector< vector<word> > word_list;
  expr = Format(expr);
  if(expr == ""){
    scr.res = _finally;
    scr.Content.vtype = _bol;
    scr.Content.content[0] = (char)1;
    return scr;
  }
  /*if(getTypeContent(expr).type != _not_exist && !iscmd(expr)){
    scr.Content = getTypeContent(expr);
    scr.res = _finally;
    return scr;
  }*/


  // 判断是否为代码块
  /*
    These code not working at newest wordparser
  */
  /*if(expr[0] == '{'){
    expr.erase(expr.begin());
    expr.erase(expr.end() - 1);
    //cout << "Expr:" << expr << " Formated: " << expr.substr(0) << endl;
    vector<string> CodeArr = CodeSplit(expr.substr(0,expr[find(expr,'}',1)]),';');
    for (size_t i = 0; i < CodeArr.size(); i++) {
      if(CodeArr[i] == "" || CodeArr[i] == " ")  continue;
      vector<word> tmplst = WordParser(CodeArr[i]);
      ScriptResult scr = Script(tmplst);
      if(scr.res != _finally)  return scr;
      //word_list.push_back(tmplst);
    }
    scr.res = _finally;
    scr.Content.vtype = _bol;
    scr.Content.content[0] = (char)1;
    return scr;
  }*/


  // 正常解析后交给Script
  vector<string> CodeArr = CodeSplit(expr,';');
  //printf("CodeArray Size: %d\n",CodeArr.size());
  //ScriptResult scr;
  for (size_t i = 0; i < CodeArr.size(); i++) {
    if(CodeArr[i] == "" || CodeArr[i] == " ")  continue;
    vector<word> tmplst = WordParser(CodeArr[i]);
    scr = Script(tmplst);
    if(CodeArr.size() == 1)  return scr;
    if(scr.res != _finally)  return scr;
    //cout << CodeArr[i] << endl;
  }
  return scr;
}
