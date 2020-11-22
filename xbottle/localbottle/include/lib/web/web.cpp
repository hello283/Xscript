#include "../../../../../src/stdc++.h"
#include "../../../../../src/script.h"

extern "C" ScriptResult GetUrlArgs(Type* this_,vector<Type> list){
    if(list.size() == 1 && list[0].type == _str){
        cout << "findResult:" << list[0].content.find('?') << endl;
        if(list[0].content.find('?') != 18446744073709551615){
            vector<string> s = CodeSplit(CodeSplit(list[0].content,'?')[1],'&');
            ScriptResult scrs;
            scrs.Content.type = _var;
            scrs.Content.vtype = _str;
            scrs.Content.node["prototype_"].type = _var;
            scrs.Content.node["prototype_"].vtype = _str;
            scrs.Content.node["prototype_"].content = "__stdlib_array__";
            for(int i = 0;i < s.size();i++){
                scrs.Content.node[to_string(i)].type = _var;
                scrs.Content.node[to_string(i)].vtype = _str;
                scrs.Content.node[to_string(i)].content = s[i];
            }
            scrs.res = _finally;
            return scrs;
        }else{
            return ScriptResult(__FAILED__);
        }
    }else{
        return ScriptResult(__FAILED__);
    }
}

extern "C" ScriptResult GetItem(Type* this_,vector<Type> list){
    if(list.size() == 2 && list[0].node["prototype_"].content == "__stdlib_array__" && list[1].type == _str){
        for(int i = 0;list[0].node.find(to_string(i)) != list[0].node.end() && list[0].node[to_string(i)].type != _not_exist;i++){
            vector<string> arr=CodeSplit(list[0].node[to_string(i)].content,'=');
            if(arr[0] == list[1].content){
                ScriptResult scrs;
                scrs.Content.content = (arr.size() == 1) ? "" : arr[1];
                scrs.Content.type = _var;
                scrs.Content.vtype = _str;
                return scrs;
            }else{
                continue;
            }
        }
        ScriptResult scrs;
        scrs.Content.type = _var;
        scrs.Content.vtype = _str;
        scrs.Content.content = "";
    }else{
        ScriptResult scrs;
        scrs.Content.type = _var;
        scrs.Content.vtype = _str;
        scrs.Content.content = "";
        return scrs;
    }
}