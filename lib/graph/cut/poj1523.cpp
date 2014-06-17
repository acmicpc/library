#include <map>
#include <set>
#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 1005;
const int MAXE = MAXN * MAXN * 2;

int n;
vector<int> adj[MAXN];

void init(){
    for (int i = 0;i < MAXN;i++) adj[i].clear();
    n = 0;
    while (1){
        int x, y;
        scanf("%d", &x);
        if (x == 0) break;
        scanf("%d", &y);
        adj[x].push_back(y);
        adj[y].push_back(x);
        n = max(n, x); n = max(n, y);
    }
    if (n == 0) exit(0);
}

int num[MAXN], low[MAXN], cnt[MAXN], stamp;
void dfs(int x, int fa = -1){
    num[x] = low[x] = stamp++;
    cnt[x] = 1;
    for (int i = 0;i < (int)adj[x].size();i++){
        int nx = adj[x][i];
        if (num[nx] < 0){
            dfs(nx, x);
            low[x] = min(low[x], low[nx]);
            if (low[nx] >= num[x]) cnt[x] += 1;
        }
        else if (nx != fa){
            low[x] = min(low[x], num[nx]);
        }
    }
    if (fa < 0) cnt[x] -= 1;
//    printf("dfs %d %d %d\n", x, num[x], low[x]);
}

void work(){
    for (int i  = 1;i <= n;i++){
        num[i] = -1;
        low[i] = -1;
    }
    stamp = 0;
    for (int i = 1;i <= n;i++){
        if (num[i] < 0) dfs(i);
    }
    int tot = 0;
    for (int i = 1;i <= n;i++){
        if (cnt[i] > 1){
            printf("  SPF node %d leaves %d subnets\n", i, cnt[i]);
            tot += 1;
        }
    }
    if (!tot) printf("  No SPF nodes\n");
    printf("\n");
}

int main(){
#ifdef ACMWF
    freopen("poj1523.in", "r", stdin);
#endif
    int t = 0;
    while (1){
        init();
        printf("Network #%d\n", ++t);
        work();
    }
    return 0;
}
