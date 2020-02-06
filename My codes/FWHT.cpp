//Problem : https://www.hackerearth.com/problem/algorithm/submatrix-queries-c33aca97/

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
const int M =1e9+7;
const int N = 256;
const int NN = 1e5+1;

//Fast Walsh Hadamard Transform

//XOR [  1 1 ]   //AND [ 0 1 ]  //OR  [ 1 1 ]
      [ -1 1 ]         [ 1 1 ]        [ 1 0 ]

vector<int> FWHT(vector<int> P,bool inv)
{
    for(int len=1;2*len <=N;len<<=1)
        for(int i=0;i<N;i+=(len<<1))
        f(j,len)
    {
        int a = P[i+j];
        int b = P[i+j+len];
    
       if(inv)
       {
        P[i+j] = ((-a+b)%M + M)%M;
        P[i+j+len] = a; 
       }
       else
       {
        P[i+j] = b;
        P[i+j+len] = (a+b)%M; 
       }
    }
    
    return P;
}

int a[NN][N];

void solve()
{
  int n,m;
  cin >> n;
    
  int l,r,x;
    
  f(i,n)
  {
      cin >> x;
      a[i][x] = 1;
      if(i) f(j,N) a[i][j]+=a[i-1][j];
  }
    
  cin >> m;  
    
  while(m--)
  {
      cin >> l >> r >> x;
      vi poly(N,0);
      f(i,N) poly[i] = a[r-1][i];
      if(l>1) f(i,N) poly[i] -= a[l-2][i];
      
      auto v = FWHT(poly,0);
      f(i,N) v[i] = (((v[i]*v[i])%M)*v[i])%M;
      v = FWHT(v,1);
      
      cout << v[x] << '\n';
  }
    
    
}

signed main()
{
    fast;
    solve();
}
