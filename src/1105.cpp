#include <iostream>
using namespace std;

class CHeap{
private:
	int *data;
	int N;
public:
	CHeap(int maxN){
		data = new int[maxN + 1];
		N = 0;
	}
	
	~CHeap(){
		delete[] data;
	}
	
	bool empty(){
		return N == 0;
	}
	
	int size(){
		return N;
	}
	
	void push(int ele){
		data[++N] = ele;
		swim(N);
	}
	
	int top(){
		return data[1];
	}
	
	void pop(){
		exch(1, N--);
		//data[N-1] = 0;
		sink(1);
	}
	
private:
	bool less(int i, int j){
		return i < j;
	}
	
	void exch(int i, int j){
		int tmp = data[i];
		data[i] = data[j];
		data[j] = tmp;
	}
	
	void swim(int k){
		while(k > 1 && data[k / 2] < data[k]){
			exch(k / 2, k);
			k /= 2;
		}
	}
	
	void sink(int k){
		while(2 * k <= N){
			int j = 2 * k;
			if(j < N && data[j] < data[j + 1])
				j++;
			if(data[k] >= data[j])
				break;
			exch(k, j);
			k = j;
		}
	}
};

int N;

int main(){
	cin >> N;
	CHeap heap(N);
	
	char op;
	int weight;
	for(int i = 0; i < N; i++){
		cin >> op;
		if(op == 'A'){
			cin >> weight;
			heap.push(weight);
		}
		else{
			cout << heap.top() << endl;
			heap.pop();
		}
	}
	return 0;
}