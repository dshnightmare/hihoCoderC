#include <iostream>
#include <algorithm>
using namespace std;

int main(){
	int n, m, LL, l, r, t, b, maxA = 0;
	cin >> n >> m >> LL >> l >> r >> t >> b;
	LL /= 2;
	for(int L = LL; L >= 2; L--){
		// if((L / 2) * ((L + 1) / 2) < maxA)
// 			break;
		for(int i = 1; i < L; i++){
			// 长为i宽为j
			int j = L - i;
			if(i > n || j > m || i * j)
				continue;
			// 枚举这个矩形的位置
			for(int p = 0; p <= n - i; p++){
				for(int q = 0; q <= m - j; q++){
					// 减去水塘面积
					int ll = max(l, q);
					int rr = min(r, q + j);
					int tt = max(t, p);
					int bb = min(b, p + i);
					int area = 0;
					if(ll >= rr || tt >= bb)
						area = i * j;
					else{
						int inside = 0;
						if (ll > q && ll < q + j && tt > p && tt < p + i)
							inside++;
						if (rr > q && rr < q + j && tt > p && tt < p + i)
							inside++;
						if(ll > q && ll < q + j && bb > p && bb < p + i)
							inside++;
						if (rr > q && rr < q + j && bb > p && bb < p + i)
							inside++;
						if (inside == 1 || inside == 4)
							area = i * j - (rr - ll) * (bb - tt);
					}
					if(area > maxA)
						maxA = area;
				}
			}
		}
	}
	cout << maxA << endl;
}