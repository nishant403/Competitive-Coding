#include <bits/stdc++.h>
using namespace std;
 
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds; 
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
int getRand(int l, int r)
{
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
  
#define int long long 
#define pb push_back
#define S second
#define F first
#define f(i,n) for(int i=0;i<n;i++)
#define fast ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define vi vector<int>
#define pii pair<int,int>
 
struct Hopcroft_Karp
{
	static const int inf = 1e9;
 
	int n;
	vector<int> matchL, matchR, dist;
	vector<vector<int> > g;
 
	Hopcroft_Karp(int n) :
		n(n), matchL(n+1), matchR(n+1), dist(n+1), g(n+1) {}
 
	void add_edge(int u, int v)
	{
		g[u].push_back(v);
	}
 
	bool bfs()
	{
		queue<int> q;
		for(int u=1;u<=n;u++)
		{
			if(!matchL[u])
			{
				dist[u]=0;
				q.push(u);
			}
			else
				dist[u]=inf;
		}
		dist[0]=inf;
 
		while(!q.empty())
		{
			int u=q.front();
			q.pop();
			for(auto v:g[u])
			{
				if(dist[matchR[v]] == inf)
				{
					dist[matchR[v]] = dist[u] + 1;
					q.push(matchR[v]);
				}
			}
		}
 
		return (dist[0]!=inf);
	}
 
	bool dfs(int u)
	{
		if(!u)
			return true;
		for(auto v:g[u])
		{
			if(dist[matchR[v]] == dist[u]+1 &&dfs(matchR[v]))
			{
				matchL[u]=v;
				matchR[v]=u;
				return true;
			}
		}
		dist[u]=inf;
		return false;
	}
 
	int max_matching()
	{
		int matching=0;
		while(bfs())
		{
			for(int u=1;u<=n;u++)
			{
				if(!matchL[u])
					if(dfs(u))
						matching++;
			}
		}
		return matching;
	}
};
 
void solve()
{  
    int n,m,k;
   cin >> n >> m >> k;
    
   int u,v;
    
   Hopcroft_Karp go(n+m); 
    
   while(k--)
   {
       cin >> u >> v;
       go.add_edge(u,v+n);
   }
    
   cout << go.max_matching() << '\n'; 
    
   for(int i=1;i<=n;i++)
       if(go.matchL[i] > n) cout << i<<" "<<go.matchL[i]-n<<'\n';
    
}
 
signed main()
{
    fast;
    solve();
}
