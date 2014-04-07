/*
- set `MAXNODE` to maximum total numbers of node in graph, and `MAXE` to be maximum number of edges(don't forget to multiply it by 2 for reverse edges).
- set `ss` to be the source and `st` to be the sink. `st` should have the maximum number among all the nodes.
- set init value for `totalEdge` and `pnt[]` before add edges.
- use `addBi()` to add edge.
- call `maxflow()` to get the max flow.
*/
#include <map>
#include <set>
#include <queue>
#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 205;
const int MAXM = 205;
const int MAXNODE = MAXN;
const int MAXE = MAXM * 2;
const int INF = 1 << 29;

int n, m;
struct Edge{
    int u, v, nxt;
    int cap, flow;
}   e[MAXE];
int totalEdge, pnt[MAXNODE];
int ss, st;

void addEdge(int x, int y, int z){
    int i = totalEdge++;
    e[i].u = x;
    e[i].v = y;
    e[i].cap = z;
    e[i].flow = 0;
    e[i].nxt = pnt[x];
    pnt[x] = i;
}

void addBi(int x, int y, int z){
    addEdge(x, y, z);
    addEdge(y, x, 0);
}

int dis[MAXNODE];
int cur[MAXNODE];
int q[MAXNODE];
bool bfs(){
    for (int i = 0;i <= st;i++) dis[i] = -1;
    for (int i = 0;i <= st;i++) cur[i] = pnt[i];
    int l = 0, r = 0;
    dis[ss] = 0;
    q[r++] = ss;
    while (l < r){
        int cx = q[l++];
        for (int i = pnt[cx];i >= 0;i = e[i].nxt){
            int nx = e[i].v;
            if (dis[nx] < 0 && e[i].flow < e[i].cap){
                dis[nx] = dis[cx] + 1;
                if (nx == st) return true;
                q[r++] = nx;
            }
        }
    }
    return false;
}

int dfs(int x, int y){
    if (x == st) return y;
    for (int &i = cur[x];i >= 0;i = e[i].nxt){
        int nx = e[i].v;
        if (dis[nx] == dis[x] + 1 && e[i].flow < e[i].cap){
            int r = dfs(nx, min(y, e[i].cap - e[i].flow));
            if (r){
                e[i].flow += r;
                e[i ^ 1].flow -= r;
                return r;
            }
        }
    }
    return 0;
}

int maxflow(){
    int tot = 0;
    while (bfs()){
        while (1){
            int cur = dfs(ss, INF);
            if (cur == 0) break;
            tot += cur;
        }
    }
    return tot;
}

void init(){
    if (scanf("%d%d", &m, &n) == EOF) exit(0);
    ss = 1; st = n;
    totalEdge = 0;
    for (int i = 0;i <= st;i++) pnt[i] = -1;
    for (int i = 0;i < m;i++){
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        addBi(x, y, z);
    }
}

void work(){
    printf("%d\n", maxflow());
}

int main(){
#ifdef LATTE
    freopen("poj1273.in", "r", stdin);
#endif
    while (1){
        init();
        work();
    }
    return 0;
}
