/// http://acm.wf
#include <map>
#include <set>
#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 10005;
const int MAXE = 50005;

int n, m;
vector<int> adj[MAXN];
int totalEdge, pnt[MAXN];
int stk[MAXN], stkTop;
int num[MAXN], low[MAXN], id[MAXN], stamp;
int totalScc;
vector<int> scc[MAXN];

void init(){
    if (scanf("%d%d", &n, &m) == EOF) exit(0);
    for (int i = 1;i <= n;i++) adj[i].clear();
    for (int i = 0;i < m;i++){
        int x, y;
        scanf("%d%d", &x, &y);
        adj[x].push_back(y);
    }
}

void dfs(int x){
    num[x] = low[x] = stamp++;
    stk[stkTop++] = x;
    for (int i = 0;i < (int)adj[x].size();i++){
        int nx = adj[x][i];
        if (num[nx] < 0){
            dfs(nx);
            low[x] = min(low[x], low[nx]);
        }
        else if (id[nx] < 0){
            low[x] = min(low[x], num[nx]);
        }
    }
    if (low[x] == num[x]){
        int i = totalScc++;
        scc[i].clear();
        while (1){
            int t = stk[--stkTop];
            id[t] = i;
            scc[i].push_back(t);
            if (t == x) break;
        }
    }
}

int outd[MAXN];
void work(){
    totalScc = 0;
    for (int i  = 1;i <= n;i++){
        num[i] = -1;
        id[i] = -1;
    }
    stkTop = 0;
    for (int i = 1;i <= n;i++){
        if (num[i] < 0) dfs(i);
    }
//    for (int i = 0;i < totalScc;i++){
//        for (int j = 0;j < (int)scc[i].size();j++){
//            printf("%d ", scc[i][j]);
//        }
//        printf("\n");
//    }
    int ans = 0;
    for (int i = 0;i < totalScc;i++) outd[i] = 0;
    for (int i = 1;i <= n;i++){
        for (int j = 0;j < (int)adj[i].size();j++){
            int k = adj[i][j];
            if (id[i] != id[k]){
                outd[id[i]] += 1;
            }
        }
    }
    for (int i = 0;i < totalScc;i++){
        if (outd[i] == 0){
            if (ans){
                printf("0\n");
                return;
            }
            ans += (int)scc[i].size();
        }
    }
    printf("%d\n", ans);
}

int main(){
#ifdef LATTE
    freopen("poj2186.in", "r", stdin);
#endif
    while (1){
        init();
        work();
    }
    return 0;
}
