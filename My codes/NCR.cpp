const ll mod = 1e9+7;
const ll M = 1e9+7;
const ll N = 1e6+5;
vector<ll> fact(N) , ifact(N);


int inv(int x)
{
 int res = 1;
 int b = M - 2;
    
  while(b)
  {
    if(b&1) res=(res*x)%M;
    x=(x*x)%M;
    b>>=1;
  }
    
    return res;
}

void init()
{
    fact[0] = 1;
    
    for(int i=1;i<N;i++) fact[i] = (fact[i-1]*i)%M;
    
    ifact[(int)1e6] = inv(fact[(int)1e6]);
    
    for(int i=(int)1e6-1;i>=0;i--) 
        ifact[i] = (ifact[i+1]*(i+1))%M;
    
    
}

int ncr(int n,int r)
{
 if(r>n) return 0;
    
 int res = fact[n];
    
 res=(res*ifact[r])%M;
 res=(res*ifact[n-r])%M;
    
  return res;
}
