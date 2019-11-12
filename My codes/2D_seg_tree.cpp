//g++  5.4.0
//2-D segment Tree
#include<bits/stdc++.h>
using namespace std;
 
#define ff first
#define ss second
#define int long long
#define pb push_back
#define pii pair< int,int >
#define fast ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0) ;
#define L(p) 2*p+1
#define R(p) 2*p+2
 
const int nax = 1e3+10;
int jt[4*nax][4*nax];
 
int fun(int x,int y )
{
    return x + y;
}
void build_y(int ly,int ry,int lx,int rx,int px,int py)
{
    if( ly == ry )
    {
        if( lx == rx )
        {
            char x;
            cin >> x;
            if( x == '*' ) jt[px][py] = 1;
            else           jt[px][py] = 0;
        }
        else
            jt[px][py] = fun(jt[L(px)][py] , jt[R(px)][py]);
        return ;
    }
    int my = (ly+ry)>>1;
    build_y( ly, my ,lx,rx, px, L(py) );
    build_y( my+1 , ry ,lx,rx, px , R(py) );
    jt[px][py] = fun( jt[px][L(py)] , jt[px][R(py)] );
    return ;
}
void build_x(int lx,int rx,int ly,int ry,int px)
{
    if( lx == rx )
    {
        build_y(ly,ry,lx,rx,px,0);
        return ;
    }
    int mx = (lx+rx)>>1;
    build_x(lx , mx, ly, ry, L(px) );
    build_x(mx+1 , rx, ly, ry, R(px) );
    build_y(ly,ry,lx,rx,px,0);
    return ;
}
void update_y(int ly , int ry, int y,int lx,int rx, int px, int py )
{
    if( ly == ry )
    {
        if( lx == rx ) jt[px][py] = 1-jt[px][py];
        else           jt[px][py] = fun(jt[L(px)][py] , jt[R(px)][py]);
        return ;
    }
    int my = (ly+ry)>>1;
    if(my >= y )  update_y(ly,my,y,lx,rx,px,L(py));
    else          update_y(my+1,ry,y,lx,rx,px,R(py));
    jt[px][py] = fun( jt[px][L(py)] , jt[px][R(py)] );
    return ;
}
void update_x(int lx,int rx ,int ly, int ry , int x,int y,int px)
{
    if( lx == rx )
    {
        update_y(ly, ry, y,lx,rx, px, 0);
        return;
    }
    int mx = (lx+rx)>>1;
    if( mx >= x ) update_x(lx,mx,ly,ry,x,y,L(px));
    else          update_x(mx+1,rx,ly,ry,x,y,R(px));
    update_y(ly,ry,y,lx,rx,px,0);
    return ;
}
int query_y(int ly,int ry,int y1,int y2,int px, int py )
{
    if( y1 > ry || y2 < ly ) return 0;
    else if( ly >= y1 && ry <= y2 )
        return jt[px][py];
    int my = (ly+ry)>>1;
    return query_y(ly,my,y1,y2,px,L(py)) + query_y(my+1,ry,y1,y2,px,R(py));
}
int query_x(int lx, int rx , int ly , int ry,int x1 , int y1 , int x2 , int y2 , int px )
{
    if( x1 > rx || x2 < lx ) return 0;
    else if( lx >= x1 && rx <= x2 )
    {
        int p = query_y( ly,ry,y1,y2,px,0);
 
        return p;
    }
    int mx = (lx+rx)>>1;
    return query_x(lx,mx,ly,ry,x1,y1,x2,y2,L(px)) + query_x(mx+1,rx,ly,ry,x1,y1,x2,y2,R(px));
}
signed main()
{
    fast;
    int n , q;
    cin >> n >> q;
    build_x( 1,n,1,n,0 );
    while( q-- )
    {
        int type;
        cin>>type;
        if( type == 1 )
        {
            int x,y;
            cin >> x >> y;
            update_x( 1,n,1,n,x,y,0);
        }
        else
        {
 
            int x1,y1,x2,y2;
            cin >> x1 >> y1 >> x2 >> y2;
            cout << query_x(1,n,1,n,x1,y1,x2,y2,0) << "\n";
        }
    }
}