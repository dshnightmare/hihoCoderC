#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

const int NMax = 15;

int T, N, M;
int board[NMax][NMax];
int result[NMax][NMax];
vector<pair<int, int> > neighbor[NMax][NMax];
vector<pair<int, int> > undecided;
bitset<NMax> guess1, guess2;

// 对于已经探明的点，纪录周围为探明点的位置，对于未探明的点，纪录周围探明点的位置
void inline getNeightbor(int i, int j){
	int top = i - 1 >= 1 ? i - 1 : i;
	int bot = i + 1 <= N ? i + 1 : i;
	int left = j - 1 >= 1 ? j - 1 : j;
	int right = j + 1 <= M ? j + 1 : j;
	if(board[i][j] == -1){
		for(int m = top; m <= bot; m++){
			for(int n = left; n <= right; n++){
				if(board[m][n] != -1)
					neighbor[i][j].push_back(make_pair(m, n));
			}
		}
	}
	else{
		for(int m = top; m <= bot; m++){
			for(int n = left; n <= right; n++){
				if(board[m][n] == -1)
					neighbor[i][j].push_back(make_pair(m, n));
			}
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

void dfs(int pos, bitset<NMax> cur_guess){
	if(pos == undecided.size())
	{
		//cout << "a possible guess" << endl;
		guess1 |= cur_guess;
		guess2 &= cur_guess;
		return;
	}
	int i = undecided[pos].first, j = undecided[pos].second;
	// 放雷
	cur_guess.set(pos);
	result[i][j] = 1;
	// 遍历雷周围的已探明点
	bool flag = false;
	for(auto k = neighbor[i][j].begin(); k != neighbor[i][j].end(); k++){
		int count = 0;
		for(auto l = neighbor[k->first][k->second].begin(); l != neighbor[k->first][k->second].end(); l++){
			if(result[l->first][l->second] == 1)
				count++;
		}
		if(count > board[k->first][k->second]){
			flag = true;
			break;
		}
	}
	if(!flag)
		dfs(pos + 1, cur_guess);
	// 不放雷
	cur_guess.reset(pos);
	result[i][j] = 2;
	// 遍历周围已探明点
	flag = false;
	for(auto k = neighbor[i][j].begin(); k != neighbor[i][j].end(); k++){
		int count = 0;
		for(auto l = neighbor[k->first][k->second].begin(); l != neighbor[k->first][k->second].end(); l++){
			if(result[l->first][l->second] == 2)
				count++;
		}
		if(count > neighbor[k->first][k->second].size() - board[k->first][k->second]){
			flag = true;
			break;
		}
	}
	if(!flag)
		dfs(pos + 1, cur_guess);
	result[i][j] = 0;
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
		
		undecided.clear();
		for(int i = 1; i <= N; i++){
			for(int j = 1; j <= M; j++)
				if(board[i][j] == -1 && result[i][j] == 0)
					undecided.push_back(make_pair(i, j));
		}
		//cout << undecided.size() << endl;
		
		// sort(undecided.begin(), undecided.end(), [](const pair<int, int> &ele1, const pair<int, int> &ele2{
// 			board
// 		}))
		guess1.reset();
		guess2.set();
		bitset<NMax> cur;
		cur.reset();
		dfs(0, cur);
		
		int count1 = 0, count2 = 0;
		for(int i = 1; i <= N; i++){
			for(int j = 1; j <= M; j++){
				if(result[i][j] == 1)
					count2++;
				else if(result[i][j] == 2)
					count1++;
			}
		}
		for(int i = 0; i < undecided.size(); i++)
			if(!guess1.test(i))
				count1++;
		for(int i = 0; i < undecided.size(); i++)
			if(guess2.test(i))
				count2++;
		cout << count2 << " " << count1 << endl;
	}
	return 0;
}