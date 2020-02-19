#include <bits/stdc++.h>
using namespace std;
  
#define pb push_back
#define S second
#define F first
#define f(i,n) for(int i=0;i<n;i++)
#define fast ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define vi vector<int>
#define pii pair<int,int>

struct FlowEdge {
    int v, u;
    long long cap, flow = 0;
    FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
    const long long flow_inf = 1e18;
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    int n, m = 0;
    int s, t;
    vector<int> level, ptr;
    queue<int> q;

    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int v, int u, long long cap) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }

    bool bfs() {
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap - edges[id].flow < 1)
                    continue;
                if (level[edges[id].u] != -1)
                    continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }

    long long dfs(int v, long long pushed) {
        if (pushed == 0)
            return 0;
        if (v == t)
            return pushed;
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
                continue;
            long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    long long flow() {
        long long f = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs())
                break;
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, flow_inf)) {
                f += pushed;
            }
        }
        return f;
    }
};

void solve()
{
    int n,m;
    cin >> n >> m;
    
    pii a[m];
    f(i,m) cin >> a[i].F >> a[i].S;
    
    int source = 0;
    int sink = (4*m+n+1);
    
    Dinic go(4*m+n+20,source,sink);
    
    for(int i=1;i<=n;i++) go.add_edge(source,i,1);
    
    vi nrep(n+1,0);
    vi erep(m,-1);
   
    f(i,n) nrep[i+1] = i+1;
    
    int cnt = n+1; 
    int ecnt = (2*n);
    
    f(i,m)
    {
        go.add_edge(nrep[a[i].F],cnt,1);
        go.add_edge(nrep[a[i].S],cnt,1);
        
        ecnt+=4;
        go.add_edge(cnt,cnt+1,1);
        
        go.add_edge(cnt+1,cnt+2,1);
        nrep[a[i].F] = cnt+2;
        go.add_edge(cnt+1,cnt+3,1);
        nrep[a[i].S] = cnt+3;
        erep[i] = ecnt+2;
        cnt+=4;
        ecnt+=6;
    }
    
    for(int i=1;i<=n;i++) go.add_edge(nrep[i],sink,1);
   
    int fl = go.flow();
    
    if(fl>= (n+1)/2)
    {
        f(i,m) if(go.edges[erep[i]].flow == 1) cout <<'^';
               else cout << 'v';
            
        cout << '\n';
    }
    else cout <<"failure\n";
}

signed main()
{
    fast;
    
    int t = 1;
    
    cin >> t;
    
    while(t--)
        
    solve();
}
