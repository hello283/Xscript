//#include "../src/env.h"
#include "./xconfig.h"

map<string,string> bottle_args;
string help_doc[] = {
    "Xbottle Help Doc:\n",
    "===================================\n",
    "action:\n",
    "---- create ... Create a new bottle\n",
    "---- run    ... Run Bottle         \n",
    "---- man    ... manage a bottle    \n",
    "===================================\n",
    "If you have any questions,please send an email to developer: 3134714226@qq.com or zhouyongkang4321@gmail.com\n",
};

void show_help(){
    for(int i = 0;i < 8;i++){
        cout << help_doc[i];
    }
    return;
}

int main(int argc,const char ** argv){
    cout << "Xscript bottle runner\nPowered by Xiaokang00010\n" << endl;

    // Args Parser
    for (size_t i = 1; i < argc; i++)
    {
        if(i==1){
            bottle_args["action"] = argv[1];
        }else{
//            cout << argv[i] << " " << argv[i+1] << endl;
            bottle_args[argv[i]] = argv[i+1];
            i++;continue;
        }
    }

    if(bottle_args["action"] == ""){
        cout << "Invalid Arg!\n";
        show_help();
    }else if(bottle_args["action"] == "create"){
        cout << "Create a new bottle...\n";
        if(bottle_args["name"] == ""){
            cout << "No Output!\n";
            show_help();
        }else if(bottle_args["from-github"] == "false" || bottle_args["from-github"] == "0"){
            cout << "Cloning Repo from another repository\n";
            if(bottle_args["with-stdlib"] == "" || bottle_args["with-stdlib"] == "false" || bottle_args["with-stdlib"] == "0"){
                cout << "Type: No stdlib\n";
                system((Text::ToString("git clone -b no-stdlib ") + bottle_args["repo-url"]).data());
                rename("xbottle-repo",bottle_args["output"].data());
            }else{
                cout << "Type: With stdlib\n";
                cout << "Type: No stdlib\n";
                system((Text::ToString("git clone -b with-stdlib ") + bottle_args["repo-url"]).data());
                rename("xbottle-repo",bottle_args["output"].data());
            }
        }else{
            cout << "Cloning Repo from github\n";
            if(bottle_args["with-stdlib"] == "" || bottle_args["with-stdlib"] == "false" || bottle_args["with-stdlib"] == "0"){
                cout << "Type: No stdlib\n";
                system("git clone -b no-stdlib https://github.com/xiaokang00010/xbottle-repo/");
                rename("xbottle-repo",bottle_args["output"].data());
            }else{
                cout << "Type: With stdlib\n";
                cout << "Type: No stdlib\n";
                system("git clone -b with-stdlib https://github.com/xiaokang00010/xbottle-repo/");
                rename("xbottle-repo",bottle_args["output"].data());
            } 
        }
    }else if(bottle_args["action"] == "run"){
        if(bottle_args["path"] == ""){
            cout << "Please Select An Bottle!\n";
            show_help();
        }else{
            Xconfig bottle_config;
            try{
                bottle_config = Xconfig(bottle_args["path"]+"/bottles-settings.list");
            }catch(EasyFiles::FileError::CanNotOpenFile e){
                cout << "Can Not Open File!\n";
                exit(-1);
            };
            try{
                now_scope = &root_scope;
                init_env(&root_scope);
                Script(Text::ToString("var __CONST_APP_INCLUDE_DIR=") + '"' + bottle_args["path"] + "/" + bottle_config.key_["include-path"] + '"');
                Script(Text::ToString("var __CONST_APP_PREFIX=") + '"' + bottle_args["path"] + '"');
                Script(EasyFiles::ReadFile(bottle_args["path"]+"/"+bottle_config.key_["main-script"]));
                Script(bottle_config.key_["main-class-name"] + ".main(" + '"' + bottle_args["callline"] + '"' + ")");
            }catch(Error::SyntaxError e){
                e.what();
                exit(-1);
            };
        }
    }else if(bottle_args["action"] == "idle"){
        Xconfig bottle_config;
        try{
            bottle_config = Xconfig(bottle_args["path"]+"/bottles-settings.list");
        }catch(EasyFiles::FileError::CanNotOpenFile e){
            cout << "Can Not Open File!\n";
            exit(-1);
        };
        init_env(&root_scope);
        Script(Text::ToString("var __CONST_APP_INCLUDE_DIR=") + '"' + bottle_args["path"] + "/" + bottle_config.key_["include-path"] + '"');
        Script(Text::ToString("var __CONST_APP_PREFIX=") + '"' + bottle_args["path"] + '"');
        Script(EasyFiles::ReadFile(bottle_args["path"]+"/"+bottle_config.key_["main-script"]));
        while(true){
            #ifndef __WIN32
            cout << "\033[32m>>> \033[0m";
            #endif
            #ifdef __WIN32
            cout << ">>> ";
            #endif
            try{
                string expr;
                getline(cin,expr);
                //Script(expr);
                ScriptResult scr = Script(expr);
                if(scr.Content.vtype == _int){
                cout << stoi_(scr.Content.content) << endl;
                }else if(scr.Content.vtype == _str){
                    cout << scr.Content.content << endl;
                }else if(scr.Content.vtype == _bol){
                    Type iftrue(now_scope);iftrue.type = _var; iftrue.vtype = _bol;iftrue.content.resize(1);iftrue.content[0] = (char)1;
                    //Type iffalse(now_scope);iffalse.type = _var;iffalse.vtype = _bol;iffalse.content.resize(1);iffalse.content[0] = (char)0;
                    cout << (int)scr.Content.content[0] << endl;
                }else{
                    cout << scr.Content.content << endl;
                }
                }catch(Error::SyntaxError syx){
                    syx.what();
                }catch(Error::TypeError tpx){
                    tpx.what();
                }
            }
        }
}