#include <iostream>
#include <bitset>
using namespace std;

const int NMax = 100010;

int T, N;

bitset<NMax> result1, result2;
int grid[NMax];


//
void f(bitset<NMax> cur){
	int res;
	int count;
	for(int i = 2; i <= N; i++){
		res = grid[i - 1];
		count = 0;
		if(cur[i - 2])
			count++;
		if(cur[i - 1])
			count++;
		if(count == res){
			cur.reset(i);
		}
		else if(count == res - 1){
			cur.set(i);
		}
		else
			return;	
	}
	res = grid[N];
	count = 0;
	if(cur[N - 1])
		count++;
	if(cur[N])
		count++;
	if(count == res){
		result1 |= cur;
		result2 &= cur;
	}
}

int main(){
	cin >> T;
	while(T--){
		result1.reset();
		result2.set();
		cin >> N;
		for(int i = 1; i <= N; i++){
			cin >> grid[i];
		}
		bitset<NMax> begin;
		f(begin);
		begin.set(1);
		f(begin);
		cout << result2.count();
		for(int i = 1; i <= N; i++){
			if(result2.test(i))
				cout << " " << i;
		}
		cout << endl;
		cout << N - result1.count();
		for(int i = 1; i <= N; i++){
			if(!result1.test(i))
				cout << " " << i;
		}
		cout << endl;
	}
	return 0;
}