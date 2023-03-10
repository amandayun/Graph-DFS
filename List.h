//Amanda Yun, akyun, 1903241, pa1
#include <stdio.h>
#include <stdbool.h>


typedef int ListElement;
typedef struct ListObj* List;


//constructor and destructor
List newList(void);

void freeList(List* pL);

int isEmpty(List L);

void printList(FILE* out, List L);

bool equals(List A, List B);

int length(List L);

int index(List L);

int front(List L);

int back(List L);

int get(List L);

void append(List L, int x);

void prepend(List L, int x);

void deleteBack(List L);
void deleteFront(List L);


void clear(List L);

void set(List L, int x);

void moveBack(List L);

void moveFront(List L);
void movePrev(List L);
void moveNext(List L);
void insertBefore(List L, int x);
void insertAfter(List L, int x);
void delete(List L);

List copyList(List L);