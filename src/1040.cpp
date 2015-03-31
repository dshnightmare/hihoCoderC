#include <iostream>
#include <set>
using namespace std;

struct Point{
	int x, y;
	bool operator<(const Point &p) const {
		if(x < p.x || (x == p.x && y < p.y))
			return true;
		return false;
	}
	
	bool operator==(const Point &p) const {
		return (x == p.x && y == p.y);
	}
};

struct Line{
	Point p1, p2;
};

bool JudgePoint(Line l[]){
	set<Point> s;
	for(int i = 0; i < 4; i++){
		s.insert(l[i].p1);
		s.insert(l[i].p2);
	}
	return (s.size() == 4);
}

bool JudgeRect(Line l[]){
	for(int i = 1; i < 4; i++){
		if((l[0].p1.y - l[0].p2.y) * (l[i].p1.y - l[i].p2.y) == -(l[0].p1.x - l[0].p2.x) * (l[i].p1.x - l[i].p2.x))
			continue;
		if((l[0].p1.y - l[0].p2.y) * (l[i].p1.x - l[i].p2.x) == (l[0].p1.x - l[0].p2.x) * (l[i].p1.y - l[i].p2.y))
			continue;
		return false;
	}
	return true;
}

int main(){
	int n;
	Line l[4];
	cin >> n;
	while(n--){
		for(int i = 0; i < 4; i++){
			cin >> l[i].p1.x >> l[i].p1.y >> l[i].p2.x >> l[i].p2.y; 
		}
		if(!JudgePoint(l)) {
			cout << "NO" << endl;
			continue;
		}
		if(!JudgeRect(l)) {
			cout << "NO" << endl;
			continue;
		}
		cout << "YES" << endl;
	}
}