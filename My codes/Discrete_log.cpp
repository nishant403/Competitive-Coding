#include <bits/stdc++.h>
using namespace std;
 
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"
#define int long long
 
const int N=1e5+5;
 
int modInverse(int a, int m)
{
    int m0 = m;
    int y = 0, x = 1;
 
    if (m == 1)
      return 0;
 
    while (a > 1)
    {
        int q = a / m;
        int t = m;
 
        m = a % m, a = t;
        t = y;
 
        y = x - q * y;
        x = t;
    }
 
    if (x < 0)
       x += m0;
 
    return x;
}
 
int solve(int a, int b, int m) 
{
    int n = (int) sqrt (m + .0) + 1;
 
    int an = 1;
    for (int i=0; i<n; ++i)
        an = (an * a) % m;
 
    map<int,int> vals;
    for (int i=1, cur=an; i<=n; ++i) 
    {
        if (!vals.count(cur))
            vals[cur] = i;
        cur = (cur * an) % m;
    }
 
    for (int i=0, cur=b; i<=n; ++i) 
    {
        if (vals.count(cur)) 
        {
            int ans = vals[cur] * n - i;
            if (ans < m)
                return ans;
        }
        cur = (cur * a) % m;
    }
    return -1;
}
 
bool problem(int a, int b, int m)
{
	return (__gcd(a, m)>1);
}
 
void change(int &a, int &b, int &n)
{
	int g=__gcd(a, n);
	int v=n/g;
	int beta=b/g;
	int alpha=a/g;
	int inv=modInverse(alpha, v);
	b=(inv*beta)%v;
	n=v;
}
 
int32_t main()
{
	IOS;
	int t;
	cin>>t;
	while(t--)
	{
		int a, b, m;
		cin>>a>>b>>m;
		if(b==1)
		{
			cout<<"0"<<endl;
			continue;
		}
		if(a==b)
		{
			cout<<"1"<<endl;
			continue;
		}
		int ctr=0;
		while(problem(a, b, m))
		{
			ctr++;
			change(a, b, m);
		}
		cout<<solve(a, b, m)+ctr<<endl;
	}
	return 0;
}