//g++  5.4.0

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FAST ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
const  ll N = 51;
const ll M = 1e9+7;
ll dp[N][36][36][2][2][2];
vector<ll> jt1,jt2;
ll p;

ll calc( ll idx , ll n3 , ll n6 , bool f1,bool f2,bool f3)
{
   
    if(n3<0 || n6<0 || n3>34 || n6>34) return 0;
   
     if(idx == p)
       return (n3 == 17 && n6 == 17 && f3==1);
    
    
    if( dp[idx][n3][n6][f1][f2][f3] != -1)
         return dp[idx][n3][n6][f1][f2][f3];
    
           
    ll lim1 = 0;
    if(!f1) lim1 = jt1[idx];
    
    ll lim2 = 9;
    if(!f2) lim2 = jt2[idx];
    
    ll ans = 0;
    
    for(int i = lim1 ; i <= lim2 ; i++ )
    {
       ll n33 = n3 + (i==3) - (i==6);
       ll n66 = n6 + (i==6) - (i==9);
        
       bool f33 = (i==3) | (i==6) | (i==9) | f3;
        
       ans = ( ans + calc(idx+1 , n33 , n66 , i==lim1 ? f1 : 1 ,i==lim2 ? f2 : 1,f33) )%M;
    }
    
    return dp[idx][n3][n6][f1][f2][f3] = ans;
}
void solve()
{
    string a,b;
    cin >> a >> b;
    
    reverse(a.begin(),a.end());
    while(a.length() < b.length()) a+='0';
    reverse(a.begin(),a.end());
    
    jt1.clear();
    jt2.clear();
    memset(dp,-1,sizeof(dp));
    
    p = a.size();
    
    for(int i = 0;i < p ; i++ ) jt1.push_back(a[i]-'0'),jt2.push_back(b[i]-'0');
    
    ll a2 = calc( 0 , 17 , 17 , 0 , 0 ,0 );
    
    cout << a2 << "\n"; 
}

int main()
{
    FAST;
    int t;
    cin >> t;
    while(t--)
        solve();
}