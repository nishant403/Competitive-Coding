#include<bits/stdc++.h>
using namespace std;
#define ll long long

const ll N = 1e5+5;
const ll LN= 4;

vector<ll> grundy( (1LL << (LN*LN)) , -1);
vector<ll> mm ;                       //make-mask
struct Fenwick                        //Xor-Fenwick
{
    ll jt[N];
    void clear()
    {
        memset( jt , 0 , sizeof(jt));
    }
    void set( ll p , ll v )
    {
        while( p < N )
        {
            jt[p] ^= v;
            p += (p & (-p));
        }
    }
    ll query( ll p )
    {
        ll temp = 0;
        while( p > 0 )
        {
            temp ^= jt[p];
            p -= (p & (-p));
        }
        return temp;
    }
    ll range_query( ll l , ll r)
    {
        return query(l) ^ query(r);
    }
} F;

ll get_mask( ll sr , ll er , ll sc , ll ec )
{
    ll mask = 0 ;
    for(ll i = sr ; i <= er ; i++ )
        for( ll j = sc ; j <= ec ; j++ )
            mask |= (1 << (LN*i + j));
    return mask;
}

ll get_grundy(ll mask) // dynamic - programming part
{
    if(mask == 0) return 0;
    if(grundy[mask] != -1) return grundy[mask];
    
    unordered_set<ll> us;
    
    for(auto &it : mm )
        if( (it & mask) == it )      //sub-mask
            us.insert(get_grundy(it^mask));
    
    ll mex = 0;
    while( us.find(mex) != us.end())
        mex++;
    return grundy[mask] = mex;
}
ll ip_mg()
{
    ll mask = 0;
    for(ll i = 0 ; i < LN ; i++ )
    {
        for(ll j = 0 ; j < LN ; j++ )
        {
            char x;
            cin >> x;
            if( x == '1' )
                mask |= (1 << (LN*i + j));
        }
    }
    return get_grundy(mask);
}
void solve()
{
    F.clear();
    ll n , m;
    cin >> n >> m;
    for(ll i = 1 ; i <= n ; i++ )
    {
        ll g = ip_mg();
        F.set(i,g);
    }
    while(m--)
    {
        int type;
        cin >> type;
        if( type == 1 )
        {
            ll l , r;
            cin >> l >> r;
            ll x = F.range_query(l-1,r);
            if(!x) cout << "Lotsy\n";
            else   cout << "Pishty\n";
        }
        else
        {
            ll x;
            cin >> x;
            ll y = F.range_query(x-1,x);
            ll g = ip_mg();
            F.set(x,y^g);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    for(ll i = 0 ; i < LN ; i++ ) 
        for( ll j = i ; j < LN ; j++ )
            for( ll l = 0; l < LN ; l++ )
               for( ll k = l ; k < LN ; k++ )
                    mm.push_back(get_mask(i,j,l,k));
    int t;
    cin >> t;
    
    while( t-- )
        solve();
}