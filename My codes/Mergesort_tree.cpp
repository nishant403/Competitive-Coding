//Tirth Jarsania

#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back
#define ff first
#define ss second
#define pii pair<ll,ll>
#define L(p) 2*p+1
#define R(p) 2*p+2

const int N = 1e6+1;
vector<int> g[4*N] , lef[N];

void cst(int p , int l , int h)
{
    if(l == h)
    {
        g[p] = lef[l];
        sort(g[p].begin() , g[p].end());
        return;
    }
    int mid = (l+h)>>1;
    cst(L(p) , l , mid);
    cst(R(p) , mid+1 , h);
    merge(g[L(p)].begin() , g[L(p)].end(),g[R(p)].begin() , g[R(p)].end() , back_inserter(g[p]));
    return;
}

int query( int p , int l ,int h , int ql ,int qh)
{
    if( ql > h || qh < l || ql > qh)
        return 0;
    else if( l >= ql && h <= qh)
    {
        return upper_bound(g[p].begin() , g[p].end() , qh ) -g[p].begin();
    }
    int mid = (l+h)>>1;
    return query( L(p) , l ,mid , ql ,qh) + query( R(p) , mid+1 ,h , ql ,qh);
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n , m ;
    cin >> n >> m;
    
    for(int i = 0 ; i < n ; i++ )
    {
        int x,y;
        cin >> x >> y;
        lef[x].pb(y);
    }
    
    cst( 0 , 1 , N-1);
    
    while(m--)
    {
        int x , y ,z;
        cin >> x >> y;
        int ans = 0;
        z = y;
        y = 0;
        while(--x)
        {
            ans += query(0,1,N-1,y+1,z-1);
            //cout << ans << endl;
            cin >> y;
            swap(y,z);
        }
        ans += query(0,1,N-1,y+1,z-1);
        ans += query(0,1,N-1,z+1,N-1);
        cout << n - ans << "\n";
    }
}
