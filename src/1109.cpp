#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

const int NMax = 100010;

int N, M;

struct cmp{
	bool operator()(pair<int, int> &a, pair<int, int> &b){
		return a.second > b.second;
	}
};
unordered_map<int, int> check;
priority_queue<pair<int, int>, vector<pair<int, int> >, cmp> que;
vector<pair<int, int> > edge[NMax];

int main(){
	cin >> N >> M;
	int u, v, length, sum = 0;
	for(int i = 0; i < M; i++){
		cin >> u >> v >> length;
		edge[u].push_back(make_pair(v, length));
		edge[v].push_back(make_pair(u, length));
	}
	
	que.push(make_pair(1, 0));
	pair<int, int> cur;
	while(!que.empty()){
		cur = que.top();
		//cout << cur.first << endl;
		que.pop();
		// already add to set
		if(check.find(cur.first) != check.end())
			continue;
		check[cur.first] = 1;
		sum += cur.second;
		for(auto i = edge[cur.first].begin(); i != edge[cur.first].end(); i++){
			if(check.find(i->first) == check.end()){
				que.push(*i);
			}
		}
	}
	cout << sum << endl;
	return 0;
}