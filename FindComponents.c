//Amanda Yun, akyun, 1903241, pa2

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include <assert.h>
#include <stdbool.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
	
	int num, u, v;
	
	int strong = 0;
	
	Graph G;
	Graph T;
	List S;
	
	FILE *in, *out;
	
	
	if(argc!=3){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}
	
	in = fopen(argv[1], "r");
	if(in ==NULL){
		printf("unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	
	out = fopen(argv[2], "w");
	if(out==NULL){
		printf("unable to open file %s for writing\n", argv[2]);
		exit(1);
	}
	
	fscanf(in, "%d", &num);
	G = newGraph(num);
	
	u = 1;
	v = 1;
	
	while(u!=0 || v!=0){
		fscanf(in, "%d", &u);
		fscanf(in, "%d", &v);
		
		if(u==0 || v==0){
			break;
		}
		
		addArc(G, u, v);
		//addEdge(G, u, v);
	}
	
	printGraph(out, G);
	fprintf(out, "\n");
	
	
	
	//find strongly connected components
	S = newList();
	T = transpose(G);
	
	for(int i=1; i<=getOrder(T);i++){
		append(S, i);
	}

	DFS(G, S);
	DFS(T, S);
	
//	for(int i = 1; i<=getOrder(T); i++){
//		if(getParent(T, i)!=NIL){
//			strong++;
//		}
//	}
	
	List comp = newList();
	moveBack(S);
	
	for(int i =1; i<=length(S); i++){
		if(index(S)>=0){
			int x = get(S);
			if(getParent(T, x)==NIL){
				strong++;
			}
			
			movePrev(S);
		}
	}
	
	fprintf(out, "G contains %d strongly connected components:\n", strong);
	
	int count = 0;
	moveBack(S);
	for(int i =1; i<=length(S); i++){
		if(index(S)>=0){
			int x = get(S);
			prepend(comp, x);
			if(getParent(T, x)==NIL){
				count++;
				fprintf(out, "Component %d: ", count);
				printList(out, comp);
				clear(comp);
			}
			
			movePrev(S);
		}
	}
	
	
	
	/*
	int x = strong;
	List C = newList();
	
	for(int i=1; i<= strong; i++){
		append(C, i);
	}
	
	
	moveFront(S);
	for(int i = 1; i<=length(S); i++){
		int K = get(S);
		if(getParent(T, i)!=NIL){
			x--;
		}
		moveFront(C);
		while(get(C)<x){
			moveNext(C);
			if(index(C)<0){
				break;
			}
		}
		
		if(index(C)<0){
			append(C, x);
		}else{
			insertBefore(C, x);
		}
		
		
		
		//if x is greater than get(C) then insertAfter, else insertBefore
		
	}
		
	for(int i = 0; i<strong; i++){
		fprintf(out, "Component %d: ", i+1);
		fprintf(out, "\n");
	}	
	
	*/
	
	freeGraph(&T);
	freeGraph(&G);
	freeList(&S);
	freeList(&comp);
	
	
	return 0;
}