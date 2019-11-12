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

const int N = 1e4+5;
const int bt = 17;

typedef struct Trie 
{
   int cnt;
   Trie* next[2];
    
   Trie()
   {
     cnt = 0;
     next[0] = next[1] = NULL;
   }
} Trie;

Trie seg[2*N];
int a[N],pw[bt+2],n,m,typ,l,r,x;
bitset<bt> temp;

void insert(Trie* node,bitset<bt> & num,int id)
{
   if(id == -1) return; 
    
   if(node->next[num[id]] == NULL) node->next[num[id]] = new Trie;
    
   (node-> next[num[id]]->cnt)++;
    
   insert(node->next[num[id]],num,id-1); 
}

void remove(Trie* node,bitset<bt> & num,int id)
{
  if(id == -1) return;

  node->next[num[id]]->cnt--; 
    
  if(node->next[num[id]]->cnt == 0) node->next[num[id]] = NULL;
  else remove(node->next[num[id]],num,id-1);  
}
    
void merge(Trie* main,Trie* node)
{
   if(node == NULL) return;
    
   if(node->next[0] != NULL)
   {
     if(main->next[0] == NULL) main-> next[0] = new Trie;
     main->next[0]->cnt += node->next[0]->cnt;
     merge(main->next[0],node->next[0]);  
   }
    
   if(node->next[1] != NULL)
   {
     if(main->next[1] == NULL) main-> next[1] = new Trie;
     main->next[1]->cnt += node->next[1]->cnt;
     merge(main->next[1],node->next[1]);  
   } 
}

int getxor(Trie* node,bitset<bt> & num,int id)
{
  if(id == -1) return 0;
    
  if(node->next[num[id]^1] != NULL) return pw[id]+getxor(node->next[num[id]^1],num,id-1);
  if(node->next[num[id]] != NULL) return getxor(node->next[num[id]],num,id-1);
                                                
  return 0;                                             
}

int query(int l,int r,int x)
{
    r++;
    
    int res = 0;
    
    temp = x;
    
    for(l+=n,r+=n;l<r;l>>=1,r>>=1)
    {
      if(l&1) res=max(res,getxor(&seg[l++],temp,bt-1));
      if(r&1) res=max(res,getxor(&seg[--r],temp,bt-1));  
    }
    
    return res;
}

void upd(int id,int old,int val)
{
    a[id] = val;
    
    for(id+=n;id;id>>=1)
    {
     temp = old;
     remove(&seg[id],temp,bt-1);
     temp = val;
     insert(&seg[id],temp,bt-1);   
    }
}

void solve()
{   
  cin >> n >> m;  
    
  pw[0] = 1;
    
  f(i,bt+1) pw[i+1] = pw[i]*2;
    
  f(i,n) cin >> a[i];  
   
  f(i,n) 
  {
      temp = a[i];
      insert(&seg[i+n],temp,bt-1);
  }
    
  for(int i=n-1;i;i--) 
  {
      merge(&seg[i],&seg[i<<1]);
      merge(&seg[i],&seg[i<<1^1]);
  }
    
  while(m--)  
  {
      cin >> typ;
      
      if(typ == 1)
      {
       cin >> l >> r >> x;
       cout << query(l-1,r-1,x) << "\n";   
      }
      else
      {
       cin >> l >> x;
       upd(l-1,a[l-1],x);   
      }
  }
    
}

signed main()
{
    fast;
    solve();
}