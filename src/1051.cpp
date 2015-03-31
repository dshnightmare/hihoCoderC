#include <iostream>
#include <memory.h>
using namespace std;

const int NMax = 105;

int T, N, M;
int days[NMax];
int valid[NMax];

int main(){
	cin >> T;
	while(T--){
		cin >> N >> M;
		for(int i = 0; i < N; i++)
			cin >> days[i];
		if(M >= N)
			cout << 100 << endl;
		else{
			int max = 0;
			for(int i = 0; i <= N - M; i++){
				memset(valid, 0, sizeof(valid));
				for(int j = 0; j < M; j++){
					valid[i + j] = 1;
				}
				int pre = 1;
				for(int i = 0; i < N; i++){
					if(valid[i] != 1){
						if(days[i] - pre > max)
							max = days[i] - pre;
						pre = days[i] + 1;
					}
				}
				if(101 - pre > max)
					max = 101 - pre;
			}
			cout << max << endl;
		}
	}
	return 0;
}