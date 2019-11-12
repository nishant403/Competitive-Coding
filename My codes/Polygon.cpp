#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define ftype double

const double EPS = 1e-9;

//make sure to define ftype as int / float / double as required
//It can be used as 2D as well

struct point {
    ftype x, y, z=0;
    point() {}
    point(ftype x, ftype y, ftype z=0): x(x), y(y), z(z) {}
    
    point& operator=( pair<ftype,ftype> P)
    {
     x=P.first;
     y=P.second;
        return *this;
    }

    bool operator==(const point &t)
    {
      return (x==t.x && y==t.y && z==t.z);  
    }
    
    point& operator+=(const point &t) {
        x += t.x;
        y += t.y;
        z += t.z;
        return *this;
    }
    
    
    point& operator-=(const point &t) {
        x -= t.x;
        y -= t.y;
        z -= t.z;
        return *this;
    }
    
     point& operator/=(const point &t) {
        
        return *this;
    }
    
    point& operator*=(ftype t) {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }
    point& operator/=(ftype t) {
        x /= t;
        y /= t;
        z /= t;
        return *this;
    }
    
    point operator+(const point &t) const {
        return point(*this) += t;
    }
    point operator-(const point &t) const {
        return point(*this) -= t;
    }
    point operator*(ftype t) const {
        return point(*this) *= t;
    }
  
    point operator/(ftype t) const {
        return point(*this) /= t;
    }
    
    point operator/(const point &t) const {
        return point(*this) /= t;
    }
    
    
    bool operator<(const point& p) const
    {
        return x < p.x - EPS || (abs(x - p.x) < EPS && y < p.y - EPS);
    }
    
};


int sgn(long long val){
    return val > 0 ? 1 : (val == 0 ? 0 : -1);
}

ftype dot(point a, point b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

ftype norm(point a) {
    return dot(a, a);
}

double abs(point a) {
    return sqrt(norm(a));
}

double proj(point a, point b) {
    return dot(a, b) / abs(b);
}

double angle(point a, point b) {
    return acos(dot(a, b) / abs(a) / abs(b));
}

point cross(point a, point b) {
    return point(a.y * b.z - a.z * b.y,
                   a.z * b.x - a.x * b.z,
                   a.x * b.y - a.y * b.x);
}

double cross2d(point a,point b)
{
 return cross(a,b).z;   
}

//volume of parallelepiped
ftype triple(point a, point b, point c) {
    return dot(a, cross(b, c));
}

//only for 2D lines given in vector form
point intersect (point a1, point d1, point a2, point d2) {
    return a1 + d1*(cross(a2 - a1, d2).z/cross(d1, d2).z ) ;
}

//intersection of 3 planes
point intersect(point a1, point n1, point a2, point n2, point a3, point n3) {
    point x(n1.x, n2.x, n3.x);
    point y(n1.y, n2.y, n3.y);
    point z(n1.z, n2.z, n3.z); 
    point d(dot(a1, n1), dot(a2, n2), dot(a3, n3));
    return point(triple(d, y, z),
                   triple(x, d, z),
                   triple(x, y, d)) / triple(n1, n2, n3);
}

//ax + by = c
struct line
{
 ftype a,b,c;
    
    line() {}
    
    //passing through p and q
    line(point p,point q)
    {
     a=p.y-q.y;
     b=q.x-p.x;
     c=(a*p.x)+(b*p.y);
        
    norm();
    }
    
    line(ftype a1,ftype b1,ftype c1)
    {
    a = a1;
    b = b1;
    c = c1;
        
        norm();
    }
    
    void norm()
    {
        double z = sqrt(a * a + b * b);
        if (abs(z) > EPS)
            a /= z, b /= z, c /= z;
        
        if(a<0 || (a==0 && b<0) ) 
            a=-a,b=-b,c=-c;
    }
    
    double distance(point p)
    {
      norm();
      return abs(a*p.x + b*p.y - c); 
    }
    
    void shift_origin(point p)
    {
     c = c - (p.x*a + p.y*b);       
    }
    
};

ftype give_x(line L,ftype y)
{
    if(L.a==0) { cerr << " error : parallel to  x axis\n"; return -1; }
 return (L.c-(L.b*y))/(L.a);   
}

ftype give_y(line L,ftype x)
{
        if(L.b==0) { cerr << " error : parallel to  y axis\n"; return -1; }
 return (L.c-(L.a*x))/(L.b);   
}

bool satisfy(line L,point p)
{
return (L.a*p.x + L.b*p.y == L.c);
}

double det(double a, double b, double c, double d) {
    return a*d - b*c;
}

//for line in 2-D
bool intersect(line m, line n, point & res) {
    double zn = det(m.a, m.b, n.a, n.b);
    if (abs(zn) < EPS)
        return false;
    res.x = -det(m.c, m.b, n.c, n.b) / zn;
    res.y = -det(m.a, m.c, n.a, n.c) / zn;
    return true;
}

bool parallel(line m, line n) {
    return abs(det(m.a, m.b, n.a, n.b)) < EPS;
}

bool equivalent(line m, line n) {
    return abs(det(m.a, m.b, n.a, n.b)) < EPS
        && abs(det(m.a, m.c, n.a, n.c)) < EPS
        && abs(det(m.b, m.c, n.b, n.c)) < EPS;
}

double distance(line a,line b)
{
   a.norm();
   b.norm();
    
    if(parallel(a,b) ) return 0;
    else return abs(a.c-b.c);
}

//intersection of 2D line-segments , given endpoints of both segments
//All cases covered
inline bool betw(double l, double r, double x)
{
    return min(l, r) <= x + EPS && x <= max(l, r) + EPS;
}

inline bool seg_intersect_1d(double a, double b, double c, double d)
{
    if (a > b)
        swap(a, b);
    if (c > d)
        swap(c, d);
    return max(a, c) <= min(b, d) + EPS;
}

bool seg_intersect(point a, point b, point c, point d, point& left, point& right)
{
    if (!seg_intersect_1d(a.x, b.x, c.x, d.x) || !seg_intersect_1d(a.y, b.y, c.y, d.y))
        return false;
    
    line m(a, b);
    line n(c, d);
    
    double zn = det(m.a, m.b, n.a, n.b);
    
    if (abs(zn) < EPS) {
        if (abs(m.distance(c)) > EPS || abs(n.distance(a)) > EPS)
            return false;
        
        if (b < a)
            swap(a, b);
        if (d < c)
            swap(c, d);
        left = max(a, c);
        right = min(b, d);
        return true;
    } else {
    
        left.x = right.x = det(m.c, m.b, n.c, n.b) / zn;
        left.y = right.y = det(m.a, m.c, n.a, n.c) / zn;
        
        return betw(a.x, b.x, left.x) && betw(a.y, b.y, left.y) &&
               betw(c.x, d.x, left.x) && betw(c.y, d.y, left.y);
    }
}


//circle line and circle circle intersection 
struct circle
{
 ftype r;
 point center;
    
    circle(){}
    circle(ftype r1,point c )
    {
        r = r1;
        center = c;
    }
    
    circle(ftype r1)
    {
     r=r1;
     center.x=center.y=0;
    }
};


void circle_line_intersect(circle C,line L)
{
    
double r, a, b, c; // given as input
    
r=C.r;
    
L.shift_origin(C.center);

a=L.a,b=L.b,c=L.c;
    
double x0 = a*c/(a*a+b*b) + C.center.x, y0 = b*c/(a*a+b*b) + C.center.y;
if (c*c > r*r*(a*a+b*b)+EPS)
    puts ("no points");
else if (abs (c*c - r*r*(a*a+b*b)) < EPS) {
    puts ("1 point");
    cout << x0 << ' ' << y0 << '\n';
}
else {
    double d = r*r - c*c/(a*a+b*b);
    double mult = sqrt (d / (a*a+b*b));
    double ax, ay, bx, by;
    ax = x0 + b * mult;
    bx = x0 - b * mult;
    ay = y0 - a * mult;
    by = y0 + a * mult;
    puts ("2 points");
    cout << ax << ' ' << ay << '\n' << bx << ' ' << by << '\n';
}   
    
}   
 
void circle_circle_intersect(circle c1,circle c2)
{
if(c1.center==c2.center && c1.r==c2.r)
{
 cout << "Infinite intersection points\n";
 return;
}
 
  line L;
  
  L.a = -2*(c1.center.x - c2.center.x);
  L.b = -2*(c1.center.y - c2.center.y);
  L.c = (c1.r*c1.r) - (c2.r*c2.r) - (c1.center.x*c1.center.x) -
        (c1.center.y*c1.center.y) + (c2.center.x*c2.center.x) + (c2.center.y*c2.center.y);
  
  L.norm();
    
  circle_line_intersect(c2,L);
}


//Common Tangent of two circles
//The described algorithm will also work in the case when one (or both) circles degenerate into points. 
//Thus, this algorithm can also be used to find tangents to a circle passing through a given point.
void tangents (point c, double r1, double r2, vector<line> & ans) {
    double r = r2 - r1;
    double z = (c.x*c.x) + (c.y*c.y);
    double d = z - (r*r);
    if (d < -EPS)  return;
    d = sqrt (abs (d));
    line l;
    l.a = (c.x * r + c.y * d) / z;
    l.b = (c.y * r - c.x * d) / z;
    l.c = -r1;
  
    ans.push_back (l);
}

vector<line> tangents (circle a, circle b) {
    
    
    vector<line> ans;
    
    if(a.center==b.center && a.r==b.r) {cout << "Same circle : Infinite tangents\n"; return ans;}
    
    for (int i=-1; i<=1; i+=2)
        for (int j=-1; j<=1; j+=2)
            tangents (b.center-a.center, a.r*i, b.r*j, ans);
        for (size_t i=0; i<ans.size(); ++i){
        ans[i].c += ans[i].a * a.center.x + ans[i].b * a.center.y;
        ans[i].norm();
    }
        
    return ans;
}

//Area of polygon
double area(const vector<point>& fig) {
    double res = 0;
    for (unsigned i = 0; i < fig.size(); i++) {
        point p = i ? fig[i - 1] : fig.back();
        point q = fig[i];
        res += (p.x - q.x) * (p.y + q.y);
    }
    return fabs(res) / 2;
}

//Helpful for Pick's theorem Area = (Integer points on Boundary)/2 + (Interger points inside) - 1
//Note : Assumed that p and q have interger coordinates and thus boundary is included 

int interger_points(point p,point q)
{
    // Check if line parallel to axes 
    if (p.x==q.x) 
        return abs(p.y - q.y) + 1; 
    if (p.y == q.y) 
        return abs(p.x-q.x) + 1; 
  
    return __gcd((int)abs(p.x-q.x),(int)abs(p.y-q.y))+1;    
}



//we can check for a point in polygon in O(n) using below function,
//if area of polygon = summation (abs(area of triangle (P(i),P(i+1),given point)))

//To check if point is inside a triangle
bool pointInTriangle(point a, point b, point c, point P)
{
    long long s1 = abs(cross2d(b-a,c-a));
    long long s2 = abs(cross2d(a-P,b-P)) + abs(cross2d(b-P,c-P)) + abs(cross2d(c-P,a-P));
    return s1 == s2;
}


//To check if point is inside a convex polygon, with multiple queries, each query in Log(N)
//Call prepare for preprocessing points of polygon

vector<point> seq;

//points are assumed to be in counter clockwise 

void prepare(vector<point> & points){
   int n = points.size();
    int pos = 0;
    
    for(int i = 1; i < n; i++){
        if( points[i] < points[pos] )
            pos = i;
    }
    
    rotate(points.begin(), points.begin() + pos, points.end());

    n--;
    seq.resize(n);
    for(int i = 0; i < n; i++)
        seq[i] = points[i + 1] - points[0];
}


bool pointInConvexPolygon(point P)
{
    int n = seq.size();
    //corner cases  checked first
    
    if( cross2d(seq[0],P) != 0 && sgn(cross2d(P,seq[0])) != sgn(cross2d(seq[n - 1],seq[0])))
        return false;
    
    if(cross2d(seq[n-1],P) != 0 && sgn(cross2d(P,seq[n-1])) != sgn(cross2d(seq[0],seq[n-1])))
        return false;

    if(cross2d(P,seq[0]) == 0)
        return norm(seq[0]) >= norm(P);
    
    
    //binary search to find triangle inside which point must be 
    int l = 0, r = n - 1;
    while(r - l > 1){
        int mid = (l + r)/2;
        int pos = mid;
        if(cross2d(seq[pos],P) >= 0)l = mid;
        else r = mid;
    }
    
    int pos = l;
    return pointInTriangle(seq[pos], seq[pos + 1], point(0, 0), P);
}


signed main()
{
    
}