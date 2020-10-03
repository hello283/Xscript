//#include "src/words.h"
#include "src/script.h"
//EasyFiles::ReadFile("./sample/first.xs0")
int main(int argc , const char **argv){
	string origin = EasyFiles::ReadFile("./sample/first.xs0");
	string after = Format(origin);
	cout << after << endl;
	/*vector< vector<word> > getMember = getTokens(tokenlist,word(chr,"("),word(chr,")"),0);
	for(int i = 0;i < getMember.size();i++){
		for(int j = 0;j < getMember[i].size();j++){
			cout << getMember[i][j].wd << " ";
		}
		cout << endl;
	}*/
}
