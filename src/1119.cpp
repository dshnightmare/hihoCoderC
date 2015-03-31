#include <iostream>
#include <vector>
using namespace std;

const int NMax = 205;

int T, N, M;
int board[NMax][NMax];
int result[NMax][NMax];
vector<pair<int, int> > neighbor[NMax][NMax];

void inline getNeightbor(int i, int j){
	int top = i - 1 >= 1 ? i - 1 : i;
	int bot = i + 1 <= N ? i + 1 : i;
	int left = j - 1 >= 1 ? j - 1 : j;
	int right = j + 1 <= M ? j + 1 : j;
	for(int m = top; m <= bot; m++){
		for(int n = left; n <= right; n++){
			if(board[m][n] == -1)
				neighbor[i][j].push_back(make_pair(m, n));
		}
	}
}

void inline check(int i, int j){
	int top = i - 2 >= 1 ? i - 2 : i - 1 >= 1 ? i - 1 : i;
	int bot = i + 2 <= N ? i + 2 : i + 1 <= N ? i + 1 : i;
	int left = j - 2 >= 1 ? j - 2 : j - 1 >= 1 ? j - 1 : j;
	int right = j + 2 <= M ? j + 2 : j + 1 <= M ? j + 1 : j;
	vector<pair<int, int> > notsame;
	for(int m = top; m <= bot; m++){
		for(int n = left; n <= right; n++){
			if(board[m][n] != -1 && (board[i][j] - board[m][n] == neighbor[i][j].size() - neighbor[m][n].size())){
				//neighbor[i][j]和neighor[m][n]是否互相包含
				if(board[i][j] > board[m][n]){
					notsame.clear();
					for(auto u = neighbor[i][j].begin(); u != neighbor[i][j].end(); u++){
						bool flag = false;
						for(auto v = neighbor[m][n].begin(); v != neighbor[m][n].end(); v++){
							if(u->first == v->first && u->second == v->second){
								flag = true;
								break;
							}
						}
						if(!flag)
							notsame.push_back(*u);
					}
					if(notsame.size() == board[i][j] - board[m][n]){
						for(auto u = notsame.begin(); u != notsame.end(); u++)
							result[u->first][u->second] = 1;
					}
				}
				else if(board[i][j] < board[m][n]){
					notsame.clear();
					for(auto u = neighbor[m][n].begin(); u != neighbor[m][n].end(); u++){
						bool flag = false;
						for(auto v = neighbor[i][j].begin(); v != neighbor[i][j].end(); v++){
							if(u->first == v->first && u->second == v->second){
								flag = true;
								break;
							}
						}
						if(!flag)
							notsame.push_back(*u);
					}
					if(notsame.size() == board[m][n] - board[i][j]){
						//cout << i << " " << j  << " " << m  << " " << n << endl;
						for(auto u = notsame.begin(); u != notsame.end(); u++)
							result[u->first][u->second] = 1;
					}
				}
			}
		}
	}
}

int main(){
	cin >> T;
	while(T--){
		cin >> N >> M;
		for(int i = 1; i <= N; i++){
			for(int j = 1; j <= M; j++){
				cin >> board[i][j];
				result[i][j] = 0;
				neighbor[i][j].clear();
			}
		}
	
		for(int i = 1; i <= N; i++){
			for(int j = 1; j <= M; j++){
				if(board[i][j] != -1)
					getNeightbor(i, j);
			}
		}
	
		// 1 表示一定为地雷，2表示一定不为地雷
		for(int i = 1; i <= N; i++){
			for(int j = 1; j <= M; j++){
				if(board[i][j] == -1)
					continue;
				// rule1
				if(board[i][j] == 0){
					for(auto k = neighbor[i][j].begin(); k != neighbor[i][j].end(); k++){
						result[k->first][k->second] = 2;
					}
				}
				// rule2
				else if(board[i][j] == neighbor[i][j].size()){
					for(auto k = neighbor[i][j].begin(); k != neighbor[i][j].end(); k++){
						result[k->first][k->second] = 1;
					}
				}
			
				// rule3
				check(i, j);
			}
		}
		
		int count1 = 0, count2 = 0;
		for(int i = 1; i <= N; i++){
			for(int j = 1; j <= M; j++){
				if(result[i][j] == 1)
					count1++;
				else if(result[i][j] == 2)
					count2++;
			}
		}
		cout << count1 << " " << count2 << endl;
	}
	return 0;
}