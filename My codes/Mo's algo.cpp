const int N = 30004;
const int M = 1e6;

int n,m,k;
int a[N];
int ans = 0;
int aa[M];

void add(int idx)
{
   if(aa[a[idx]] == 0) ans++;
   aa[a[idx]]++;
}

void remove(int idx)
{
   aa[a[idx]]--;
   if(aa[a[idx]] == 0) ans--;
}

int get_answer()
{
   return ans;   
}

int block_size = 170;

struct Query {
    int l, r, idx;
    bool operator<(Query other) const
    {
        return make_pair(l / block_size, r) <
               make_pair(other.l / block_size, other.r);
    }
};

vector<int> mo(vector<Query> & queries) {
    vector<int> answers(queries.size());
    sort(queries.begin(), queries.end());
    
    int cur_l = 0;
    int cur_r = -1;
  
   for (Query q : queries) {
        while (cur_l > q.l) {
            cur_l--;
            add(cur_l);
        }
        while (cur_r < q.r) {
            cur_r++;
            add(cur_r);
        }
        while (cur_l < q.l) {
            remove(cur_l);
            cur_l++;
        }
        while (cur_r > q.r) {
            remove(cur_r);
            cur_r--;
        }
       
        answers[q.idx] = get_answer();
    }
    return answers;
}
