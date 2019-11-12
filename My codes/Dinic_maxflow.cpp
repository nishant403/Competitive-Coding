#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define pb push_back
const int N = 1e18;

struct fe
{
    int u , v , cap , f = 0;
    fe(int u,int v,int c) : u(u) , v(v) , cap(c){}
};

struct Dinic
{
     int n , m = 0;
     vector < fe > e ;
     vector < vector<int> > g;
     vector< int > ptr , lev;
     queue < int > q;
     int s , t;
     Dinic(int s,int t, int n): s(s) , t(t) , n(n)
     {
        g.resize(n+1);
        ptr.resize(n+1);
        lev.resize(n+1);
     }
     
     void add_edge(int u, int v,int cap)
     {
         e.pb({u,v,cap});
         e.pb({v,u,0LL});
         g[u].pb(m);m++;
         g[v].pb(m);m++;
     }
     
     bool bfs()
     {
        
         while(!q.empty())
         {
             int p = q.front();
             q.pop();
             for(auto id : g[p])
             {
                 if( e[id].cap != e[id].f && lev[e[id].v] == -1)
                 {
                    lev[e[id].v] = lev[p] + 1;
                    q.push(e[id].v);
                 }
             }
         }
         return lev[t] != -1;
     }
     
     int dfs(int u,int cur)
     {
         if(u == t) return cur;
         for(int &cid = ptr[u] ; cid < (int)g[u].size() ; cid++ )
         {
             int id = g[u][cid] ; 
             int v  = e[id].v ;
             if( lev[u] == lev[v] -1 && e[id].f != e[id].cap)
             {
                 int x = dfs(v,min(e[id].cap-e[id].f,cur));
                 if(x!=0)
                 {
                     e[id].f += x;
                     e[id^1].f -= x; 
                     return x;
                 }
             }
         }
         return 0;
     }
     
     int maxflow()
     {
         int ff = 0;
         while(1)
         {
             fill(lev.begin() , lev.end() , -1);
             lev[s] = 0;
             q.push(s);
             if(!bfs()) return ff;
             fill(ptr.begin(), ptr.end(), 0);
             while(auto x = dfs(s,N))
                ff+= x;
         }
         
     }
};