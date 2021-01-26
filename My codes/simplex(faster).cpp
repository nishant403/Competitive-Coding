#include <bits/stdc++.h>
using namespace std;
 
//problem : https://www.codechef.com/DEC20A/problems/DGMATRIX/ 
 
#define lp for(;;)
#define repf(i,a,b)
#define ft(i,a,b) for (int i=(a);i<=(b);++i)
#define rep(i,n) for (int i=0;i<(n);++i)
#define rtn return
#define pb push_back
#define mp make_pair
#define sz(x) (int((x).size()))
typedef double db;
typedef vector<int> vi;

db inf = 1e+6;
db eps = 1e-6;
inline int sgn(const db& x){rtn (x>+eps)-(x<-eps);}
 
const int N = 110;
const int MAXN = N+N;
const int MAXM = (2*N*N) + N + N + N;
const int maxn = N+N;
const int maxm = (2*N*N) + N + N + N;

int n,m;
db A[MAXM+1][MAXN+1],X[MAXN];
int basis[MAXM+1],out[MAXN+1];
 
void pivot(int a,int b)
{
	ft(i,0,m) if (i!=a&&sgn(A[i][b])) ft(j,0,n) if (j!=b) A[i][j]-=A[a][j]*A[i][b]/A[a][b];
	ft(j,0,n) if (j!=b) A[a][j]/=A[a][b];
	ft(i,0,m) if (i!=a) A[i][b]/=-A[a][b];
	A[a][b]=1/A[a][b];
	swap(basis[a],out[b]);
}

db simplex()
{
	rep(j,n) A[0][j]=-A[0][j];
	ft(i,0,m) basis[i]=-i;
	ft(j,0,n) out[j]=j;
	lp
	{
		int ii=1,jj=0;
		ft(i,1,m) if (mp(A[i][n],basis[i])<mp(A[ii][n],basis[ii])) ii=i;
		if (A[ii][n]>=0) break;
		rep(j,n) if (A[ii][j]<A[ii][jj]) jj=j;
		if (A[ii][jj]>=0) rtn -inf;
		pivot(ii,jj);
	}
	lp
	{
		int ii=1,jj=0;
		rep(j,n) if (mp(A[0][j],out[j])<mp(A[0][jj],out[jj])) jj=j;
		if (A[0][jj]>=0) break;
		ft(i,1,m)
			if (A[i][jj]>0&&(A[ii][jj]<=0||mp(A[i][n]/A[i][jj],basis[i])<mp(A[ii][n]/A[ii][jj],basis[ii])))
				ii=i;
		if (A[ii][jj]<=0) rtn +inf;
		pivot(ii,jj);
	}
	rep(j,n) X[j]=0;
	ft(i,1,m) if (basis[i]>=0) X[basis[i]]=A[i][n];
	rtn A[0][n];
}

int a[N][N];
int eqs[N][N][maxn];

int equ;
int var;

void add(int I,int J,int K,int L)
{
    for(int i=0;i<=var;i++) eqs[I][J][i]-=eqs[K][L][i];
}

int res[N][N];
int nn;

int main() 
{
    cin >> nn;
    
    equ = nn + nn + 1 + (nn*nn) + (nn*nn);
    var = nn + nn + 1;
    
    n = var;
    m = equ;
    
    for(int i=0;i<nn;i++)
      for(int j=0;j<nn;j++) cin >> a[i][j];
    
   for(int i=0;i<=nn;i++) eqs[0][i][i] = 1;
   for(int i=1;i<=nn;i++) eqs[i][0][nn+i] = 1;   
        
  for(int i=1;i<=nn;i++)
    for(int j=1;j<=nn;j++)
    {
        add(i,j,i-1,j);
        add(i,j,i-1,j-1);
        add(i,j,i,j-1);
        eqs[i][j][var]+=a[i-1][j-1];
    }
    
  for(int i=0;i<var;i++) 
  {
      A[i+1][i] = 1;
      A[i+1][var] = 9;
  }
    
  for(int i=0;i<nn;i++) for(int j=0;j<nn;j++)
  {   
      for(int k=0;k<var;k++) A[var+(i*nn)+j+1][k] = -eqs[i+1][j+1][k];
      for(int k=0;k<var;k++) A[var+(i*nn)+j+1+(nn*nn)][k] = eqs[i+1][j+1][k];
      
     A[var+(i*nn)+j+1][var] = eqs[i+1][j+1][var];
     A[var+(i*nn)+j+(nn*nn)+1][var] = 9 - eqs[i+1][j+1][var];
  }
    
  db get = simplex();
      
  for(int i=0;i<=nn;i++) res[0][i] = round(X[i]);
  for(int i=1;i<=nn;i++) res[i][0] = round(X[i+nn]);
    
  for(int i=1;i<=nn;i++)
    for(int j=1;j<=nn;j++) res[i][j] = a[i-1][j-1] - res[i-1][j] - res[i][j-1] - res[i-1][j-1];
      
  for(int i=0;i<=nn;i++)
  {
    for(int j=0;j<=nn;j++)
        cout<< res[i][j];
      cout << '\n';
  }
    
  return 0;
}
