#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
#define LIM 111111

vector< vector<int> > succ(LIM);
vector< vector<int> > pred(LIM);
int n, v, m;
int semi[LIM];
int vertex[LIM];
int parent[LIM];
int dom[LIM];
vector< set<int> > bucket(LIM);

// TODO make iterative?
void dfs(int v) {
    semi[v] = ++n;
    vertex[n] = v;
    for (int nb = 0; nb < succ[v].size(); nb++) {
        int w = succ[v][nb];
        if (semi[w] == 0) {
            parent[w] = v;
            dfs(w);
        }
        pred[w].push_back(v);
    }
}

int ancestor[LIM];
int label[LIM];

void INIT() {
    for (int i = 0; i < v; i++) {
        ancestor[i] = -1;
        label[i] = i;
    }
}

void COMPRESS(int v) {
    if (ancestor[ancestor[v]] >= 0) {
        COMPRESS(ancestor[v]);
        if (semi[label[ancestor[v]]] < semi[label[v]]) {
            label[v] = label[ancestor[v]];
        }
        ancestor[v] = ancestor[ancestor[v]];
    }
}

int EVAL(int v) {
    if (ancestor[v] < 0) {
        return v;
    } else {
        COMPRESS(v);
        return label[v];
    }
}

void LINK(int v, int w) {
    ancestor[w] = v;
}

int fdom[LIM];
int fdct[LIM];

int main() {
    scanf("%d%d", &v, &m);
    for (int mm = 0; mm < m; mm++) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--, b--;
        succ[a].push_back(b);
    }

    // step 1
    for (int i = 0; i < v; i++) {
        semi[i] = 0;
    }
    dfs(0);

    INIT();

    for (int i = n; i >= 2; i--) {
        // step 2
        int w = vertex[i];
        for (int nb = 0; nb < pred[w].size(); nb++) {
            int v = pred[w][nb];
            int u = EVAL(v);
            if (semi[u] < semi[w]) semi[w] = semi[u];
        }
        bucket[vertex[semi[w]]].insert(w);
        LINK(parent[w], w);
        // step 3
        for (set<int>::iterator it = bucket[parent[w]].begin(); it != bucket[parent[w]].end(); it++) {
            int v = *it;
            int u = EVAL(v);
            dom[v] = semi[u] < semi[v] ? u : parent[w];
        }
        bucket[parent[w]].clear();
    }

    // step 4
    for (int i = 2; i <= n; i++) {
        int w = vertex[i];
        if (dom[w] != vertex[semi[w]]) dom[w] = dom[dom[w]];
    }
    dom[0] = 0;

    vector<int> res;
    int vv = v-1;
    
    while(1)
    {
        res.push_back(vv);
        if(vv == 0) break;
        vv = dom[vv];
    }
    
    sort(res.begin(),res.end());
    printf("%d\n",res.size());
    for(auto x : res) printf("%d ",x + 1);
}
