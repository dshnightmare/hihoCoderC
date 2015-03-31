#include <iostream>
#include <set>
#include <unordered_map>
using namespace std;

const int NMax = 100010;

set<int> indexs;
unordered_map<int, int> maps;
unordered_map<int, int> exist;
int leftB[NMax], rightB[NMax];
int N, L;

struct Line{
	int left, right;
	int tag;
} line[NMax << 3];

void build(int node, int left, int right){
	int mid = (left + right) / 2;
	line[node].left = left;
	line[node].right = right;
	line[node].tag = -1;
	if(left != right){
		build(node << 1, left, mid);
		build((node << 1) + 1, mid + 1, right);
	}
}

void updateRange(int node, int left, int right, int value){
	if(line[node].left == left && line[node].right == right){
		line[node].tag = value;
	}
	else{
		if(line[node].tag != -1){
			line[node << 1].tag = line[node].tag;
			line[(node << 1) + 1].tag = line[node].tag;
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
	}
}

void traverse(int node){
	if(line[node].tag != -1){
		exist[line[node].tag] = 1;
	}
	else{
		if(line[node].left != line[node].right){
			traverse(node << 1);
			traverse((node << 1) + 1);
		}
	}
}

int main(){
	cin >> N >> L;
	for(int i = 0; i < N; i++){
		cin >> leftB[i] >> rightB[i];
	}
	indexs.insert(leftB, leftB + N);
	indexs.insert(rightB, rightB + N);
	//cout << indexs.size() << endl;
	int count = 1;
	for(auto i = indexs.begin(); i != indexs.end(); i++){
		//cout << *i << "map to";
		maps[*i] = count++;
		//cout << maps[*i] << endl;
	}
	
	build(1, 1, indexs.size());
	for(int i = 0; i < N; i++){
		// 这里右边界需要－1 important
		updateRange(1, maps[leftB[i]], maps[rightB[i]] - 1, i);
	}
	traverse(1);
	cout << exist.size() << endl;
	return 0;
}