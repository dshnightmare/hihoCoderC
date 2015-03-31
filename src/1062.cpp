#include <iostream>
#include <unordered_map>
using namespace std;

struct Node{
	Node *parent;
	string value;
	Node() : parent(nullptr), value("") {}
	Node(string s) : parent(nullptr), value(s) {}
};

int main(){
	unordered_map<string, Node> map;
	int N, M;
	cin >> N;
	string s1, s2;
	for(int i = 0; i < N; i++){
		cin >> s1 >> s2;
		if(map.find(s1) == map.end())
			map[s1] = Node(s1);
		if(map.find(s2) == map.end())
			map[s2] = Node(s2);
		map[s2].parent = &map[s1];
	}
	cin >> M;
	for(int i = 0; i < M; i++){
		int l1 = 0, l2 = 0;
		cin >> s1 >> s2;
		Node *cur;
		if(map.find(s1) == map.end())
			map[s1] = Node(s1);
		cur = &map[s1];
		while(cur != nullptr){
			cur = cur->parent;
			l1++;
		}
		if(map.find(s2) == map.end())
			map[s2] = Node(s2);
		cur = &map[s2];
		while(cur != nullptr){
			cur = cur->parent;
			l2++;
		}
		Node *p = &map[s1], *q = &map[s2];
		if(l2 > l1){
			for(int j = 0; j < l2 - l1; j++)
				q = q->parent;
		}
		else{
			for(int j = 0; j < l1 - l2; j++)
				p = p->parent;
		}
		while(p != q){
			p = p->parent;
			q = q->parent;
		}
		if(p == nullptr)
			cout << -1 << endl;
		else
			cout << p->value << endl;
	}
	return 0;
}