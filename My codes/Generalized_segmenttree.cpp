#include <bits/stdc++.h>
using namespace std;

//Problem : https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/problem/B

//reference code : https://www.codechef.com/viewsolution/25336654

int segtree_size(int n) {
    // 2^(ceil(lg(n)) + 1) - 1
    n -= 1;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return 2 * n + 1;
}

template<class M, class F>
class SegTree {
// M is a monoid
// F is an endomorphism
public:
    typedef M value_type;
    typedef F func_type;

    static void identity_check() {
        if(!F().is_identity()) {
            fprintf(stderr, "SegTree: endomorphism's default constructor is not identity\n");
            std::exit(1);
        }
    }

private:
    int n;
    std::vector<M> values;
    std::vector<F> pends;

public:
    explicit SegTree(int _n):
        n(_n), values(segtree_size(n)), pends(values.size()) {identity_check();}
    explicit SegTree(int _n, const M& x):
        n(_n), values(segtree_size(n)), pends(values.size()) {identity_check(); assign(x);}
    explicit SegTree(int _n, const M* a):
        n(_n), values(segtree_size(n)), pends(values.size()) {identity_check(); assign(a);}
    explicit SegTree(const std::vector<M>& v):
        n(v.size()), values(segtree_size(v.size())), pends(values.size()) {identity_check(); assign(v);}

private:
    void assign_values(int root, int first, int last, const M* a) {
        // root has the node number, first and last have the array indices.
        if(first == last) {
            values[root] = a[first];
        }
        else {
            int left = 2 * root + 1;
            int mid = (first + last) / 2;
            assign_values(left, first, mid, a);
            assign_values(left+1, mid+1, last, a);
            values[root] = M(values[left], values[left+1]);
        }
    }

    void assign_values(int root, int first, int last, const M& x) {
        // root has the node number, first and last have the array indices.
        if(first == last) {
            values[root] = x;
        }
        else {
            int left = 2 * root + 1;
            int mid = (first + last) / 2;
            assign_values(left, first, mid, x);
            assign_values(left+1, mid+1, last, x);
            values[root] = M(values[left], values[left+1]);
        }
    }

public:
    void assign(const M* a) {
        pends.assign(values.size(), F());
        assign_values(0, 0, n-1, a);
    }

    void assign(const M& x) {
        pends.assign(values.size(), F());
        assign_values(0, 0, n-1, x);
    }

    void assign(const std::vector<M>& v) {
        if(v.size() < n) {
            fprintf(stderr, "SegTree: vector input to assign is too short\n");
            std::exit(3);
        }
        assign(v.data());
    }

private:
    void print(int root, int first, int last,int level) const {
        for(int i=0; i<level; ++i) {
            cout << " ";
        }
        
        cout << root << "[" << first << "-" << last << "]: ";
        values[root].print();
        if(!pends[root].is_identity()) {
            cout << ": ";
            pends[root].print();
        }
        cout << '\n';
        if(first != last) {
            int left = 2 * root + 1;
            int mid = (first + last) / 2;
            print(left, first, mid,  level+1);
            print(left+1, mid+1, last,  level+1);
        }
    }

public:
    void print() const {
        print(0, 0, n-1, 0);
    }

private:
    void propagate(int root, int first, int last) {
        if(!pends[root].is_identity()) {
            values[root] = pends[root](values[root]);
            if(first != last)
            {
                int left = 2 * root + 1;
                pends[left] = F(pends[root], pends[left]);
                pends[left+1] = F(pends[root], pends[left+1]);
            }
            pends[root] = F();
        }
    }

    M query(int root, int first, int last, int i, int j) {
        if(i>last || j<first) {
            return M();
        }
        propagate(root, first, last);
        if(i<=first && last<=j) {
            return values[root];
        }
        else {
            int left = 2 * root + 1;
            int mid = (first + last) / 2;
            return M(query(left, first, mid, i, j), query(left+1, mid+1, last, i, j));
        }
    }

public:
    M query(int i, int j) {
        return query(0, 0, n-1, i, j);
    }

private:
    void update(int root, int first, int last, int i, int j, const F& f) {
        if(i>last || j<first) {
            propagate(root, first, last);
        }
        else if(i<=first && last<=j) {
            pends[root] = F(f, pends[root]);
            propagate(root, first, last);
        }
        else {
            propagate(root, first, last);
            int left = 2 * root + 1;
            int mid = (first + last)/2;
            update(left, first, mid, i, j, f);
            update(left+1, mid+1, last, i, j, f);
            values[root] = M(values[left], values[left+1]);
        }
    }

public:
    void update(int i, int j, const F& f) {
        update(0, 0, n-1, i, j, f);
    }
    
private:
    int find_first_knowingly(int root, int first, int last,const function<bool(const M &)> & f) {
        if(first == last) {
            return first;
        }
       
        propagate(root, first, last);
       
        int left = 2 * root + 1;
        int mid = (first + last)/2;
        
        if(f(values[left])) {
          return find_first_knowingly(left,first,mid,f);
        } else {
          return find_first_knowingly(left+1,mid+1,last,f);
        }
    }
    
    int find_first(int root, int first, int last, int i, int j, const function<bool(const M &)> & f) {
        propagate(root, first, last);
        
        if(i>last || j<first) {
            return -1;
        }
        
        if(i <= first && last <= j) {
            if(!f(values[root])) return -1;
            else return find_first_knowingly(root,first,last,f);
        }
        
        int res = -1;
        int left = 2 * root + 1;
        int mid = (first + last)/2;
        
        if(i <= mid) {
            res = find_first(left,first,mid,i,j,f);
        }
        
        if(j > mid && res == -1) {
            res = find_first(left+1,mid+1,last,i,j,f);
        }
        
        return res;
    }
    
public:
    int find_first(int i,int j,const function<bool(const M&)> & f) {
        return find_first(0,0,n-1,i,j,f);
    }
    
};

using namespace std;

#define int long long 

/*
CoinCount is a Monoid, so it should implement the following constructors:
* Monoid();
* Monoid(const Monoid&, const Monoid&);
* void print()
*/

const int inf = 1e18;

class CoinCount {
private:
    int sum,sz;

public:
    // mandatory methods
    CoinCount(): sum(0),sz(1) {}

    CoinCount(const CoinCount& l, const CoinCount& r) : sum(l.sum + r.sum),sz(l.sz+r.sz) {}

    // custom methods
    CoinCount(int _sum,int _sz): sum(_sum),sz(_sz) {}

    CoinCount flip() const {
        return CoinCount(sz-sum,sz);
    }

    void print() const {
        cout <<"CC(sum = " << sum << ")\n";
    }

    int get_answer() const {
        return sum;
    }
};

/*
FlipOp is an Endomorphism, so it should implement these methods:
* (constructor) EndF();  // identity function
* (constructor) EndF(const EndF& f1, const EndF& f2);  // function composition: f1.f2
* bool is_identity() const;
* Monoid operator()(const Monoid&);
* void print();
*/
class FlipOp {
private:
    bool flip;

public:
    typedef CoinCount value_type;

    // mandatory methods
    bool is_identity() const {
        return (flip == false);
    }

    FlipOp(): flip(false) {}

    FlipOp(const FlipOp& a, const FlipOp& b):
        flip(a.flip != b.flip) {}

    CoinCount operator()(const CoinCount& x) {
        if(flip) return x.flip();
        else return x;
    }

    void print() const {
        cout << static_cast<int>(flip) << '\n';
    }

    // custom methods
    explicit FlipOp(bool _flip): flip(_flip) {}
};

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n, q;
    cin >> n >> q;
    
    vector<CoinCount> arr(n);
    
    for(int i=0;i<n;i++) 
    {
        int x;
        cin >> x;
        if(x == 1) arr[i] = arr[i].flip();
    }
    
    SegTree<CoinCount, FlipOp> segTree(arr);
    FlipOp upd(true);
    
    while(q--)
    {
        int x,y;
        cin >> x >> y;
        
        if(x == 1)
        {
            segTree.update(y,y,upd);
        }
        else
        {
            auto fc = [&y](const CoinCount & cc) {
                if(cc.get_answer() > y) return true;
                y -= cc.get_answer();
                return false;
            };
            
            cout << segTree.find_first(0,n-1,fc) << '\n';
        }
    }
 
    return 0;
}
