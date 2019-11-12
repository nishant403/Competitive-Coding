struct segTree
{
    ll n;
    vector<ll> a, tree, lazy;
 
    void _update(ll l, ll r, ll val, ll ss, ll se, ll node)
    {
        if(ss < 0 || se >= n)
            return;
        if(r < ss || se < l)
            return;
        tree[node] += lazy[node]*(se-ss+1);
        if(ss != se)
        {
            lazy[2*node+1] += lazy[node];
            lazy[2*node+2] += lazy[node];
        }
        lazy[node] = 0;
 
        if(ss == se)
        {
            tree[node] += val;
            return;
        }
        ll mid = (ss+se)>>1;
        
        if(l <= ss && se <= r)
        {
            tree[node] += val*(se-ss+1);
            lazy[2*node+1] += val;
            lazy[2*node+2] += val;
            return;
        }
        _update(l, r, val, ss, mid, 2*node+1);
        _update(l, r, val, mid+1, se, 2*node+2);
        tree[node] = tree[2*node+1]+tree[2*node+2];
        return ;
    }
 
    ll _query(ll l, ll r, ll ss, ll se, ll node)
    {
        
        if(r < ss || se < l)
            return 0;
        tree[node] += lazy[node]*(se-ss+1);
        if(ss != se)
        {
            lazy[2*node+1] += lazy[node];
            lazy[2*node+2] += lazy[node];
        }
        lazy[node] = 0;
 
        if(l <= ss && se <= r)
            return tree[node];
        ll mid = (ss+se)>>1;
        ll x = _query(l, r, ss, mid, 2*node+1);
        ll y = _query(l, r, mid+1, se, 2*node+2);
        return x+y;
    }
      void _build(ll ss, ll se, ll node)
    {
        if(ss < 0 || se >= n)
            return;
        if(ss == se)
        {
            tree[node] = a[ss];
            return;
        }
        ll mid = (ss+se)>>1;
        _build(ss, mid, 2*node+1);
        _build(mid+1, se, 2*node+2);
        tree[node] = tree[2*node+1]+tree[2*node+2];
    }
    segTree(ll sz)
    {
        n = sz;
        a.resize(n, 0);
        tree.resize(4*n, 0);
        lazy.resize(4*n, 0);
    }
    ll query(ll l, ll r) {return _query(l, r, 0, n-1, 0);}
    void update(ll l, ll r, ll v) {_update(l, r, v, 0, n-1, 0);}
};
