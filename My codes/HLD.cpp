//AUTHOR : TIRTH JARSANIA
//COLLEGE : DAIICT

#include<bits/stdc++.h>
using namespace std;

#define INF LONG_LONG_MAX
#define MINF LONG_LONG_MIN
#define bp __builtin_popcountll
#define ll long long int
#define ld long double
#define pb push_back
#define ff first
#define ss second
#define pii pair<ll,ll>
#define L(p) 2*p+1
#define R(p) 2*p+2
#define precision(x,d) cout<<fixed<<setprecision(d)<<x
#define minQueue priority_queue<pii,vector<pii>,greater<pii>> 
#define maxQueue priority_queue<pii> 
#define FAST ios_base::sync_with_stdio(false),cin.tie(0),cout.tie(0);srand(time(NULL))

const ll N = 1e5+5;
const ll LN = 17;
ll ptr,grp;
vector<ll> g[N] ;
vector<ll> lev(N) , sz(N) , head(N) , place(N) , val(N) , pos(N) , a(N); 

ll par[LN][N];
ll jt1[4*N] , jt2[4*N];
ll fun1(ll a,ll b)
{
    return max(a,b); // whatever u wish
}

ll fun2(ll a,ll b)
{
    return min(a,b); // whatever u wish
}
void build(ll l , ll h , ll p )
{
	if(l == h)
	{
		jt1[p] = val[l];
        jt2[p] = val[l];
		return;
	}
	ll m = (l+h)>>1;
	build(l , m , L(p));
	build(m+1 , h , R(p));
	jt1[p] = fun1(jt1[L(p)],jt1[R(p)]);
    jt2[p] = fun2(jt2[L(p)],jt2[R(p)]);
	return;
}

void update(ll l ,ll h , ll p, ll ql, ll qh,ll v)
{
	if(l > qh || h < ql)
		return;
	else if(l >= ql && h <= qh)
	{
		jt1[p] = v;
        jt2[p] = v;
		return;
	}
	ll m = (l + h )>> 1;
	update( l , m , L(p) ,ql ,qh,v);
	update( m+1,h , R(p) , ql ,qh,v);
	jt1[p] = fun1(jt1[L(p)],jt1[R(p)]);
    jt2[p] = fun2(jt2[L(p)],jt2[R(p)]);
	return;
}

ll query1(ll l,ll h, ll p, ll ql ,ll qh)
{
	if(l > qh || h < ql)
		return MINF;
	else if(l >= ql && h <= qh)
		return jt1[p] ;
	ll m = (l + h )>> 1;
	ll p1 = query1( l , m , L(p) ,ql ,qh);
	ll p2 = query1(m+1 , h , R(p) , ql ,qh);
	return fun1(p1,p2);
}

ll query2(ll l,ll h, ll p, ll ql ,ll qh)
{
	if(l > qh || h < ql)
		return INF;
	else if(l >= ql && h <= qh)
		return jt2[p] ;
	ll m = (l + h )>> 1;
	ll p1 = query2( l , m , L(p) ,ql ,qh);
	ll p2 = query2(m+1 , h , R(p) , ql ,qh);
	return fun2(p1,p2);
}

void dfs(ll v,ll p)
{
    par[0][v] = p;
    sz[v] = 1;
    lev[v] = lev[p]+1;
    
    for(auto &it:g[v])
    {
        if(it!=p)
        {
            dfs(it,v);
            sz[v] += sz[it];
        }
    }
    return ;
}
ll lca(ll u,ll v)
{
    if(lev[u] < lev[v]) swap(u,v);
    ll diff = lev[u] - lev[v];
    for(ll i = 0; i < LN; i++)
        if((1<<i) & diff)
            u = par[i][u];
    
    if(u == v)
        return u;
    
    for(ll i = LN-1 ; i>=0 ; i--)
        if(par[i][u] != -1 && par[i][v] != par[i][u])
            u = par[i][u] , v = par[i][v];
    
    return par[0][u];
}

void HLD(ll v,ll p)
{
    if(head[grp] == -1)
        head[grp] = v;
    
    place[v] = grp;
    pos[v] = ptr;
    val[ptr++] = a[v];
    
    ll special_child = -1;
    ll maxi = -1;
    
    for(auto &it:g[v])
    {
        if(it!=p)
        {
            if(maxi < sz[it])
            {
                maxi = sz[it];
                special_child = it;
       
            }
        }
    }
    
    if(maxi!=-1) HLD(special_child , v);
    
    for(auto &it:g[v])
    {
        if(it!=p && it!=special_child)
        {
            grp++;
            HLD(it,v);
        }
    }
    return ;
}

bool work(ll l,ll h)
{
    return (query1(0,ptr-1,0,l,h) == query2(0,ptr-1,0,l,h));
}

void solve(ll u)
{
    ll ans = 0;
    while(1)
	{
        ll v = head[place[u]];
		ll x = pos[u];
        ll y = pos[v];
		if(work(y,x))
		{
			ans += (lev[u]-lev[v]);
			if(v==1) break;
			if(a[par[0][v]] == a[v])
			{
				ans++;
				u = par[0][v];
			}
			else
				break;
		}
		else
		{
            ll ap = x;
            ll xx = x;
			while(y <= x)
			{
				ll m = (x+y)>>1;
				if(work(m,xx))
                {
                    ap = m;
                    x = m-1;
                }
				else
					y = m+1;
			}
			ans+=(xx-ap);
			break;
		}
	}
	printf("%lld\n",ans);
}

void change(ll i, ll w)
{
    ll x = pos[i];
    a[i] = w;
   
    update(0,ptr-1,0,x,x,w);
    return;
}
                  
int main()
{
    FAST;
    lev[0]=0;
   
        ll n;
        scanf("%lld",&n);
    
        ptr = 0;
        grp = 0;
        for(int i=0;i<=n;i++)
        {
            g[i].clear();
            head[i] = -1;
        }
        for(int i=0;i<LN;i++)
            for(int j=1;j<=n;j++)
                par[i][j] = 0;
        for(int i=1;i<n;i++)
        {
            ll u,v;
            scanf("%lld%lld",&u,&v);
            g[u].pb(v);
            g[v].pb(u);
        }
        for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
        dfs(1,0);
        HLD(1,0);
        build(0,ptr-1,0);
        for(ll i=1 ; i < LN ; i++ )
            for(ll j=1 ; j<= n ; j++ )
                if(par[i-1][j] != 0)
                    par[i][j] = par[i-1][par[i-1][j]];
        
        ll q;
        scanf("%lld",&q);
        while(q--)
        {
            ll type;
            scanf("%lld",&type);
           
            ll x,y;
            if(type == 2)
                scanf("%lld",&x), solve(x);
            else
                scanf("%lld%lld",&x,&y), change(x,y);
        }
}
https://www.codechef.com/problems/COMA19E