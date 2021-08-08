/*
 * course: CSc352
 * Author: Zengrui Luo
 * assignment: assignment8
 *
 * this assignment is used to
 * doubly-linke Int List

 */
#include <stdio.h>
#include <stdlib.h>
#include "dblListInt.h"
DblList_Int *dblList_Int__alloc(int val){
	DblList_Int *t = malloc(sizeof(DblList_Int));
	if(t != NULL){
		t->val = val;
		t->next = NULL;
		t->prev = NULL;
		return t;
	}else{
		perror("error 1");
		return NULL;
	}
}

// -------------- free() - Destructor ----------------
// Parameters: 't' pointer
//
// Frees an existing DblList_Int object.  The object must not be part of any
// list (that is, its 'next' and 'prev' must both be NULL).
//
// ERRORS:
//   - Pointer is NULL
//   - The node has non-NULL next or prev pointers.  Print error, but still
//     free the object before returning.

void dblList_Int__free(DblList_Int *t){
	if(t!=NULL){
		/*if(t->next != NULL || t->prev != NULL){
			perror("error 2");
		}*/
		free(t);
	}
	
	
}

int     dblList_Int__getVal (DblList_Int* t){
	return t->val;
}
DblList_Int *dblList_Int__getNext(DblList_Int* t){
	return t->next;
}
DblList_Int *dblList_Int__getPrev(DblList_Int* t){
	return t->prev;
}



DblList_Int *dblList_Int__getHead(DblList_Int* t){
	if(t != NULL){
		while(t->prev != NULL){
			t = t->prev;
		}
		return t;
	}else{
	 	return NULL;
	}
	
}
DblList_Int *dblList_Int__getTail(DblList_Int* t){
	if(t != NULL){
		while(t->next != NULL){
			t = t->next;
		}
		return t;
	}else{
	 	return NULL;
	}
}


void dblList_Int__addAfter(DblList_Int* t, DblList_Int* p){
	if(p==NULL||t==NULL){
		return;
	}
	p->next = t->next;
	p->prev=t;
	if(t->next!=NULL){
		t->next->prev = p;
	}
	t->next=p;
	
}


void dblList_Int__addTail(DblList_Int* t, int val){
	t = dblList_Int__getTail(t);
	if(t != NULL){
		DblList_Int* p = dblList_Int__alloc(val);
		t->next = p;
		p->prev = t;
	}
		
	
}

// ---------------- remove ---------------------------------
// Parameters: 't' pointer
//
// Removes the current node from the list it is part of.
//
// ERRORS:
//   - Pointer is NULL.  Print error.
//   - Object is not part of any list (that is, next==prev==NULL).  Print
//     error.

void dblList_Int__remove(DblList_Int* t){
	if(t == NULL||(t->next == NULL && t->prev == NULL)){
		fprintf(stderr, "error\n");
		return;
	}
	
	if(t->next!=NULL){
	 	t->next->prev=t->prev;
	}
	if(t->prev!=NULL){
		t->prev->next=t->next;
	}
	t->next = NULL;
	t->prev = NULL;
}


void dblList_Int__swapWithNext(DblList_Int* t){
	if(t == NULL || t->next == NULL){
		fprintf(stderr, "error\n");
		return;
	}
	int k=t->next->val;
	t->next->val=t->val;
	t->val=k;
}
