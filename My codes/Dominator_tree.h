//g++  5.4.0
 
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
const int LN = 20; 
#define ll long long 
#define pb push_back
#define ff first
#define ss second
#define pii pair<ll,ll>
#define INF LONG_LONG_MAX
#define minQueue priority_queue < pii , vector<pii> , greater<pii> >

vector< pii > g[N];
vector<bool > vis(N,0);
vector<ll> dist(N , INF);
vector<ll> ord(N);
ll par[LN][N];
vector<ll> dep(N,0);
vector<ll> sz(N,1);
ll total = 0;

ll lca(ll u , ll v )
{
    if(dep[u] > dep[v] ) swap(u,v);
    ll diff = dep[v] - dep[u];
    
    for(int i = LN-1 ; i >= 0 ; i-- )
    {
        if( diff & (1<<i) )
            v = par[i][v]  ;
    }
    
    if(u == v) return u;
    
    for(int i = LN-1 ; i >= 0 ; i-- )
    {
        if( par[i][v] != par[i][u] )
            v = par[i][v] , u = par[i][u];
    }
    return par[0][v];
    
}
void dijistra(ll s)
{
    dist[s] = 0;
    minQueue Q;
    Q.push({0,s});
    
    while(!Q.empty())
    {
        pii p = Q.top();
        ll v  = p.ss;
        ll d  = p.ff;
        Q.pop();
        if(vis[v]) continue;
        
        ord[total++] = v;
        
        vis[v] = 1;
        for(auto it : g[v] )
        {
            if(!vis[it.ff])
            {
                if(dist[it.ff] > dist[v] + it.ss)
                {
                    dist[it.ff] = dist[v] + it.ss;
                    Q.push({dist[it.ff] , it.ff});
                }
       
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll  n , m , s;
    cin >> n >> m >> s;
    for(int i = 0 ; i <  m ; i++ )
    {
        ll u ,  v, w;
        cin >> u >> v >> w;
        g[u].pb({v,w});
        g[v].pb({u,w});
    }
    
    dijistra(s);
    
    //create a dominatory tree
    for(int i = 0 ; i < LN ; i++)
        for(int j = 1 ; j <= n ; j++ )
            par[i][j] = -1;

        
    for(int i = 0 ; i < total ; i++ )
    {
        ll v = ord[i];
        ll dn = -1;
        
        for(auto it : g[v])
        {
            if(dist[it.ff] + it.ss == dist[v] )
            {
                if(dn == -1) dn = it.ff;           // only one shortest path from s to v via dn till now
                else dn = lca(dn,it.ff); // if multiple shortest path exist then dominatory node for v is lca of dn and it.ff 
            }
            
        }
        
        if(dn == -1)    continue;
        dep[v] = dep[dn] + 1;
        par[0][v] = dn ;
        
    for(int i = 1 ; i < LN ; i++ )
        {    
                if( par[i-1][v] != -1 )
                    par[i][v] = par[i-1][ par[i-1][v] ] ;
        }    
    }
    
    ll ans = 0;
    
    for(int i = total-1; i >= 0 ; i--)
    {
        ll v = ord[i];
       
        if(v==s) continue;
        
         sz[par[0][v]] += sz[v];
        
        ans = max(ans,sz[v]);
    }
    
    cout << ans;
}