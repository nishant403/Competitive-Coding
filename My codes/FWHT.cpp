//Problem : https://www.hackerearth.com/problem/algorithm/submatrix-queries-c33aca97/

const int MOD = 1e9 + 7;
const int N = 256;

//Fast Walsh Hadamard Transform

//XOR [  1 1 ]   //AND [ 0 1 ]  //OR  [ 1 1 ]
//    [ -1 1 ]         [ 1 1 ]        [ 1 0 ]

vector<int> FWHT(vector<int> P,bool inv)
{
    for(int len=1;2*len <=N;len<<=1)
        for(int i=0;i<N;i+=(len<<1))
        f(j,len)
    {
        int a = P[i+j];
        int b = P[i+j+len];
    
       if(inv)
       {
        P[i+j] = ((-a+b)%MOD  + MOD )%MOD ;
        P[i+j+len] = a; 
       }
       else
       {
        P[i+j] = b;
        P[i+j+len] = (a+b)%MOD; 
       }
    }
    
    return P;
}
