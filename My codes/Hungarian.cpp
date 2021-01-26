#include <bits/stdc++.h>
using namespace std;

//Solve assignment problem of n x m matrix in O(n*m*m)
//problem : https://cses.fi/problemset/task/2129/

#define int long long 
#define pb push_back
#define S second
#define F first
#define f(i,n) for(int i=0;i<n;i++)
#define fast ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define vi vector<int>
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
 
const int inf = 1e18;

pair<int,vi> hungarian(const vector<vi> &a) 
{
	if (a.empty()) return {0, {}};
	int n = ((int)a.size()) + 1, m = ((int)a[0].size()) + 1;
    
	vi u(n), v(m), p(m), ans(n - 1);
    
    for(int i=1;i<n;i++) 
    {
		p[0] = i;
		int j0 = 0; 
		vi dist(m, inf), pre(m, -1);
		vector<bool> done(m + 1);
        
		do {
			done[j0] = true;
			int i0 = p[j0], j1, delta = inf;
            
            for(int j=1;j<m;j++)
                if (!done[j]) 
            {
				auto cur = a[i0 - 1][j - 1] - u[i0] - v[j];
				if (cur < dist[j]) dist[j] = cur, pre[j] = j0;
				if (dist[j] < delta) delta = dist[j], j1 = j;
			}
            
            f(j,m) 
            {
				if (done[j]) u[p[j]] += delta, v[j] -= delta;
				else dist[j] -= delta;
			}
            
			j0 = j1;
            
		} while (p[j0]);
        
		while (j0) {
			int j1 = pre[j0];
			p[j0] = p[j1], j0 = j1;
		}
	}
    
    for(int i=1;i<m;i++)
        if (p[i]) ans[p[i] - 1] = i - 1;
        
	return {-v[0], ans};
}
 
signed main()
{
    fast;
  
    int n; 
    cin >> n;
    
	vector<vi> a(n, vi(n));
    f(i,n) f(j,n) cin >> a[i][j];
 
    auto res = hungarian(a);
	cout << res.F << '\n';
    f(i,n) cout << i+1 << ' ' << res.S[i]+1 << endl;	
}
