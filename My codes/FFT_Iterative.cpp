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

using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd> & a, bool invert) {
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (cd & x : a)
            x /= n;
    }
}
    
vector<int> multiply(vector<int> const& a, vector<int> const& b) 
{
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) 
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    return result;
}

const int M = 1e9+7;

void solve()
{
    string a,b;
    cin >> a >> b;
    
    int n = a.length();
    int m = b.length();
    
    vi one[4],two[4];
    vi onei[4],twoi[4];
    
    f(i,4) one[i].resize(n),two[i].resize(m);
    
    f(i,n) one[0][i] = (a[i] == 'A');
    f(i,n) one[1][i] = (a[i] == 'C');
    f(i,n) one[2][i] = (a[i] == 'T');
    f(i,n) one[3][i] = (a[i] == 'G');
    
    f(i,m) two[0][i] = (b[i] == 'A');
    f(i,m) two[1][i] = (b[i] == 'C');
    f(i,m) two[2][i] = (b[i] == 'T');
    f(i,m) two[3][i] = (b[i] == 'G');
    
    f(i,4) reverse(two[i].begin(),two[i].end());
    
    vi res[4];
    
    f(i,4) res[i] = multiply(one[i],two[i]);
    
    int ans = 0;
    
    for(int i=m-1;i<=n-1;i++)
        ans=max(ans,res[0][i]+res[1][i]+res[2][i]+res[3][i]);
    
    cout << m-ans;
    
}

signed main()
{
    fast;
    solve();
}

//Time with recursive fft : 32
//Time with iterative fft : 12 