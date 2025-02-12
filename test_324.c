#include <stdio.h>
#include <stdlib.h>

#define MAXN 100

typedef struct {
    int x, y;
} Point;

int maze[MAXN][MAXN];
int visited[MAXN][MAXN];
int steps[MAXN][MAXN];
int n, m;
int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int is_valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && maze[x][y] == 0;
}

void bfs(int start_x, int start_y) {
    Point queue[MAXN * MAXN];
    int front = 0, rear = 0;
    queue[rear++] = (Point){start_x, start_y};
    visited[start_x][start_y] = 1;
    steps[start_x][start_y] = 0;

    while (front < rear) {
        Point current = queue[front++];
        for (int i = 0; i < 4; i++) {
            int nx = current.x + directions[i][0];
            int ny = current.y + directions[i][1];
            if (is_valid(nx, ny) && !visited[nx][ny]) {
                queue[rear++] = (Point){nx, ny};
                visited[nx][ny] = 1;
                steps[nx][ny] = steps[current.x][current.y] + 1;
            }
        }
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

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j != 0) {
                printf(" ");
            }
            if (visited[i][j]) {
                printf("%d", steps[i][j]);
            } else {
                printf("-1");
            }
        }
        printf("\n");
    }

    return 0;
}