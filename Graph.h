//Amanda Yun, akyun, 1903241, pa3
#include <stdio.h>
#include <stdlib.h>
#include "List.h"

#define NIL -1
#define UNDEF -8

typedef struct GraphObj* Graph;

Graph newGraph(int n);
void freeGraph(Graph *pG);


int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);


void addArc(Graph G, int u, int v);
void addEdge(Graph G, int u, int v);
void DFS(Graph G, List S);

Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);


void Visit(Graph G, int i, List S, int *t);