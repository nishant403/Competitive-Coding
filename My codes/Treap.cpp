#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define f(i,n) for(int i=0;i<n;i++)

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int getrand()
{
    uniform_int_distribution<int> uid(0, 999999999999999);
    return uid(rng);
}

const int N = 2e5+10;

int upr[N],lwr[N];

struct node{
    int prior,size;
    int val;//value stored in the array
    int sum;//whatever info you want to maintain in segtree for each node
    int lazy;//whatever lazy update you want to do
    struct node *l,*r;
    bool rev;
};

typedef node* pnode;
int sz(pnode t){
    return t?t->size:0;
}

void upd_sz(pnode t){
    if(t)t->size=sz(t->l)+1+sz(t->r);
}

void lazy(pnode t){
    if(!t || !t->lazy)return;
    t->val+=t->lazy;//operation of lazy
    t->sum+=t->lazy*sz(t);
    if(t->l)t->l->lazy+=t->lazy;//propagate lazy
    if(t->r)t->r->lazy+=t->lazy;
    t->lazy=0;
}

void push (pnode it) {
    if (it && it->rev) {
        it->rev = false;
        swap (it->l, it->r);
        if (it->l)  it->l->rev ^= true;
        if (it->r)  it->r->rev ^= true;
    }
}

void reset(pnode t){
    if(t)t->sum = t->val;//no need to reset lazy coz when we call this lazy would itself be propagated
}

void combine(pnode& t,pnode l,pnode r){//combining two ranges of segtree
    if(!l || !r)return void(t = l?l:r);
    t->sum = l->sum + r->sum;
}

void operation(pnode t){//operation of segtree
    if(!t)return;
    reset(t);//reset the value of current node assuming it now represents a single element of the array
    lazy(t->l);lazy(t->r);//imp:propagate lazy before combining t->l,t->r;
    push(t->l); push(t->r);
    combine(t,t->l,t);
    combine(t,t,t->r);
}

void split(pnode t,pnode &l,pnode &r,int pos,int add=0){
    if(!t)return void(l=r=NULL);
    lazy(t);
    push(t);
    int curr_pos = add + sz(t->l);
    if(curr_pos<=pos)
        split(t->r,t->r,r,pos,curr_pos+1),l=t;
    else 
        split(t->l,l,t->l,pos,add),r=t;
    upd_sz(t);
    operation(t);
}

void merge(pnode &t,pnode l,pnode r){ //l->leftarray,r->rightarray,t->resulting array
    lazy(l);lazy(r);
    push(l);
    push(r);
    if(!l || !r) t = l?l:r;
    else if(l->prior>r->prior)merge(l->r,l->r,r),t=l;
    else    merge(r->l,l,r->l),t=r;
    upd_sz(t);
    operation(t);
}

pnode init(int val){
    pnode ret = new node();
    ret->prior=getrand();ret->size=1;
    ret->val=val;
    ret->sum=val;ret->lazy=0;
    ret->rev = 0;
    return ret;
}

int range_query(pnode t,int l,int r){//[l,r]
    pnode L,mid,R;
    split(t,L,mid,l-1);
    split(mid,t,R,r-l);//note: r-l!!
    int ans = t->sum;
    merge(mid,L,t);
    merge(t,mid,R);
    return ans;
}

void output (pnode t) {
    if (!t)  return;
    push (t);
    output (t->l);
    cout << t->val << " ";
    output (t->r);
}
signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
   
    int n,m,type,l,r,a,b,c,d,k=-1;

    cin >> n >> m;
    int x = 0;
    f(i,n) cin >> upr[i];
    f(i,n) cin >> lwr[i];
    
    pnode upper = init(upr[0]);
    pnode lower = init(lwr[0]);
    
    for(int i=1;i<n;i++)
    {
     merge(upper,upper,init(upr[i])); 
     merge(lower,lower,init(lwr[i]));    
    }
    
    while(m--)
    {
      cin >> type;   
     
      if(type == 1)  
      {
        cin >> l >> r;
        
        l--;  
        r--;
          
        pnode u1,u2,u3,l1,l2,l3;
          
        split(upper,u1,u2,l-1);
        split(u2,u2,u3,r-l);  
          
        split(lower,l1,l2,l-1);
        split(l2,l2,l3,r-l);  
          
        l2->rev^=1;
        u2->rev^=1;
          
        merge(u1,u1,l2);
        merge(u1,u1,u3);
          
        merge(l1,l1,u2);
        merge(l1,l1,l3);
      
        upper = u1;
        lower = l1;
      } 
        
      else if(type == 2)
      {
            cin >> k;
            x = k - x;
      }
        
      else
      {
       cin >> a >> b >> c >> d; 
          
       a--;
       b--;
       c--;
       d--;   
       
       int ans = 0;
        ans = range_query(upper,a,b);    
      
       if(c+1<=x)
       {
        if(d>x-1) d = x-1;
           
        int cnt = d-c+1;   
           
        ans-=2*range_query(upper,a,a+cnt-1);   
       }  
                    
       cout << ans << "\n";   
      }
        
    }
    
}