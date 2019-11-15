#include <stdio.h> 
#include <stdlib.h> 
#define MAX_VERTEX_NUM 20//最大顶点数 
#define MAX_EDGE_NUM 40 //最大边数
#define OK 1
#define ERROR 0
typedef int InfoType;
typedef int VertexType;
typedef int Status;
enum Boolean{FALSE,TRUE};
Boolean visited[MAX_VERTEX_NUM]; //访问标志矢量数组 

typedef struct ArcNode{
	int adjvex;//边的邻接顶点 
	struct ArcNode *nextarc;//下一条边指针 
	InfoType *info;//权值类型 
} ArcNode;
typedef struct VNode{
	VertexType data;//顶点信息 
	ArcNode *firstarc; //该顶点邻接的一条边 
}VNode,AdjList[MAX_VERTEX_NUM];
typedef struct{
	AdjList vertices;
	int vexnum,arcnum;
	int Kind;
}ALGraph;

Status LocateVex(ALGraph &G,int v){
	int k,n;
	for(k=0;k<G.vexnum;k++){
		if(G.vertices[k].data==v){
			n=k;  break;
		}
	}
	return n;
}

Status Build_AdjList(ALGraph &G){
	int v,v1,v2,i,j;
	ArcNode *q,*p;
	printf("请输入图的顶点数和边数：\n");
	scanf("%d%d",&G.vexnum,&G.arcnum);
	if(G.vexnum<0) return ERROR;
	//scanf("%d",&G.arcnum);
	if(G.arcnum<0) return ERROR;
	for(v=0;v<G.vexnum;v++){
		printf("顶点V%d：\n",v);
		scanf("%d",&G.vertices[v].data);
		G.vertices[v].firstarc=NULL;
	}
		for(v=1;v<=G.arcnum;v++)
	{	printf("请输入边的两个邻接顶点（空格隔开）：\n");
		scanf("%d%d",&v1,&v2);
	if((i=LocateVex(G,v1))<0)	return ERROR;
	if((j=LocateVex(G,v2))<0)	return ERROR;
	p=(ArcNode*)malloc(sizeof(ArcNode));
	if(!G.vertices[i].firstarc)	
		G.vertices[i].firstarc=p;
	else{
		for(q=G.vertices[i].firstarc;q->nextarc!=NULL;q=q->nextarc);
		q->nextarc=p;
	}
	p->adjvex=j;
	p->nextarc=NULL;
	}
	return OK;
}

Status printelem(VertexType d){
printf("V%d->",d);
return OK;	
}
Status(*VisitFunc)(VertexType d);
void DFS(ALGraph &G,int v){
	ArcNode *w;
	visited[v]=TRUE;
//	VisitFunc(v);
	VisitFunc(G.vertices[v].data);
	for(w=G.vertices[v].firstarc;w;w=w->nextarc) 
		if(!visited[w->adjvex]) DFS(G,w->adjvex);
}

void DFSTreaverse(ALGraph G,Status (*Visit)(VertexType d)){
	VisitFunc=Visit;
	int v,n;
	for(v=0;v<G.vexnum;++v) visited[v]=FALSE;
	printf("请输入遍历起始顶点：\n");
	scanf("%d",&n);
	printf("深度优先遍历点顺序：\n");
	DFS(G,n-1);
	for(v=0;v<G.vexnum;++v) 
		if(!visited[v]) DFS(G,v);
	}  
	
int main(){
	ALGraph G;
	Build_AdjList(G);
	DFSTreaverse(G,printelem);
	printf("\n");
	return 0;
}

