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
int x,y;
int directions[8][2] = {{-2, -1}, {-2, 1}, {-1, 2}, {-1, -2},{2,1},{2,-1},{1,2},{1,-2}};

int is_valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && maze[x][y] == 0;
}

int is_valid_ma(int x,int y,int x1,int y1){
    if (abs(x - x1) == 2 && abs(y - y1) == 1) {
        if (!is_valid((x + x1) / 2, y)) {
            return 0;
        }
    }
    if (abs(x - x1) == 1 && abs(y - y1) == 2) {
        if (!is_valid(x, (y + y1) / 2)) {
            return 0;
        }
    }
    return 1;
}

void bfs(int start_x, int start_y) {
    Point queue[MAXN * MAXN];
    int front = 0, rear = 0;
    queue[rear++] = (Point){start_x, start_y};
    visited[start_x][start_y] = 1;
    steps[start_x][start_y] = 0;

    while (front < rear) {
        Point current = queue[front++];
        for (int i = 0; i < 8; i++) {
            int nx = current.x + directions[i][0];
            int ny = current.y + directions[i][1];
            if (is_valid(nx, ny) && !visited[nx][ny]&& is_valid_ma(current.x,current.y,nx,ny)) {
                queue[rear++] = (Point){nx, ny};
                visited[nx][ny] = 1;
                steps[nx][ny] = steps[current.x][current.y] + 1;
            }
        }
    }
}

int main() {
    scanf("%d %d %d %d\n", &n, &m,&x,&y);
    int k;
    scanf("%d",&k);
    for (int i = 0; i < k; i++) {
        int x,y;
        scanf("%d %d",&x,&y);
        maze[x-1][y-1]=1;
    }

    bfs(x-1,y-1);

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