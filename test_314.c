#include <stdio.h>

#define MAXN 100

int maze[MAXN][MAXN];
int visited[MAXN][MAXN];
int n, m, t;
int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int is_valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && maze[x][y] == 0 && !visited[x][y];
}

int dfs(int x, int y, int steps) {
    if (x == n - 1 && y == m - 1) {
        return steps == t;
    }
    if (steps > t) {
        return 0;
    }
    visited[x][y] = 1;
    for (int i = 0; i < 4; i++) {
        int nx = x + directions[i][0];
        int ny = y + directions[i][1];
        if (is_valid(nx, ny)) {
            if (dfs(nx, ny, steps + 1)) {
                return 1;
            }
        }
    }
    visited[x][y] = 0;
    return 0;
}

int main() {
    scanf("%d %d %d", &n, &m, &t);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &maze[i][j]);
        }
    }
    if (dfs(0, 0, 0)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    return 0;
}