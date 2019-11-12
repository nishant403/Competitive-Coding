#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ff first
#define ss second
//Manacher's Algorithm
//Longest Pallidromic Sequence

string s;

pair<string , ll > manacheralgo()
{
    ll wr = 1;
    ll c = 1;
    ll n = s.size();
    vector<ll> ans(n+5,1);
    for(ll i=1;i<n-1;i++)
    {
        ll m = c - (i-c);
        if( wr > i ) ans[i] = min( wr - i , ans[m] );
        while( i-ans[i] >=0 && i+ans[i]<n && s[i+ans[i]] == s[i-ans[i]])
            ans[i]++;
        if(i + ans[i] > wr )
        {
            wr = i+ans[i]-1;
            c = i;
        }
    }
    ll maxi = 1;
    for(ll i=1;i<n-1;i++)
            if(ans[i] > maxi)
                maxi = ans[i] , c = i;
    string jt;
    //cout << s << endl;
    //cout << c << " " << maxi << endl;
    for(ll i=c-maxi+1;i<c+maxi;i++)
        if(s[i]!='$')
            jt += s[i];
        return {jt,(2*maxi-1)/2};
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>s;
    string t;
    for(ll i=0;i<s.size();i++)
        t += '$' , t+=s[i];
    t += '$';
    s = t;
       pair<string ,ll> p = manacheralgo();
    cout << p.ff << " " << p.ss << endl;
}