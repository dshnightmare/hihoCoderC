#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

const int NMax = 10010;

int T, N, M;
vector<int> edge[NMax];
unordered_map<int, bool> check;
queue<int> que;

int main(){
	cin >> T;
	int u, v;
	while(T--){
		cin >> N >> M;
		for(int i = 1; i <= N; i++){
			edge[i].clear();
		}
		for(int i = 0; i < M; i++){
			cin >> u >> v;
			edge[u].push_back(v);
			edge[v].push_back(u);
		}
		check.clear();
		check[u] = true;
		que.push(u);
		int cur;
		bool flag = true;
		while(!que.empty()){
			cur = que.front();
			que.pop();
			for(auto i = edge[cur].begin(); i != edge[cur].end(); i++){
				if(check.find(*i) == check.end()){
					check[*i] = !check[cur];
					que.push(*i);
				}
				else{
					if(check[cur] == check[*i]){
						flag = false;
						break;
					}
				}
			}
			if(!flag)
				break;
		}
		while(!que.empty())
			que.pop();
		if(flag)
			cout << "Correct" << endl;
		else
			cout << "Wrong" << endl;
	}
	return 0;
}