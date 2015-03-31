#include <iostream>
using namespace std;

class TreeNode {
public:
	char alp;
	bool isWord;
	int count;
	TreeNode *next[26];
	
	TreeNode(char _alp, bool _isWord = false) : alp(_alp), isWord(_isWord), count(0) {
		for(int i = 0; i < 26; i++)
			next[i] = nullptr;
	};
};

int main() {
	int n, m;
	char word[11];
	TreeNode root(0), *cur;
	cin >> n;
	for(int i = 0; i < n; i++) {
		cur = &root;
		cin >> word;
		for(int j = 0; word[j] != '\0'; j++) {
			cur->count++;
			TreeNode* &next = cur->next[word[j] - 'a'];
			if(next == nullptr){
				next = new TreeNode(word[j]);
			}
			cur = next;
		}
		cur->count++;
		cur->isWord = true;
	}
	cin >> m;
	for(int i = 0; i < m; i++) {
		cur = &root;
		cin >> word;
		for(int j = 0; word[j] != '\0'; j++) {
			TreeNode* &next = cur->next[word[j] - 'a'];
			cur = next;
			if(cur == nullptr)
				break;
		}
		if(cur != nullptr)
			cout << cur->count << endl;
		else
			cout << 0 << endl;
	}
	return 0;
}