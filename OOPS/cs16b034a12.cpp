#include<bits/stdc++.h>
using namespace std;
#define MP make_pair
#define x first
#define y second
#define PB push_back
#define total(A) A.begin(), A.end()
#define lowbit(k) (k & -k)
#define bcnt(x) __builtin_popcountll(x) 

typedef long long ll;

const int N = 110;
const ll INF = (ll)1e18;
const double PI = acos(-1.0);
const double eps = 1e-6;
const int M = 1e9 + 7;

typedef pair<int, int> PII;

int dcmp(double x)
{
	if(fabs(x) < eps)  return 0;
	return x > 0 ? 1 : -1;
}


struct Point {
	double x, y;
	Point(double x = 0, double y = 0): x(x), y(y) { }
	
	void read() { scanf("%lf %lf", &x, &y); }
};

typedef Point Vector;

Vector operator + (Vector A, Vector B) { return Vector(A.x + B.x, A.y + B.y); }
Vector operator - (Vector A, Vector B) { return Vector(A.x - B.x, A.y - B.y); }
Vector operator * (Vector A, double p) { return Vector(A.x * p, A.y * p); }
Vector operator / (Vector A, double p) { return Vector(A.x / p, A.y / p); }
bool operator == (const Point &a, const Point &b) { return !dcmp(a.x - b.x) && !dcmp(a.y - b.y); }
bool operator > (Vector A, Vector B) {
	int t = dcmp(A.x - B.x);
	return t ? t > 0 : dcmp(A.y - B.y) > 0 ;
}

double Dot (Vector A, Vector B) { return A.x * B.x + A.y * B.y; }
double Length(Vector A) { return sqrt(Dot(A, A)); }
double Angle(Vector A, Vector B) { return acos(Dot(A, B / Length(A) / Length(B))); }
double Cross(Vector A, Vector B) { return A.x * B.y - A.y * B.x; }
double Area2(Point A, Point B, Point C)  { return Cross(B - A, C - A); }
double angle(Vector A) { return atan2(A.y, A.x); }

bool OS(Point p, Point a1, Point a2)
{
	return dcmp(Cross(a1 - p, a2 - p)) == 0 && dcmp(Dot(a1 - p, a2 - p)) < 0;
}

bool SPI(Point a1, Point a2, Point b1, Point b2)
{
	double c1 = Cross(a2 - a1, b1 - a1), c2 = Cross(a2 - a1, b2 - a1);
	double c3 = Cross(b2 - b1, a1 - b1), c4 = Cross(b2 - b1, a2 - b1);
	return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}

Point a[N], b[N], c[N];
bool ok[N][N];
double dis[N][N];

void prt(int n)
{
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++)
			printf("%d ", ok[i][j]);
		puts("");
	}
	puts("");
}

void find_prt(int n)
{
	for(int i = 0; i < n; i++){
		printf("%d : ", i);
		for(int j = 0; j < n; j++)
			if(ok[i][j]) printf("%d ", j);
		puts("");
	}
	puts("");
}

int main ()
{
//	Point A = Point(0, 1), B = Point(0, 1);
//	printf("%d %lf\n", A==B, Angle(A, B));
	
	int n, m;
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		a[i].read(); c[i] = a[i];
	}
	scanf("%d", &m);
	for(int i = 0; i < m; i++){
		b[i].read(); c[i + n] = b[i];
	}
	
//	for(int i = 0; i < n + m; i++)
//		printf("%.2lf %.2lf  ", c[i].x, c[i].y);
//	puts("");
	
	for(int i = 0; i < n + m; i++)
	for(int j = 0; j < n + m; j++){
		bool f = i != j;
		for(int k = 0; k < n + m && f; k++)
			f &= !OS(c[k], c[i], c[j]);
		ok[i][j] = f;
	}
	
//	find_prt(n + m);
	
	for(int i = 0; i < n + m; i++)
	for(int j = 0; j < i; j++)if(ok[i][j]){
		bool f = 1;
		for(int k = 0; k < n && f; k++)
			f &= !SPI(a[k], a[(k + 1) % n], c[i], c[j]);
		for(int k = 0; k < m && f; k++)
			f &= !SPI(b[k], b[(k + 1) % m], c[i], c[j]);
		ok[i][j] = ok[j][i] = f;
	}
	
//	find_prt(n + m);
//	
//	return 0;
	
	for(int i = 0; i < n; i++){
		double l = angle(a[(i + 1) % n] - a[i]);
		double r = angle(a[(i - 1 + n) % n] - a[i]);
		if(dcmp(l - r) > 0) r += 2 * PI;
		for(int j = 0; j < n + m; j++)if(i != j && ok[i][j]){
			double mt = angle(c[j] - a[i]);
			if(dcmp(mt - l) <= 0) mt += 2 * PI;
			if(dcmp(mt - r) < 0) ok[i][j] = ok[j][i] = 0;
		}
	}
	
	for(int i = 0; i < m; i++){
		double l = angle(b[(i + 1) % m] - b[i]);
		double r = angle(b[(i - 1 + m) % m] - b[i]);
		if(dcmp(l - r) > 0) r += 2 * PI;
		for(int j = 0; j < n + m; j++)if(i != j && ok[i + n][j]){
			double mt = angle(c[j] - b[i]);
			if(dcmp(mt - l) < 0) mt += 2 * PI;
			if(dcmp(mt - r) > 0) ok[i + n][j] = ok[j][i + n] = 0;
		}
	}
	
//	find_prt(n + m);
	
	int r = 0, s;
	for(int i = 0; i < n; i++)
		if(a[i] > a[r]) r = i;
	s = (r + 1) % n;
	
	for(int i = 0; i < n + m; i++) if(i != r)
	for(int j = 0; j < i; j++) if(j != r && ok[i][j]){
//		if(j == 7 && i == 8){
//			puts("IN");
//			printf("?? %lf %.15lf %d\n", Angle(c[i] - c[r], c[r] - c[s]), Angle(c[j] - c[r], c[r] - c[s]), dcmp(Angle(c[j] - c[r], c[r] - c[s])));
//		}
		if(dcmp(Angle(c[i] - c[r], c[r] - c[s])) == 0 || dcmp(Angle(c[j] - c[r], c[r] - c[s])) == 0){
			ok[i][j] = ok[j][i] = 0;
		}
			
		if(dcmp(Angle(c[i] - c[r], c[r] - c[s]) + Angle(c[j] - c[r], c[r] - c[s]) - Angle(c[i] - c[r], c[j] - c[r])) == 0)
			ok[i][j] = ok[j][i] = 0;
	}
		
			
//	find_prt(n + m);
	
	for(int i = 0; i < n + m; i++) if(ok[r][i]){
		ok[r][i] = ok[i][r] = 0;
		int t = dcmp(Cross(c[r] - c[s], c[i] - c[r]));
		if(t < 0){
			ok[r][i] = 1;
		}else if(t > 0 || (t == 0 && i == s)){
			ok[i][n + m] = 1;
		}
	}
//	find_prt(n + m);
//	prt(n + m + 1);
	
	for(int i = 0; i < n + m; i++){
		for(int j = 0; j < n + m; j++)
			if(ok[i][j]) dis[i][j] = Length(c[i] - c[j]);
			else dis[i][j] = INF;
		if(ok[i][n + m]) dis[i][n + m] = Length(c[i] - c[r]);
		else dis[i][n + m] = INF;
	}
	
	int mn = n + m;
	for(int k = 0; k <= mn; k++)
	for(int i = 0; i <= mn; i++) if(i != k) 
	for(int j = 0; j <= mn; j++) if(i != j && j != k)
		dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
	
	printf("%.4lf\n", dis[r][mn]);
	
//	for(int i = 0; i <= n + m; i++){
//		for(int j = 0; j <= n + m; j++)
//			printf("%.2lf ", dcmp(dis[i][j] - INF) == 0 ? 0 : dis[i][j]);
//		puts("");
//	}
//	puts("");
	
	return 0;
}
