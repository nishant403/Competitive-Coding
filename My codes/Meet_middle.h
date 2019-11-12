#include<bits/stdc++.h>
using namespace std;
 
#define int long long 
#define f(i,n) for(int i=0;i<n;i++)
#define fast ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
 
int s1[1<<20],s2[1<<20];  
 
void solve()
{
 int n,x;
 cin >> n >> x;
   
    
 int a[n];  
    
 f(i,n) cin >> a[i];   
    
    
  if(n==1)
  {
    cout << (x==0) + (x==a[0]);
      return;
  }
    
 int g1 = (n/2);
 int g2 = n - g1;
 int ans = 0;
 int s = -1;   
       
    
 for(int i=1;i<(1<<g1);i++)
 {
    if((i&(i-1)) == 0) s++;
    s1[i] = s1[i^(1<<s)] + a[s]; 
 }
 
 s=-1;   
    
 for(int i=1;i<(1<<g2);i++)
 {
    if( (i&(i-1)) == 0) s++;
    s2[i] = s2[i^(1<<s)] + a[s+g1];
 } 
  
     
 sort(s1,s1+(1<<g1));
 sort(s2,s2+(1<<g2));
     
 int prev = 0,temp=0;
 int l = 0;
 int r = (1<<g2)-1;
 
 while(l<(1<<g2) && r>=0)   
 {
   temp=0;  
         
   if(r != (1<<g2) )
   {
       
   if(s2[r] == s2[r+1])
   {
    ans+=prev;
    r--;
    continue;   
   }
   else prev=0;    
       
   }
     
   if(s1[l] + s2[r] > x)
   {
    r--;
    continue;
   }
   else if(s1[l] + s2[r] < x)
   {
    l++;
    continue;
   }
     
   while(s1[l] + s2[r] == x)
   {
       l++;
       temp++;
   }
     
   ans+=temp;
   prev=temp;
     
   r--;       
 }
    
 cout << ans;
}
 
signed main()
{
    fast;
    
    int t = 1;
    
//    cin >> t;
    
    while(t--)
        
    solve();
}