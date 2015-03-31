#include <iostream>
#include <vector>
#include <memory.h>
using namespace std;

const int NMax = 1005;

int N, M;
vector<int> edge[NMax];
bool visited[NMax] = {0};
int linker[NMax] = {0};

bool findPath(int u){
	for(auto i = edge[u].begin(); i != edge[u].end(); i++){
		if(!visited[*i]){
			visited[*i] = true;
			if(linker[*i] == 0 || findPath(linker[*i])){
				linker[*i] = u;
				return true;
			}
		}
	}
	return false;
}
int main(){
	cin >> N >> M;
	int u, v;
	for(int i = 0; i < M; i++){
		cin >> u >> v;
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	
	int count = 0;
	for(int i = 1; i <= N; i++){
		memset(visited, 0, sizeof(visited));
		if(findPath(i))
			count++;
	}
	cout << count / 2 << endl;
	return 0;
}