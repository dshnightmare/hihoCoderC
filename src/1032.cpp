#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

const int MAX = 100010;
int length, p[2 * MAX];
char str[MAX], newstr[2 * MAX];

void change(){
	newstr[0] = '@';
	newstr[1] = '#';
	for(int i = 0; i < length; i++){
		newstr[2 * i + 2] = str[i];
		newstr[2 * i + 3] = '#';
	}
	newstr[2 * length + 2] = '\0';
}

int manacher(){
	int maxid = 0, id, ans = 1;
	length = length * 2 + 2;
	for(int i = 0; i < length; i++){
		if(maxid > i){
			p[i] = min(p[2 * id - i], maxid - i);
		}
		else
			p[i] = 1;
		while(newstr[i + p[i]] == newstr[i - p[i]])
			p[i]++;
		if(p[i] + i > maxid){
			maxid = p[i] + i;
			id = i;
		}
		if(ans < p[i])
			ans = p[i];
	}
	return ans - 1;
}

int main(){
	int num;
	cin >> num;
	while(num-- != 0){
		cin >> str;
		length = strlen(str);
		change();
		cout << manacher() << endl;
	}
	return 0;
}