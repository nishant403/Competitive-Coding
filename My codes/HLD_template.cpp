#include <bits/stdc++.h>
using namespace std;
 
#define int long long 
#define pb push_back
#define S second
#define F first
#define f(i,n) for(int i=0;i<n;i++)
#define fast ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define vi vector<int>
#define pii pair<int,int>

const int N = 2e5+10;
const int LN = 18;

//SEGTREE
int seg[4*N];

void update(int node,int ss,int se,int id,int val)
{
    if(se < id || id < ss) return;
    
    if(id <= ss && se <= id)
    {
        seg[node] = val;
        return;
    }
    
    int mid = (ss + se)/2;
    
    update(node*2+1,ss,mid,id,val);
    update(node*2+2,mid+1,se,id,val);
    seg[node] = max(seg[node*2+1] , seg[node*2+2]);
}

int query(int node,int ss,int se,int l,int r)
{
    if(se < l || r < ss) return 0;
    
    if(l <= ss && se <= r) return seg[node];
    
    int mid = (ss + se)/2;
    
    return max(query(node*2+1,ss,mid,l,r) , query(node*2+2,mid+1,se,l,r));
}

vi g[N];
int par[N];
int dep[N];
int sz[N];
int heavy[N];
int head[N];
int pos[N];
int a[N];
int cur_pos = 0;
int n;

void dfs(int node,int p = -1) 
{
    if(p == -1) dep[node] = 0;
    else dep[node] = dep[p] + 1;
    
    par[node] = p;
    
    sz[node] = 1;
    
    for (int x : g[node]) 
        if (x != p) 
        {
            dfs(x,node);
            sz[node]+=sz[x];
        }
}

void dfs2(int v, int hed)
{
    pos[v] = cur_pos++;
    head[v] = hed;
    update(0,0,n-1,pos[v],a[v]);
    int mx = -1, bigChild = -1;
    
    for(auto u : g[v])
    {
       if(u != par[v] && sz[u] > mx)
             mx = sz[u], bigChild = u;
    }
    
    if(bigChild != -1) dfs2(bigChild,hed);
    
    for(auto u : g[v])
        if(u != par[v] && u != bigChild) dfs2(u,u);  
}
 
int paint(int a, int b) 
{
    int res = 0;
    
    for (; head[a] != head[b]; b = par[head[b]])
    {
        if(dep[head[a]] > dep[head[b]]) swap(a,b); 
        res = max(res , query(0,0,n-1,pos[head[b]],pos[b]));
    }
    
    if (dep[a] > dep[b]) swap(a, b);
    res = max(res,query(0,0,n-1,pos[a],pos[b]));
    
    return res;
}

void solve()
{
  int q,x,l,r;
  cin >> n >> q;
    
  for(int i=1;i<=n;i++) cin >> a[i];
    
  int u,v;
    
  for(int i=2;i<=n;i++)
  {
    cin >> u >> v;
    g[u].pb(v);
    g[v].pb(u);
  }
    
  dfs(1); 
  dfs2(1,1);
    
  while(q--)
  {
      int t,l,r;
      cin >> t >> l >> r;
     
      if(t == 1) update(0,0,n-1,pos[l],r);
      else cout << paint(l,r) << ' ';
  }
    
}
 
signed main()
{
    fast;
    solve();
}
