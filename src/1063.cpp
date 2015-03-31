#include <iostream>
#include <vector>
using namespace std;

const long long MOD = 1000000007;
const int NMax = 105, DMax = 1000005;

int N, Q;
long long dp[NMax][NMax << 2][2];
int value[NMax], top[NMax], ans[DMax];
vector<pair<int, int> > edge[NMax];

void getdp(int fa, int node){
	for(int i = 0; i <= N << 2; i++)
		dp[node][i][0] = dp[node][i][1] = MOD;
	dp[node][0][0] = 0;
	dp[node][0][1] = 0;
	dp[node][value[node]][0] = 0;
	dp[node][value[node]][1] = 0;
	top[node] = value[node];
	for(auto i : edge[node]){
		if(i.first != fa){
			getdp(node, i.first);
			for(int j = top[node] + top[i.first]; j >= 0; j--){
				for(int k = 0; k <= top[i.first] && k <= j; k++){
					if(j - k > top[node])
						continue;
					dp[node][j][0] = min(dp[node][j][0], dp[node][j - k][0] + 2 * i.second + dp[i.first][k][0]); // 能回来
					dp[node][j][1] = min(dp[node][j][1], dp[node][j - k][0] + i.second + dp[i.first][k][1]);
					dp[node][j][1] = min(dp[node][j][1], dp[node][j - k][1] + 2 * i.second + dp[i.first][k][0]);
				}
			}
			top[node] += top[i.first];
		}
	}
}

int main(){
	cin >> N;
	for(int i = 1; i <= N; i++){
		cin >> value[i];
	}
	int a, b, w;
	for(int i = 1; i < N; i++){
		cin >> a >> b >> w;
		edge[a].push_back(make_pair(b, w));
		edge[b].push_back(make_pair(a, w));
	}
	getdp(0, 1);
	for(int i = 1; i <= top[1]; i++)
		dp[1][i][0] = min(dp[1][i][0], dp[1][i][1]);
	for(int i = 0; i <= 1000000; i++)
		ans[i] = 0;
	ans[0] = value[1];
	for(int i = 0; i <= top[1]; i++){
		if(dp[1][i][0] <= 1000000)
			ans[dp[1][i][0]] = max(ans[dp[1][i][0]], i);
	}
	for(int i = 1; i <= 1000000; i++)
		ans[i] = max(ans[i], ans[i-1]);
	cin >> Q;
	int query;
	for(int i = 0; i < Q; i++){
		cin >> query;
		cout << ans[query] << endl;
	}
	return 0;
}