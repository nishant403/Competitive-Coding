#include <bits/stdc++.h>
using namespace std;
  
#define f(i,n) for(int i=0;i<n;i++)
#define fast ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define pb push_back

const int N = 2e5+10;
int n,m;
vector<int> g[N], gt[N];
vector<bool> used;
vector<int> order, comp;
vector<bool> assignment;

void dfs1(int v) {
    used[v] = true;
    for (int u : g[v]) {
        if (!used[u])
            dfs1(u);
    }
    order.push_back(v);
}

void dfs2(int v, int cl) {
    comp[v] = cl;
    for (int u : gt[v]) {
        if (comp[u] == -1)
            dfs2(u, cl);
    }
}

bool solve_2SAT() {
    used.assign(n, false);
    for (int i = 0; i < n; ++i) {
        if (!used[i])
            dfs1(i);
    }

    comp.assign(n, -1);
    for (int i = 0, j = 0; i < n; ++i) {
        int v = order[n - i - 1];
        if (comp[v] == -1)
            dfs2(v, j++);
    }

    assignment.assign(n / 2, false);
    for (int i = 0; i < n; i += 2) {
        if (comp[i] == comp[i + 1])
            return false;
        assignment[i / 2] = comp[i] > comp[i + 1];
    }
    return true;
}

signed main()
{
    fast;
    
    cin >> m >> n;
    
    char c1,c2;
    int u,v;
    
    while(m--)
    {
         cin >> c1 >> u >> c2 >> v;      
         u--;
         v--;
         u<<=1;
         v<<=1;
        
        if(c1 == '-') u++;
        if(c2 == '-') v++;
        
        g[u^1].pb(v);
        g[v^1].pb(u);
        
        gt[u].pb(v^1);
        gt[v].pb(u^1);
    }
    
    n<<=1;
    
    if(solve_2SAT())
    {
        for(int i=0;i<(n/2);i++)
            if(assignment[i]) cout << "+ ";
            else cout << "- ";
    }
    else cout << "IMPOSSIBLE";
}
