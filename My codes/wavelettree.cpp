    #include <bits/stdc++.h>
    using namespace std;
     
    #define pb push_back
    #define S second
    #define F first
    #define f(i,n) for(int i=0;i<n;i++)
    #define fast ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
    #define vi vector<int>
    #define pii pair<int,int>
     
    vector<pii> prepare(vector<int> & a)
    {
            int n = a.size();
        
        vector<pii> b(n);
        
        f(i,n) b[i].F = a[i],b[i].S = i;
        
        sort(b.begin(),b.end());
        f(i,n) a[b[i].S] = i;
        f(i,n-1) if(b[i].F == b[i+1].F) a[b[i+1].S] = a[b[i].S];
            
        return b;    
    }
     
    struct node
    {
        public :
        
        int lo,hi;
        vector<int> b;
        node* left;
        node* right;
            
        node() {}
        
        node(auto l,auto r,int low,int high) : lo(low),hi(high) 
        {
            if(l>=r) return;
            
            if(low == high) return;
            
            int mid = (low + high)/2;
            
            b.reserve(r-l+1);
            
            b.pb(0);
            
            for(auto it = l;it != r;it++)
                b.pb(b.back() + ((*it) <=mid));
            
            auto pivot = stable_partition(l,r,[mid](int x)  { return x<=mid; });
            left = new node(l,pivot,low,mid);                              
            right = new node(pivot,r,mid+1,high);
        }
        
        //no of elements >= k in range[l,r]
        int query(int l,int r,int k)
        {
           if(l>r) return 0; 
            
           if(lo >= k) return r-l+1;
           if(hi < k) return 0;
           
           int atleft = b[r] - b[l-1]; 
           int atright = (r-l+1) - atleft;
           int mid = (lo + hi)/2;
            
           if(mid+1 >= k) return atright + left->query(b[l-1]+1,b[r],k); 
           else return right->query(l-b[l-1],r-b[r],k);
        }   
        
        int kth(int l,int r,int k)
        {
           if(lo == hi) return lo;
            
           int atleft = b[r] - b[l-1];
            
           if(atleft < k) return right->kth(l-b[l-1],r-b[r],k-atleft);
           return left->kth(b[l-1] + 1,b[r],k);
        }
    };
      
    void solve()
    {
       int n,q,x,y,k;
       cin >> n >> q;
        
       vector<int> a(n);
       f(i,n) cin >> a[i];
       
       auto b = prepare(a);
       
       node* wavelet = new node(a.begin(),a.end(),0,n); 
        
       f(i,q)
       {
           cin >> x >> y >> k;
           cout << b[wavelet->kth(x,y,k)].F << '\n';
       }    
    }
     
    signed main()
    {
        fast;
        solve();
    } 
