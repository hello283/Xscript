#pragma once
#include "stdc++.h"
using namespace std;

class Error{
public:
  class SyntaxError{
  private:
    string content = "";
  public:
    SyntaxError(){}
    SyntaxError(string c){content = c;}
    void what(){
      cout << "Xscript SyntaxError: " << content << endl;
    }
  };

  class TryChangeConst{
  private:
    string content = "";
  public:
    TryChangeConst(string c){content = c;}
    void what(){
      cout << "Xscript Error: Try to change a const!\n" << content << endl;
    }
  };

  class TypeError{
  private:
    string content = "";
  public:
    TypeError(string c){content = c;}
    void what(){
      cout << "Xscript Error: " << content << " Type Error!\n" << endl;
    }
  };

  class AlreadyExist{
  private:
    string content = "";
  public:
    AlreadyExist(string c){content = c;}
    void what(){
      cout << "Xscript Error: " << content << " Already Exist!\n" << endl;
    }
  };

  class NotDefine{
  private:
    string content = "";
  public:
    NotDefine(string c){content = c;}
    void what(){
      cout << "Xscript Error: " << content << " Not define!\n" << endl;
    }
  };
};
