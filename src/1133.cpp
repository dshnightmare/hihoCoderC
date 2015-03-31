#include <iostream>
using namespace std;

const int NMax = 1000010;

int N, K;
int num[NMax];

int partition(int left, int right){
	int pivot = num[left];
	while(left < right){
		while(left < right && num[right] > pivot)
			right--;
		if(left < right)
			num[left++] = num[right];
		while(left < right && num[left] <= pivot)
			left++;
		if(left < right)
			num[right--] = num[left];
	}
	num[left] = pivot;
	return left;
}

int findK(int left, int right){
	int mid = partition(left, right);
	if(mid == K)
		return num[K];
	else if(mid < K)
		return findK(mid + 1, right);
	else
		return findK(left, mid - 1);
}

int main(){
	cin >> N >> K;
	for(int i = 1; i <= N; i++){
		cin >> num[i];
	}
	cout << findK(1, N) << endl;
	return 0;
}