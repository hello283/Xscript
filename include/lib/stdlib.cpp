#include "../../src/stdc++.h"
#include "../../src/script.h"

using namespace std;

extern "C" ScriptResult test(vector<Type> list){
    cout << "called!\n";
    return ScriptResult(__SUCCESS__);
}

extern "C" ScriptResult __max(vector<Type> list){
    if(list.size() != 2){
        ScriptResult s(__SUCCESS__);
        s.Content.content[1]=0;
        return s;
    }else{
        ScriptResult s;
        Type x = list[0];
        Type y = list[1];
        if(x.vtype == _int && y.vtype == _int){
            s.Content = (stoi_(x.content) > stoi_(y.content)) ? x : y;
            return s;
        }else if(x.vtype == _str && y.vtype == _str){
            s.Content = (x.content > y.content) ? x : y;
            return s;
        }else if(x.vtype == _bol && y.vtype == _bol){
            s.Content = (x.content[0] > y.content[0]) ? x : y;
            return s;
        }else{
            s.Content = (x.content > y.content) ? x : y;
            return s;
        }
    }
}

extern "C" ScriptResult __min(vector<Type> list){
    if(list.size() != 2){
        ScriptResult s(__SUCCESS__);
        s.Content.content[1]=0;
        return s;
    }else{
        ScriptResult s;
        Type x = list[0];
        Type y = list[1];
        if(x.vtype == _int && y.vtype == _int){
            s.Content = (stoi_(x.content) < stoi_(y.content)) ? x : y;
            return s;
        }else if(x.vtype == _str && y.vtype == _str){
            s.Content = (x.content < y.content) ? x : y;
            return s;
        }else if(x.vtype == _bol && y.vtype == _bol){
            s.Content = (x.content[0] < y.content[0]) ? x : y;
            return s;
        }else{
            s.Content = (x.content < y.content) ? x : y;
            return s;
        }
    }
}

extern "C" ScriptResult toCharCode(vector<Type> list){
    if(list.size() != 1){
        ScriptResult s(__SUCCESS__);
        s.Content.content[1]=0;
        return s;
    }else{
        ScriptResult s;
        s.res = _finally;
        s.Content.type = _var;
        s.Content.vtype = _int;
        s.Content.content = itos(list[0].content[0]);
        return s;
    }
}

extern "C" ScriptResult charToStr(vector<Type> list){
    if(list.size() != 1){
        ScriptResult s(__SUCCESS__);
        s.Content.content[1]=0;
        return s;
    }else{
        ScriptResult s;
        s.res = _finally;
        s.Content.type = _var;
        s.Content.vtype = _str;
        s.Content.content = list[0].content;
        return s;
    }
}

extern "C" ScriptResult print(vector<Type> list){
    for(int i = 0;i < list.size();i++){
        if(list[i].vtype == _int){
            cout << stoi_(list[i].content);
        }else if(list[i].vtype == _str){
            cout << list[i].content;
        }else if(list[i].vtype == _bol){
            cout << (int)list[i].content[0];
        }else{
            return ScriptResult(__SUCCESS__);
        }
    }
    return ScriptResult(__SUCCESS__);
}