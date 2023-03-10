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
	
	in = fopen("in1.txt", "r");
	out = fopen("out1.txt", "w");
	

	
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
	
	printGraph(stdout, G);
	printf("\n");
	
	
	
	
	
	
	S = newList();
	T = transpose(G);
	
	
	for(int i=1; i<=getOrder(T);i++){
		append(S, i);
	}
	DFS(G, S);
	DFS(T, S);
	
	printGraph(stdout, T);
	
//	for(int i = 1; i<=getOrder(T); i++){
//		if(getParent(T, i)!=NIL){
//			printf("parent: %d  i: %d\n", getParent(T, i), i);
//			strong++;
//		}
//	}
	
	
	List comp = newList();
	
	//from tutor notes
	moveBack(S);
	
	for(int i =1; i<=length(S); i++){
		if(index(S)>=0){
			int x = get(S);
			//append(comp, x);
			if(getParent(T, x)==NIL){
				strong++;
//				printf("Component %d: ", strong);
//				printList(stdout, comp);
//				clear(comp);
//				append(comp, x);
			}
			
			movePrev(S);
		}
	}
	
	
	
	fprintf(stdout, "G contains %d strongly connected components:\n", strong);
	moveBack(S);
	int count = 0;
	for(int i =1; i<=length(S); i++){
		if(index(S)>=0){
			int x = get(S);
			prepend(comp, x);
			if(getParent(T, x)==NIL){
				count++;
				printf("Component %d: ", count);
				printList(stdout, comp);
				clear(comp);
				//				append(comp, x);
			}
			
			movePrev(S);
		}
	}

	
	
	/*
	moveFront(comp);
	int w= get(comp);
	for(int i = 0; i<strong; i++){
		if(length(comp)>0){
			printf("%d ",getParent(T, w));
			while(getParent(T, w)!=NIL){
				printf("%d ", getParent(T, w));
				w = getParent(T, w);
			}
		}
		if(index(comp)>=0){
			moveNext(comp);
		}
	}
	
	
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
		fprintf(stdout, "Component %d: ", i+1);
		fprintf(stdout, "\n");
	}	
	
	
	*/
	freeGraph(&T);
	freeGraph(&G);
	freeList(&S);
	freeList(&comp);
	
	
	return 0;
}