//Amanda Yun, akyun, 1903241, pa1
#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include <assert.h>
#include <stdbool.h>



typedef struct NodeObj* Node;

typedef struct NodeObj{
	Node prev;
	ListElement data;
	Node next;
	
} NodeObj;

typedef struct ListObj{
	Node front;
	Node cursor;
	Node back;
	int index;
	int length;
} ListObj;

Node newNode(ListElement data){
	Node N = malloc(sizeof(NodeObj));
	assert(N!=NULL);
	N->data = data;
	N->next = NULL;
	N->prev = NULL;
	
	return(N);
}

List newList(void){
	List L = malloc(sizeof(ListObj));
	assert(L!=NULL);
	
	
	L->front = L->back = NULL;
	L->length = 0;
	L->cursor = NULL;
	L->index = -1;
	
	return(L);
}



void freeNode(Node *pN){
	if(pN!=NULL && *pN!=NULL){
		free(*pN);
		*pN=NULL;
	}
}



int isEmpty(List L){
	if(L==NULL){
		printf("List error: calling isEmpty() on a NULL list reference\n");
		exit(EXIT_FAILURE);
	}
	
	if(L->length==0){
		return 1;
	}
	
	return 0;
}



void printList(FILE* out, List L){
	Node N = NULL;
	if(L==NULL){
		printf("Queue Error: calling printQueue() on NULL Queue reference\n");
		exit(EXIT_FAILURE);
	}
	
	for(N=L->front; N!=NULL; N=N->next){
		fprintf(out, "%d ", N->data);
	}
	
	fprintf(out, "\n");
	
}

bool equals(List A, List B){
	if(A==NULL || B==NULL){
		printf("Queue Error: calling equals() on NULL Queue reference\n");
		exit(EXIT_FAILURE);
	}
	
	bool eq;
	Node N, M;
	
	eq = (A->length==B->length);
	
	N = A->front;
	M = B->front;
	
	while(eq && N!=NULL){
		eq = (N->data==M->data);
		N = N->next;
		M = M->next;
	}
	
	return eq;
}

int length(List L){
	
	if(L==NULL){
		printf("List Error: calling length() when List is NULL\n");
		exit(EXIT_FAILURE);
	}
	
	return L->length;
}


int index(List L){
	if(L==NULL){
		printf("List Error: calling index() when List is NULL\n");
		exit(EXIT_FAILURE);
	}
	
	return L->index;
}


int front(List L){
	if(L==NULL){
		printf("List Error: calling getFront() on a NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	
	if(isEmpty(L)){
		printf("List error: calling Dequeue() on an empty List\n");
		exit(EXIT_FAILURE);
	}
	
	
	return(L->front->data);
}

int back(List L){
	if(L==NULL){
		printf("List Error: calling back() when List is NULL\n");
		exit(EXIT_FAILURE);
	}
	if(L->length==0){
		printf("List Error: calling back() on empty list\n");
		exit(EXIT_FAILURE);
	}
	return L->back->data;
	
}

int get(List L){
	if(L==NULL){
		printf("List Error: calling get() when List is NULL\n");
		exit(EXIT_FAILURE);
	}
	
	if(L->cursor == NULL){
		printf("List Error: calling get() with undefined cursor\n");
		exit(EXIT_FAILURE);
	}
	
	return L->cursor->data;
}


void append(List L, int x){
	if(L==NULL){
		printf("List Error: calling append() on a NULL list\n");
		exit(EXIT_FAILURE);
	}	
	
	Node N = newNode(x);
	
	if(L->length==0){
		L->front = L->back = N;
	}else{
		N->prev = L->back;
		L->back->next = N;
		
		L->back = N;
	}
	
	L->length++;
	
}


void prepend(List L, int x){
	if(L==NULL){
		printf("List Error: calling append() on a NULL list\n");
		exit(EXIT_FAILURE);
	}	
	
	Node N = newNode(x);
	
	if(L->length==0){
		L->front = L->back = N;
	}else{
		L->front->prev = N;
		N->next = L->front;
		
		L->front = N;
	}
	
	L->length++;
	
	if(L->cursor!=NULL){
		L->index++;
	}
		
	
}


void deleteBack(List L){
	if(L==NULL){
		printf("List error: calling deleteBack() on a NULL list reference\n");
		exit(EXIT_FAILURE);
	}
	
	//check if there's even anything to dequeue
	if(isEmpty(L)){
		printf("List error: calling deleteBack() on an empty List\n");
		exit(EXIT_FAILURE);
	}
	if(L->cursor==L->back){
		L->cursor=NULL;
		L->index = -1;
	}
	
	Node freeMe = L->back;
	
	if(length(L)==1){
		L->front = L->back = NULL;
	}else{
		L->back->prev->next = NULL;
		L->back = L->back->prev;
	}
	
	
	
	
	L->length--;

	freeNode(&freeMe);
	
}

void deleteFront(List L){
	if(L==NULL){
		printf("List Error: calling deleteFront() when List is NULL\n");
		exit(EXIT_FAILURE);
	}
	
	if(L->cursor == L->front){
		L->cursor = NULL;
		L->index = -1;
	}else {
		L->index--;
	}
	
	Node freeMe = L->front;
	
	if(length(L)==1){
		L->front = L->back = NULL;
	}else{
		L->front->next->prev = NULL;
		L->front = L->front->next;
	}
	

	
	freeNode(&freeMe);
	L->length--;
	
}

void clear(List L){
	while(length(L)>0){
		deleteBack(L);
	}
}

void set(List L, int x){
	if(L==NULL){
		printf("List Error: calling set() when List is NULL\n");
		exit(EXIT_FAILURE);
	}
	if(L->cursor==NULL){
		printf("List Error: calling set() with an undefined cursor\n");
		exit(EXIT_FAILURE);
	}
	
	L->cursor->data = x;
}

void moveFront(List L){
	if(L==NULL){
		printf("List Error: calling moveFront() when List is NULL\n");
		exit(EXIT_FAILURE);
	}
	if(length(L)==0){
		return;
	}

	
	L->cursor= L->front;
	L->index=0;

}

void moveBack(List L){
	if(L==NULL){
		printf("List Error: calling set() when List is NULL\n");
		exit(EXIT_FAILURE);
	}
	
	if(length(L)==0){
		printf("List Error: calling set() when List is empty\n");
		exit(EXIT_FAILURE);
	}
	
	L->cursor = L->back;
	L->index = L->length-1;

}
void movePrev(List L){
	if(L->index<0){
		printf("Index Error: calling movePrev() when cursor is not defined\n");
		exit(EXIT_FAILURE);
	}
	
	
	if(L->index==0){
		L->cursor = NULL;
		L->index = -1;
	}else{
		L->cursor = L->cursor->prev;
		L->index--;
	}
}

void moveNext(List L){
	if(L->index<0){
		printf("Index Error: calling moveNext() when cursor is not defined\n");
		exit(EXIT_FAILURE);
	}
	
	if(L->cursor==L->back){
		L->cursor = NULL;
		L->index = -1;
	}else{
		
		L->cursor = L->cursor->next;
		L->index++;
	}
	
	
}


void insertBefore(List L, int x){
	
	
	if(L==NULL){
		printf("Index Error: calling insertBefore() on NULL list\n");
		exit(EXIT_FAILURE);
	}
	
	if(L->cursor==NULL){
		printf("Index Error: calling insertBefore() when cursor is not defined\n");
		exit(EXIT_FAILURE);
		
	}
	
	
	if(L->cursor == L->front){
		prepend(L, x);
	}else{
		Node N = newNode(x);
		
		N->prev = L->cursor->prev;
		N->next = L->cursor;
		L->cursor->prev->next = N;
		L->cursor->prev = N;

		
		L->index++;
		L->length++;
	}
	
}

void insertAfter(List L, int x){
	
	if(L==NULL){
		printf("Index Error: calling insertBefore() on NULL list\n");
		exit(EXIT_FAILURE);
	}
	
	if(L->cursor==NULL){
		printf("Index Error: calling insertBefore() when cursor is not defined\n");
		exit(EXIT_FAILURE);
		
	}
	
	if(L->cursor==L->back){
		append(L, x);
	}else{
		Node N = newNode(x);
		
		N->next = L->cursor->next;
		N->prev = L->cursor;
		L->cursor->next->prev = N;
		L->cursor->next = N;
		
		L->length++;
		
	}

}

void delete(List L){
	if(L->index<0){
		printf("List error: calling delete() when cursor is undefined");
		exit(EXIT_FAILURE);
	}
	
	if(L->length<=0){
		printf("List error: calling delete() on an empty list");
		exit(EXIT_FAILURE);
	}
	
	if(L==NULL){
		printf("List error: calling delete() on a NULL list");
		exit(EXIT_FAILURE);
	}
	
	if(length(L)==1){
		L->front = L->back = NULL;
		L->length--;
	}else if(L->cursor==L->front){
		deleteFront(L);
	}else if(L->cursor == L->back){
		deleteBack(L);
	}else{
		Node freeMe = L->cursor;
		L->cursor->prev->next = L->cursor->next;
		L->cursor->next->prev = L->cursor->prev;
		
		L->length--;
		free(freeMe);
	}
	
	
	L->cursor = NULL;
	L->index = -1;
	
}


List copyList(List L){
	List K = newList();
	Node N = NULL;
	if(L==NULL){
		printf("Queue Error: calling copyList() on NULL Queue reference\n");
		exit(EXIT_FAILURE);
	}
	
	for(N=L->front; N!=NULL; N=N->next){
		append(K, N->data);
	}
	
	return K;
	
}


void freeList(List* pL){
	if(pL==NULL){
		printf("ListError: calling freeList() on a NULL list\n");
		exit(EXIT_FAILURE);
	}
	clear(*pL);
	free(*pL);
	*pL= NULL;

}

	