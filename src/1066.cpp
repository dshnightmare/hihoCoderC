#include <iostream>
#include <unordered_map>
using namespace std;

class Node{
public:
	Node *represent;
	string name;
	Node() : represent(nullptr) {}
	Node(string s) : represent(nullptr), name(s) {}
};

Node* find_represent(Node *n){
	if(n == n->represent)
		return n;
	else{
		n->represent = find_represent(n->represent);
		return n->represent;
	}
}

int main(){
	int N, op;
	string s1, s2;
	Node *n1, *n2;
	cin >> N;
	unordered_map<string, Node> map;
	for(int i = 0; i < N; i++){
		cin >> op >> s1 >> s2;
		if(map.find(s1) == map.end()){
			map[s1] = Node(s1);
			map[s1].represent = &map[s1];
		}
		if(map.find(s2) == map.end()){
			map[s2] = Node(s2);
			map[s2].represent = &map[s2];
		}
		n1 = &map[s1];
		n2 = &map[s2];
		n1 = find_represent(n1);
		n2 = find_represent(n2);
		if(op == 1){
			if(n1 == n2)
				cout << "yes" << endl;
			else
				cout << "no" << endl;
		}
		else{
			if(n1 != n2){
				n1->represent = n2;
			}
		}
	}
}