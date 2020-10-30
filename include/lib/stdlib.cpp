#include "../../src/stdc++.h"
#include "../../src/script.h"

using namespace std;

extern "C" ScriptResult test(Type* scope){
    cout << "called!\n";
    return ScriptResult(__SUCCESS__);
}