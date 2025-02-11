#include <stdio.h>
#include <stdlib.h>

#define MAXN 100

typedef struct {
    int x, y;
} Point;

int maze[MAXN][MAXN];
int visited[MAXN][MAXN];
Point prev[MAXN][MAXN];
int n, m;
int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int is_valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && !visited[x][y] && maze[x][y] == 0;
}

void bfs(int start_x, int start_y) {
    Point queue[MAXN * MAXN];
    int front = 0, rear = 0;
    queue[rear++] = (Point){start_x, start_y};
    visited[start_x][start_y] = 1;

    while (front < rear) {
        Point current = queue[front++];
        if (current.x == n - 1 && current.y == m - 1) {
            return;
        }
        for (int i = 0; i < 4; i++) {
            int nx = current.x + directions[i][0];
            int ny = current.y + directions[i][1];
            if (is_valid(nx, ny)) {
                queue[rear++] = (Point){nx, ny};
                visited[nx][ny] = 1;
                prev[nx][ny] = current;
            }
        }
    }
}

void print_path() {
    Point path[MAXN * MAXN];
    int length = 0;
    Point current = {n - 1, m - 1};
    while (!(current.x == 0 && current.y == 0)) {
        path[length++] = current;
        current = prev[current.x][current.y];
    }
    path[length++] = (Point){0, 0};

    for (int i = length - 1; i >= 0; i--) {
        printf("%d %d\n", path[i].x+1, path[i].y+1);
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &maze[i][j]);
        }
    }

    bfs(0, 0);
    print_path();

    return 0;
}