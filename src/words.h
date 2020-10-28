#pragma once

#include "./stdc++.h"
#include "const.h"
#include "error.h"
#define WORD_NOTFOUND 18446744073709551615UL

using namespace std;
namespace Text{
	string getSubText(string MasterText, int startPoint, int length){
	    return MasterText.substr(startPoint,length);
	}

	string getLeftText(string MasterText, int length){
		return MasterText.substr(0,length);
	}

	string getRightText(string MasterText, int length){
		string tempText;
		tempText=getSubText(MasterText, MasterText.length() - length, MasterText.length());
		return tempText;
	}

	int isInString(string MasterText, string subtext){
		string tempText;
		for(int i = 0;i < MasterText.length();i++){
			tempText = Text::getSubText(MasterText,i,i+subtext.length());
			if(tempText==subtext){
				return i;
			}
		}
		return 0;
	}

	int getStrCount(string MasterText, string subtext){
		string tempText;
		int cnt;
		for(int i = 0;i < MasterText.length();i++){
			tempText = Text::getSubText(MasterText,i,i+subtext.length());
			if(tempText==subtext){
				cnt++;
			}
		}
		return cnt;
	}


	string ToString(string s){
		return s;
	}

	vector<string> split(string f,const string t){
	    vector<string> c;
	    while(f!=""){
	        c.push_back(f.substr(0,f.find(t)==string::npos?f.length():f.find(t)));
	        f.erase(0,f.find(t)==string::npos?f.length():f.find(t)+1);
	    }
	    return c;
	} // change by awathefox

	string deleteStr(string MasterText, string s){
		const string str = s;
		string ret;
		vector<string> strVec = split(MasterText,str);
		for(int i = 0;i < strVec.size();i++){
			ret+=strVec[i];
		}
		return ret;
	}
    vector<string> comSplit(string str,const char splitCh){
        string command = str;
        //cout << command;
        vector<string> ret;
        string buf;
        for(size_t i = 0;i < command.length();i++){
            bool flag;

            if(command[i] == '"'){
                flag = !flag;
            }

            // 放入缓存
            if(command[i] != splitCh || flag == true || i == command.length() - 1){
                char n = command[i];
                buf = buf + n;
            }

            // 放入数组
            if((command[i] == splitCh && flag != true)){
                ret.push_back(buf);
                buf = "";
            }else if(i + 1 == command.length()){
                ret.push_back(buf);
                buf = "";
            }
        }
        return ret;
    }
}

enum wtype{
	chr=0,
	sep=1,
	nam=2,
	wod=3,
	con=4,
	blo=5,
	emp=6,
};

class word{
public:
	wtype word_type = emp;
	string wd = "";

	word(){} // For C++ Compiler Default
	word(wtype wt,string w){
		word_type = wt;
		wd = w;
	}

	void clear(){
		word_type=emp;
		wd="";
		return;
	}

	bool operator== (word other){
		if(word_type == other.word_type && wd == other.wd)  return true;
		return false;
	}
};

vector<word> WordParser(string code){
	vector<word> result;
	word tmpwrd;
	//bool inBlock;
	int bk1=0;
	bool content = 0,num = false,descript=false;

	for(int i = 0;i < code.length();i++){
		// ""
		if(code[i] == '"' && bk1 == 0){
			tmpwrd.word_type = con;
			content = !content;
			if(content == false){
				tmpwrd.wd += code[i];
				result.push_back(tmpwrd);
				continue;
			}
		}
		if(content){
			tmpwrd.wd += code[i];
			continue;
		}
		
		// Number
		if(tmpwrd.wd == "" && (code[i] >= 48 && code[i] <= 57)){
			//cout << "Number!" << code[i] << endl;
			num = true;
		}

		if(!(code[i] >= 48 && code[i] <= 57)){
			if(num){
				num = false;
				tmpwrd.word_type = con;
				result.push_back(tmpwrd);
				tmpwrd.clear();
			}
		}

		// Space
		if(code[i] == ' ' && bk1 == 0 && content == 0){
			if(tmpwrd.wd != ""){
				tmpwrd.word_type = (tmpwrd.wd == "true" || tmpwrd.wd == "false") ? con : nam;
				result.push_back(tmpwrd);
				tmpwrd.clear();
			}
			continue;
		}

		// sep
		if(code[i] == ',' && bk1 == 0 && content == 0){
			if(tmpwrd.wd != ""){
				//if(tmpwrd.wd == "true" || tmpwrd.wd == "false")  tmpwrd.word_type = con;
				tmpwrd.word_type = (tmpwrd.wd == "true" || tmpwrd.wd == "false") ? con : nam;
				result.push_back(tmpwrd);

				tmpwrd.clear();
			}
			tmpwrd.word_type = chr;
			tmpwrd.wd = ",";
			result.push_back(tmpwrd);
			tmpwrd.clear();
			continue;
		}else if(code[i] == '=' && bk1 == 0 && content == 0){
			if(tmpwrd.wd != ""){
				tmpwrd.word_type = (tmpwrd.wd == "true" || tmpwrd.wd == "false") ? con : nam;
				result.push_back(tmpwrd);

				tmpwrd.clear();
			}
			tmpwrd.word_type = chr;
			tmpwrd.wd = (code[i-1] != '!') ? "=" : "!=";
			tmpwrd.wd = (code[i+1] != '=') ? "=" : "==";
			result.push_back(tmpwrd);
			tmpwrd.clear();
			continue;
		}else if(code[i] == '+' && bk1 == 0 && content == 0){
			if(tmpwrd.wd != ""){
				tmpwrd.word_type = (tmpwrd.wd == "true" || tmpwrd.wd == "false") ? con : nam;
				result.push_back(tmpwrd);

				tmpwrd.clear();
			}
			tmpwrd.word_type = chr;
			tmpwrd.wd = "+";
			result.push_back(tmpwrd);
			tmpwrd.clear();
			continue;
		}else if(code[i] == '-' && bk1 == 0 && content == 0){
			if(tmpwrd.wd != ""){
				tmpwrd.word_type = (tmpwrd.wd == "true" || tmpwrd.wd == "false") ? con : nam;
				result.push_back(tmpwrd);

				tmpwrd.clear();
			}
			tmpwrd.word_type = chr;
			tmpwrd.wd = "-";
			result.push_back(tmpwrd);
			tmpwrd.clear();
			continue;
		}else if(code[i] == '*' && bk1 == 0 && content == 0){
			if(tmpwrd.wd != ""){
				tmpwrd.word_type = (tmpwrd.wd == "true" || tmpwrd.wd == "false") ? con : nam;
				result.push_back(tmpwrd);

				tmpwrd.clear();
			}
			tmpwrd.word_type = chr;
			tmpwrd.wd = "*";
			result.push_back(tmpwrd);
			tmpwrd.clear();
			continue;
		}else if(code[i] == '/' && bk1 == 0 && content == 0){
			if(tmpwrd.wd != ""){
				tmpwrd.word_type = (tmpwrd.wd == "true" || tmpwrd.wd == "false") ? con : nam;
				result.push_back(tmpwrd);

				tmpwrd.clear();
			}
			tmpwrd.word_type = chr;
			tmpwrd.wd = "/";
			result.push_back(tmpwrd);
			tmpwrd.clear();
			continue;
		}else if(code[i] == '%' && bk1 == 0 && content == 0){
			if(tmpwrd.wd != ""){
				tmpwrd.word_type = (tmpwrd.wd == "true" || tmpwrd.wd == "false") ? con : nam;
				result.push_back(tmpwrd);

				tmpwrd.clear();
			}
			tmpwrd.word_type = chr;
			tmpwrd.wd = "%";
			result.push_back(tmpwrd);
			tmpwrd.clear();
			continue;
		}

		// 括号处理
		if(code[i] == '<' && bk1 == 0 && content == 0){
			if(tmpwrd.wd != ""){
				tmpwrd.word_type = (tmpwrd.wd == "true" || tmpwrd.wd == "false") ? con : nam;
				result.push_back(tmpwrd);

				tmpwrd.clear();
			}
			tmpwrd.word_type = chr;
			tmpwrd.wd = (code[i+1] != '=') ? "<" : "<=";
			result.push_back(tmpwrd);
			tmpwrd.clear();
		}else if(code[i] == '>' && bk1 == 0 && content == 0){
			if(tmpwrd.wd != ""){
				tmpwrd.word_type = (tmpwrd.wd == "true" || tmpwrd.wd == "false") ? con : nam;
				result.push_back(tmpwrd);

				tmpwrd.clear();
			}
			tmpwrd.word_type = chr;
			tmpwrd.wd = (code[i+1] != '=') ? ">" : ">=";
			result.push_back(tmpwrd);
			tmpwrd.clear();
		}else if(code[i] == '[' && bk1 == 0 && content == 0){
			if(tmpwrd.wd != ""){
				tmpwrd.word_type = (tmpwrd.wd == "true" || tmpwrd.wd == "false") ? con : nam;
				result.push_back(tmpwrd);

				tmpwrd.clear();
			}
			tmpwrd.word_type = chr;
			tmpwrd.wd = "[";
			result.push_back(tmpwrd);
			tmpwrd.clear();
		}else if(code[i] == ']' && bk1 == 0 && content == 0){
			if(tmpwrd.wd != ""){
				tmpwrd.word_type = (tmpwrd.wd == "true" || tmpwrd.wd == "false") ? con : nam;
				result.push_back(tmpwrd);

				tmpwrd.clear();
			}
			tmpwrd.word_type = chr;
			tmpwrd.wd = "]";
			result.push_back(tmpwrd);
			tmpwrd.clear();
		}else if(code[i] == '(' && bk1 == 0 && content == 0){
			if(tmpwrd.wd != ""){
				tmpwrd.word_type = (tmpwrd.wd == "true" || tmpwrd.wd == "false") ? con : nam;
				result.push_back(tmpwrd);

				tmpwrd.clear();
			}
			//printf("WordParser: Bracket(\n");
			tmpwrd.word_type = chr;
			tmpwrd.wd = "(";
			result.push_back(tmpwrd);
			tmpwrd.clear();
		}else if(code[i] == ')' && bk1 == 0 && content == 0){
			if(tmpwrd.wd != ""){
				tmpwrd.word_type = (tmpwrd.wd == "true" || tmpwrd.wd == "false") ? con : nam;
				result.push_back(tmpwrd);

				tmpwrd.clear();
			}
			//printf("WordParser: Bracket)\n");
			tmpwrd.word_type = chr;
			tmpwrd.wd = ")";
			result.push_back(tmpwrd);
			tmpwrd.clear();
		}else if(code[i] == '{' && content == 0){
			if(bk1 == 0){
				if(tmpwrd.wd != ""){
					tmpwrd.word_type = wod;
					result.push_back(tmpwrd);

					tmpwrd.clear();
				}
				tmpwrd.word_type = blo;
				//bk1++; // 在手机上写，懒得优化了
			}else{
				tmpwrd.wd+=code[i];
				//bk1++;
			}
			bk1++;
		}else if(code[i] == '}' && content == 0){
			if(bk1 == 0){
				perror ("SyntaxError");
			}else{
				bk1--;
				if(bk1 == 0){
					result.push_back(tmpwrd);
					tmpwrd.clear();
				}else{
					tmpwrd.wd+=code[i];
				}
			}
		}else{
			tmpwrd.wd+=code[i];
		}
		if(i == code.length() - 1){
			// End of loop
			if(num){
				// If End Loop Is Num
				tmpwrd.word_type = con;
				//tmpwrd.wd += code[i];
				result.push_back(tmpwrd);
				break;
			}else if(tmpwrd.wd != ""){
				// If not num , then type default is 'name' but if this is bool type then is const.
				tmpwrd.word_type = (tmpwrd.wd == "true" || tmpwrd.wd == "false") ? con : nam;
				//tmpwrd.wd += code[i];
				result.push_back(tmpwrd);
				break;
			}
		}
	}
	return result;
}

// 获取词法单元，只匹配type
size_t getWordPos(vector<word> obj,wtype type,int begin = 0,int end = 0,bool findBracket = false){
	int bk1 = 0; // ()括号匹配
	if(end == 0)  end = obj.size();

	for (size_t i = begin; i < end; i++) {
		if(obj[i].word_type == chr && obj[i].wd == ")" && !findBracket) bk1--;

		if(type == obj[i].word_type && bk1 == 0){
			return i;
		}

		if(obj[i].word_type == chr && obj[i].wd == "(" && !findBracket) bk1++;
	}

	return WORD_NOTFOUND;
}

// 获取词法单元，type 和 word 一起匹配
size_t getWordPos(vector<word> obj,wtype type,string wd,int begin = 0,int end = 0,bool findBracket = false){
	int bk1 = 0; // ()括号匹配
	if(end == 0)  end = obj.size();

	for (size_t i = begin; i < end; i++) {
		if(obj[i].word_type == chr && obj[i].wd == ")" && !findBracket) bk1--;

		if(type == obj[i].word_type && obj[i].wd == wd && bk1 == 0){
			return i;
		}

		if(obj[i].word_type == chr && obj[i].wd == "(" && !findBracket) bk1++;
	}

	return WORD_NOTFOUND;
}

// 获取词法单元，只匹配word
size_t getWordPos(vector<word> obj,string wd,int begin = 0,int end = 0,bool findBracket = false){
	int bk1 = 0; // ()括号匹配
	if(end == 0)  end = obj.size();

	for (size_t i = begin; i < end; i++) {
		if(obj[i].word_type == chr && obj[i].wd == ")" && !findBracket) bk1--;

		if(obj[i].wd == wd && bk1 == 0){
			return i;
		}

		if(obj[i].word_type == chr && obj[i].wd == "(" && !findBracket) bk1++;
	}

	return WORD_NOTFOUND;
}

// 词法单元收集器
vector<word> WordCollection(vector<word> obj,wtype type,int begin = 0,int end = 0,bool findBracket = false){
	vector<word> result;
	int bk1 = 0; // ()括号匹配
	if(end == 0)  end = obj.size();

	for (size_t i = begin; i < end; i++) {
		if(obj[i].word_type == type && bk1 == 0){
			result.push_back(obj[i]);
		}

		if(obj[i].word_type == chr && obj[i].wd == "(" && !findBracket) bk1++;
		if(obj[i].word_type == chr && obj[i].wd == ")" && !findBracket) bk1--;
	}

	return result;
}

vector<word> WordCollection(vector<word> obj,int begin = 0,int end = 0,bool findBracket = false){
	vector<word> result;
	int bk1 = 0; // ()括号匹配
	if(end == 0)  end = obj.size();

	for (size_t i = begin; i < end; i++) {
		result.push_back(obj[i]);

		if(obj[i].word_type == chr && obj[i].wd == "(" && !findBracket) bk1++;
		if(obj[i].word_type == chr && obj[i].wd == ")" && !findBracket) bk1--;
	}

	return result;
}

// 妈的，这死吗玩意有时候会不灵光，自己慢慢改吧
vector< vector<word> > WordSpliter(vector<word> obj,word split,int begin = 0,int end = 0,bool findBracket = false){
	vector<word> result;
	vector< vector<word> > rresult;
	int bk1 = 0; // ()括号匹配
	if(end == 0)  end = obj.size();

	for (size_t i = begin; i < end; i++) {
		//cout << obj[i].wd << endl;
		result.push_back(obj[i]);
		if(obj[i] == split && bk1 == 0){
			//cout << obj[i].wd << endl;
			//result.push_back(obj[i]);
			result.erase(result.end() - 1);
			rresult.push_back(result);
			result.clear();
			continue;
		}
		if(i == end - 1){
			//result.push_back(obj[i]);
			rresult.push_back(result);
			result.clear();
			continue;
		}

		if(obj[i].word_type == chr && obj[i].wd == "(" && !findBracket) bk1++;
		if(obj[i].word_type == chr && obj[i].wd == ")" && !findBracket) bk1--;
	}

	return rresult;
}

bool iscmd(string s){
	if(s == "return")  return true;else if(s == "exit")  return true;else if(s == "var") return true;else if(s == "const")  return true;
	if(s == "for")  return true;else if(s == "while")  return true;else if(s == "dlopen") return true;else if(s == "dlclose")  return true;
	return false;
}