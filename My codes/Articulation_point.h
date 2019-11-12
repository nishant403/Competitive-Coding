#include<bits/stdc++.h>
using namespace std;
#define ll long long int
const int N=1e6;
vector<ll> v[N],tin(N),low(N);
vector<pair<ll,ll> > ans;
map<ll,ll> S;
ll vis[N+1],timer=0;

void dfs(ll s,ll p)
{
    vis[s]=1;
    tin[s]=timer;
    low[s]=timer;
    timer++;
    
    for(auto des : v[s])
    {
        if(des==p)       continue;
        if(vis[des])     {if(S.find({des,s})==S.end())  cout<<s<<" "<<des<<endl; low[s]=min(low[s],tin[des]),S.insert({s,des});}
        else
        {
            if(S.find({des,s})==S.end())  cout<<s<<" "<<des<<endl;
             dfs(des,s);
             low[s]=min(low[s],low[des]);
            if(low[des]>tin[s]) cout<<des<<" "<<s<<endl;
            S.insert({s,des});S.insert({des,s});
        }
    }
}

