#include <iostream>
using namespace std;

struct Node{
	char val;
	Node *left, *right;
	Node(char v) : val(v), left(nullptr), right(nullptr) {};
};

Node *build(string pre, string in){
	if(pre.size() == 0)
		return nullptr;
	Node *root = new Node(pre[0]);
	if(pre.size() == 1)
		return root;
	int mid = 0;
	for(mid = 0; mid < in.size(); mid++){
		if(pre[0] == in[mid])
			break;
	}
	root->left = build(pre.substr(1, mid), in.substr(0, mid));
	root->right = build(pre.substr(mid + 1), in.substr(mid + 1));
	return root;
}

void postTraversal(Node *root){
	if(root == nullptr)
		return;
	postTraversal(root->left);
	postTraversal(root->right);
	cout << root->val;
}
int main(){
	string pre, in;
	cin >> pre >> in;
	postTraversal(build(pre, in));
	cout << endl;
	return 0;
}