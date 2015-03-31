#include <iostream>
#include <stdio.h>
using namespace std;

const int NMax = 1000020;
int dp[NMax][20];
int weight[NMax];
int N, Q;

void process(int maxj){
	for(int i = 1; i <= N; i++)
		dp[i][0] = weight[i];
	for(int j = 1; j < maxj; j++){
		for(int i = 1; i + (1 << j) - 1 <= N; i++){
			dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
		}
	}
}

int getMaxj(int m){
	int n = 1;
	int count = 0; 
	while(n <= m){
		n = n << 1;
		count++;
	}
	return count;
}

int main(){
	cin >> N;
	for(int i = 1; i <= N; i++){
		scanf("%d", &weight[i]);
	}
	process(getMaxj(N));
	cin >> Q;
	int left, right, gap;
	for(int i = 0; i < Q; i++){
		scanf("%d %d", &left, &right);
		//cin >> left >> right;
		gap = getMaxj(right - left + 1);
		printf("%d\n", min(dp[left][gap - 1], dp[right + 1 - (1 << (gap - 1))][gap - 1]));
		//cout << min(dp[left][gap - 1], dp[right + 1 - (1 << (gap - 1))][gap - 1]) << endl;
	}
	return 0;
}