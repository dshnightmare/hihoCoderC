#include <iostream>
using namespace std;

const int NMax = 100001;

struct Node{
	Node *parent;
	int first, second;
	Node() : parent(nullptr), first(0), second(0){}
};

int main(){
	Node nodes[NMax];
	int N;
	cin >> N;
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
	
	int maxL = 0;
	for(int i = N; i > 0; i--){
		if(nodes[i].first + nodes[i].second > maxL)
			maxL = nodes[i].first + nodes[i].second;
		int first = nodes[i].first + 1;
		if(first > nodes[i].parent->first){
			nodes[i].parent->second = nodes[i].parent->first;
			nodes[i].parent->first = first;
		}
		else if(first > nodes[i].parent->second){
			nodes[i].parent->second = first;
		}
	}
	cout << maxL << endl;
	return 0;
}