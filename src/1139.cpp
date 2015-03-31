#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <memory.h>
using namespace std;

const int NMax = 100010, WMax = 1000000, WMin = 1;

int N, M, K, T;
vector<pair<int, int> > edge[NMax];
queue<pair<int, int> > que;
bool visited[NMax] = {false};

bool findX(int u, int k, int x){
	while(!que.empty())
		que.pop();
	que.push(make_pair(1, 0));
	memset(visited, 0, sizeof(visited));
	visited[1] = true;
	pair<int, int> cur;
	while(!que.empty()){
		cur = que.front();
		que.pop();
		
		if(cur.second > K)
			break;
		if(cur.first == T)
			return true;
		for(auto i = edge[cur.first].begin(); i != edge[cur.first].end(); i++){
			if(!visited[i->first] && i->second <= x){
				visited[i->first] = true;
				que.push(make_pair(i->first, cur.second + 1));
			}
		}
	}
	return false;
}

int main(){
	cin >> N >> M >> K >> T;
	int u, v, w;
	int up = WMin, low = WMax, mid;
	for(int i = 0; i < M; i++){
		scanf("%d %d %d", &u, &v, &w);
		edge[u].push_back(make_pair(v, w));
		edge[v].push_back(make_pair(u, w));
		if(w < low)
			low = w;
		if(w > up)
			up = w;
	}
	
	
	//findX(1, 0, 100);
	while(low != up - 1){
		mid = (up + low) / 2;
		//cout << mid << endl;
		if(findX(1, 0, mid))
			up = mid;
		else
			low = mid;
	}
	cout << up << endl;
}