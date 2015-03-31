#include <iostream>
#include <vector>
using namespace std;

string getString(const string &str){
	int len = str.size();
	if(len <= 1)
		return str;
	vector<char> v;
	
	for(int i = 0; i + 1 < len; i++){
		if(str[i] == str[i + 1]){
			while(i + 1 < len && str[i] == str[i + 1])
				i++;
		}
		else
			v.push_back(str[i]);
	}
	if(str[len - 2] != str[len - 1])
		v.push_back(str[len - 1]);
	return string(v.begin(), v.end());
}

int main(){
	int n, length, min;
	cin >> n;
	string insert = "ABC";
	string cur;
	while(n--){
		cin >> cur;
		length = min = cur.size();
		for(int i = 0; i <= length; i++){
			for(int j = 0; j < 3; j++){
				string str = cur.substr(0, i) + insert[j] + cur.substr(i, length);
				int len = str.size();
				while(len > (str = getString(str)).size()){
					len = str.size();
				}
				if(min > str.size())
					min = str.size();
			}
		}
		cout << length - min + 1 << endl;
	}
}