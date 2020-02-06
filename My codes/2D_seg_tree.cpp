#include <bits/stdc++.h>
using namespace std;
 
#define pb push_back
#define S second
#define F first
#define f(i,n) for(int i=0;i<n;i++)
#define fast ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define vi vector<int>
#define pii pair<int,int>
 
const int N = 1005;
int n,q;
int seg[4*N][4*N];
 
void uy(int nodex,int nodey,int ly,int ry,int y,int flag)
{
    if(ly == ry)
    {
        if(flag) seg[nodex][nodey]^=1;
        else seg[nodex][nodey] = seg[nodex*2+1][nodey] + seg[nodex*2+2][nodey];
        
        return;
    }
    
    int mid = (ly + ry)/2;
    
    if(y <= mid) uy(nodex,nodey*2+1,ly,mid,y,flag);
    else uy(nodex,nodey*2+2,mid+1,ry,y,flag);
    
    seg[nodex][nodey] = seg[nodex][nodey*2+1] +  seg[nodex][nodey*2+2];
}
 
void ux(int nodex,int lx,int rx,int x,int y)
{
   if(lx != rx)
   {
       int mid =(lx+rx)/2;
       
       if(x <= mid) ux(nodex*2+1,lx,mid,x,y);
       else ux(nodex*2+2,mid+1,rx,x,y);
   }
    
   uy(nodex,0,0,n-1,y,(lx==rx));  
}
 
int qy(int nodey,int nodex,int ly,int ry,int y1,int y2)
{
    if(ly > y2 || ry < y1) return 0;
    
    if(y1 <= ly && ry <= y2) return seg[nodex][nodey];
    
    int mid = (ly + ry)/2;
    
    return qy(nodey*2+1,nodex,ly,mid,y1,y2) + qy(nodey*2+2,nodex,mid+1,ry,y1,y2);
}
 
int qx(int nodex,int lx,int rx,int x1,int y1,int x2,int y2)
{   
    if(lx > x2 || rx < x1) return 0;
 
    if(x1 <= lx && rx <= x2) return qy(0,nodex,0,n-1,y1,y2);
    
    int mid = (lx + rx)/2;
    
    return qx(nodex*2+1,lx,mid,x1,y1,x2,y2) + qx(nodex*2+2,mid+1,rx,x1,y1,x2,y2);   
}
 
void solve()
{
  cin >> n >> q;
    
  string s;
    
  f(i,n)
  {
      cin >> s;
      f(j,n) if(s[j] == '*') ux(0,0,n-1,i,j);
  }
   
  int t,x1,y1,x2,y2; 
    
  while(q--)
  {
      cin >> t;
      
      if(t==1)
      {
          cin >> x1 >> y1;
          ux(0,0,n-1,x1-1,y1-1);
      }
      else
      {
          cin >> x1 >> y1 >> x2 >> y2;
          cout << qx(0,0,n-1,x1-1,y1-1,x2-1,y2-1) << '\n';
      }
  }
    
}
 
signed main()
{
    fast;
    solve();
}
