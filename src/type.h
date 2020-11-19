#include "stdc++.h"
#include "words.h"

union fbyte{
  bool hex[32];
  int i;
  char ch[4];
};

//int sss;

string itos(int r){
  //cout << "ItoS:" << r << endl;;
  string s = "****";
  fbyte fb;
  fb.i = r;
  for(int i = 0;i < 4;i++){
    s[i] = fb.ch[i];
  }
  return s;
}

int stoi_(string s){
  if(s.length() != 4)  cout << "[StringToInt:Warning] String Not Currently!" << s << endl;
  fbyte fb;
  for(int i = 0;i < 4;i++){
    fb.ch[i] = s[i];
  }
  return fb.i;
}

enum TType{
    _var=1,
    _not_exist=2
};

enum VType{
  _int=0,
  _str=1,
  _bol=2,
  _function=4,
  _emp=5
};

enum TModifier{
  _const=0,
  _temp=1,
  _none=2
};

struct TypeFinder{
  string name;
  stack<string> path;
};

TypeFinder getPath(string name){
  TypeFinder ret;
  vector<string> pth = Text::split(name,".");

  ret.name = pth[pth.size() - 1];
  pth.erase(pth.end() - 1);

  for(int i = 0;i < pth.size();i++){
    ret.path.push(pth[i]);
  }

  return ret;
}

// 一些类型
class Type{
    private:
    public:
        Type* parent = this;
        Type& getParent(){
          return *parent;
        };

        // 变量定义
        VType vtype = _emp;
        TType type = _not_exist;
        TModifier mod = _temp;
        string name = "";
        string content = "";
        vector< vector<word> > args;
        word funcontent;
        void* fromDLL = NULL;
        map<string,Type> node;

        Type(){}
        Type(Type* parent_){
            parent = parent_;
        }

        Type getNode(TypeFinder tyfind){
          if(tyfind.path.empty()){
		        if(node[tyfind.name].type == _not_exist){
			        node.erase(tyfind.name);
			        return Type();
		        }
            return node[tyfind.name];
          }
          string name = tyfind.path.top();
          tyfind.path.pop();
          return node[name].getNode(tyfind);
        }

        Type* getNodeAddr(TypeFinder tyfind){
          if(tyfind.path.empty()){
			      if(node[tyfind.name].type == _not_exist){
			        node.erase(tyfind.name);
  			      return this;  // here is a bomb
			      }
            return &node[tyfind.name];
          }
          string name = tyfind.path.top();
          tyfind.path.pop();
          return node[name].getNodeAddr(tyfind);
        }

        bool newNode(TypeFinder tyfind,Type ToNew){
          if(tyfind.path.empty()){
            if(node[tyfind.name].type == _not_exist){node[tyfind.name] = ToNew;return true;}
            return false;
          }
          string name = tyfind.path.top();
          tyfind.path.pop();
          return node[name].newNode(tyfind,ToNew);
        }

        bool setNode(TypeFinder tyfind,Type ToNew){
          if(tyfind.path.empty()){
            // 丢弃掉原有的修饰符
            ToNew.mod = _none;

            if(node[tyfind.name].mod != _const){node[tyfind.name] = ToNew;return true;}
            return false;
          }
          string name = tyfind.path.top();
          tyfind.path.pop();
          return node[name].setNode(tyfind,ToNew);
        }

        bool isexist(TypeFinder tyfind){
          if(tyfind.path.empty()){
            // 丢弃掉原有的修饰符
            if(node[tyfind.name].type != _not_exist){
              return true;
            }else{
              node.erase(tyfind.name);
              return false;
            }
          }
          string name = tyfind.path.top();
          tyfind.path.pop();
          return node[name].isexist(tyfind);
        }

        bool deletes(TypeFinder tyfind){
          if(tyfind.path.empty()){
            // 丢弃掉原有的修饰符
            if(node.find(tyfind.name) != node.end()){
              return node.erase(tyfind.name);
            }
            return false;
          }
          string name = tyfind.path.top();
          tyfind.path.pop();
          return node[name].deletes(tyfind);
        }
};
