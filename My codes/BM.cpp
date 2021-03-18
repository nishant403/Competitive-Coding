//reference : https://codeforces.com/blog/entry/61306
//problem : https://www.hackerrank.com/contests/daiict-ipc-1-2020/challenges/counting-good-strings/problem

#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define pb push_back

const int N = 205;
const int MOD = 1e9+7;

int mod_pow(int a,int b,int M = MOD)
{
    if(a == 0) return 0;
    b %= (M - 1);  //M must be prime here
    
    int res = 1;
    
    while(b > 0)
    {
        if(b&1) res=(res*a)%M;
        a=(a*a)%M;
        b>>=1;
    }
    
    return res;
}

namespace linear_seq {
    
    inline vector<int> BM(vector<int> x)
    {
        //ls: (shortest) relation sequence (after filling zeroes) so far
        //cur: current relation sequence
        vector<int> ls,cur;
        
        //lf: the position of ls (t')
        //ld: delta of ls (v')
        int lf,ld;
        
        for(int i=0;i<(int)x.size();i++)
        {
            int t=0;
            
            //evaluate at position i
            for(int j=0;j<(int)cur.size();j++)
                t=(t+x[i-j-1]*cur[j])%MOD;
            
            if((t-x[i])%MOD==0) continue; //good so far
            
            //first non-zero position
            if(!cur.size())
            {
                cur.resize(i+1);
                lf=i; ld=(t-x[i])%MOD;
                continue;
            }
            
            //cur=cur-c/ld*(x[i]-t)
            int k=-(x[i]-t)*mod_pow(ld,MOD-2)%MOD/*1/ld*/;
            
            vector<int> c(i-lf-1); //add zeroes in front
            c.pb(k);
            
            for(int j=0;j<(int)ls.size();j++)
                c.pb(((-ls[j]*k)%MOD + MOD)%MOD);
            
            
            if(c.size() < cur.size()) c.resize(cur.size());
            
            for(int j=0;j<(int)cur.size();++j)
                c[j] = (c[j]+cur[j])%MOD;
            
            //if cur is better than ls, change ls to cur
            if(i-lf+(int)ls.size()>=(int)cur.size())
                ls = cur,lf = i,ld = (t-x[i])%MOD;
            
            cur = c;
        }
        
        return cur;
    }
    
    int m; //length of recurrence
    
    //a: first terms
    //h: relation
    int a[N],h[N],t_[N],s[N],t[N];
    
    //calculate p*q mod f
    inline void mull(int*p,int*q)
    {
        for(int i=0;i<m+m;i++) t_[i] = 0;
        
        for(int i=0;i<m;i++) if(p[i])
            for(int j=0;j<m;j++)
                t_[i+j] = (t_[i+j] + p[i]*q[j])%MOD;
            
        for(int i=m+m-1;i>=m;i--) if(t_[i])
            for(int j=m-1;j>=0;j--)
                t_[i-j-1] = (t_[i-j-1] + t_[i]*h[j])%MOD;
            
        for(int i=0;i<m;i++) p[i] = t_[i];
    }
    
    inline int calc(int K)
    {
        for(int i=m;i>=0;i--) s[i] = t[i] = 0;
        
        //init
        s[0] = 1; 
        if(m != 1) t[1] = 1;
        else t[0] = h[0];
        
        //binary-exponentiation
        while(K > 0)
        {
            if(K&1) mull(s,t);
            mull(t,t); 
            K>>=1;
        }
        
        int su = 0;
        for(int i=0;i<m;i++) su = (su + s[i]*a[i])%MOD;
        return su;
    }
    
    inline int work(vector<int> x,int n)
    {
        if(n < (int)x.size()) return x[n];
        
        vector<int> v = BM(x); 
        
        m = v.size(); 
        if(!m) return 0;
        
        for(int i=0;i<m;i++) h[i] = v[i] , a[i] = x[i];
        
        return calc(n);
    }
}

vector<int> prime(1000,1);
int mat[100][100];
int dp[N][100];

signed main()
{
   prime[0] = prime[1] = 0;

   for (int i = 2 ; i < 1000 ; i++) {
      for (int j = 2 * i ; j < 1000 ; j += i)
         prime[j] = 0;
   }
    
   for(int i=0;i<100;i++)
   {
       for(int j=0;j<100;j++)
       {
           if((i%10) != (j/10)) continue;
           mat[j][i] = !prime[(i*10) + (j%10)];
       }
   }
    
   for(int i=0;i<1000;i++)
       if(!prime[i]) dp[3][i/10]++;
    
   for(int i=4;i<N;i++)
   {
       for(int j=0;j<100;j++)
       {
           dp[i][j] = 0;
           
           for(int k=0;k<100;k++)
           {
               dp[i][j] += dp[i-1][k]*mat[k][j];
               dp[i][j]%=MOD;
           }
       }
   }
    
   int res = 0; 
   
   int n;
   cin >> n;
    
   for(int term=10;term<100;term++)
   {
       vector<int> terms;
       for(int i=3;i<N;i++) terms.pb(dp[i][term]);
       
       res = (res + linear_seq::work(terms,n-3))%MOD;
   }
    
   cout << res; 
}
