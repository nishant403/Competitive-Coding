#include <bits/stdc++.h>
using namespace std;
 
//NOTE : This algorithm is exponential in n for max flow 
//For polynomial time algorithm, refer : https://loj.ac/s/649516
 
#define int long long 
#define pb push_back
#define S second
#define F first
#define f(i,n) for(int i=0;i<n;i++)
#define fast ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define vi vector<int>
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
 
//Mincost maxflow returns a pair {max_flow,min_cost}
//supports multiple edges 
//problem : https://cses.fi/problemset/task/2121/
 
const int inf = 1e18;
 
template<typename T>
using minpq = priority_queue<T, vector<T>, greater<T>>;
 
struct edge {
    int v, cap, flow, cost;
};
 
struct mcmf {
    vector<edge> e;
    vector<vi> g;
    vi dist, pot, par, f;
    vector<bool> vis;
    int n;
    mcmf(int n) : n(n) {
        g.resize(n);
        dist.assign(n, 0);
        pot.assign(n, 0);
        vis.resize(n);
        par.resize(n);
        f.resize(n);
    }
    void add_edge(int u, int v, int cap, int cost) {
        int k = (int)e.size();
        e.push_back({v, cap, 0, cost});
        e.push_back({u, cap, cap, -cost});
        g[u].push_back(k);
        g[v].push_back(k ^ 1);
    }
    pii solve(int s, int t, int amt) {
        int flow = 0, cost = 0;
        while(flow < amt) {
            minpq<pii> Q;
            fill(all(dist), INT_MAX);
            fill(all(vis), false);
            Q.push({0, s});
            dist[s] = 0;
            f[s] = amt - flow;
            while(!Q.empty()) {
                int d, x;
                tie(d, x) = Q.top(); Q.pop();
                if(vis[x]) continue;
                vis[x] = true;
                for(int i : g[x]) {
                    int d2 = d + e[i].cost + pot[x] - pot[e[i].v];
                    if(!vis[e[i].v] && e[i].flow < e[i].cap && d2 < dist[e[i].v]) {
                        dist[e[i].v] = d2;
                        par[e[i].v] = i;
                        f[e[i].v] = min(f[x], e[i].cap - e[i].flow);
                        Q.push({d2, e[i].v});
                    }
                }
            }
            if(!vis[t]) break;
            
            for(int i=1;i<=n;i++) 
                dist[i] += pot[i] - pot[s];
           
            cost += dist[t] * f[t];
            flow += f[t];
            int x = t;
            while(x != s) {
                e[par[x]].flow += f[t];
                e[par[x] ^ 1].flow -= f[t];
                x = e[par[x] ^ 1].v;
            }
            dist.swap(pot);
        }
        return {flow, cost};
    }
};
signed main()
{
    fast;
    
    int n,m,k;
    cin >> n >> m >> k;
    
    mcmf go(n+2);
    
    int a,b,r,c;
    
    f(i,m)
    {
        cin >> a >> b >> r >> c;
        go.add_edge(a,b,r,c);
    }
    
    pii res = go.solve(1,n,k);
    
    if(res.F < k) cout << -1;
    else cout << res.S;
}
