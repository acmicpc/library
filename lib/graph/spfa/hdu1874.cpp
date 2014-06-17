#include <map>
#include <set>
#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 205;
const int INF = 1 << 29;

int n, m;
vector<pair<int, int> > adj[MAXN];

void init(){
    if (scanf("%d%d", &n, &m) == EOF) exit(0);
    for (int i = 0;i < n;i++) adj[i].clear();
    while (m--){
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        adj[x].push_back(make_pair(y, z));
        adj[y].push_back(make_pair(x, z));
    }
}

int d[MAXN];
bool inq[MAXN];
int q[MAXN];
void work(){
    int s, t;
    scanf("%d%d", &s, &t);
    for (int i = 0;i < n;i++) d[i] = INF;
    for (int i = 0;i < n;i++) inq[i] = false;
    d[s] = 0;
    int l = 0, r = 0;
    q[r++] = s;
    while (l != r){
        int cx = q[l++];
        inq[cx] = false;
        if (l > n) l = 0;
        for (int i = 0;i < (int)adj[cx].size();i++){
            int nx = adj[cx][i].first, nd = d[cx] + adj[cx][i].second;
            if (d[nx] > nd){
                d[nx] = nd;
                if (!inq[nx]){
                    q[r++] = nx;
                    if (r > n) r = 0;
                    inq[nx] = true;
                }
            }
        }
    }
    printf("%d\n", d[t] < INF ? d[t] : -1);
}

int main(){
#ifdef ACMWF
    freopen("hdu1874.in", "r", stdin);
#endif
    int t = 0;
    while (1){
        init();
        work();
    }
    return 0;
}
