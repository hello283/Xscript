#include "../xconfig.h"
#include <iostream>
using namespace std;

//非Unix系统
#if defined(_MSC_VER) || defined(__MINGW32__) || defined(WIN32)
//#pragma comment( lib, "ws2_32.lib")
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <windows.h>
#define close closesocket

class WinSockInit
{
    WSADATA _wsa;
public:
    WinSockInit()
    {  //分配套接字版本信息2.0，WSADATA变量地址
        WSAStartup(MAKEWORD(2, 0), &_wsa); 

    }
    ~WinSockInit()
    {
        WSACleanup();//功能是终止Winsock 2 DLL (Ws2_32.dll) 的使用
    }
}; 

//Unix系统
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#if defined(_MSC_VER) || defined(__MINGW32__) || defined(WIN32)
WinSockInit socklibInit;
#endif

int sock = -1,rc = -1;
sockaddr_in addr = { 0 };

// Client
sockaddr_in clientAddr;
int clientAddrSize = sizeof(clientAddr);
int clientSock = 0;

void webinit(int port){
    cout << "Web Server Init...\n";
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // make socket
    addr.sin_family = AF_INET;                        // select addres table
    addr.sin_addr.s_addr = INADDR_ANY;                // init ip
    addr.sin_port = htons(port);                      // init port
    rc = bind(sock, (sockaddr*)&addr, sizeof(addr));  // alloc ip and port
    rc = listen(sock,0);
    cout << "Ending...\n";
}

void webecho(string s){
    if(sock == -1){
        cout << "Server Not Init!\n";
        return;
    }else{
        send(clientSock, s.c_str(), s.length(), 0);
    }
}

Xconfig mime_tab = Xconfig("./web_kit/mime_table.conf");

class servfilereq{
    public:
        string req_mime = "text/plain";
        string fcontent;
        bool finish = false;
        servfilereq(string prefix,string filename){
            string line = filename;

            filename = filename.substr(0,filename.find('?'));
            filename = (filename == "") ? "/index.xs0" : filename ;
            try{
                fcontent = EasyFiles::ReadFile(prefix + filename);
                req_mime = mime_tab.key_[filename.substr(filename.find('.')+1)];
                req_mime = (req_mime == "") ? "application/octet-stream" : req_mime;
                finish = true;
            }catch(EasyFiles::FileError::CanNotOpenFile e){
                cout << "File: OpenFailed!\n";
                return;
            }
        }
};