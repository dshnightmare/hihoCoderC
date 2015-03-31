#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

const int NMax = 100010;
const int MMax = 100010;
bool vis[NMax];
int head[NMax], represent[NMax], size[NMax], ans[MMax], ancestor[NMax];
string name[NMax];

int T, N, M;

unordered_map<string, int> map;
inline int getId(string s){
	if(map.find(s) == map.end()){
		name[T] = s;
		map[s] = T++;
	}
	return map[s];
}

vector<pair<int, int> > QueVec[MMax];

int en;
struct E{
	int s, next;
	E(): next(0) {}
}e[NMax];
inline void add(int fa, int so){
	e[en].s = so;
	e[en].next = head[fa];
	head[fa] = en++;
}

int find(int a){
	// find represent
	int r = a;
	while(r != represent[r])
		r = represent[r];
	int now = a, tmp;
	// 路径压缩
	while(now != r){
		tmp = represent[now];
		represent[now] = r;
		now = tmp;
	}
	return r;
}

void join(int a, int b){
	int ra = find(a), rb = find(b);
	if(ra != rb){
		if(size[ra] >= size[rb]){
			represent[rb] = ra;
			size[ra] += size[rb];
		}
		else{
			represent[ra] = rb;
			size[rb] += size[ra];
		}
	}
}

void init(){
	for(int i = 0; i < NMax; i++){
		represent[i] = i;
		size[i] = 1;
		head[i] = 0;
		vis[i] = false;
	}
	en = T = 1;
}

void Tarjan(const int u){
	ancestor[u] = u;
	for(int i = head[u]; i != 0; i = e[i].next){
		int v = e[i].s;
		Tarjan(v);
		join(u, v);
		// 并查集的represent不一定是根结点
		ancestor[find(u)] = u;
	}
	vis[u] = true;
	for(auto i = QueVec[u].begin(); i != QueVec[u].end(); i++){
		int v = i->first, index = i->second;
		if(vis[v]){
			ans[index] = ancestor[find(v)];
		}
	}
}

int main(){
	init();
	string a, b;
	int sa, sb;
	
	cin >> N;
	for(int i = 0; i < N; i++){
		cin >> a >> b;
		sa = getId(a);
		sb = getId(b);
		add(sa, sb);
	}
	
	cin >> M;
	for(int i = 0; i < M; i++){
		cin >> a >> b;
		sa = getId(a);
		sb = getId(b);
		QueVec[sa].push_back(make_pair(sb, i));
		QueVec[sb].push_back(make_pair(sa, i));
	}
	
	Tarjan(1);
	for(int i = 0; i < M; i++){
		cout << name[ans[i]] << endl;
	}
	return 0;
}