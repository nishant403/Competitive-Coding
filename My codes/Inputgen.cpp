#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pb push_back
#define pii pair<int,int>
#define F first
#define S second
#define f(i,n) for(int i=1;i<=n;i++)

//Input Generation
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int getRand(int l,int r)
{
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void get()
{

}

signed main()
{
    freopen("cases.txt","r",stdin);

    int t = 0;

    while(cin >> )
    {
       string name;

       name = "input";
       name+=to_string(t);
       name+=".txt";
       t++;

       const char *s = name.c_str();
       freopen(s,"w",stdout);

       get();
    }
}
