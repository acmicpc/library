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

void work(){
    for (int k = 0;k < n;k++){
        for (int i = 0;i < n;i++){
            for (int j = 0;j < n;j++){
                f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
            }
        }
    }
    int s, t;
    scanf("%d%d", &s, &t);
    printf("%d\n", f[s][t] < INF ? f[s][t] : -1);
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
