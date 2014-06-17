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

int n, m;
vector<pair<int, int> > adj[MAXN];

void init(){
    if (scanf("%d%d", &n, &m) == EOF) exit(0);
    for (int i = 1;i <= n;i++) adj[i].clear();
    for (int i = 0;i < m;i++){
        int x, y;
        scanf("%d%d", &x, &y);
        adj[x].push_back(make_pair(y, i));
        adj[y].push_back(make_pair(x, i));
    }
}

int num[MAXN], low[MAXN], stamp;
vector<int> ans;
void dfs(int x, int fa = -1){
    num[x] = low[x] = stamp++;
    for (int i = 0;i < (int)adj[x].size();i++){
        int nx = adj[x][i].first, ny = adj[x][i].second;
        if (num[nx] < 0){
            dfs(nx, ny);
            low[x] = min(low[x], low[nx]);
            if (low[nx] > num[x]) ans.push_back(ny + 1);
        }
        else if (ny != fa){
            low[x] = min(low[x], num[nx]);
        }
    }
}

void work(){
    for (int i  = 1;i <= n;i++){
        num[i] = -1;
        low[i] = -1;
    }
    stamp = 0;
    ans.clear();
    for (int i = 1;i <= n;i++){
        if (num[i] < 0) dfs(i);
    }
    sort(ans.begin(), ans.end());
    printf("%d\n", (int)ans.size());
    for (int i = 0;i < (int)ans.size();i++){
        if (i) printf(" ");
        printf("%d", ans[i]);
    }
    if ((int)ans.size()) printf("\n");
}

int main(){
#ifdef ACMWF
    freopen("zoj2588.in", "r", stdin);
#endif
    int T, t = 0;
    scanf("%d", &T);
    while (T--){
        init();
        if (t++) printf("\n");
        work();
    }
    return 0;
}
