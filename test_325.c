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
int x1;
int y1_pos;
int x2;
int y2_pos;
int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int is_valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && (maze[x][y] == 0||maze[x][y]==2);
}

void bfs(int start_x, int start_y) {
    Point queue[MAXN * MAXN];
    int front = 0, rear = 0;
    queue[rear++] = (Point){start_x, start_y};
    visited[start_x][start_y] = 1;
    steps[start_x][start_y] = 0;

    while (front < rear) {
        Point current = queue[front++];
        if (current.x == n - 1 && current.y == m - 1) {
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
            if(maze[current.x][current.y]==2){
                int x,y;
                if(current.x==x1&&current.y==y1_pos){
                    x=x2;y=y2_pos;
                }
                else{
                    x=x1;y=y1_pos;
                }
                if(!visited[x][y]){
                    queue[rear++]=(Point){x,y};
                    visited[x][y]=1;
                    steps[x][y]=steps[current.x][current.y];
                }
            }
        }
    }
    printf("-1\n");
}

int main() {
    scanf("%d %d", &n, &m);
    int flag=1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &maze[i][j]);
            if(flag==1&&maze[i][j]==2){
                x1=i;y1_pos=j;
                flag++;
            }
            else if(flag==2&&maze[i][j]==2){
                x2=i;y2_pos=j;
            }
        }
    }

    bfs(0, 0);

    return 0;
}