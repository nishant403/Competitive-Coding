https://rextester.com/UBTF3103#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define ftype double
#define pb push_back

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

//clockwise : right turn
bool cw(point a, point b, point c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) < 0;
}

//counter-clockwise : left turn
bool ccw(point a, point b, point c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) > 0;
}

//Andrew's Algorithm

void convex_hull(vector<point> & a)
{
if(a.size()==1) return;
   
 //points are sorted according  to x coordinates ( tie broken by y)   
 //remove if already sorted
    
 sort(a.begin(),a.end());

    //remove duplicates - a corner case
    auto ip = unique(a.begin(),a.end());
    a.resize(distance(a.begin(),ip));
    
  //Main part  
  point p1 = a[0],p2=a.back();   
  vector<point> up,down;
 
  int n = a.size();    
    
  up.push_back(p1),down.push_back(p1);   
   
  for(int i=1;i<n;i++)  
  {
      //upper hull
   if (i == a.size() - 1 || cw(p1, a[i], p2)) {
            while (up.size() >= 2 && !cw(up[up.size()-2], up[up.size()-1], a[i]))
                up.pop_back();
       
            up.push_back(a[i]);
        }
      
     //lower hull 
  if (i == a.size() - 1 || ccw(p1, a[i], p2)) {
            while(down.size() >= 2 && !ccw(down[down.size()-2], down[down.size()-1], a[i]))
                down.pop_back();
      
            down.push_back(a[i]);
        } 
  } 
       
  //Merging points of upper and lower hull into a  in clockwise fashion 
    a.clear();
    for (int i = 0; i < (int)up.size(); i++)
        a.push_back(up[i]);
    for (int i = down.size() - 2; i > 0; i--)
        a.push_back(down[i]); 
    
}


//Trial Question : https://www.hackerrank.com/contests/justins-test-contest/challenges/convex-hull-1
// https://open.kattis.com/problems/convexhull

signed main()
{
    
int k;    

    while(cin >> k)    
    {
   if(k==0) break;     
vector<point> A(k);    
    
for(int i=0;i<k;i++)
 cin >> A[i].x >> A[i].y;   
 
convex_hull(A);
      
reverse(++A.begin(),A.end()); 
    
 cout << A.size() << "\n"; 
for(auto p : A) cout << p.x << " " << p.y << "\n";
    
}
    
}