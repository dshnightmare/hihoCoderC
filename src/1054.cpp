#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

const int NMax = 400000;

int T, N;

bool mp[NMax][11][11] = {false}, vis[11] = {false};
unordered_map<int, int> check;
int total, ans[11] = {0};
int g[10][10] = {0};
int x[11] = {0}, y[11] = {0};

void init(){
	g[1][3] = 2;
	g[3][1] = 2;
	g[4][6] = 5;
	g[6][4] = 5;
	g[7][9] = 8;//.push_back(8);
	g[9][7] = 8;//.push_back(8);
	g[1][7] = 4;//.push_back(4);
	g[7][1] = 4;//.push_back(4);
	g[2][8] = 5;//.push_back(5);
	g[8][2] = 5;//.push_back(5);
	g[3][9] = 6;//.push_back(6);
	g[9][3] = 6;//.push_back(6);
	g[1][9] = 5;//.push_back(5);
	g[9][1] = 5;//.push_back(5);
	g[3][7] = 5;//.push_back(5);
	g[7][3] = 5;//.push_back(5);
}

void dfs(int cur){
	if(cur > 4){
		int sum = 0;
		for(int i = 1; i < cur; i++){
			sum = sum * 10 + ans[i];
		}
		if(check.find(sum) == check.end()){
			check[sum] = 1;
			for(int i = 2; i < cur; i++){
				mp[total][ans[i - 1]][ans[i]] = true;
				mp[total][ans[i]][ans[i - 1]] = true;
			}
			total++;
		}
	}
	if(cur >= 10)
		return;
	for(int i = 1; i < 10; i++){
		if(!vis[i]){
			vis[i] = true;
			ans[cur] = i;
			if(g[ans[cur - 1]][i] != 0 && !vis[g[ans[cur - 1]][i]]){
				
			}
			else
				dfs(cur + 1);
			vis[i] = false;
		}
	}
}

int main(){
	init();
	dfs(1);
	//cout << total << endl;
	cin >> T;
	while(T--){
		cin >> N;
		for(int i = 0; i < N; i++){
			cin >> x[i] >> y[i];
		}
		int result = 0;
		for(int i = 0; i < total; i++){
			int j;
			for(j = 0; j < N; j++){
				if(mp[i][x[j]][y[j]] == false && mp[i][x[j]][y[j]] == false)
					break;
			}
			if(j == N)
				result++;
		}
		cout << result << endl;
	}
}