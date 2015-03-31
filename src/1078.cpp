#include <iostream>
#include <stdio.h>
using namespace std;

const int NMax = 1000010;

int weight[NMax];
int N, Q;
	
struct Line{
	int left, right;
	int sum;
	int tag;
} line[NMax << 2];

void build(int node, int left, int right){
	int mid = (left + right) / 2;
	line[node].left = left;
	line[node].right = right;
	line[node].tag = -1;
	if(left == right)
		line[node].sum = weight[left];
	else{
		build(node << 1, left, mid);
		build((node << 1) + 1, mid + 1, right);
		line[node].sum = line[node << 1].sum + line[(node << 1) + 1].sum;
	}
}

int search(int node, int left, int right){
	if(line[node].left == left && line[node].right == right)
		return line[node].sum;
	else{
		if(line[node].tag != -1){
			line[node << 1].tag = line[node].tag;
			line[node << 1].sum = (line[node << 1].right - line[node << 1].left + 1) * line[node].tag;
			
			line[(node << 1) + 1].tag = line[node].tag;
			line[(node << 1) + 1].sum = (line[(node << 1) + 1].right - line[(node << 1) + 1].left + 1) * line[node].tag;
			
			line[node].tag = -1;
		}
		
		int mid = (line[node].left + line[node].right) / 2;
		if(right <= mid)
			return search(node << 1, left, right);
		else if(left > mid)
			return search((node << 1) + 1, left, right);
		else{
			return search(node << 1, left, mid) + search((node << 1) + 1, mid + 1, right);
		}
	}
}

void update(int node, int pos, int value){
	//cout << line[node].left << "  " << line[node].right << endl;
	if(line[node].left == pos && line[node].right == pos){
		line[node].sum = value;
		return;
	}
	int mid = (line[node].left + line[node].right) / 2;
	if(pos <= mid)
		update(node << 1, pos, value);
	else
		update((node << 1) + 1, pos, value);
	line[node].sum = line[node << 1].sum + line[(node << 1) + 1].sum;
}

void updateRange(int node, int left, int right, int value){
	if(line[node].left == left && line[node].right == right){
		line[node].tag = value;
		line[node].sum = (right - left + 1) * value;
	}
	else{
		if(line[node].tag != -1){
			line[node << 1].tag = line[node].tag;
			line[node << 1].sum = (line[node << 1].right - line[node << 1].left + 1) * line[node].tag;
			
			line[(node << 1) + 1].tag = line[node].tag;
			line[(node << 1) + 1].sum = (line[(node << 1) + 1].right - line[(node << 1) + 1].left + 1) * line[node].tag;
			
			line[node].tag = -1;
		}
		
		int mid = (line[node].left + line[node].right) / 2;
		if(right <= mid)
			updateRange(node << 1, left, right, value);
		else if(left > mid)
			updateRange((node << 1) + 1, left, right, value);
		else{
			updateRange(node << 1, left, mid, value);
			updateRange((node << 1) + 1, mid + 1, right, value);
		}
		
		line[node].sum = line[node << 1].sum + line[(node << 1) + 1].sum;
	}
}

int main(){
	cin >> N;
	for(int i = 1; i <= N; i++){
		scanf("%d", &weight[i]);
	}
	build(1, 1, N);
	int left, right, op, value;
	cin >> Q;
	for(int i = 0; i < Q; i++){
		//cin >> op >> left >> right;
		scanf("%d", &op);
		//query
		if(op == 0){
			scanf("%d %d", &left, &right);
			//cout << search(1, left, right) << endl;
			printf("%d\n", search(1, left, right));
		}
		else{//update
			scanf("%d %d %d", &left, &right, &value);
			updateRange(1, left, right, value);
		}
	}
	return 0;
}
