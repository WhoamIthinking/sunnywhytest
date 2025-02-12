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

void bfs(int start_x, int start_y,int dx,int dy) {
    Point queue[MAXN * MAXN];
    int front = 0, rear = 0;
    queue[rear++] = (Point){start_x, start_y};
    visited[start_x][start_y] = 1;
    steps[start_x][start_y] = 0;

    while (front < rear) {
        Point current = queue[front++];
        if (current.x == dx && current.y == dy) {
            printf("%d\n", steps[current.x][current.y]);
            return;
        }
        for (int i = 0; i < 4; i++) {
            int nx1 = current.x + directions[i][0];
            int ny1 = current.y + directions[i][1];
            if (is_valid(nx1, ny1) && !visited[nx1][ny1]) {
                queue[rear++] = (Point){nx1, ny1};
                visited[nx1][ny1] = 1;
                steps[nx1][ny1] = steps[current.x][current.y] + 1;
            }
        }
    }
    printf("-1\n");
}

int main() {
    int sx,sy;
    int dx,dy;
    scanf("%d %d\n", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char a;
            scanf("%c", &a);
            if(a=='.'){
                maze[i][j]=0;
            }
            if(a=='*'){
                maze[i][j]=1;
            }
            if(a=='S'){
                maze[i][j]=0;
                sx=i;sy=j;
            }
            if(a=='T'){
                maze[i][j]=0;
                dx=i;dy=j;
            }
        }
        getchar();
    }

    bfs(sx,sy,dx,dy);
    return 0;
}