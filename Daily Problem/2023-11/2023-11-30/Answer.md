凸包周长+原周长即可。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX = 1e6 + 100;
typedef long long ll;
typedef unsigned long long ull;
const ll mod = 998244353;
const ll inf = 0x3f3f3f3f3f3fll;
const double pi = 3.1415926535;
void solve();
 
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	// clock_t c1 = clock();
#ifdef LOCAL
	freopen("in.in", "r", stdin);
	freopen("out.out", "w", stdout);
#endif
	//ll T;
	//for(cin >> T;T--;)
	solve();
 
	// cerr << "Time Used: " << clock() - c1 << " ms\n";
	return 0;
}
class p {
public:
    double x, y;//二维向量，表示一个点
    p(double _x = 0, double _y = 0):x(_x),y(_y){}
    
    //向量基本运算的实现+ - · *
    p operator+(const p& a)const { return { x + a.x,y + a.y }; }
    p operator-(const p& a)const { return { x - a.x,y - a.y }; }
    p operator-() const { return { -x,-y }; }

    double operator*(const p& a)const { return x * a.y - y * a.x; }//叉乘
    double disPoint(const p& a) const;//点到点的距离

	bool operator<(const p& a)
	{
		if(a.x == x)
			return y < a.y;
		return x < a.x; 
	}

};

double p::disPoint(const p& a) const {//点到点的距离
    return sqrt((x - a.x) * (x - a.x) + (y - a.y) * (y - a.y));
}


void solve()
{
	double r;
	int n,tot = 0;
	cin >> n >> r;
	vector<p> a(1);
	for(int i = 0;i < n;++i)
	{
		int m;
		cin >> m;
		tot += m;
		while(m--)
		{
			p now;
			cin >> now.x >> now.y;
			a.push_back(now);
		}
	}
	sort(a.begin() + 1,a.end());
	vector<int> st(tot + 1);
	vector<int> used(tot + 1);
	int tp = 0;
	st[++tp] = 1;
	for(int i = 2;i <= tot;++i)
	{
		while(tp > 1 && 
			(a[st[tp]] - a[st[tp - 1]]) * (a[i] - a[st[tp]]) <= 0)
			used[st[tp--]] = 0;
		used[i] = 1;
		st[++tp] = i;
	} 
	int tmp = tp;
	for(int i = tot - 1;i > 0;--i)
	{
		if(!used[i])
		{
			while(tp > tmp 
				&& (a[st[tp]] - a[st[tp - 1]]) * (a[i] - a[st[tp]]) <= 0)
				used[st[tp--]] = 0;
			used[i] = 1;
			st[++tp] = i;
		}
	}
	double ans = 0;
	for(int i = 1;i < tp;++i)
		ans += a[st[i]].disPoint(a[st[i + 1]]);
	cout << fixed << setprecision(5) << ans + 2 * pi * r << '\n';
}
```