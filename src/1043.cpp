#include <iostream>
using namespace std;

const int NMax = 505;
const int MMax = 100005;

int N, M;
int need[NMax], value[NMax];
int dp[MMax] = {0};


int main(){
	cin >> N >> M;
	for(int i = 1; i <= N; i++)
		cin >> need[i] >> value[i];
	for(int i = 1; i <= N; i++){
		for(int x = 0; x <= M; x++){
			if(need[i] <= x)
				dp[x] = max(dp[x], dp[x - need[i]] + value[i]);
		}
	}
	cout << dp[M] << endl;
	return 0;
}