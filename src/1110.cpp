#include <iostream>
#include <memory.h>
using namespace std;

const int NMax = 105;

bool dp[NMax][NMax] = {{false}};

int main(){
	string reg;
	while(cin >> reg){
		memset(dp, 0, sizeof(dp));
		int len = reg.size();
		for(int i = 0; i < len; i++){
			if(reg[i] == '0' || reg[i] == '1')
				dp[i][i] = true;
		}
		
		for(int i = len - 1; i >= 0; i--){
			for(int j = i + 1; j < len; j++){
				for(int k = i; k < j; k++){
					dp[i][j] |= dp[i][k] && dp[k+1][j];
					if(reg[k] == '|')
						dp[i][j] |= dp[i][k-1] && dp[k+1][j];
				}
				if(reg[i] == '(' && reg[j] == ')')
					dp[i][j] |= dp[i+1][j-1];
				if(reg[j] == '*')
					dp[i][j] |= dp[i][j-1];
			}
		}
		
		cout << (dp[0][len - 1] ? "yes" : "no") << endl;
	}
}