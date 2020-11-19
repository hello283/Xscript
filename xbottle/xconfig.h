#include "../src/env.h"
using namespace std;

class Xconfig{
    public:
        map<string,string> key_;
        Xconfig(){}
        Xconfig(string fname){
            vector<string> config_file = Text::split(EasyFiles::ReadFile(fname),"\n");
            for(int i = 0;i < config_file.size();i++){
                vector<string> key_vol = CodeSplit(config_file[i],'=');
                if(config_file[i][0] == '#' || key_vol.size() <= 1) continue;
                key_[key_vol[0]] = key_vol[1];
            }
        }

        void toFile(string fname){
            string content;
            for(map<string,string>::iterator iter = key_.begin();iter != key_.end();iter++){
                content += iter->first + "=" + iter->second + "\n";
            }
            EasyFiles::WriteFile(fname,content);
        }
};