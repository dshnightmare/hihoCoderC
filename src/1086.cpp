#include <iostream>
#include <unordered_map>
#include <string>
#include <unordered_map>
using namespace std;

class Cache{
private:
	class CacheNode{
	public:
		string key;
		CacheNode *pre;
		CacheNode *post;
		CacheNode(){
			pre = post = nullptr;
		}
	};
public:
	Cache(int _capacity){
		count = 0;
		capacity = _capacity;
		head = new CacheNode;
		tail = new CacheNode;
		head->post = tail;
		tail->pre = head;
	}
	
	~Cache(){
		
	}
	
	bool get(string key){
		if(check.find(key) == check.end())
			return false;
		CacheNode *cur = check[key];
		moveToHead(cur);
		return true;
	}
	
	void set(string key){
		if(check.find(key) == check.end()){
			check[key] = new CacheNode;
			check[key]->key = key;
			addNode(check[key]);
			
			++count;
			if(count > capacity){
				CacheNode *last = popTail();
				check.erase(last->key);
				delete last;
				--count;
			}
		}
		else
			moveToHead(check[key]);
	}
private:
	void addNode(CacheNode *node){
		node->pre = head;
		node->post = head->post;
		
		head->post->pre = node;
		head->post = node;
	}
	
	void removeNode(CacheNode *node){
		CacheNode *pre = node->pre;
		CacheNode *post = node->post;
		
		pre->post = post;
		post->pre = pre;
	}
	
	void moveToHead(CacheNode *node){
		removeNode(node);
		addNode(node);
	}
	
	CacheNode* popTail(){
		CacheNode *res = tail->pre;
		removeNode(res);
		return res;
	}
	
	unordered_map<string, CacheNode *> check;
	int count;
	int capacity;
	CacheNode *head, *tail;
};

int main(){
	int n = 0, m = 0;
	string key;
	cin >> n >> m;
	Cache c(m);
	for(int i = 0; i < n; i++){
		cin >> key;
		if(c.get(key))
			cout << "Cache" << endl;
		else{
			cout << "Internet" << endl;
			c.set(key);
		}
	}
	return 0;
}