#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 2e5 + 10;

vector<int> lastprime(N,-1);

void sieve_lastprime()
{
  lastprime[0] = lastprime [1] = 0;
    
  //-1 is prime
    
  for(int i=2;i<N;i++)
  {
    if(lastprime[i] == -1)
        for(int j=i*i;j<N;j+=i) 
            lastprime[j] = i;  
  }
}

vector<int> phi(N);

void sieve_phi()
{
    for(int i=0;i<N;i++) phi[i] = i;
    
    for(int i=2;i<N;i++)
    {
      if(phi[i] == i)
          for(int j=i;j<N;j+=i)
             phi[j] -= (phi[j]/i);
    }
}

vector<int> mobius(N);

void sieve_mobius()
{
  sieve_lastprime();  
    
  mobius[0] = 0;
  mobius[1] = 1;
    
  for(int i=2;i<N;i++)
  {
      if(lastprime[i] == -1) mobius[i] = -1;
      else if( (i/lastprime[i]) % lastprime[i] == 0) mobius[i] = 0;
      else mobius[i] = (mobius[lastprime[i]]*mobius[i/lastprime[i]]);
  }
}

signed main()
{
    sieve_phi();
    sieve_mobius();
    
    for(int i=1;i<=10;i++) cout << phi[i] <<" ";
    cout << "\n";
    for(int i=1;i<=10;i++) cout << mobius[i] <<" ";
}