//Amanda Yun, akyun, 1903241, pa3
#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"
#include <assert.h>
#include <stdbool.h>


typedef struct GraphObj{
	List* adj;
	int* color;
	int* parent;
	int* discover;
	int* finish;
	
	
	int order;
	int size;
//	int source;
	
	
}GraphObj;



Graph newGraph(int n){
	
	if(n<1){
		printf("Graph error: calling newGraph when number of vertices is less than 1/n");
		exit(EXIT_FAILURE);
	}
	Graph G = malloc(sizeof(GraphObj));
	assert(G!=NULL);
	
	
	G->order = n;
	G->size= 0;
	//G->source = NIL;
		
	//white = 0, grey = 1, black = 2
	
	G->color = malloc(sizeof(int)*(n+1));
	G->parent = malloc(sizeof(int)*(n+1));
	G->discover = malloc(sizeof(int)*(n+1));
	G->finish = malloc(sizeof(int)*(n+1));
	G->adj = malloc(sizeof(List)*(n+1));

	for(int i = 1; i<=n; i++){
		G->adj[i] = newList();
		G->color[i] =  0;
		G->parent[i] = NIL;
		G->discover[i] = UNDEF;
		G->finish[i] = UNDEF;
		
	}
		
	
	return(G);
	
}


void freeGraph(Graph* pG){
	int n;
	if(pG==NULL){
		printf("Graph error: calling freeGraph() on a NULL Graph\n");
		exit(EXIT_FAILURE);
	}
	if(*pG==NULL){
		printf("Graph error: calling freeGraph() on a NULL pointer to Graph\n");
		exit(EXIT_FAILURE);
	}
	
	n = (*pG)->order;
	for(int i=1; i<n+1; i++){
		freeList(&(*pG)->adj[i]);
	}
	
	free((*pG)->color);
	free((*pG)->adj);
	free((*pG)->discover);
	free((*pG)->finish);
	free((*pG)->parent);
	
	free(*pG);
}




int getOrder(Graph G){
	if(G==NULL){
		printf("Graph error: calling getOrder on NULL Graph\n");
		exit(EXIT_FAILURE);
	}
	return G->order;
}

int getSize(Graph G){
	if(G==NULL){
		printf("Graph error: calling getSize on NULL Graph\n");
		exit(EXIT_FAILURE);
	}
	return G->size;
}

int getParent(Graph G, int u){
	if(G==NULL){
		printf("Graph error: calling getParent on NULL Graph\n");
		exit(EXIT_FAILURE);
	}
	if(u<1|| u>getOrder(G)){
		printf("Bounds error: calling getParent with parameters that are out of range\n");
		exit(EXIT_FAILURE);
	}
	return G->parent[u];
}

int getDiscover(Graph G, int u){
	if(G==NULL){
		printf("Graph error: calling getDiscover on NULL Graph\n");
		exit(EXIT_FAILURE);
	}
	if(1>u || u>getOrder(G)){
		printf("Bounds error: calling getDiscover with parameters that are out of range\n");
		exit(EXIT_FAILURE);
	}
	
	return G->discover[u];
}

int getFinish(Graph G, int u){
	if(G==NULL){
		printf("Graph error: calling getFinish on NULL Graph\n");
		exit(EXIT_FAILURE);
	}
	if(1>u || u>getOrder(G)){
		printf("Bounds error: calling getFinish with parameters that are out of range\n");
		exit(EXIT_FAILURE);
	}
	
	return G->finish[u];
}





void addArc(Graph G, int u, int v){
	if(G==NULL){
		printf("Graph error: calling addArc on NULL Graph\n");
		exit(EXIT_FAILURE);
	}
	if(u<1 || u>getOrder(G)){
		printf("Bounds error: calling addArc with parameters that are out of range\n");
		exit(EXIT_FAILURE);
	}
	if(v<1|| v>getOrder(G)){
		printf("Bounds error: calling addArc with parameters that are out of range\n");
		exit(EXIT_FAILURE);
	}
	
	//check if arc is already there?
	
	
	
	if(length(G->adj[u])==0){
		append(G->adj[u], v);
	}else{
		moveFront(G->adj[u]);
		if(get(G->adj[u])==v){
			return;
		}
		while(get(G->adj[u])<=v){
			if(get(G->adj[u])==v){
				return;
			}
			moveNext(G->adj[u]);
			if(index(G->adj[u])<0){
				break;
			}
		}

		if(index(G->adj[u])<0){
			append(G->adj[u], v);
		}else{
			insertBefore(G->adj[u], v);
		}
	}
	
	G->size++;
	
}

void addEdge(Graph G, int u, int v){
	if(G==NULL){
		printf("Graph error: calling addEdge() on a NULL Graph/n");
		exit(EXIT_FAILURE);
	}
	if(u<1 || u>getOrder(G)){
		printf("Source error: calling getPath() when u is out of range");
		exit(EXIT_FAILURE);
	}
	if(v<1 || v>getOrder(G)){
		printf("Source error: calling getPath() when v is out of range");
		exit(EXIT_FAILURE);
	}
	
	
	//for u
	//append(G->neighbors[u], v);
	//moveFront(G->neighbors[u]);
	if(length(G->adj[u])==0){
		append(G->adj[u], v);
	}else{
		moveFront(G->adj[u]);
		while(get(G->adj[u])<v){
			moveNext(G->adj[u]);
			if(index(G->adj[u])<0){
				break;
			}
		}
		
		if(index(G->adj[u])==-1){
			append(G->adj[u], v);
		}else{
			insertBefore(G->adj[u], v);
		}
		
		
	}
	
	
	//for v
	//append(G->neighbors[v], u);
	//moveFront(G->neighbors[v]);
	if(length(G->adj[v])==0){
		append(G->adj[v], u);
	}else{
		moveFront(G->adj[v]);
		while(get(G->adj[v])<u){
			moveNext(G->adj[v]);
			if(index(G->adj[v])<0){
				break;
			}
		}
		
		if(index(G->adj[v])==-1){
			append(G->adj[v], u);
		}else{
			insertBefore(G->adj[v], u);
		}
	}
	
	
	G->size++;
	
	
	
}

void Visit(Graph G, int i, List S, int *t){
	/*
	let time be a local variable in DFS(), then pass the address of time to Visit(), making it an input-output
	variable to Visit().
	*/
	
	
	G->discover[i] = ++(*t);
	G->color[i] = 1;
	
	moveFront(G->adj[i]);
	for(int y = 1; y<=length(G->adj[i]); y++){
		int curr = get(G->adj[i]);
		if(G->color[curr] == 0){
		
			G->parent[curr] = i;
			Visit(G, curr, S, t);
		}
		moveNext(G->adj[i]);
	}
	
	G->color[i] = 2;
	G->finish[i] = ++(*t); //FIX TIME
	prepend(S, i);
	
}


void DFS(Graph G, List S){
	int time = 0;
	if(G==NULL){
		printf("Graph error: calling DFS on NULL Graph\n");
		exit(EXIT_FAILURE);
	}
	if(length(S)!=getOrder(G)){
		printf("List error: List length and order of Graph do not match\n");
		exit(EXIT_FAILURE);
	}
	
	for(int i = 1; i<=G->order; i++){
		G->color[i] = 0;
		G->parent[i] = NIL;
		G->discover[i] = UNDEF;
		G->finish[i] = UNDEF;
		time = 0;
	
	}
	
	
	
	
	
	//G->discover = 0; FIX TIME
	moveFront(S);
	for(int i = 0; i<length(S); i++){
		int x = get(S);
		if(G->color[x]== 0){
			Visit(G, x, S, &time);
		}
		moveNext(S);
		if(index(S)<0){
			break;
		}
	}
	
	int l = length(S);
	int diff = l-getOrder(G);
	
	for(int i=0; i<diff;i++){
		moveBack(S);
		deleteBack(S);
	}
	
	
	//have to delete back to get rid of old list nodes
	
}



/*
TRANSPOSE:
returns a reference to a new graph object representing the transpose of G
*/
Graph transpose(Graph G){
	if(G==NULL){
		printf("Graph error: calling transpose on NULL Graph\n");
		exit(EXIT_FAILURE);
	}
	
	Graph T = newGraph(getOrder(G));
	
	for(int i=1; i<=G->order; i++){
		if(length(G->adj[i])>0){
			moveFront(G->adj[i]);
			while(index(G->adj[i])>=0){
				int x = get(G->adj[i]);
				addArc(T, x, i);
				moveNext(G->adj[i]);
			}
		}
	}
	

	return T;
}



Graph copyGraph(Graph G){
	if(G==NULL){
		printf("Graph error: calling copyGraph on NULL Graph\n");
		exit(EXIT_FAILURE);
	}

	Graph C = newGraph(getOrder(G));
	
	for(int i = 1; i<=G->order; i++){
		if(length(G->adj[i])>0){
			moveFront(G->adj[i]);
			//append(C->adj[i], i);
			while(index(G->adj[i])>=0){
				append(C->adj[i], get(G->adj[i]));
				moveNext(G->adj[i]);
			}
		}
	}
	
	return C;
}

void printGraph(FILE* out, Graph G){
	if(G==NULL){
		fprintf(stderr, "Error in printGraph(). empty graph.\n");
		exit(EXIT_FAILURE);
	}
	
	fprintf(out, "Adjacency list representation of G:\n");
	
//	for(int i = 1; i<= G->order; i++){
//		if(length(G->adj[i])>0){
//			moveFront(G->adj[i]);
//			fprintf(out, "%d: ", i);
//			while(index(G->adj[i])>-1){
//				fprintf(out, "%d ", get(G->adj[i]));
//				moveNext(G->adj[i]);
//			}
//			fprintf(out, "\n");
//		}
//	}
	
	for(int i = 1; i<= G->order; i++){
		moveFront(G->adj[i]);
		fprintf(out, "%d: ", i);
		while(index(G->adj[i])>-1){
			fprintf(out, "%d ", get(G->adj[i]));
			moveNext(G->adj[i]);
		}
		fprintf(out, "\n");
		
	}
	
	
}

//void printPath(Graph G, int u){
//	if(G==NULL){
//		fprintf(stderr, "Error in printPath(). empty graph.\n");
//		exit(EXIT_FAILURE);
//	}
//	
//	for(int i = 1;)
//}
	
	
