#include "../../../src/stdc++.h"
#include "../../../src/script.h"

using namespace std;

extern "C" ScriptResult test(vector<Type> list){
    cout << "called!\n";
    return ScriptResult(__SUCCESS__);
}

extern "C" ScriptResult ___max(vector<Type> list){
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

extern "C" ScriptResult ___min(vector<Type> list){
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

extern "C" ScriptResult __stdf_max(vector<Type> list){
    if(list.size() != 2){
        ScriptResult s(__SUCCESS__);
        s.Content.content[1]=0;
        return s;
    }else{
        ScriptResult s;
        Type x;
        Type y;
        if(x.node["prototype_"].content != "__stdlib_float__"){
            cout << "__stdf_max: left arg must be float!\n";
            ScriptResult s(__SUCCESS__);
            s.Content.content[1]=0;
            return s;
        }
        if(y.node["prototype_"].content != "__stdlib_float__"){
            float x1=atof(x.content.c_str());
            float y1=atof(y.content.c_str());
            s.Content = (x1 > y1) ? x : y;
            s.res = _finally;
            return s;
        }else{
            float x1=atof(x.content.c_str());
            int y1=atoi(y.content.c_str());
            s.Content = (x1 > y1) ? x : y;
            s.res = _finally;
            return s;
        }
    }
}

extern "C" ScriptResult __stdf_min(vector<Type> list){
    if(list.size() != 2){
        ScriptResult s(__SUCCESS__);
        s.Content.content[1]=0;
        return s;
    }else{
        ScriptResult s;
        Type x;
        Type y;
        if(x.node["prototype_"].content != "__stdlib_float__"){
            cout << "__stdf_max: left arg must be float!\n";
            ScriptResult s(__SUCCESS__);
            s.Content.content[1]=0;
            return s;
        }
        if(y.node["prototype_"].content != "__stdlib_float__"){
            float x1=atof(x.content.c_str());
            float y1=atof(y.content.c_str());
            s.Content = (x1 < y1) ? x : y;
            s.res = _finally;
            return s;
        }else{
            float x1=atof(x.content.c_str());
            int y1=atoi(y.content.c_str());
            s.Content = (x1 < y1) ? x : y;
            s.res = _finally;
            return s;
        }
    }
}

extern "C" ScriptResult __stdf_toInt(vector<Type> list){
    if(list.size() != 1){
        ScriptResult s(__SUCCESS__);
        s.Content.content[1]=0;
        return s;
    }else if(list[0].node["prototype_"].content != "__stdlib_float__"){
        cout << "__stdf_max: arg must be float!\n";
        ScriptResult s(__SUCCESS__);
        s.Content.content[1]=0;
        return s;
    }else{
        ScriptResult s;
        float x1=atof(list[0].content.c_str());
        int s1=x1;
        s.Content.content = itos(s1);
        s.Content.vtype=_int;
        s.Content.type = _var;
        s.res=_finally;
        return s;
    }
}

extern "C" ScriptResult __stdf_toFloat(vector<Type> list){
    if(list.size() != 1){
        ScriptResult s(__SUCCESS__);
        s.Content.content[1]=0;
        return s;
    }else if(list[0].vtype != _int){
        cout << "__stdf_max: arg must be int!\n";
        ScriptResult s(__SUCCESS__);
        s.Content.content[1]=0;
        return s;
    }else{
        ScriptResult s;
        s.Content.content = to_string(stoi_(list[0].content));
        s.Content.vtype=_str;
        s.Content.type=_var;
        s.Content.node["prototype_"].content = "__stdlib_float__";
        s.Content.node["prototype_"].vtype = _str;
        s.Content.node["prototype_"].type = _var;
        s.res=_finally;
        return s;
    }
}

extern "C" ScriptResult __stdf_set(vector<Type> list){
    if(list.size() != 1){
        ScriptResult s(__SUCCESS__);
        s.Content.content[1]=0;
        return s;
    }else if(list[0].vtype == _str){
        ScriptResult s(__SUCCESS__);
        s.Content.content = FloatToStr(atof(list[0].content.data()));
        s.Content.node["prototype_"].content = "__stdlib_float__";
        s.Content.vtype=_str;
        s.Content.type=_var;
        s.Content.node["prototype_"].vtype = _str;
        s.Content.node["prototype_"].type = _var;
        return s;
    }else if(list[0].vtype == _int){
        ScriptResult s(__SUCCESS__);
        s.Content.content = FloatToStr(atoi(list[0].content.data()));
        s.Content.node["prototype_"].content = "__stdlib_float__";
        s.Content.vtype=_str;
        s.Content.type=_var;
        s.Content.node["prototype_"].vtype = _str;
        s.Content.node["prototype_"].type = _var;
        return s;
    }else{
        cout << "__stdf_set: Unknown Covert!\n";
        ScriptResult s(__SUCCESS__);
        s.Content.content[1]=0;
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

extern "C" ScriptResult strToInt(vector<Type> list){
    if(list.size() != 1){
        printf("strToInt: must have one arg!");
        return ScriptResult(__SUCCESS__);
    }else if(list[0].vtype != _str){
        printf("strToInt: must be string!");
    }else{
        ScriptResult scrs;
        scrs.Content.vtype = _int;
        scrs.Content.type = _var;
        scrs.Content.content = itos(atoi(list[0].content.data()));
        scrs.res = _finally;
        return scrs;
    }
}

extern "C" ScriptResult input(vector<Type> list){
    ScriptResult scrs;
    scrs.Content.type = _var;
    scrs.Content.vtype = _str;
    scrs.res = _finally;
    getline(cin,scrs.Content.content);
    return scrs;
}