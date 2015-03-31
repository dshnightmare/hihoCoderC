#include <iostream>
using namespace std;

const int NMax = 100010;

int N, M;

enum op_mode{ none = 0, inc = 1, set = 2 };
struct Line{
	int left, right;
	int sum;
	int value;
	op_mode op;
} line[NMax << 2];

void build(int node, int left, int right){
	int mid = (left + right) >> 1;
	line[node].left = left;
	line[node].right = right;
	line[node].value = 0;
	line[node].op = none;
	if(left == right)
		cin >> line[node].sum;
	else{
		build(node << 1, left, mid);
		build((node << 1) + 1, mid + 1, right);
		line[node].sum = line[node << 1].sum + line[node << 1 | 1].sum;
	}
}

void updateRange(int node, int left, int right, op_mode op, int value){
	if(line[node].left == left && line[node].right == right){
		if(op == inc){
			if(line[node].op == none)
				line[node].op = op;
			line[node].value += value;
			line[node].sum += (right - left + 1) * value;
		}
		else{
			line[node].op = op;
			line[node].value = value;
			line[node].sum = (right - left + 1) * value;
		}
	}
	else{
		if(line[node].op != none){	
			if(line[node].op == inc){
				if(line[node << 1].op == none)
					line[node << 1].op = line[node].op;
				line[node << 1].value += line[node].value;
				line[node << 1].sum += (line[node << 1].right - line[node << 1].left + 1) * line[node].value;
				
				if(line[node << 1 | 1].op == none)
					line[node << 1 | 1].op = line[node].op;
				line[node << 1 | 1].value += line[node].value;
				line[node << 1 | 1].sum += (line[node << 1 | 1].right - line[node << 1 | 1].left + 1) * line[node].value;
			}
			else{
				line[node << 1].op = line[node].op;
				line[node << 1].value = line[node].value;
				line[node << 1].sum = (line[node << 1].right - line[node << 1].left + 1) * line[node].value;
				
				line[node << 1 | 1].op = line[node].op;
				line[node << 1 | 1].value = line[node].value;
				line[node << 1 | 1].sum = (line[node << 1 | 1].right - line[node << 1 | 1].left + 1) * line[node].value;
			}
			
			line[node].value = 0;
			line[node].op = none;
		}
		
		int mid = (line[node].left + line[node].right) >> 1;
		if(right <= mid)
			updateRange(node << 1, left, right, op, value);
		else if(left > mid)
			updateRange(node << 1 | 1, left, right, op, value);
		else{
			updateRange(node << 1, left, mid, op, value);
			updateRange(node << 1 | 1, mid + 1, right, op, value);
		}
		
		line[node].sum = line[node << 1].sum + line[node << 1 | 1].sum;
	}
}

int main(){
	cin >> N >> M;
	build(1, 1, N + 1);
	int left, right, value, op;
	for(int i = 0; i < M; i++){
		cin >> op >> left >> right >> value;
		updateRange(1, left + 1, right + 1, op == 0? inc : set, value);
		cout << line[1].sum << endl;
	}
	return 0;
}