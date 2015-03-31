#include <iostream>
#include <algorithm>
using namespace std;

int main(){
	int n, num = 2, reward[120] = {0}, cur, last, tmp;
	cin >> n;
	cin >> cur;
	reward[1] = cur;
	n--;
	while(n--){
		last = reward[0];
		for(int i = 1; i <= num; i++){
			cin >> cur;
			tmp = reward[i];
			reward[i] = max(reward[i], last) + cur;	
			last = tmp;
		}
		num++;
	}
	int max = 0;
	for(int i = 1; i < num; i++){
		if(reward[i] > max)
			max = reward[i];
	}
	cout << max << endl;
	return 0;
}