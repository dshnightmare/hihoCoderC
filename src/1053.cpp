#include <iostream>
#include <algorithm>
using namespace std;

const int NMax = 100005;

int T, N, R;
pair<int, pair<int, int> > res[NMax];

struct Comp{
	bool operator()(const pair<int, pair<int, int> >&ele1, const pair<int, pair<int, int> > &ele2){
		if(ele1.first == ele2.first)
			return ele1.second.first > ele2.second.first;
		return ele1.first < ele2.first;
	}
} comp;
// 贪心的规则:尽可能的让左边的城市装满人，多了迁走，少了迁来，可以允许不满但不允许过多
bool check(int maxl){
	for(int i = 0; i < N; i++){
		int j = i + 1;
		int sl = maxl - res[i].second.second;
		if(res[i].second.first ＝= sl)
			continue;
		else if(res[i].second.first > sl){
			int sg = res[i].second.first - sl;
			while(sg > 0 && res[j].first - res[i].first <= R && j < N){
				int tmp = maxl - res[j].second.second;
				res[j].second.second += min(sg, tmp);
				sg -= min(sg, tmp);
				j++;
			}
			if(sg != 0)
				return false;
		}
		else{
			int sc = sl - res[i].second.first;
			while(sc > 0 && res[j].first - res[i].first <= R && j < N){
				sc -= 
			}
		}
	}
	return true;
}

int main(){
	cin >> T;
	while(T--){
		cin >> N >> R;
		int left = 1e9, right = 0, mid;
		for(int i = 0; i < N; i++){
			cin >> res[i].first >> res[i].second.first;
			res[i].second.second = 0;
			if(res[i].second.first > right)
				right = res[i].second.first;
			if(res[i].second.first < left)
				left = res[i].second.first;
		}
		// sort(res, res + N, [](const pair<int, pair<int, int> > &e1, const pair<int, pair<int, int}> > &e2){
// 			return e1.first < e2.first;
// 		});
		sort(res, res + N, comp);
		while(left != right - 1){
			mid = (left + right) / 2;
			
			if(check(mid)){
				right = mid;
				//cout << mid << "   true" << endl;
			}
			else{
				left = mid;
				//cout << mid << "   false" << endl;
			}
			
			for(int i = 0; i < N; i++)
				res[i].second.second = 0;
		}
		cout << right << endl;
	}
	return 0;
}