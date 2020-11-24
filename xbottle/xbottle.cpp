//#include "./xconfig.h"
#include "../src/const.h"
#include "../src/env.h"

map<string,string> bottle_args;
string help_doc[] = {
    "Xbottle Help Doc:\n",
    "===================================\n",
    "action:\n",
    "---- create ... Create a new bottle\n",
    "---- run    ... Run Bottle         \n",
    "---- server ... Start a Web Server \n",
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
        }else if(bottle_args["action"] == "server"){
            webinit(atoi(bottle_args["port"].data()));
            cout << "Server Started at port" << atoi(bottle_args["port"].data()) << endl;
            while (-1 != (clientSock = accept(sock,(sockaddr*)&clientAddr, (socklen_t*)&clientAddrSize))){
                string requestStr;
                int bufSize = 4096;
                requestStr.resize(bufSize);
                recv(clientSock, &requestStr[0], bufSize, 0);

                string firstLine = requestStr.substr(0, requestStr.find("\r\n"));
                firstLine = firstLine.substr(firstLine.find(" ") + 1);//substr，复制函数，参数为起始位置（默认0），复制的字符数目
                string url = firstLine.substr(0, firstLine.find(" "));//find返回找到的第一个匹配字符串的位置，而不管其后是否还有相匹配的字符串。
                url=replace_all(url,"%20"," ");
                cout << "\033[32m" << url << "\033[0m" << endl;
                servfilereq  servfile("./"+bottle_args["root"] + "/",url);
                if(!servfile.finish){
                    string response = "HTTP/1.1 404 OK\r\n\r\n404Error";
                    webecho(response);
                }else if(servfile.req_mime == "xbottle/xs0"){
                    string response = Text::ToString("") + "HTTP/1.1 200 OK\r\n" + "Content-Type: text/html; charset=utf-8\r\n" +"\r\n";
                    webecho(response);
                    Xconfig bottle_config = Xconfig(bottle_args["root"]+"/bottles-settings.list");
                    now_scope = &root_scope;
                    init_env(&root_scope);
                    try{
//                        cout << Script("__CONST_APP_INCLUDE_DIR").Content.vtype << endl;
                        Script(Text::ToString("var __CONST_APP_INCLUDE_DIR=") + '"' + bottle_args["root"] + "/" + bottle_config.key_["include-path"] + '"');
                        Script(Text::ToString("var __CONST_APP_PREFIX=") + '"' + bottle_args["root"] + '"');
                        Script(Text::ToString("var __BROWSER_URL=") + '"' + url + '"');
                        Script(servfile.fcontent);
                        root_scope.node.clear();
                    }catch (Error::AlreadyExist e){
                        e.what();
                    }catch (Error::SyntaxError e){
                        e.what();
                    }
                }else{
                    string response = Text::ToString("") + "HTTP/1.1 200 OK\r\n" + "Content-Type:" + servfile.req_mime + "; charset=utf-8\r\n\r\n";
                    webecho(response);
                    FILE* fd = fopen(servfile.filen.c_str(),"rb+");
                    cout << servfile.req_mime << endl;
                    char buffer[1024] = {0};
                    fseek(fd, 0, SEEK_SET);
                    while(!feof(fd)){
                    	fread(&buffer,1024,1,fd);
                    	send(clientSock, buffer, 1024, 0);
                    }
                    fclose(fd);
                }
                servfile.finish = false;
                close(clientSock);
            }
            close(sock);
        }
}