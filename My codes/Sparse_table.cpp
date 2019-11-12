vector< ll > a(N,0) , Log(N,0) , ans(N);
ll sp[LN][N];

void sparshtable( ll n )
{
    for(ll i =  2 ;  i <= n ; i++ ) Log[i] = Log[i-1] + !(i &(i-1));
    //for(ll i =  1 ;  i < n ; i++ ) cout << Log[i] << "\n";
    for(ll i =  0 ;  i < n ; i++ )
        sp[0][i] = a[i];
    for(ll i = 1 ; i < LN ; i++ )
        for(ll j =  0 ; j  < n ; j++ )
            if( j + (1LL<<(i-1)) < n )
                sp[i][j] = __gcd( sp[i-1][j] , sp[i-1][(j + (1LL<<(i-1)))] ); 
    
    return ;
}

ll work( ll st, ll en )
{
    ll p = Log[(en - st + 1)];
    return __gcd(sp[p][st],sp[p][en-(1<<p)+1]);
}