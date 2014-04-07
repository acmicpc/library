#include <set>
#include <queue>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 55;
const int MAXM = 105;
const int MAXL = 15;
const int MAXNODE = 1005;
const int MAXS = 26;

int n, m;
int id[130];
int chd[MAXNODE][MAXS];
int fail[MAXNODE];
int val[MAXNODE];
int sz, rt;
char s[MAXN];

void prep(){
    for (int i = 0;i < MAXS;i++) id[i + 'a'] = i;
}

inline int newNode(){
    memset(chd[sz], 0, sizeof(chd[sz]));
    val[sz] = 0;
    return sz++;
}

void ins(char *s, int k){
    int cur = rt;
    for (int i = 0;s[i];i++){
        int j = id[s[i]];
        if (!chd[cur][j]) chd[cur][j] = newNode();
        cur = chd[cur][j];
    }
    val[cur] = k;
}

char a[MAXM][MAXL];
void init(){
    if (scanf("%d%d", &n, &m) == EOF) exit(0);
    if (n == 0) exit(0);
    sz = 0;
    rt = newNode();
    for (int i = 0;i < m;i++){
        scanf("%s", a[i]);
    }
    for (int i = 0;i < m;i++){
        int x;
        scanf("%d", &x);
        ins(a[i], x);
    }
}

int q[MAXNODE];
void build(){
    fail[rt] = rt;
    int l = 0, r = 0;
    for (int i = 0;i < MAXS;i++){
        int j = chd[rt][i];
        if (j){
            fail[j] = rt;
            q[r++] = j;
        }
    }
    while (l < r){
        int cx = q[l++];
        for (int i = 0;i < MAXS;i++){
            int& nx = chd[cx][i];
            if (nx){
                fail[nx] = chd[fail[cx]][i];
                val[nx] += val[fail[nx]];
                q[r++] = nx;
            }
            else{
                nx = chd[fail[cx]][i];
            }
        }
    }
}

bool cmp(char* a, char* b){
    return strlen(a) < strlen(b) || (strlen(a) == strlen(b) && strcmp(a, b) < 0);
}

int f[MAXN][MAXNODE];
char g[MAXN][MAXNODE][MAXN];
char ts[MAXN];
void work(){
    build();
    for (int i = 0;i <= n;i++){
        for (int j = 0;j < sz;j++){
            f[i][j] = -1;
        }
    }
    f[0][0] = 0;
    g[0][0][0] = 0;
    for (int i = 0;i < n;i++){
        for (int j = 0;j < sz;j++){
            if (f[i][j] >= 0){
                int l = strlen(g[i][j]);
                strcpy(ts, g[i][j]);
                ts[l + 1] = 0;
                for (int k = 0;k < MAXS;k++){
                    int nx = chd[j][k];
                    int nf = f[i][j] + val[nx];
                    ts[l] = k + 'a';
                    if (f[i + 1][nx] < nf || (f[i + 1][nx] == nf && cmp(ts, g[i + 1][nx]))){
                        f[i + 1][nx] = nf;
                        strcpy(g[i + 1][nx], ts);
                    }
                }
            }
        }
    }
    ts[0] = 0;
    int ji = 0;
    for (int i = 0;i <= n;i++){
        for (int j = 0;j < sz;j++){
            if (f[i][j] > ji || (f[i][j] == ji && cmp(g[i][j], ts))){
                ji = f[i][j];
                strcpy(ts, g[i][j]);
            }
        }
    }
    printf("%s\n", ts);
}

int main(){
#ifdef ACMWF
    freopen("hdu2296.in", "r", stdin);
#endif
    prep();
    int T, t = 0;
    scanf("%d", &T);
    while (T--){
        init();
        work();
    }
    return 0;
}
