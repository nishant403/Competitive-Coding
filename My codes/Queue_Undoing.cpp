#include <bits/stdc++.h>
using namespace std;
  
 //ref : https://codeforces.com/blog/entry/83467
 //problem : https://www.codechef.com/JAN21A/problems/ARCRT

#define int long long 
#define pb push_back
#define S second
#define F first
#define f(i,n) for(int i=0;i<n;i++)
#define fast ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define vi vector<int>
#define pii pair<int,int>

const int MOD = 1e9+7;
const int N = 1e5 + 10;
int inv[N];

int res = 1;

struct dsu_save {
    int v, szv, cyv, u, szu , cyu;

    dsu_save() {}

    dsu_save(int _v, int _szv, int _cyv , int _u, int _szu, int _cyu)
        : v(_v), szv(_szv),cyv(_cyv), u(_u), szu(_szu) ,cyu(_cyu) {}
};

int get_ans(int cc,int ss)
{
    if(cc == 0) return ss;
    else return cc;
}

struct dsu_with_rollbacks 
{
    vector<int> p,sz,cyc;
    stack<dsu_save> op;

    dsu_with_rollbacks() {}

    dsu_with_rollbacks(int n) 
    {
        p.resize(n);
        sz.resize(n);
        cyc.resize(n);
        
        for (int i = 0; i < n; i++) {
            p[i] = i;
            sz[i] = 1;
            cyc[i] = 0;
        }
    }

    int find_set(int v) {
        return (v == p[v]) ? v : find_set(p[v]);
    }
    
    bool tryy(int u,int v)
    {
        int a = find_set(v);
        int b = find_set(u);
        
        if(cyc[a] > 0 && cyc[b] > 0) return 0;
        return 1;
    }

    bool unite(int v, int u) 
    {
        int a = find_set(v);
        int b = find_set(u);
        
        if(cyc[a] > 0 && cyc[b] > 0) return 0;
        
        op.push(dsu_save(a, sz[a], cyc[a], b, sz[b] , cyc[b]));
        
        if(a == b)
        {
            res = (res*inv[sz[a]])%MOD;
            
            if(u == v) cyc[a] = 1;
            else cyc[a] = 2;
            
            res = (res*get_ans(cyc[b],sz[b]))%MOD;
            
            return 1;
        }
        
        res = (res*inv[get_ans(cyc[a],sz[a])])%MOD;
        res = (res*inv[get_ans(cyc[b],sz[b])])%MOD;
        
        if(sz[a] > sz[b]) swap(a,b);
        p[a] = b;
        sz[b]+=sz[a];
        cyc[b] = max(cyc[a],cyc[b]);
        
        res = (res*get_ans(cyc[b],sz[b]))%MOD;
        
        return 1;
    }

    void rollback() 
    {
        if (op.empty()) return;
        
        dsu_save x = op.top();
        op.pop();
        
        int gg = find_set(x.v);
        res = (res*inv[get_ans(cyc[gg],sz[gg])])%MOD;
        
        p[x.v] = x.v;
        sz[x.v] = x.szv;
        cyc[x.v] = x.cyv;
        p[x.u] = x.u;
        sz[x.u] = x.szu;
        cyc[x.u] = x.cyu;
        
        res = (res*get_ans(x.cyv,x.szv))%MOD;
        if(x.u != x.v) res = (res*get_ans(x.cyu,x.szu))%MOD;
    }
};

struct Upd {
  int type, a, b;
};

void solve()
{
    int n;
    cin >> n;
    
    int a[n],b[n];
    f(i,n) cin >> a[i];
    f(i,n) cin >> b[i];
    
    int c[n+n];
    
    f(i,n) c[i] = a[i],c[i+n] = b[i];
    sort(c,c+n+n);
    f(i,n) a[i] = lower_bound(c,c+n+n,a[i]) - c;
    f(i,n) b[i] = lower_bound(c,c+n+n,b[i]) - c;
    
    res = 1;
    dsu_with_rollbacks go(n+n+5);
    int ptr = 0;

    vector<Upd> upds, tmp[2];
    int last_id = -1;
    
    f(i,n)
    {
        while(ptr < n && go.unite(a[ptr],b[ptr])) 
        {
            upds.push_back(Upd({1,a[ptr],b[ptr]}));
            ptr++;
        }
        
        cout << res << ' ';

        if (upds.back().type == 1) {
          while (upds.size() > 0) {
            auto upd = upds.back();
            upds.pop_back();
            go.rollback();
            tmp[upd.type].push_back(upd);
            if (tmp[0].size() == tmp[1].size())
              break;
          }
          if (tmp[0].empty()) {
            assert(upds.empty());
            for (auto& upd : tmp[1]) {
              upd.type = 0;
              go.unite(upd.a, upd.b);
            }
            swap(tmp[1], upds);
          } else {
            for (int z : {1, 0}) {
              for (; tmp[z].size(); tmp[z].pop_back()) {
                auto upd = tmp[z].back();
                go.unite(upd.a, upd.b);
                upds.push_back(upd);
              }
            }
          }
        }

        assert(upds.back().type == 0);
        upds.pop_back();
        go.rollback();

    }

    cout << '\n';
}

signed main()
{
    inv[0] = inv[1] = 1;
    
    for(int i=2;i<N;i++) 
        inv[i] = inv[MOD%i]*(MOD - MOD/i) % MOD;
    
    fast;
    
    int t = 1;
    
    cin >> t;
    
    while(t--)
        
    solve();
}
