#include <iostream>
using namespace std;

int gg(uint32_t n) {
	int count = 0;
	while(n){
		++count;
		n = n & (n - 1);
	}
	return count;
}

void getones(int count[], int bound){
	for(int i = 0; i < bound; i++)
		count[i] = gg(i);
}

int main(){
	int N, M, Q, maxlj = 0;
	int lj[1005];
	int dp[1005][1024] = {{0}};
	int countones[1024];
	cin >> N >> M >> Q;
	getones(countones, 1 << M);
	for(int i = 1; i <= N; i++)
		cin >> lj[i];
	for(int i = 1; i <= N; i++){
		int up = 1 << (M - 1);
		int m = (1 << (M - 1)) - 1;
		for(int j = 0; j < up; j++){
			int s0 = (j << 1) & m, s1 = ((j << 1) + 1) & m;
			// 不清理i
			dp[i][s0] = max(dp[i - 1][j], dp[i][s0]);
			if(countones[j] < Q){
				// 清理i
				dp[i][s1] = max(dp[i - 1][j] + lj[i], dp[i][s1]);
			}
		}
	}
	
	for(int i  = 0; i < (1 << (M - 1)); i++)
	{
		maxlj = max(maxlj, dp[N][i]);
	}
	cout << maxlj << endl;
	return 0;
}