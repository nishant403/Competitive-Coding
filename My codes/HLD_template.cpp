//https://codeforces.com/gym/100551/problem/C

#include <bits/stdc++.h>
using namespace std;
 
#define pb push_back
#define S second
#define F first
#define f(i,n) for(int i=0;i<n;i++)
#define fast ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define vi vector<int>
#define pii pair<int,int>

const int N = 1e5+10;
const int LN = 17;

//SEGTREE
int seg[4*N];
int lazy[4*N];

void push(int node,int ss,int se)
{
    if(lazy[node] == 0) return;
    
    if(lazy[node] == 2) seg[node] = se - ss + 1;
    else seg[node] = 0;
    
    if(ss != se)
        lazy[node*2+1] = lazy[node*2+2] = lazy[node];
    
    lazy[node] = 0;
}

void update(int node,int ss,int se,int l,int r,int val)
{
    push(node,ss,se);
    
    if(se < l || r < ss) return;
    
    if(l <= ss && se <= r)
    {
        lazy[node] = val + 1;
        push(node,ss,se);
        return;
    }
    
    int mid = (ss + se)/2;
    
    update(node*2+1,ss,mid,l,r,val);
    update(node*2+2,mid+1,se,l,r,val);
    seg[node] = seg[node*2+1] + seg[node*2+2];
}

vi g[N];
int par[N];
int dep[N];
int sz[N];
int heavy[N];
int head[N];
int pos[N];
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
    
    int mx = -1, bigChild = -1;
    
    for(auto u : g[v])
       if(u != par[u] && sz[u] > mx)
             mx = sz[u], bigChild = u;
    
    if(bigChild != -1) dfs2(bigChild,hed);
    
    for(auto u : g[v])
        if(u != par[u] && u != bigChild) dfs2(u,u);  
}
 
void paint(int a, int b) 
{
    for (; head[a] != head[b]; b = par[head[b]])
    {
        if(dep[head[a]] > dep[head[b]]) swap(a,b); 
        update(0,0,n-1,pos[head[b]],pos[b],1);
    }
    
    if (dep[a] > dep[b]) swap(a, b);
    update(0,0,n-1,pos[a]+1,pos[b],1);
}

void solve()
{
  int q,x,l,r;
  cin >> n >> q;
    
  for(int i=2;i<=n;i++)
  {
    cin >> x;
    g[x].pb(i);
  }
    
  dfs(1); 
  dfs2(1,1);
    
  while(q--)
  {
     int k;
     cin >> k;
      
     while(k--)
     {
        cin >> l >> r;
        paint(l,r);
     }
     
     cout << n - 1 - seg[0] << '\n'; 
  
     update(0,0,n-1,0,n-1,0); 
  }
    
}
 
signed main()
{
    freopen("bridges2.in","r",stdin);
    freopen("bridges2.out","w",stdout);
    solve();
}
