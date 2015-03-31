#include <iostream>
#include <stdio.h>
using namespace std;

const int NMax = 1000010;

int weight[NMax];
int N, Q;
	
struct Line{
	int left, right;
	int min;
} line[NMax << 2];

void build(int node, int left, int right){
	int mid = (left + right) / 2;
	line[node].left = left;
	line[node].right = right;
	if(left == right)
		line[node].min = weight[left];
	else{
		build(node << 1, left, mid);
		build((node << 1) + 1, mid + 1, right);
		line[node].min = min(line[node << 1].min, line[(node << 1) + 1].min);
	}
}

int search(int node, int left, int right){
	if(line[node].left == left && line[node].right == right)
		return line[node].min;
	int mid = (line[node].left + line[node].right) / 2;
	if(right <= mid)
		return search(node << 1, left, right);
	else if(left > mid)
		return search((node << 1) + 1, left, right);
	else{
		return min(search(node << 1, left, mid), search((node << 1) + 1, mid + 1, right));
	}
}

void update(int node, int pos, int value){
	//cout << line[node].left << "  " << line[node].right << endl;
	if(line[node].left == pos && line[node].right == pos){
		line[node].min = value;
		return;
	}
	int mid = (line[node].left + line[node].right) / 2;
	if(pos <= mid)
		update(node << 1, pos, value);
	else
		update((node << 1) + 1, pos, value);
	line[node].min = min(line[node << 1].min, line[(node << 1) + 1].min);
}

int main(){
	cin >> N;
	for(int i = 1; i <= N; i++){
		scanf("%d", &weight[i]);
	}
	build(1, 1, N);
	int left, right, op;
	cin >> Q;
	for(int i = 0; i < Q; i++){
		//cin >> op >> left >> right;
		scanf("%d %d %d", &op, &left, &right);
		//query
		if(op == 0){
			//cout << search(1, left, right) << endl;
			printf("%d\n", search(1, left, right));
		}
		else{//update
			update(1, left, right);
		}
	}
	return 0;
}
