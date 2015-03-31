#include <iostream>
#include <queue>
using namespace std;

class TreeNode {
public:
	bool isWord;
	TreeNode *next[26];
	TreeNode *prev;
	
	TreeNode(bool _isWord = false) : isWord(_isWord){
		prev = nullptr;
		for(int i = 0; i < 26; i++)
			next[i] = nullptr;
	};
};

void build(TreeNode *root){
	queue<TreeNode*> que;
	TreeNode *proot = root;
	for(int i = 0; i < 26; i++){
		if(proot->next[i] != nullptr){
			proot->next[i]->prev = root;
			que.push(proot->next[i]);
		}
	}
	while(!que.empty()){
		proot = que.front();
		que.pop();
		for(int i = 0; i < 26; i++){
			TreeNode *p = proot->next[i];
			if(p != nullptr && p->isWord == false){
				TreeNode *prev = proot->prev;
				while(prev){
					if(prev->next[i] != nullptr){
						p->prev = prev->next[i];
						if(p->prev->isWord == true)
							p->isWord = true;
						break;
					}
					else
						prev = prev->prev;
				}
				if(p->prev == nullptr)
					p->prev = root;

				que.push(p);
			}
		}
	}
}

bool search(string a, TreeNode *root){
	int len = a.size();
	TreeNode *proot = root;
	for(int i = 0; i < len; i++){
		while(true){
			if(proot->next[a[i] - 'a'] != nullptr){
				proot = proot->next[a[i] - 'a'];
				if(proot->isWord == true)
					return true;
				break;
			}
			else
				proot = proot->prev;
			if(proot == root || proot == nullptr){
				proot = root;
				break;
			}
		}
	}
	return false;
}

int main() {
	int n;
	string word;
	TreeNode root, *cur;
	cin >> n;
	for(int i = 0; i < n; i++) {
		cur = &root;
		cin >> word;
		for(int j = 0; j < word.size(); j++) {
			TreeNode* &next = cur->next[word[j] - 'a'];
			if(next == nullptr){
				next = new TreeNode;
			}
			cur = next;
		}
		cur->isWord = true;
	}
	build(&root);
	string artical;
	cin >> artical;
	bool result = search(artical, &root);
	if(result)
		cout << "YES" << endl;
	else
		cout <<  "NO" << endl;
	return 0;
}