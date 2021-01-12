const int N = 1e5+10;
const int inf = 1e15;
vector<pii> g[N];
vector<bool> vis(N,0);
vector<int> dis(N,inf);
 
void solve()
{
  int n,m;
  cin >> n >> m;
    
  int a,b,c;
  
  f(i,m)
  {
      cin >> a >> b >> c;
      g[a].pb({c,b});
  }
 
  dis[1] = 0;
  priority_queue<pii,vector<pii>,greater<pii> > PQ;
    
  PQ.push({0,1}); 
  
  while(!PQ.empty())
  {
      auto x = PQ.top();  PQ.pop();
      if(vis[x.S] == 1) continue;
      vis[x.S] = 1;
      
      for(auto z : g[x.S])
      {
          if(dis[z.S] > dis[x.S] + z.F)
          {
              dis[z.S] = dis[x.S] + z.F;
              PQ.push({dis[z.S],z.S});
          }
      }
}
 
  f(i,n) cout << dis[i+1] <<" ";
}
