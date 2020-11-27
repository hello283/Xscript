#include "../../../../src/stdc++.h"
#include "../../../../src/script.h"

vector<FILE*> file_handles;

extern "C" ScriptResult __std_open(Type* this_,vector<Type> list){
    if(list.size() == 2 && list[0].vtype == _str && list[1].vtype == _str){
        file_handles.push_back(fopen(list[0].content.c_str(),list[1].content.c_str()));
        if(!file_handles[file_handles.size()-1]){
            file_handles.pop_back();
            ScriptResult scrs(__FAILED__);
            scrs.Content.vtype = _int;
            scrs.Content.content = itos(-1);
            return scrs;
        }else{
            ScriptResult scrs(__FAILED__);
            scrs.Content.type = _var;
            scrs.Content.vtype = _int;
            scrs.Content.content = itos(file_handles.size()-1);
            //for(int i = 0;i < 4;i++) cout << (int)scrs.Content.content[i] << endl;
            return scrs;
        }
    }else{
        ScriptResult scrs(__FAILED__);
        scrs.Content.vtype = _int;
        scrs.Content.content = itos(-1);
        return scrs;
    }
}

extern "C" ScriptResult __std_read(Type* this_,vector<Type> list){
    if(list.size() == 2 && list[0].vtype == _int && list[1].vtype == _int && file_handles.size() > stoi_(list[0].content)){
        cout << "CALLED!\n";
        ScriptResult scrs(__FAILED__);
        scrs.Content.vtype = _str;
        char* buffer = (char*)malloc(stoi_(list[1].content)+1); // Read size,using malloc because array didn't work
        fread(buffer,stoi_(list[1].content),1,file_handles[stoi_(list[0].content)]); // Read to buffer
        scrs.Content.content.resize(stoi_(list[1].content)); // first resize then read , because only read won't complete
        scrs.Content.content = buffer;
        free(buffer);
        return scrs;
    }else{
        ScriptResult scrs(__FAILED__);
        scrs.Content.vtype = _str;
        scrs.Content.content = "";
        return scrs;
    }
}

extern "C" ScriptResult __std_write(Type* this_,vector<Type> list){
    if(list.size() == 2 && list[0].vtype == _int && list[0].vtype == _int && list[1].vtype == _str && stoi_(list[0].content) < file_handles.size()){
        ScriptResult scrs(__FAILED__);
        scrs.Content.vtype = _int;
        scrs.Content.content = itos(fwrite(list[1].content.c_str(),list[1].content.length(),1,file_handles[stoi_(list[0].content)]));

        return scrs;
    }else{
        ScriptResult scrs(__FAILED__);
        scrs.Content.vtype = _int;
        scrs.Content.content = itos(-1);
        return scrs;
    }
}

extern "C" ScriptResult __std_getlength(Type* this_,vector<Type> list){
    if(list.size() == 1 && list[0].vtype == _int && stoi_(list[0].content) < file_handles.size()){
        FILE* thisFile = file_handles[stoi_(list[0].content)];
        size_t file_pos = ftell(thisFile);
        fseek(thisFile,0,SEEK_END);

        ScriptResult scrs(__FAILED__);
        scrs.Content.vtype = _int;
        scrs.Content.content = itos(ftell(thisFile));

        fseek(thisFile,file_pos,SEEK_SET);
        return scrs;
    }else{
        ScriptResult scrs(__FAILED__);
        scrs.Content.vtype = _int;
        scrs.Content.content = itos(-1);
        return scrs;
    }
}