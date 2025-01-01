#include <stdio.h>
#include <stdlib.h>

#define MAX 500
typedef struct edge {
    struct edge* next_edge;
    int weight;
    int point_num;
} edge;

typedef struct vertex{
    int num;
    edge* first_edge;
}vertex;

typedef struct graph{
    int vertex_num;
    int edge_num;
    vertex vertices[MAX];
}graph;

void add_edge(graph* g,int start,int end,int weight1){
    edge* new=(edge*)malloc(sizeof(edge));
    edge*p=g->vertices[start].first_edge;
    new->point_num=end;
    new->weight=weight1;
    if(p!=NULL){
        while(p->next_edge!=NULL){
        p=p->next_edge;
        }
        p->next_edge=new;
        new->next_edge=NULL;
    }
    else{
        p=new;
        new->next_edge=NULL;
    } 
}
int DijstraDATA[MAX];
void Dijstra(graph *g,int a){
    int* visited=(int*)malloc(sizeof(int)*g->vertex_num);
    int i=0;
    int count=0;
    for(i=0;i<g->vertex_num;i++){
        DijstraDATA[i]=10000000;
    }
    for(i=0;i<g->vertex_num;i++){
        visited[i]=0;
    }
    visited[a]=1;count++;
    edge *p=g->vertices[a].first_edge;
    int min=1000000;
    int minindex=-1;
    while(p!=NULL){
        DijstraDATA[p->point_num]=p->weight;
        if(p->weight<min){
            min=p->weight;
            minindex=p->point_num;
        }
        p=p->next_edge;
    }
    visited[minindex]=1;
    count++;
    while(count!=g->vertex_num){
        p=g->vertices[minindex].first_edge;
        while(p!=NULL){
            if(visited[p->point_num]==0&&DijstraDATA[p->point_num]>DijstraDATA[minindex]+p->weight){
                    DijstraDATA[p->point_num]=DijstraDATA[minindex]+p->weight;
            }
            p=p->next_edge;
        }
        min=1000000;
        minindex=-1;
        for(i=0;i<g->vertex_num;i++){
            if(visited[i]==0&&DijstraDATA[i]<min){
                min=DijstraDATA[i];
                minindex=i;
            }
        }
        visited[minindex]=1;
        count++;
    }
}

int main(){
    int m,n,p;
    graph *g=(graph*)malloc(sizeof(graph));
    int i=0;
    for(i=0;i<MAX;i++){
        g->vertices[i].first_edge=NULL;
    }
    scanf("%d %d %d",&m,&n,&p);
    g->vertex_num=m;
    g->edge_num=n;
    i=0;
    while(i<=n){
        int a,b,c,d;
        scanf("%d %d %d %d",&a,&b,&c,&d);

        add_edge(g,a,b,c);
        i++;
        if(d==1){
            add_edge(g,b,a,c);
            i++;
        }
    }
    int k;
    scanf("%d\n",&k);
    int *numqueue=(int*)malloc(sizeof(int)*k);
    for(i=0;i<k;i++){
        int j;
        scanf("%d\n",&j);
        numqueue[i]=j;
    }
    for(i=0;i<k;i++){
        Dijstra(g,p);
        printf("%d",DijstraDATA[numqueue[i]]);
        printf(" ");
    }
    return 0;
}