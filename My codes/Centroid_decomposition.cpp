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

const int N = 2e5 + 10;
vector<int> g[N];
bool vis[N];
int n,k1,k2;
int res = 0;

int sz[N]; //size of the centroid subtree
int dep[N]; //depth of the subtree rooted at node
int nn; //number of nodes in the centroid subtree


//---------------Centroid Decomposition-------------------------
//reference : https://www.codechef.com/viewsolution/7402256

//To find sizes of nodes
void dfs1(int node,int par)
{
   sz[node] = 1;
   nn++;
    
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

//Add/Remove the data of the distances  
void dfs3(int node,int par,int dist,int ad)
{
    nn++;
    dep[dist]+=ad; 
    
    for(auto x : g[node])
        if(!vis[x] && x != par) dfs3(x,node,dist+1,ad);
}

//Add/Remove the answers to the nodes
void dfs4(int node,int par,int dist)
{
    if(k2 - dist >= 0) res += dep[min(nn,k2 - dist)];
    if(k1 - dist >= 0) res -= dep[min(nn,k1 - dist)];
    
    for(auto x : g[node])
        if(!vis[x] && x != par) dfs4(x,node,dist+1);
}

//Main centroid decomposition function
void decompose(int root)
{
	nn = 0;
    dfs1(root,root);
    
    int centroid = dfs2(root,root);
   
    //add for all and calculate for all
    nn = 0;
    dfs3(centroid,-1,0,1);
    for(int i=1;i<=nn;i++) dep[i]+=dep[i-1];
    dfs4(centroid,-1,0);
    for(int i=0;i<=nn;i++) dep[i] = 0;
    
    //now remove the repeated things for subtrees
    for(auto x : g[centroid])
    {
        if(vis[x]) continue;
        
        nn = 1;
        dfs3(x,centroid,1,-1);
        for(int i=1;i<=nn;i++) dep[i]+=dep[i-1];
        dfs4(x,centroid,1);
        for(int i=0;i<=nn;i++) dep[i] = 0;
    }
    
    vis[centroid] = 1;
    
    //remove centroid from the tree and recurse
    for(auto x : g[centroid])
        if(!vis[x]) decompose(x);
}

signed main()
{
    fast;
    
    cin >> n >> k1 >> k2;
    k1--;
    
    int u,v;
    
    f(i,n-1)
    {
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    
    decompose(1);
    
    cout << (res/2);
}
