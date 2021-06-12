#include <bits/stdc++.h>
using namespace std;
  
#define int long long 
#define pb push_back
#define S second
#define F first
#define f(i,n) for(int i=1;i<=n;i++)
#define fast ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define vi vector<int>
#define pii pair<int,int>
#define all(x) x.begin(),x.end()

//problem : https://www.codechef.com/problems/TATAKAI

const int N = 1e5 + 10;
const int LN = 17;
const int MOD = 1e9 + 7;
const int B = 31;

int mod_pow(int a,int b,int M = MOD)
{
    if(a == 0) return 0;
    b %= (M - 1);  //M must be prime here
    
    int res = 1;
    
    while(b > 0)
    {
        if(b&1) res=(res*a)%M;
        a=(a*a)%M;
        b>>=1;
    }
    
    return res;
}

int pw[N];
int inv_pw[N];

int p[N][LN];
int hash_up[N]; //node to root
int hash_down[N]; //root to node

vector<int> g[N];
char val[N];

vector<pair<int,int> > queries[N];
int candidates[N];
int res[N];

int nn;
bool vis[N];
int sz[N]; 
int dep[N];
int dep2[N];
set<pair<int,int> > sorted_indices[N]; 
int rnk[N];

//Prepare for path hashing
void dfs6(int node,int par)
{
    p[node][0] = par;
    
    if(par != -1)
    {
        dep[node] = dep[par] + 1;
        
        hash_up[node] = (hash_up[par]*B) + (val[node] - 'a' + 1);
        hash_up[node] %= MOD;
        
        hash_down[node] = hash_down[par] + ((val[node] - 'a' + 1)*pw[dep[node]]);
        hash_down[node] %= MOD;
    }
    else 
    {
        dep[node] = 0;
        hash_up[node] = hash_down[node] = (val[node] - 'a' + 1);
    }
    
    for(auto x : g[node])
        if(x != par) dfs6(x,node);
}

void lca_build(int n)
{
  for(int i=1;i<LN;i++)
      for(int j=1;j<=n;j++)
        if(p[j][i-1] != -1)  
           p[j][i] = p[p[j][i-1]][i-1];  
}

int lca(int a,int b)
{
 if(dep[a] > dep[b]) swap(a,b);  
 
 int z = dep[b] - dep[a];
   
 for(int i=LN-1;i>=0;i--) if(1LL<<i & z) b = p[b][i];   
     
 if(a==b) return a;    
     
 for(int i=LN-1;i>=0;i--) if(p[a][i] != p[b][i]) a=p[a][i],b=p[b][i];  
 
 return p[a][0];  
}

//kth ancestor of u
int kdis(int u,int k)
{
    for(int i=LN-1;i>=0;i--)
        if((k >> i) & 1) u = p[u][i];
        
    return u;
}

//kth node in the path from u to v
int get_kth(int u,int v,int k)
{
    if(u == v) return u;
    
    int lc = lca(u,v);
    
    if(lc == u) return get_kth(v,u,dep[v] - dep[u] - k);
    
    int d1 = dep[u] - dep[lc];
    
    if(k > d1) return get_kth(lc,v,k-d1);
    else return kdis(u,k);
}

//Hash of path from u to v
int get_hash(int u,int v)
{
    int lc = lca(u,v);
    
    if(lc == u)
    {
        int answer = hash_down[v];
        
        if(p[lc][0] != -1)
        {
            answer -= hash_down[p[lc][0]];
            answer %= MOD;
            if(answer < 0) answer += MOD;
        }
        
        answer = (answer*inv_pw[dep[lc]])%MOD;
        
        return answer;
    }
    
    int answer = hash_up[u];
    
    if(p[lc][0] != -1)
    {
        answer -= hash_up[p[lc][0]]*pw[dep[u] - dep[lc] + 1];
        answer %= MOD;
        if(answer < 0) answer += MOD;
    }
    
    if(lc != v)
    {
        int nex_node = kdis(v,dep[v] - dep[lc] - 1);
        answer += get_hash(nex_node,v)*pw[dep[u] - dep[lc] + 1];
        answer %= MOD;
    }
    
    return answer;
}

//compare path of u to v1 and u to v2, return the smallest of them
int get_best(int u,int v1,int v2)
{
    int lc1 = lca(u,v1);
    int lc2 = lca(u,v2);
    
    int dis = dep[u] + dep[v1] - 2*dep[lc1];
    
    //find maximum prefix length that matches
    int l = 0;
    int r = dis;
    int res = l;
    
    while(l <= r)
    {
        int mid = (l + r)/2;
        
        if(get_hash(u,get_kth(u,v1,mid)) == get_hash(u,get_kth(u,v2,mid)))
        {
            res = mid;
            l = mid + 1;
        }
        else r = mid - 1;
    }
    
    if(res == dis) return v1;
    else
    {
        int n1 = get_kth(u,v1,res + 1);
        int n2 = get_kth(u,v2,res + 1);
        
        if(val[n1] < val[n2]) return v1;
        return v2;
    }
}


//Find sizes of nodes
void dfs1(int node,int par)
{
   nn++;
   sz[node] = 1;
    
   for(auto x : g[node])
       if(!vis[x] && x != par) dfs1(x,node),sz[node]+=sz[x];
}

//Find centroid from the sizes
int dfs2(int node,int par)
{
    for(auto x : g[node])
        if(!vis[x] && x != par && sz[x] > (nn/2)) return dfs2(x,node);
        
	return node;
}
    
//Find depths when centroid is root
void dfs3(int node,int par)
{
    if(par == -1) dep2[node] = 0;
    else dep2[node] = dep2[par] + 1;
    
    for(auto x : g[node])
        if(!vis[x] && x != par) dfs3(x,node);
}

//Add/remove the nodes from DS
void dfs4(int node,int par,bool rem)
{
    if(rem) sorted_indices[dep2[node]].erase({rnk[node],node});
    else sorted_indices[dep2[node]].insert({rnk[node],node});
    
    for(auto x : g[node])
        if(!vis[x] && x != par) dfs4(x,node,rem);
}

void get_answer(int node)
{
    for(auto x : queries[node])
    {
        int req_depth = x.F - dep2[node] - 1;
        
        if(req_depth >= 0 && !sorted_indices[req_depth].empty())
        {
            int new_val = (*sorted_indices[req_depth].begin()).S;
            
            if(candidates[x.S] == -1) candidates[x.S] = new_val;
            else candidates[x.S] = get_best(node,candidates[x.S],new_val);
        }
    }
}

//Answer the queries of node
void dfs5(int node,int par)
{
    get_answer(node); 
      
    for(auto x : g[node])
        if(!vis[x] && x != par) dfs5(x,node);
}

//Main centroid decomposition function
void decompose(int root)
{   
    nn = 0;
    dfs1(root,root);
    
    int centroid = dfs2(root,root);
    
    dfs3(centroid,-1);
 
    //Build the set of sorted indices 
    sorted_indices[0].insert({0,centroid});
    rnk[centroid] = 0;
    
    for(int depth=0;sorted_indices[depth].size() > 0;depth++)
    {
        vector<pair<pair<int,char>,int> > go;
        
        for(auto x : sorted_indices[depth])
          for(auto y : g[x.S]) 
            if(dep2[y] == dep2[x.S] + 1)
              go.push_back({{x.F,val[y]},y});
        
        sort(all(go));
            
        if(go.empty()) break;    
            
        rnk[go[0].S] = 0;
            
        for(int i=1;i<go.size();i++)
        {
            if(go[i].F == go[i-1].F) rnk[go[i].S] = rnk[go[i-1].S];
            else rnk[go[i].S] = i;
        }
        
        for(int i=0;i<go.size();i++)
        {
            sorted_indices[depth + 1].insert({rnk[go[i].S],go[i].S});
        }
    }
    
    get_answer(centroid);
    
    //For each subtree, remove its nodes,answer the queries, insert its nodes
    for(auto x : g[centroid])
        if(vis[x] == 0)
        {
            dfs4(x,centroid,1);
            dfs5(x,centroid);
            dfs4(x,centroid,0);
        }
    
    //clear the sets
    dfs4(centroid,-1,1);
    
    //remove centroid from the tree and recurse
    vis[centroid] = 1;
    
    for(auto x : g[centroid])
        if(!vis[x]) decompose(x);
}

void solve()
{
    int n,q;
    cin >> n >> q;
    
    for(int i=1;i<=n;i++) cin >> val[i];
      
    int u,v;
    
    for(int i=1;i<=n-1;i++)
    {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    for(int i=1;i<=q;i++)
    {   
        cin >> u >> v;
        queries[u].push_back({v,i});
        candidates[i] = -1;
    }
    
    for(int i=1;i<=n;i++) 
        for(int j=0;j<LN;j++) p[i][j] = -1;
        
    dfs6(1,-1);
    
    lca_build(n);
    
    decompose(1);
    
    for(int i=1;i<=n;i++)
        for(auto x : queries[i])
         if(candidates[x.S] == -1) res[x.S] = -1;
         else res[x.S] = get_hash(i,candidates[x.S]);
    
    for(int i=1;i<=q;i++)
        cout << res[i] << '\n';
    
    for(int i=1;i<=n;i++) g[i].clear();
    for(int i=1;i<=n;i++) queries[i].clear();
    for(int i=1;i<=n;i++) vis[i] = 0;
}

signed main()
{
    fast;
    
    pw[0] = 1;
    for(int i=1;i<N;i++) pw[i] = (pw[i-1]*B)%MOD;
    
    inv_pw[N-1] = mod_pow(pw[N-1],MOD-2);
    for(int i=N-2;i>=0;i--) inv_pw[i] = (inv_pw[i+1]*B)%MOD;
    
    int t;
    cin >> t;
    while(t--) 
    solve();
}
