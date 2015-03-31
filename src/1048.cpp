#include <iostream>
using namespace std;

const int NMax = 1000;
const int MMax = (1 << 5);
int dp[NMax][MMax] = {{0}};

bool testFirstLine(int j, int M){
	int i = 0;
	while(i < M){
		if((j & (1 << i)) == 0)
			i++;
		else if(i == M - 1 || !(j & (1 << (i + 1))))
			return false;
		else
			i += 2;
	}
	return true;
}

bool testCompatible(int sa, int sb, int M){
	int i = 0;
	while(i < M){
		if((sa & (1 << i)) == 0){
			if((sb & (1 << i)) == 0)
				return false;
			i++;
		}
		else{
			if((sb & (1 << i)) == 0)
				i++;
			else if(i == M - 1 || !((sa & (1 << (i + 1))) && (sb & (1 << (i + 1)))))
				return false;
			else
				i += 2;
		}
	}
	return true;
}

int main(){
	int N, M;
	cin >> N >> M;
	int allstates = (1 << M);
	for(int i = 0; i < allstates; i++){
		if(testFirstLine(i, M))
			dp[0][i] = 1;
	}
	
	for(int i = 1; i < N; i++){
		for(int j = 0; j < allstates; j++){
			for(int k = 0; k < allstates; k++){
				if(testCompatible(j, k, M)){
					dp[i][j] += dp[i - 1][k];
					dp[i][j] = dp[i][j] % 1000000007;
				}
			}
		}
	}
	cout << dp[N - 1][allstates - 1] << endl;
	return 0;
}