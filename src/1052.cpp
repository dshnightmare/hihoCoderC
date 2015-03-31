#include <iostream>
using namespace std;

int T, K;

int main(){
	cin >> T;
	string gene;
	while(T--){
		cin >> gene >> K;
		int length = gene.size(), interval = length - K;
		int sum = 0;
		for(int i = 0; i < interval; i++){
			int count[4] = {0};
			for(int j = i; j < length; j += interval){
				if(gene[j] == 'A')
					count[0]++;
				else if(gene[j] == 'G')
					count[1]++;
				else if(gene[j] == 'C')
					count[2]++;
				else
					count[3]++;
			}
			int total = 0, maxC = 0;
			for(int j = 0; j < 4; j++){
				total += count[j];
				maxC = max(maxC, count[j]);
			}
			sum += total - maxC;
		}
		cout << sum << endl;
	}
	return 0;
}