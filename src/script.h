#include "stdc++.h"
#include "words.h"
#include "type.h"
#include "error.h"
#include "const.h"
#include "dlfcn.h"

using namespace std;

string pkgname = "";

string CoreVersion(){
  return "release1_0";
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
		string temp;
		fstream f2;
    	f2.open(FileName.data(),ios::in);
		if(!f2.is_open())throw FileError::CanNotOpenFile();
		while(!f2.eof()){
			//f2 >> ret;
			getline(f2,temp);
			ret+=temp+"\n";//加换行
		}
		ret.erase(ret.length()-1,1);
		f2.close();
		return ret;
	}

	string WriteFile(string FileName,string Output){
		fstream f1;
    	f1.open(FileName.data(),ios::out|ios::trunc|ios_base::out);
		if(!f1.is_open())throw FileError::CanNotOpenFile();
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
	__SUCCESS__=1
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
	 }
  }
};

// 变量
Type getTypeContent(string name){
  if(name == ""){
    return Type();
  }
  TypeFinder tpf = getPath(name);
  Type global = root_scope.getNode(tpf);
  Type inThisParent = now_scope->parent->getNode(tpf);
  Type thisScope = now_scope->getNode(tpf);
  if(global.type != _not_exist){
    return global;
  }else if(inThisParent.type != _not_exist){
    return inThisParent;
  }else{
    return thisScope;
  }
}

Type *getTypeAddr(string name){
  Type unk;
  if(name == ""){
    return &unk;
  }
  TypeFinder tpf = getPath(name);
  Type* global = root_scope.getNodeAddr(tpf);
  Type* inThisParent = now_scope->parent->getNodeAddr(tpf);
  Type* thisScope = now_scope->getNodeAddr(tpf);
  if((*global).type != _not_exist){
    return global;
  }else if((*inThisParent).type != _not_exist){
    return inThisParent;
  }else{
    return thisScope;
  }
}

bool setTypeContent(string name,Type write,bool inglobal = false){
  TypeFinder tpf = getPath(name);
  if(inglobal)  return root_scope.setNode(tpf,write);
  return now_scope->setNode(tpf,write);
}

bool newTypeContent(string name,Type write,bool inglobal = false){
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
    if(s[i] == '"' && !descript)  str=!str;
    if(s[i-1] == '*' && s[i] == '/' && !str){
			if(descript){descript=false;continue;}
			else throw Error::SyntaxError("InvalidSyntax");
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
    if(left.vtype != _int && right.vtype != _int) throw Error::SyntaxError("TypeError: '*' operation must apply on two int proto object!");
    left.content = itos(stoi_(left.content)*stoi_(right.content));
    return left;
  }else if(expr.oper.wd == "/"){
    // check var proto
    //cout << "我人傻掉/ \n";
    if(left.vtype != _int && right.vtype != _int) throw Error::SyntaxError("TypeError: '/' operation must apply on two int proto object!");
    left.content = itos(stoi_(left.content)/stoi_(right.content));
    return left;
  }else if(expr.oper.wd == "%"){
    //cout << "我人傻掉%.\n";
    // check var proto
    if(left.vtype != _int && right.vtype != _int) throw Error::SyntaxError("TypeError: '%' operation must apply on two int proto object!");
    left.content = itos(stoi_(left.content)%stoi_(right.content));
    return left;
  }else if(expr.oper.wd == "+"){
    //cout << "我人傻掉+.\n";
    if(left.vtype == _int && right.vtype == _int){
      //cout << stoi_(left.content) << " " << stoi_(right.content) << endl;
      left.content = itos(stoi_(left.content)+stoi_(right.content));
      return left;
    }else if(left.vtype == _str && right.vtype == _str){
      left.content = left.content + right.content;
      return left;
    }else if(left.vtype == _str && right.vtype == _int){
      left.content = left.content + (char)(stoi_(right.content));
      return left;
    }else{
      //return left;
      throw Error::SyntaxError("TypeError: Unknown Operation for this type!");
    }
  }else if(expr.oper.wd == "-"){
    //cout << "我人傻掉-.\n";
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
Type CallFunction(Type *func,vector<word> call_line){
  #ifdef __SCRIPT_DEBUG
	cout << now_scope << endl;
  #endif
  if((*func).vtype != _function){
    throw Error::TypeError((*func).name);
  }
  Type backscope = root_scope;
  call_line = WordCollection(call_line,getWordPos(call_line,chr,"(")+1,getWordPos(call_line,chr,")"));
  /*for(int i = 0;i < call_line.size();i++){
    cout << "cl:" << call_line[i].wd << endl;
  }*/
  //cout << "Splited:" << WordSpliter(call_line,word(chr,",")).size() << endl;
  vector< vector<word> > carr = WordSpliter(call_line,word(chr,",")); // 
  // 对参数进行处理
  vector<Type> tarr;
  for(int i = 0;i < carr.size();i++){
    //cout << carr[i][0].wd << endl;
    tarr.push_back(Script(carr[i]).Content);
  }
  //cout << "run,here" << endl;
  // 更改作用域
  Type* old_scope = now_scope;
  now_scope = func;
  // 参数定义
  for(int i = 0;i < (*func).args.size();i++){
    cout << now_scope << endl;
    Script((*func).args[i]);
    // 获取参数名称
    size_t namepos = getWordPos((*func).args[i],chr,Text::ToString("="));
    if(namepos == WORD_NOTFOUND){
      namepos = (*func).args[i].size() - 1;
    }
    cout << "Name: " << (*func).args[i][namepos].wd << endl;
    setTypeContent((*func).args[i][namepos].wd,tarr[i]);
  }
  #ifdef __SCRIPT_DEBUG
	cout << now_scope << endl;
  //cout << "Begin Code Run...\n";
  #endif
  //cout << "Res:" << Script((*func).content).Content.content << endl;;
  //cout << "Execute Result:" << ReturnVal.Content.content << endl;

  ScriptResult s = Script((*func).content);
  //cout << "Content： " << s.Content.content << endl;
  now_scope = old_scope;
  root_scope = backscope;
  return s.Content;
  //return Type();
}

// 解释代码
ScriptResult Script(string expr);
ScriptResult Script(vector<word> wrd){
  ScriptResult scr;
  // 判断主语
  //cout << "Hey!" << wrd[0].wd << " " << wrd[0].word_type << endl;
  // 为了防止误判断，在wrd的大小大于1的情况下，不对变量进行解析
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
      }if(wrd[1].word_type == chr && wrd[1].wd == "("){
        //lalala
		    ScriptResult scs;
        scs.Content=CallFunction(getTypeAddr(wrd[0].wd),wrd);
		    scs.res = _finally;
		    //cout << "!" << endl;
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
      }else{
        throw Error::SyntaxError("Invalid Syntax: Invalid If Definition");
      }
      scr = ScriptResult(__SUCCESS__);
      return scr;
    }else if(wrd[0].wd == "for"){
      vector<word> expr = WordCollection(wrd,getWordPos(wrd,chr,"(")+1,getWordPos(wrd,chr,")"));
      vector< vector<word> > exp = WordSpliter(expr,word(chr,","));
      ScriptResult scr1_ = Script(exp[0]);
      if(scr1_.res != _finally){
        return scr1_;
      }

      size_t sz = getWordPos(wrd,chr,")") + 1;
      Type iftrue(now_scope);iftrue.type = _var;iftrue.vtype = _bol;iftrue.content.resize(1);iftrue.content[0] = (char)1;
      while(eval(exp[1]).content[0] == 1){
        ScriptResult ifr = Script(wrd[sz].wd);
        ScriptResult scr2_ = Script(exp[2]);
        if(scr2_.res != _finally){
          return scr2_;
        }
        if(ifr.res == _lopcontinue)  continue;
        if(ifr.res != _finally)  return ifr;
      }
      scr = ScriptResult(__SUCCESS__);
      return scr;

    }else if(wrd[0].wd == "while"){
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
        if(ifr.res != _finally)  return ifr;
      }while(eval(expr).content[0] == 1);
      scr = ScriptResult(__SUCCESS__);
      return scr;
    }else if(wrd[0].wd == "show_info"){
      // Show Var Info
      scr = ScriptResult(__SUCCESS__);
      return scr;
    }else if(wrd[0].wd == "dlopen"){
      // Open Dymaic Library
      vector< vector<word> > expr = WordSpliter(WordCollection(wrd,getWordPos(wrd,chr,"(")+1,getWordPos(wrd,chr,")"))word(chr,";"));
	  Type dlname = eval(expr[0]);
	  if(dlname.vtype != _str){
		throw Error::SyntaxError("TypeError");
	  }
	  /*Unfinish!*/
      return scr;
    }else if(wrd[0].wd == "return"){
      //Type evres
      //cout << "I still here!"<< wrd[1].wd <<"\n";
      scr.Content = eval(WordCollection(wrd,1));
      //cout << scr.Content.content << endl;
      //printf("EvalContent: %s\n",scr.Content.content);
      scr.res = _return;
      return scr;
    }else if(wrd[0].wd == "delete"){
      #ifdef __SCRIPT_DEBUG
      //cout << wrd.size() << endl;
      #endif
      if(getTypeContent(wrd[1].wd).type == _not_exist){
		  cout << "Var not exist!" << endl;
		  exit(1);
	    }else{
  		  setTypeContent(wrd[1].wd,Type());
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
          Type con(now_scope);
          con.mod = _const;
          con.type = _var;
          if(!newTypeContent(tname,con)) throw Error::AlreadyExist(tname);
          continue;
        }
        Type con = eval(WordCollection(arg_list[i],2));
        con.name = tname;
        con.mod = _const;

        if(!newTypeContent(tname,con)) throw Error::AlreadyExist(tname);
        /*for(size_t j=0;j < arg_list[j].size();j++){
          cout << arg_list[i][j].wd << "  ";
        }
        cout << endl;*/
      }
      scr = ScriptResult(__SUCCESS__);
      return scr;
    //}
  }else if(wrd[0].wd == "var"){
      vector< vector<word> > arg_list = WordSpliter(wrd,word(chr,","),1);
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
          Type con(now_scope);
          con.name = tname;
          con.mod = _none;
          con.type = _var;
          if(!newTypeContent(tname,con)) throw Error::AlreadyExist(tname);
          continue;
        }
        Type con = eval(WordCollection(arg_list[i],2));
        con.name = tname;
        con.mod = _none;

        if(!newTypeContent(tname,con)) throw Error::AlreadyExist(tname);
        /*for(size_t j=0;j < arg_list[j].size();j++){
          cout << arg_list[i][j].wd << "  ";
        }
        cout << endl;*/
      }
      scr = ScriptResult(__SUCCESS__);
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
  if(getTypeContent(expr).type != _not_exist){
    scr.Content = getTypeContent(expr);
    scr.res = _finally;
    return scr;
  }


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
  }
  return scr;
}
