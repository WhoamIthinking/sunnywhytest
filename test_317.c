#include <stdio.h>

#define MAXN 100

int maze[MAXN][MAXN];
int weight[MAXN][MAXN];
int visited[MAXN][MAXN];
int n, m, t;
int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int is_valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && !visited[x][y]&&maze[x][y]!=1;
}

int max=-99999;
void dfs(int x, int y, int weights) {
    if (x == n - 1 && y == m - 1) {
        if(max<weights+weight[x][y]){
            max=weights+weight[x][y];
        }
        return;
    }
    visited[x][y] = 1;
    weights+=weight[x][y];
    for (int i = 0; i < 4; i++) {
        int nx = x + directions[i][0];
        int ny = y + directions[i][1];
        if (is_valid(nx, ny)) {
           dfs(nx,ny,weights);
        }
    }
    visited[x][y] = 0;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &maze[i][j]);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &weight[i][j]);
        }
    }
    dfs(0,0,0);
    printf("%d\n",max);
    return 0;
}