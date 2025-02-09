#include <stdio.h>

#define MAXN 100

int maze[MAXN][MAXN];
int visited[MAXN][MAXN];
int path[MAXN*MAXN];
int bestpath[MAXN*MAXN];
int bestpathlen=0;
int n, m, t;
int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int is_valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && !visited[x][y];
}

int max=-99999;
void dfs(int x, int y, int weights,int pathlen) {
    if (x == n - 1 && y == m - 1) {
        if(max<weights+maze[x][y]){
            max=weights+maze[x][y];
            bestpathlen=pathlen;
            for(int i=0;i<bestpathlen;i++){
                bestpath[i]=path[i];
            }
            bestpath[bestpathlen]=(x*m)+y;
        }
        return;
    }
    visited[x][y] = 1;
    path[pathlen]=(x*m)+y;//相当于用一个数字就存储了x，y两个坐标
    weights+=maze[x][y];
    for (int i = 0; i < 4; i++) {
        int nx = x + directions[i][0];
        int ny = y + directions[i][1];
        if (is_valid(nx, ny)) {
           dfs(nx,ny,weights,pathlen+1);
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
    dfs(0,0,0,0);
    for(int i=0;i<=bestpathlen;i++){
        int x=bestpath[i]/m+1;
        int y=bestpath[i]%m+1;
        printf("%d %d\n",x,y);
    }
    return 0;
}