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
int f[MAXN][MAXN];

void init(){
    if (scanf("%d%d", &n, &m) == EOF) exit(0);
    for (int i = 0;i < n;i++){
        for (int j = 0;j < n;j++){
            f[i][j] = INF;
        }
        f[i][i] = 0;
    }
    while (m--){
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        f[x][y] = f[y][x] = min(f[x][y], z);
    }
}

int d[MAXN];
bool v[MAXN];
void work(){
    int s, t;
    scanf("%d%d", &s, &t);
    for (int i = 0;i < n;i++) d[i] = INF;
    for (int i = 0;i < n;i++) v[i] = false;
    d[s] = 0;
    int lst = s;
    for (int i = 1;i < n;i++){
        for (int j = 0;j < n;j++) d[j] = min(d[j], d[lst] + f[lst][j]);
        v[lst] = true;
        for (int j = 0;j < n;j++){
            if (!v[j] && (v[lst] || d[j] < d[lst])) lst = j;
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
