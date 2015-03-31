#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

const int NMax = 1010;
int N, M, S, T;

struct cmp{
	bool operator()(pair<int, int> &a, pair<int, int> &b){
		return a.second > b.second;
	}
};
vector<pair<int, int> > path[NMax];
unordered_map<int, int> check;
priority_queue<pair<int, int>, vector<pair<int, int> >, cmp> que;

int main(){
	int u, v, length;
	cin >> N >> M >> S >> T;
	for(int i = 0; i < M; i++){
		cin >> u >> v >> length;
		path[u].push_back(make_pair(v, length));
		path[v].push_back(make_pair(u, length));
	}
	// init
	for(auto i = path[S].begin(); i != path[S].end(); i++)
		que.push(*i);
	check[S] = 0;
	while(!que.empty()){
		pair<int, int> cur = que.top();
		que.pop();
		// 尚未加入S集合，距离集合最近的元素
		if(check.find(cur.first) == check.end()){
			check[cur.first] = cur.second;
			for(auto i = path[cur.first].begin(); i != path[cur.first].end(); i++){
				if(check.find(i->first) == check.end()){
					que.push(make_pair(i->first, cur.second + i->second));
				}
			}
		}
	}
	cout << check[T] << endl;
	return 0;
}


