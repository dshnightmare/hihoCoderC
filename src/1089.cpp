#include <iostream>
using namespace std;

const int NMax = 105;
int N, M;
int matrix[NMax][NMax];

int main(){
	int u, v, length;
	cin >> N >> M;
	for(int i = 1; i <= N; i++){
		for(int j = 1; j <= N; j++){
			if(i == j)
				matrix[i][j] = 0;
			else
				matrix[i][j] = 10000;
		}
	}
	for(int i = 0; i < M; i++){
		cin >> u >> v >> length;
		if(length < matrix[u][v])
		 	matrix[u][v] = matrix[v][u] = length;
	}
	for(int k = 1; k <= N; k++){
		for(int i = 1; i <= N; i++){
			for(int j = 1; j <= N; j++){
				if(matrix[i][k] + matrix[k][j] < matrix[i][j])
					matrix[i][j] = matrix[i][k] + matrix[k][j];
			}
		}
	}
	for(int i = 1; i <= N; i++){
		for(int j = 1; j <= N; j++){
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}