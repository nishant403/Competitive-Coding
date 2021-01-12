#include <bits/stdc++.h>
using namespace std;

#define int long long
#define f(i,n) for(int i=1;i<=n;i++)
#define fast ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)

void solve()
{
    
}

signed main()
{
   for(int i=0;i<19;i++)
   {
     string name = "input" + to_string(i) + ".txt";
     const char* c = name.c_str();
     freopen(c,"r",stdin);

     string name2 = "output" + to_string(i) + ".txt";
     const char* cc = name2.c_str();
     freopen(cc,"w",stdout);
     solve();
   }
}
