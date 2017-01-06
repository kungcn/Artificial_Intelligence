#include <stdio.h>
#include <cstdlib>
#define random(x) (rand()%x)
#define MAX_VERTEX_NUM 20

typedef struct {
    int vertexNum;
    int edgeNum;
    char vertex[MAX_VERTEX_NUM];
    int arc[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
} Graph,*PGraph;

typedef struct {
    int from;
    int to;
    int weight;
    int flag;
} ArrayNode;

void createdGraph(PGraph g) {
    int i,j;
    g->vertexNum=8;
    g->edgeNum=7;
    for(i=0;i<g->vertexNum;i++)
        g->vertex[i]='A'+i;
    for(i=0;i<g->vertexNum;i++)
        for(j=0;j<g->vertexNum;j++)
            g->arc[i][j]=0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (i == j) {
                g->arc[i][j] = 300;
            }
            if (i < j) {
                g->arc[i][j] = random(8) + 1;
            }
        }
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (i > j) {
                g->arc[i][j] = g->arc[j][i];
            }
        }
    }
}

void initTree(PGraph tree) {
    int i,j;
    tree->vertexNum=6;
    tree->edgeNum=5;
    for(i=0;i<tree->vertexNum;i++)
        tree->vertex[i]='0';
    for(i=0;i<tree->vertexNum;i++)
        for(j=0;j<tree->vertexNum;j++)
            tree->arc[i][j]=0;
}

void prim(PGraph g,PGraph tree) {
    int i,j,k;
    int index;
    ArrayNode edgeArray[MAX_VERTEX_NUM*2];
    int length=0;
    int n=1;

    tree->vertex[0]='A';
    printf("%-3c",tree->vertex[0]);
    i=0;
    while(1) {
        for(j=0;j<g->vertexNum;j++) {
            if(g->arc[i][j] > 0) {
                for(k=0;k<tree->vertexNum;k++){
                    if(tree->vertex[k] == g->vertex[j])
                        break;
                }
                if(k == tree->vertexNum){
                    edgeArray[length].from=i;
                    edgeArray[length].to=j;
                    edgeArray[length].weight=g->arc[i][j];
                    edgeArray[length].flag=0;
                    length++;
                }
            }
        }
        index=-1;
        for(j=0;j<length;j++){
            if(index == -1 && edgeArray[j].flag == 0)
                index=j;
            if(edgeArray[j].flag==0 && edgeArray[j].weight < edgeArray[index].weight)
                index=j;
        }
        tree->vertex[edgeArray[index].to]='A'+edgeArray[index].to;
        edgeArray[index].flag=1;
        tree->arc[edgeArray[index].from][edgeArray[index].to]=edgeArray[index].weight;
        tree->arc[edgeArray[index].to][edgeArray[index].from]=edgeArray[index].weight;
        for(k=0;k<length;k++){
            if(edgeArray[k].to == edgeArray[index].to)
                edgeArray[k].flag=1;
        }
        i=edgeArray[index].to;
        printf("%-3c",tree->vertex[i]);
        n++;
        if(n==g->vertexNum)
            break;
    }
}

int connected(PGraph tree,int from,int to) {
    int i,j,k;
    int vertex[MAX_VERTEX_NUM];
    int front,rear;
    if(from==to)
        return 1;
    front=rear=0;
    vertex[rear++]=from;
    while(front<=rear){
        i=vertex[front];
        for(j=0;j<tree->vertexNum;j++)
            if(tree->arc[i][j]>0){
                if(j==to)
                    return 1;
                for(k=0;k<rear;k++)
                    if(vertex[k] == j)
                        break;
                if(k==rear)
                    vertex[rear++]=j;
            }
        front++;
    }
    return 0;
}

int main() {
    Graph graph;
    Graph tree;
    createdGraph(&graph);
    initTree(&tree);
    printf("Prim:\n");
    prim(&graph,&tree);
    printf("\n");
    initTree(&tree);
}
