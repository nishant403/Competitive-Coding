//SPOJ Problem : COT
//Using persistent segment tree

#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define f(i,n) for(int i=1;i<=n;i++)
#define F first
#define S second
#define pb push_back
#define fast ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)

const int N = 1e5+10;
const int LN = 18;

vector<int> tree[N],depth(N),rev(N);
vector<pair<int,int> > val(N);
int par[N][LN],n,m,a,b,k;

struct node
{
	int count;
	node *left, *right;

	node(int count, node *left, node *right):
		count(count), left(left), right(right) {}
};

node* null = new node(0,NULL,NULL);
node* nodes[N];

node* insert(node* old,int l,int r,int val)
{
    if(l > val || r < val) return old;
     
    if(l==r) return new node(1,null,null);
   
    int mid = (l+r)/2;
    
    return new node(old->count+1,insert(old->left,l,mid,val),insert(old->right,mid+1,r,val));
}

int query(node* a,node* b,node* c,node* d,int l,int r,int k)
{
 if(l==r) return l;
 
 int mid = (l+r)/2;
 int cn = a->left->count + b->left->count - c->left->count - d->left->count;
    
 if(cn < k) return query(a->right,b->right,c->right,d->right,mid+1,r,k-cn);
 else return query(a->left,b->left,c->left,d->left,l,mid,k);  
}

void dfs(int v)
{   
  if(par[v][0]==-1)
  {
   depth[v] = 0;
   nodes[v] = insert(null,1,n,rev[v]);  
  }
  else
  {
   depth[v] = depth[par[v][0]] + 1;
   nodes[v] = insert(nodes[par[v][0]],1,n,rev[v]);   
  }
    
  for(auto x : tree[v])
     if(x!=par[v][0]) 
     {
         par[x][0] = v;
         dfs(x);
     }
}

int lca(int u,int v)
{
  if(depth[u] > depth[v]) swap(u,v);
   
  int diff = depth[v] - depth[u];
    
  for(int i=0;i<LN;i++) if(diff & (1LL<<i)) v=par[v][i];
      
  if(u==v) return u;
      
  for(int i=LN-1;i>=0;i--)
      if(par[u][i] != par[v][i])
         u=par[u][i],v=par[v][i];
   
  u = par[u][0];    
  
  return u;  
}

signed main()
{
 fast;
   
 cin >> n >> m;

 f(i,n) val[i].S = i;  
 f(i,n) cin >> val[i].F;   
       
 sort(val.begin()+1,val.begin()+n+1);
     
 f(i,n) rev[val[i].S] = i;   
      
 f(i,n-1)
 {
  cin >> a >> b;
  tree[a].pb(b);
  tree[b].pb(a);
 }
  
 null->left = null->right = null;  
    
 f(i,n) f(j,LN-1) par[i][j] = -1;  
 par[1][0] = -1;   
 dfs(1);   
    
 for(int i=0;i<LN-1;i++) f(j,n)
     if(par[j][i] != -1)   
       par[j][i+1] = par[par[j][i]][i]; 
  
 while(m--)
 {
   cin >> a >> b >> k;   
   int lc = lca(a,b);
   int id = query(nodes[a],nodes[b],nodes[lc],par[lc][0] == -1 ? null : nodes[par[lc][0]],1,n,k);   
   cout << val[id].F << "\n";
 }  
}