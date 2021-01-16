//CSES : https://cses.fi/problemset/task/2143/

#include <bits/stdc++.h>
using namespace std;
  
#define pb push_back
#define S second
#define F first
#define f(i,n) for(int i=1;i<=n;i++)
#define fast ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define pii pair<int,int>
#define all(x) x.begin(),x.end()

const int N = 5e4 + 10;
vector<int> g[N],gr[N],topo;

//Condensation graph 
int label[N];
vector<int> gnew[N];

bitset<N> go[N];
bitset<N> vis = 0;

void dfs(int node)
{
    vis[node] = 1;
    
    for(auto x : g[node])
        if(!vis[x]) dfs(x);
      
    topo.push_back(node);    
}

vector<int> cmp;

void dfs2(int node)
{
    vis[node] = 1;
    cmp.push_back(node);
    
    for(auto x : gr[node])
        if(!vis[x]) dfs2(x);
}

void dfs3(int node)
{
    if(vis[node]) return;
    vis[node] = 1;
    
    for(auto x : gnew[node])
    {
        dfs3(x);
        go[node] |= go[x];
    }
}

signed main()
{
    fast;
    
    int n,m,q;
    cin >> n >> m >> q;
    
    int u,v;
    
    f(i,m)
    {
        cin >> u >> v;
        g[u].push_back(v);
        gr[v].push_back(u);               
    }
    
    f(i,n) if(!vis[i]) dfs(i);
        
    vis = 0;
    
    reverse(topo.begin(),topo.end());
    
    for(auto v : topo)
    {
        if(!vis[v])
        {
            dfs2(v);
            for(auto x : cmp) label[x] = v, go[v][x] = 1;
            cmp.clear();
        }
    }
    
    f(i,n) for(auto x : g[i])
        if(label[i] != label[x]) gnew[label[i]].push_back(label[x]);

    vis = 0;
    f(i,n) if(!vis[i]) dfs3(i);
        
    while(q--)
    {
        cin >> u >> v;
        
        if(go[label[u]][label[v]]) cout <<"YES\n";
        else cout <<"NO\n";
    }
}
