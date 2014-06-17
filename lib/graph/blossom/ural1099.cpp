#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

const int N = 250;

int belong[N];
int findb(int x) {
	return belong[x] == x ? x : belong[x] = findb(belong[x]);
}
void unit(int a, int b) {
	a = findb(a);
	b = findb(b);
	if (a != b) belong[a] = b;
}

int n, match[N];
vector<int> e[N];
int Q[N], rear;
int nxt[N], mark[N], vis[N];

int LCA(int x, int y) {
	static int t = 0; t++;
	while (true) {
		if (x != -1) {
			x = findb(x);
			if (vis[x] == t) return x;
			vis[x] = t;
			if (match[x] != -1) x = nxt[match[x]];
			else x = -1;
		}
		swap(x, y);
	}
}

void group(int a, int p) {
	while (a != p) {
		int b = match[a], c = nxt[b];
		if (findb(c) != p) nxt[c] = b;
		if (mark[b] == 2) mark[Q[rear++] = b] = 1;
		if (mark[c] == 2) mark[Q[rear++] = c] = 1;
		unit(a, b); unit(b, c);
		a = c;
	}
}

void aug(int s) {
	for (int i = 0; i < n; i++)
		nxt[i] = -1, belong[i] = i, mark[i] = 0, vis[i] = -1;
	mark[s] = 1;
	Q[0] = s; rear = 1;
	for (int front = 0; match[s] == -1 && front < rear; front++) {
		int x = Q[front];
		for (int i = 0; i < (int)e[x].size(); i++) {
			int y = e[x][i];
			if (match[x] == y) continue;
			if (findb(x) == findb(y)) continue;
			if (mark[y] == 2) continue;
			if (mark[y] == 1) {
				int r = LCA(x, y);
				if (findb(x) != r) nxt[x] = y;
				if (findb(y) != r) nxt[y] = x;
				group(x, r);
				group(y, r);
			}
			else if (match[y] == -1) {
				nxt[y] = x;
				for (int u = y; u != -1; ) {
					int v = nxt[u];
					int mv = match[v];
					match[v] = u, match[u] = v;
					u = mv;
				}
				break;
			}
			else {
				nxt[y] = x;
				mark[Q[rear++] = match[y]] = 1;
				mark[y] = 2;
			}
		}
	}
}

bool g[N][N];
int main(){
#ifdef ACMWF
    freopen("ural1099.in", "r", stdin);
#endif // ACMWF
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) g[i][j] = false;

	int x, y; while (scanf("%d%d", &x, &y) != EOF) {
		x--, y--;
		if (x != y && !g[x][y])
			e[x].push_back(y), e[y].push_back(x);
		g[x][y] = g[y][x] = true;
	}
	for (int i = 0; i < n; i++) match[i] = -1;
	for (int i = 0; i < n; i++) if (match[i] == -1) aug(i);
	int tot = 0;
	for (int i = 0; i < n; i++) if (match[i] != -1) tot++;
	printf("%d\n", tot);
	for (int i = 0; i < n; i++) if (match[i] > i)
		printf("%d %d\n", i + 1, match[i] + 1);
	return 0;
}
