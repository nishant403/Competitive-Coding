#include <bits/stdc++.h>
using namespace std;
  
#define pb push_back
#define S second
#define F first
#define f(i,n) for(int i=0;i<n;i++)
#define fast ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define vi vector<int>
#define pii pair<int,int>
 
const int N = 1e5 + 10;
vector<int> res;
vi g[N];
int vis[N];
int tin[N];
int mx[N];
int tim = 0;
 
void dfs(int node,int par = -1)
{
    vis[node] = 1;
    
    tin[node] = mx[node] = tim++;
    
    int child = 0;
    int flag = 0;
    
    for(auto x : g[node])
    {
        if(x == par) continue;
        
        if(!vis[x])
        {
            dfs(x,node);  
            if(mx[x] >= tin[node] && par != -1) flag = 1; 
            child++; 
        }
        
        mx[node] = min(mx[node],mx[x]);  
    } 
    
    if(par == -1 && child > 1) flag = 1;
    
    if(flag) res.pb(node);
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
    for(auto x : res) cout << x << ' '; 
}
