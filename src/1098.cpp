#include <iostream>
#include <algorithm>
using namespace std;

const int NMax = 100010;
const int MMax = 1000010;

int N, M;
int represent[NMax], size[NMax], sum[NMax];
struct E{
	int u, v;
	int length;
} edge[MMax];

struct {
	bool operator()(const E &e1, const E &e2){
		return e1.length < e2.length;
	}
} cmp;

int find(int u){
	int r = u;
	while(r != represent[r]){
		r = represent[r];
	}
	int now = u, tmp;
	while(now != r){
		tmp = represent[now];
		represent[now] = r;
		now = tmp;
	}
	return r;
}

int join(int u, int v, int length){
	int ru = find(u), rv = find(v);
	if(ru != rv){
		if(size[ru] >= size[rv]){
			represent[rv] = ru;
			size[ru] += size[rv];
			sum[ru] += (sum[rv] + length);
			return size[ru];
		}
		else{
			represent[ru] = rv;
			size[rv] += size[ru];
			sum[rv] += (sum[ru] + length);
			return size[rv];
		}
	}
	return size[ru];
}

int main(){
	cin >> N >> M;
	for(int i = 1; i <= N; i++){
		represent[i] = i;
		size[i] = 1;
		sum[i] = 0;
	}
	
	for(int i = 0; i < M; i++){
		cin >> edge[i].u >> edge[i].v >> edge[i].length;
	}
	sort(edge, edge + M, cmp);
	for(int i = 0; i < M; i++){
		if(join(edge[i].u, edge[i].v, edge[i].length) == N){
			cout << sum[find(edge[i].u)] << endl;
			break;
		}
	}
	return 0;
}