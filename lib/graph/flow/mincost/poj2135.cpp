/*
- set `MAXNODE` to maximum total numbers of node in graph, and `MAXE` to be maximum number of edges(don't forget to multiply it by 2 for reverse edges).
- set `ss` to be the source and `st` to be the sink. `st` should have the maximum number among all the nodes.
- set init value for `totalEdge` and `pnt[]` before add edges.
- use `addBi()` to add edge.
- call `mincost()` to get the totcost and totflow.
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

const int MAXN = 1005;
const int MAXM = 10005;
const int MAXNODE = MAXN;
const int MAXE = MAXM * 2 * 2;
const int INF = 1 << 29;

int n, m;
struct Edge{
    int u, v, nxt;
    int cost, cap, flow;
}   e[MAXE];
int totalEdge, pnt[MAXNODE];
int ss, st;

void addEdge(int x, int y, int z1, int z2){
    int i = totalEdge++;
    e[i].u = x;
    e[i].v = y;
    e[i].cost = z1;
    e[i].cap = z2;
    e[i].flow = 0;
    e[i].nxt = pnt[x];
    pnt[x] = i;
}

void addBi(int x, int y, int z1, int z2){
    addEdge(x, y, z1, z2);
    addEdge(y, x, -z1, 0);
}

int dis[MAXNODE];
int pre[MAXNODE];
bool inq[MAXNODE];
void mincost(int& totcost, int& totflow){
    totcost = totflow = 0;
    while (1){
        for (int i = 0;i <= st;i++) dis[i] = INF;
        for (int i = 0;i <= st;i++) inq[i] = false;
        queue<int> q;
        dis[ss] = 0;
        q.push(ss);
        inq[ss] = true;
        while (!q.empty()){
            int cx = q.front();
            q.pop();
            inq[cx] = false;
            for (int i = pnt[cx];i >= 0;i = e[i].nxt){
                int nx = e[i].v;
                if (dis[nx] > dis[cx] + e[i].cost && e[i].flow < e[i].cap){
                    dis[nx] = dis[cx] + e[i].cost;
                    pre[nx] = i;
                    if (!inq[nx]){
                        q.push(nx);
                        inq[nx] = true;
                    }
                }
            }
        }
        if (dis[st] >= INF) break;
        int curflow = INF;
        for (int i = st;i != ss;){
            int j = pre[i];
            curflow = min(curflow, e[j].cap - e[j].flow);
            i = e[j].u;
        }
        totcost += curflow * dis[st];
        totflow += curflow;
        for (int i = st;i != ss;){
            int j = pre[i];
            e[j].flow += curflow;
            e[j ^ 1].flow -= curflow;
            i = e[j].u;
        }
    }
}

void init(){
    if (scanf("%d%d", &n, &m) == EOF) exit(0);
    ss = n + 1; st = n + 2;
    totalEdge = 0;
    for (int i = 0;i <= st;i++) pnt[i] = -1;
    for (int i = 0;i < m;i++){
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        addBi(x, y, z, 1);
        addBi(y, x, z, 1);
    }
    addBi(ss, 1, 0, 2);
    addBi(n, st, 0, 2);
}

void work(){
    int c, f;
    mincost(c, f);
    printf("%d\n", c);
}

int main(){
#ifdef ACMWF
    freopen("poj2135.in", "r", stdin);
#endif
    while (1){
        init();
        work();
    }
    return 0;
}
