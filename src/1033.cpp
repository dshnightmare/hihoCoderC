#include <iostream>
#include <string.h>
using namespace std;

const long long mod = 1e9 + 7;
long long base[21];
int bits[21], length, cur;

struct node{
	long long s, n;
};

// -100 <= target <= 100
node dp[21][201];
node dfs(int len, int target, bool end_flag){
	node t;
	t.s = t.n = 0;
	if(len == 0){
		if(target == 100)
			t.n = 1;
		return t;
	}
	
	if(!end_flag && dp[len][target].n != -1)
		return dp[len][target];
	int sign = ((cur - len) & 1) ? (-1) : 1;
	int tail = end_flag ? bits[len - 1] : 9;
	int head;
	if(len == cur)
		head = 1;
	else
		head = 0;
	for(int i = head; i <= tail; i++){
		node tmp = dfs(len - 1, target - i * sign, end_flag && (i == tail));
		if(tmp.n > 0){
			t.n += tmp.n;
			t.s = (t.s + tmp.s) % mod;
			long long q = ((((tmp.n % mod) * base[len - 1]) % mod) * i) % mod;
			t.s = (t.s + q) % mod;
		}
	}
	if(!end_flag)
		dp[len][target] = t;
	return t;
}

long long cal(long long n, int target){
	long long ans = 0;
	if(n <= 0)
		return 0;
	length = 0;
	while(n){
		bits[length++] = n % 10;
		n /= 10;
	}
	for(cur = 1; cur <= length; cur++){
		memset(dp,-1,sizeof dp);
		ans = (ans + dfs(cur, target + 100, cur == length).s) % mod;
	}
	return ans;
}

int main(){
	// 数位DP
	long long l, r;
	int k;
	node t;
	t.n = -1;
	t.s = 0;
	for(int i = 0; i < 21; i++){
		for(int j = 0; j < 202; j++)
			dp[i][j] = t;
	}
	base[0] = 1;
	for(int i = 1; i < 21; i++){
		base[i] = (base[i - 1] * 10) % mod;  
	}
	cin >> l >> r >> k;
	cout << (cal(r, k) - cal(l - 1, k) + mod) % mod << endl;
	return 0;
}