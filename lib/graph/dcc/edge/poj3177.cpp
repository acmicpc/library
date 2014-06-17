/*
- edge-dcc is a sub-graph that, remove any edge of it, it's still connected.
- one node can ONLY belong to one edge-dcc.
*/
#include <map>
#include <set>
#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 5005;

int n, m;
vector<pair<int, int> > adj[MAXN];

void init(){
    if (scanf("%d%d", &n, &m) == EOF) exit(0);
    for (int i = 1;i <= n;i++) adj[i].clear();
    while (m--){
        int x, y;
        scanf("%d%d", &x, &y);
        adj[x].push_back(make_pair(y, m));
        adj[y].push_back(make_pair(x, m));
    }
}

int num[MAXN], low[MAXN], id[MAXN], totDcc, stamp;
int stk[MAXN], stkTop;
void dfs(int x, int fa = -1){
    num[x] = low[x] = stamp++;
    stk[stkTop++] = x;
    for (int i = 0;i < (int)adj[x].size();i++){
        int nx = adj[x][i].first, ny = adj[x][i].second;
        if (num[nx] < 0){
            dfs(nx, ny);
            low[x] = min(low[x], low[nx]);
        }
        else if (ny != fa){
            low[x] = min(low[x], num[nx]);
        }
    }
    if (num[x] == low[x]){
        while (1){
            int cur = stk[--stkTop];
            id[cur] = totDcc;
            if (cur == x) break;
        }
        totDcc += 1;
    }
}

int deg[MAXN];
void work(){
    for (int i  = 1;i <= n;i++){
        num[i] = -1;
        low[i] = -1;
    }
    stamp = stkTop = totDcc = 0;
    for (int i = 1;i <= n;i++){
        if (num[i] < 0) dfs(i);
    }
    for (int i = 0;i < totDcc;i++) deg[i] = 0;
    int ans = 0;
    for (int i = 1;i <= n;i++){
        for (int j = 0;j < (int)adj[i].size();j++){
            int k = adj[i][j].first;
            if (id[i] != id[k]){
                deg[id[i]] += 1;
                deg[id[k]] += 1;
            }
        }
    }
    for (int i = 0;i < totDcc;i++){
        if (deg[i] == 2) ans += 1;
    }
    printf("%d\n", (ans + 1) / 2);
}

int main(){
#ifdef ACMWF
    freopen("poj3177.in", "r", stdin);
#endif
    int t = 0;
    while (1){
        init();
        work();
    }
    return 0;
}
