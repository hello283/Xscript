#include "../src/script.h"

using namespace std;

int main(){
    string str = "\
    dlopen(\"err\",233)\
    ";
    str=Format(str);
    vector<word> srtarr=WordParser(str);
    for(int i = 0;i < srtarr.size();i++){
        cout << srtarr[i].wd << " ";
    }
    cout << endl;
}