#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
using namespace std;

const int NMax = 1005;

int N;
int matrix[NMax][NMax];

struct cmp{
	bool operator()(pair<int, int> &a, pair<int, int> &b){
		return a.second > b.second;
	}
};
unordered_map<int, int> maxL;
priority_queue<pair<int, int>, vector<pair<int, int> >, cmp> que;

int main(){
	cin >> N;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++)
			cin >> matrix[i][j];
	}
	for(int i = 1; i < N; i++){
		que.push(make_pair(i, matrix[0][i]));
		maxL[i] = matrix[0][i];
	}
	int sum = 0;
	pair<int, int> cur;
	while(!que.empty()){
		cur = que.top();
		que.pop();
		if(maxL.find(cur.first) != maxL.end()){
			sum += cur.second;
			maxL.erase(cur.first);
			for(int i = 0; i < N; i++){
				if(maxL.find(i) != maxL.end() && matrix[cur.first][i] < maxL[i]){
					que.push(make_pair(i, matrix[cur.first][i]));
					maxL[i] = matrix[cur.first][i];
				}
			}
		}
	}
	cout << sum << endl;
	return 0;
}