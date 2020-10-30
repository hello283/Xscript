#include "../../src/stdc++.h"
#include "../../src/script.h"

using namespace std;

extern "C" ScriptResult test(vector<Type> list){
    cout << "called!\n";
    return ScriptResult(__SUCCESS__);
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