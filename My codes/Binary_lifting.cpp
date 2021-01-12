#include <bits/stdc++.h>
using namespace std;
 
#define pb push_back
#define S second
#define F first
#define f(i,n) for(int i=0;i<n;i++)
#define fast ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define vi vector<int>
#define pii pair<int,int>
 
const int N = 2e5+10;
const int LOGN = 18;
 
int lg[N];
int sparse[N][LOGN];
 
void solve()
{
int n,q,x,l,r;
cin >> n >> q;
  
f(i,n) cin >> sparse[i][0];
        
for(int i=1;i<LOGN;i++)
    for(int j=0;j+(1<<i)<=n;j++)
      sparse[j][i] = min(sparse[j][i-1],sparse[j+(1<<(i-1))][i-1]);
   
 lg[1] = 0;
    
 for(int i=2;i<=n;i++) lg[i] = lg[i/2]+1;
    
while(q--)
{
    cin >> l >> r;
    
    int t = lg[r-l+1];
   
    cout << min(sparse[l-1][t],sparse[r-(1<<t)][t]) << "\n";
}
       
}
 
signed main()
{
    fast;
    solve();
}
