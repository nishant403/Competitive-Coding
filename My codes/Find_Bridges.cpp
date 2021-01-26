#include <bits/stdc++.h>
using namespace std;

//problem : https://cses.fi/problemset/task/2076/
  
#define pb push_back
#define S second
#define F first
#define f(i,n) for(int i=0;i<n;i++)
#define fast ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define vi vector<int>
#define pii pair<int,int>
 
const int N = 1e5 + 10;
vector<pii> res;
vi g[N];
int vis[N];
int tin[N];
int mx[N];
int tim = 0;
 
void dfs(int node,int par = -1)
{
    vis[node] = 1;
    
    tin[node] = mx[node] = tim++;
    
    for(auto x : g[node])
    {
        if(x == par) continue;
        
        if(!vis[x])
        {
            dfs(x,node);
            if(mx[x] > tin[node]) res.pb({x,node});
        }
        
        mx[node] = min(mx[node],mx[x]);
    } 
}
 
signed main()
{
    fast;
    
    int n,m;
    cin >> n >> m;
    
    int u,v;
    
    f(i,m)
    {
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    
    for(int i=1;i<=n;i++)
        if(!vis[i]) dfs(i);
        
    cout << res.size() << '\n';
    for(auto x : res) cout << x.F << ' ' << x.S << '\n'; 
}
