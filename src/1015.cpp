#include <iostream>
using namespace std;

void getNext(char *p, int *next) {
	next[0] = -1;
	for(int i = 0; p[i] != '\0'; i++){
		int q = next[i];
		while(q >= 0 && p[i] != p[q])
			q = next[q];
		next[i + 1] = q + 1;
	}
}

int match(char *p, char *q, int *next) {
	int i = 0, j = 0, num = 0;
	while(q[j] != '\0'){
		if(p[i] == q[j]){
			i++;
			j++;
		}
		else{
			i = next[i];
			if(i == -1){
				i = 0;
				j++;
			}
		}
		//A successful match
		if(p[i] == '\0'){
			num++;
			i = next[i];
		}
	}
	return num;
}

int main(){
	int num;
	char p[10002];
	char ori[1000001];
	int next[10003];
	cin >> num;
	while(num-- != 0){
		cin >> p >> ori;
		getNext(p, next);
		cout << match(p, ori, next) << endl;
	}
}