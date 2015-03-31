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

int bsearch(int left, int right, int value){
	if(left > right)
		return -1;
	int mid = partition(left, right);
	if(value == num[mid]){
		return mid;
	}
	else if(value > num[mid])
		return bsearch(mid + 1, right, value);
	else
		return bsearch(left, mid - 1, value);
}

int main(){
	cin >> N >> K;
	for(int i = 1; i <= N; i++){
		cin >> num[i];
	}
	cout << bsearch(1, N, K) << endl;
	// int countS = 0, countB = 0;
// 	for(int i = 1; i <= N; i++){
// 		if(num[i] < K)
// 			countS++;
// 		else if(num[i] > K)
// 			countB++;
// 	}
// 	if(countS + countB == N)
// 		cout << -1 << endl;
// 	else
// 		cout << countS + 1 << endl;
	return 0;
}