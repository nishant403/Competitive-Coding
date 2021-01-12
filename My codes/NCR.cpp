
const int N = 1e5 + 10;

int fact[N];
int ifact[N];

void init()
{
    fact[0] = 1;
    
    for(int i=1;i<N;i++) fact[i] = (fact[i-1]*i)%MOD;
    
    ifact[N-1] = mod_pow(fact[N-1],MOD-2);
    
    for(int i=N-2;i>=0;i--) 
        ifact[i] = (ifact[i+1]*(i+1))%MOD;
}

int ncr(int n,int r)
{
 if(r>n) return 0;
    
 int res = fact[n];
    
 res = (res*ifact[r])%MOD;
 res = (res*ifact[n-r])%MOD;
    
  return res;
}


