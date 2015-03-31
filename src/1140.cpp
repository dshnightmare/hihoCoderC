#include <iostream>
using namespace std;

const int NMax = 100010;

int N;

unsigned int power[NMax];
unsigned int back[NMax];
long long sum = 0;

void mergeSort(int left, int right){
	if(left >= right)
		return;
	int mid = (left + right) / 2;
	mergeSort(left, mid);
	mergeSort(mid + 1, right);
	int p = left, q = mid + 1, m = left;
	while(p <= mid && q <= right){
		if(power[p] <= power[q]){
			back[m++] = power[p++];
		}
		else{
			back[m++] = power[q++];
			sum += mid - p + 1;
		}
	}
	while(p <= mid)
		back[m++] = power[p++];
	while(q <= right)
		back[m++] = power[q++];
	for(m = left; m <= right; m++)
		power[m] = back[m];
}
int main(){
	cin >> N;
	for(int i = 1; i <= N; i++)
		cin >> power[i];
	mergeSort(1, N);
	cout << sum << endl;
}