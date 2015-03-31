#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

const int NMax = 100010;
int head[NMax] = {0}, height[NMax], indexs[NMax];
int dp[NMax << 1][18];
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

int en;
struct E{
	int s, next;
	E() : next(0) {}
}e[NMax];
inline void add(int fa, int so){
	e[en].s = so;
	e[en].next = head[fa];
	head[fa] = en++;
}

// 转换数组，存的index
vector<int> result;

void convert(int root, int level, vector<int> &result){
	height[root] = level;
	result.push_back(root);
	indexs[root] = result.size() - 1;
	for(int i = head[root]; i != 0; i = e[i].next){
		int v = e[i].s;
		convert(v, level + 1, result);
		result.push_back(root);
		indexs[root] = result.size() - 1;
	}
}

int mymin(int index1, int index2){
	if(height[index1] < height[index2])
		return index1;
	else
		return index2;
}

int getMaxj(int m){
	int n = 1;
	int count = 0; 
	while(n <= m){
		n = n << 1;
		count++;
	}
	return count;
}

void process(int maxj){
	for(int i = 0; i < result.size(); i++)
		dp[i][0] = result[i];
	for(int j = 1; j < maxj; j++){
		for(int i = 0; i + (1 << j) - 1 < result.size(); i++){
			dp[i][j] = mymin(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
		}
	}
}

void init(){
	T = en = 1;
}

int main(){
	init();
	string a, b;
	int sa, sb, left, right, gap;
	
	cin >> N;
	for(int i = 0; i < N; i++){
		cin >> a >> b;
		sa = getId(a);
		sb = getId(b);
		add(sa, sb);
	}
	
	convert(1, 0, result);
	process(getMaxj(result.size()));
	
	cin >> M;
	for(int i = 0; i < M; i++){
		cin >> a >> b;
		sa = getId(a);
		sb = getId(b);
		left = indexs[sa];
		right = indexs[sb];
		if(left > right){
			left ^= right;
			right ^= left;
			left ^= right;
		}
		gap = getMaxj(right - left + 1);
		cout << name[mymin(dp[left][gap - 1], dp[right + 1 - (1 << (gap - 1))][gap - 1])] << endl;
	}
	return 0;
}