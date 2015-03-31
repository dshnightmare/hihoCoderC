#include <iostream>
#include <algorithm>
using namespace std;

int value[501], need[501], dp[10001] = {0};
int main(){
	int n, m;
	cin >> n >> m;
	for(int i = 0; i < n; i++){
		cin >> need[i] >> value[i];
	}
	for(int i = 0; i < n; i++){
		for(int j = m; j >= need[i]; j--){
			dp[j] = max(dp[j], dp[j - need[i]] + value[i]);
		}
	}
	cout << dp[m - 1] << endl;
	return 0;
}