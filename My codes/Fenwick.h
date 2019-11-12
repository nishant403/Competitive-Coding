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
}