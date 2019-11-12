//AUTHOR : TIRTH JARSANIA
//COLLEGE : DAIICT
//TOPIC : DSU ON TREES(SACK)

#include<bits/stdc++.h>
using namespace std;

#define INF LONG_LONG_MAX
#define MINF LONG_LONG_MIN
#define bp __builtin_popcountll
#define ll long long int
#define ld long double
#define pb push_back
#define ff first
#define ss second
#define pii pair<ll,ll>
#define precision(x,d) cout<<fixed<<setprecision(d)<<x
#define minQueue priority_queue<pii,vector<pii>,greater<pii> > 
#define maxQueue priority_queue<pii> 
#define FAST ios_base::sync_with_stdio(false),cin.tie(0),cout.tie(0);srand(time(NULL))

const ll N = 1e5+5;
vector<ll> g[N] , col(N) , tin(N) , tout(N) , sz(N) , ans(N),  cnt(N,0) , rev(N);
map<ll,ll> mpp;
ll timer = 0;

void dfs(ll v,ll p)
{
    sz[v] = 1;
    rev[timer] = v;
    tin[v] = timer++;
    for(auto &it:g[v])
    {
        if(it!=p)
        {
            dfs(it,v);
            sz[v] += sz[it];
        }
    }
    tout[v] = timer;
    return ;
}

void dfs_hld(ll v,ll p,bool keep)
{
    ll maxi = -1;
    ll special_child = -1;
    for(auto &it : g[v])
    {
        if(it!=p)
        {
            if(maxi < sz[it])
            {
                maxi = sz[it];
                special_child = it;
            }
        }
    }
    
    for(auto &it : g[v])
        if(it!=p && it!= special_child)
            dfs_hld(it,v,0);
    if(maxi != -1)
        dfs_hld(special_child,v,1);
    
    for(auto &it : g[v])
    {
        if(it!=p && it!= special_child)
        {
            for(ll i=tin[it];i<tout[it];i++)
            {
                //whatever doing new in this part
            }
        }
    }
    //whatever doing new in this part
    ans[v] = (--mpp.end())->ss;
    if(keep == 0)
    {
        for(ll i=tin[v];i<tout[v];i++)
        {
              //whatever doing new in this part
        }
    }
    return ;
}
int main()
{
    FAST;
    ll n;
    cin >> n;
    for(ll i = 1 ; i <= n ;  i++ ) cin >> col[i];
    for(ll i = 0 ; i  <  n -1 ; i++ )
    {
        ll u , v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    dfs(1,0);
    dfs_hld(1,0,1);
    for(ll i=1;i<=n;i++)
        cout << ans[i] << " "; 
}