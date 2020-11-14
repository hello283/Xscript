#include "../../../src/stdc++.h"
#include "../../../src/script.h"

extern "C" ScriptResult __init_array(vector<Type> list){
    ScriptResult scrs;
    for(int i = 0;i < list.size();i++){
        scrs.Content.node[to_string(i)] = list[i];
    }
    scrs.Content.node["prototype_"].content = "__stdlib_array__";
    scrs.Content.node["prototype_"].type = _var;
    scrs.Content.node["prototype_"].vtype = _str;
    scrs.Content.type = _var;
    scrs.Content.vtype = _str;
    scrs.res = _finally;
    return scrs;
}

extern "C" ScriptResult __get_val(vector<Type> list){
    ScriptResult scrs;
    if(list.size() != 2){
        printf("__get_val: must has two args!\n");
        return ScriptResult(__SUCCESS__);
    }else if(list[0].node["prototype_"].content != "__stdlib_array__"){
        printf("__get_val: arg must be array!\n");
        return ScriptResult(__SUCCESS__);
    }else{
        scrs.Content = list[0].node[to_string(stoi_(list[1].content))];
        if(scrs.Content.type == _not_exist){
            printf("__get_val: out of array size!\n");
        }else{
            scrs.res = _finally;
            return scrs;
        }
    }
}

extern "C" ScriptResult __set_val(vector<Type> list){
    ScriptResult scrs;
    if(list.size() != 3){
        printf("__set_val: must has three args!\n");
        return ScriptResult(__SUCCESS__);
    }else if(list[0].node["prototype_"].content != "__stdlib_array__"){
        printf("__set_val: arg must be array!\n");
        return ScriptResult(__SUCCESS__);
    }else{
        if(list[0].node[to_string(stoi_(list[1].content))].type == _not_exist){
            printf("__set_val: out of array size!\n");
        }else{
            list[0].node[to_string(stoi_(list[1].content))] = list[2];
            scrs.Content = list[0];
            scrs.res = _finally;
            return scrs;
        }
    }
}

extern "C" ScriptResult __push_back(vector<Type> list){
    ScriptResult scrs;
    if(list.size() != 2){
        printf("__push_back: call format error!\n");
        return ScriptResult(__SUCCESS__);
    }else if(list[0].node["prototype_"].content != "__stdlib_array__"){
        printf("__push_back: arg must be array!\n");
        return ScriptResult(__SUCCESS__);
    }else{
        int Index = 0;
        for(;list[0].node.find(to_string(Index)) != list[0].node.end() ;Index++){};
        //cout << list[0].node["1"].type << endl;
        list[0].node[to_string(Index)] = list[1];
        //cout << to_string(Index) << " " << list[0].node["1"].type << endl;
        scrs.Content = list[0];
        scrs.res = _finally;
        return scrs;
    }
}

extern "C" ScriptResult __pop_back(vector<Type> list){
    ScriptResult scrs;
    if(list.size() != 1){
        printf("__pop_back: call format error!\n");
        return ScriptResult(__SUCCESS__);
    }else if(list[0].node["prototype_"].content != "__stdlib_array__"){
        printf("__pop_back: arg must be array!\n");
        return ScriptResult(__SUCCESS__);
    }else{
        int Index = 0;
        for(;list[0].node.find(to_string(Index)) != list[0].node.end() ;Index++){};
        list[0].node.erase(to_string(--Index));
        scrs.Content = list[0];
        scrs.res = _finally;
        return scrs;
    }
}

extern "C" ScriptResult __out_size(vector<Type> list){
    ScriptResult scrs;
    if(list.size() != 2){
        printf("__out_size: call format error!\n");
        return ScriptResult(__SUCCESS__);
    }else if(list[0].node["prototype_"].content != "__stdlib_array__"){
        printf("__out_size: arg must be array!\n");
        return ScriptResult(__SUCCESS__);
    }else{
        map<string,Type>::iterator s = list[0].node.find(to_string(stoi_(list[1].content)));
        if(s != list[0].node.end()){
            return ScriptResult(__SUCCESS__);
        }else{
            scrs = ScriptResult(__SUCCESS__);
            scrs.Content.content[0] = 0;
            return scrs;
        }
    }
}