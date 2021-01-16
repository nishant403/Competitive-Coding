const int N = 1e5 + 10;
vector<int> g[N],gr[N],topo;
 
//Condensation graph 
int label[N];
vector<int> gnew[N];
 
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
 
signed main()
{
    fast;
    
    int n,m;
    cin >> n >> m;
    
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
}	
