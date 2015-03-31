#include <iostream>
#include <bitset>
#include <string.h>
using namespace std;

int t, n, m, c1, c2;
int graph[105][105], order[105];
bitset<105> Bit[105];

void getBit(int root, int pre){
	Bit[root][root] = 1;
	for(int i = 1; i <= n; i++){
		if(graph[root][i] == 1 && i != pre){
			getBit(i, root);
			Bit[root] |= Bit[i];
		}
	}
}

bool solve(int start){
	if(start >= m)
		return true;
	int i = start + 1;
	while(i < m && Bit[order[start]][order[i]] == 1)
		i++;
	i++;
	while(i < m){
		// order[i] 不是 order[start] 的子孙
		if(Bit[order[start]][order[i]] == 0)
			return false;
		i++;
	}
	return solve(start + 1);
}

int main(){
	cin >> t;
	while(t--){
		cin >> n;
		memset(graph, 0, sizeof(graph));
		for(int i = 0; i < n - 1; i++){
			cin >> c1 >> c2;
			graph[c1][c2] = graph[c2][c1] = 1;
		}
		for(int i = 1; i <= n; i++)
			Bit[i].reset();
		cin >> m;
		for(int i = 0; i < m; i++){
			cin >> order[i];
		}
		getBit(1, 0);
		if(solve(0) == true)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
}