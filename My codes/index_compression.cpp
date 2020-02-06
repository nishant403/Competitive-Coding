void compress(vector<int> & a)
{
    int n = a.size();
    vector<pii> b(n);
    f(i,n) b[i].F = a[i],b[i].S = i;
    
    sort(b.begin(),b.end());
    f(i,n) a[b[i].S] = i;
    f(i,n-1) if(b[i].F == b[i+1].F) a[b[i+1].S] = a[b[i].S];
    
    //return b if you want to get back original value from the index
}
