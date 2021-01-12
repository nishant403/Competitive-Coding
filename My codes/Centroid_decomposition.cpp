
const int N = 3e5 + 10;
const int BT = 20;

int pw[N];
int msk[BT];

unordered_set<int> g[N];
int c[N];
int n;

int xo[N]; //value of xor of node[i]
int sz[N]; //size of the centroid subtree
int dep[N]; //depth of the subtree rooted at node 
int nn; //number of nodes in the centroid subtree
int ln; //number of bits we need to care about

//------Data Structure to maintain distances bitwise-------------------------

int get_log[N];

vector<bool> distances[BT];

//compute prefix sums of the data upto ln
void build(int ln)
{
    for(int i=0;i<ln;i++)
    {
        bool sum = 0;
        
        vector<bool> temp(pw[i+1],0);
        
        for(int j=0;j<pw[i]-1;j++) sum^=distances[i][j];
        
        int idd = msk[i];
        
        for(int j=0;j<pw[i+1];j++)
        {
            sum^=distances[i][idd];
            temp[idd] = sum;   
            sum^=distances[i][j];
            idd++;
            idd&=(msk[i+1]);
        }
        
        swap(distances[i],temp);
    }
}

//xor value of node at distance dist
int query(int dist)
{
    int res = 0;
    
    for(int i=0;i<ln;i++)
        if(distances[i][(dist^msk[i+1])&msk[i+1]]) res|=pw[i];
    
    return res;
}

//remove the data upto ln
void reset(int ln)
{
    for(int i=0;i<ln;i++)
        for(int j=0;j<pw[i+1];j++) distances[i][j] = 0;
}

//---------------Centroid Decomposition-------------------------
//reference : https://www.codechef.com/viewsolution/7402256

//To find sizes of nodes
void dfs1(int node,int par)
{
   sz[node] = 1;
   nn++; 
    
    for(auto it=g[node].begin();it!=g[node].end();it++)
		if(*it!=par)
			dfs1(*it,node),sz[node]+=sz[*it];
}

//Find centroid from the sizes
int dfs2(int node,int par)
{
    
	for(auto it=g[node].begin();it!=g[node].end();it++)
		if(*it!=par && sz[*it]>nn/2)
			return dfs2(*it,node);
        
	return node;
}

//Add/Remove the data of the distances  
void dfs3(int node,int par,int dist)
{
    for(int i=0;i<ln;i++) 
        distances[i][dist%pw[i+1]]=distances[i][dist%pw[i+1]]^c[node];
    
    for(auto x : g[node])
        if(x != par) dfs3(x,node,dist+1);
}

//Add the answers to the nodes
void dfs4(int node,int par,int dist)
{
    xo[node]^=query(dist);   
    
    for(auto x : g[node])
        if(x != par) dfs4(x,node,dist+1);
}

//Depth of the nodes according the centroid
void dfs5(int node,int par = -1)
{
    dep[node] = 1;
    
    for(auto x : g[node])
        if(x != par)
    {
        dfs5(x,node);
        dep[node] = max(dep[node],dep[x] + 1);
    }
}

//Main centroid decomposition function
void decompose(int root)
{
	nn = 0;
    
	dfs1(root,root);
    
    int centroid = dfs2(root,root);
	
    //calculate depths according to centroid 
    dfs5(centroid,-1);
   
    //calculate for all nodes
    ln = get_log[dep[centroid]] + 1;
    dfs3(centroid,-1,0);
    build(ln);
    dfs4(centroid,-1,0);
    reset(ln);
    
    //now remove the repeated things for subtrees
    for(auto x : g[centroid])
    {
        ln = get_log[dep[x]] + 1;
        dfs3(x,centroid,1);
        build(ln);
        dfs4(x,centroid,1);
        reset(ln);
    }
    
    //remove centroid from the tree and recurse
    for(auto x : g[centroid])
    {
        g[x].erase(centroid);
        decompose(x);
    }
}
