#include <iostream>
using namespace std;

const int NMax = 101;

struct Node{
	Node *parent;
	int value;
	Node() : parent(nullptr), value(0){}
} nodes[NMax];

int N, M;
int f[NMax][NMax] = {{0}};

void dp(int pos, int m){
	f[pos][1] = nodes[pos].value;
	if(m == 1)
		return;
	for(int i = 1; i <= N; i++){
		if(nodes[i].parent == (nodes + pos)){
			for(int p = m; p >= 2; p--){
				for(int q = 1; q <= p - 1; q++)
					f[pos][p] = max(f[pos][p], f[pos][p - q] + f[i][q]);
			}
		}
	}
}

void post_order(int pos, int m){
	for(int i = 1; i <= N; i++){
		if(nodes[i].parent == (nodes + pos))
			post_order(i, m - 1);
	}
	dp(pos, m);
}

int main(){
	cin >> N >> M;
	for(int i = 1; i <= N; i++)
		cin >> nodes[i].value;
	for(int i = 1; i < N; i++){
		int a, b;
		cin >> a >> b;
		if(a > b){
			int tmp = a;
			a = b;
			b = tmp;
		}
		nodes[b].parent = (nodes + a);
	}
	nodes[1].parent = nodes;
	post_order(1, M);
	cout << f[1][M] << endl;
}