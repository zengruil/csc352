/*
 * course: CSc352
 * Author: Zengrui Luo
 * assignment: assignment8
 *
 * this assignment is used to
 * encapsulate String List
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encapsulatedListStr.h"


struct EncapsulatedList_Str{
	EncNode_Str *head;
	EncNode_Str *tail;
	int length;	
};

struct EncapsulatedList_Str_Node{
	char *val;
	int dup;
	struct EncapsulatedList_Str_Node *next;
	struct EncapsulatedList_Str_Node *prev;
	
};



EncList_Str *encList_Str__alloc(){
	EncList_Str *t = malloc(sizeof(EncList_Str));
	if(t != NULL){
		t->length = 0;
		t->tail = NULL;
		t->head = NULL;
		return t;
	}else{
		perror("error 1");
		return NULL;
	}
}


void encList_Str__free(EncList_Str* t){
	if(t!=NULL){
		
		while(t->head!=NULL){
			
			EncNode_Str* p=t->head;
			t->head=t->head->next;
			if(p->dup==1){
				free(p->val);
			}
			
			free(p);
		}
		free(t);
	}
	
}



void encList_Str__addHead(EncList_Str* t, char *string, int dup){
	if(t == NULL){
		perror("error was NULL");
		
		return;
	}
	
	char *buffer;
	if(dup){
		
		int length = strlen(string) + 1;
		buffer = malloc(length * sizeof(char));
		strcpy(buffer,string);
	}else{
		buffer = string;
	}
		
		
	EncNode_Str *p = malloc(sizeof(EncNode_Str));
	p->val = buffer;
	p->prev = NULL;
	p->next = t->head;
	p->dup = dup;
	if(t->head != NULL){
		t->head->prev = p;
	}else{
		t->tail = p;
	}
	t->length+=1;
	t->head = p;
	
}

void encList_Str__addTail(EncList_Str* t, char *string, int dup){
	if(t == NULL){
		perror("error was NULL");
		return;
	}
	char *buffer;
	if(dup){
		
		int length = strlen(string) + 1;
		buffer = malloc(length * sizeof(char));
		strcpy(buffer,string);
	}else{
		buffer = string;
	}
	EncNode_Str *p = malloc(sizeof(EncNode_Str));
	p->dup = dup;
	p->val = buffer;
	p->next = NULL;
	p->prev = t->tail;
	if(t->tail!=NULL){
		t->tail->next = p;
	}else{
		t->head = p;
	}
	t->length+=1;
	t->tail = p;
	
}



int encList_Str__count(EncList_Str* t){
	if(t == NULL){
		perror("error was NULL");
		return -1;
	}else{
		return t->length;
	}
}


char *encList_Str__getMin(EncList_Str* t){
	char *re;
	if(t == NULL){
		perror("error was NULL");
		return NULL;
	}
	if(t->head == NULL){
		return NULL;
	}
	re=t->head->val;
	EncNode_Str *p = t->head;
	
	while(p != NULL){
		if(strcmp(re, p->val) > 0){
			re = p->val;
		}	
		p = p->next;
	}
	return re;
}
char *encList_Str__getMax(EncList_Str* t){
	char *re;
	if(t == NULL){
		perror("error was NULL");
		return NULL;
	}
	if(t->head == NULL){
		return NULL;
	}
	re=t->head->val;
	EncNode_Str *p = t->head;
	
	while(p != NULL){
		if(strcmp(re, p->val) < 0){
			re = p->val;
		}	
		p = p->next;
	}
	return re;
}
 EncNode_Str* mergeTwoLists(EncNode_Str* l1, EncNode_Str* l2,EncNode_Str* pre) {
        if (l1 == NULL) {
	 
	  l2->prev=pre; 
	  
            return l2;
        } else if (l2 == NULL) {
	  l1->prev=pre; 
            return l1;
        } else if (strcmp(l1->val, l2->val) <= 0) {
            l1->next = mergeTwoLists(l1->next, l2,l1);
	  l1->prev=pre; 
            return l1;
        } else {
            l2->next = mergeTwoLists(l1, l2->next,l2);
	  l2->prev=pre; 
            return l2;
        }
        return NULL;
    }

void encList_Str__merge(EncList_Str* left, EncList_Str* right){
	if(left == NULL || right == NULL){
		perror("error was NULL");
		return;
	}
	left->head=mergeTwoLists(left->head,right->head,NULL);
	right->head=NULL;
	right->tail=NULL;
	left->length+=right->length;
	right->length=0;
	EncNode_Str *p=left->head;
	while(p->next!=NULL){
		p=p->next;
	}
	left->tail=p;

}



void encList_Str__append(EncList_Str* t, EncList_Str* p){
	if(t == NULL || p == NULL){
		perror("error was NULL");
		return;
	}
	p->head->prev = t->tail;
	t->tail->next = p->head;
	
	t->tail = p->tail;
	t->length = t->length + p->length;
	
}



EncNode_Str *encList_Str__index(EncList_Str* t, int index){
	if(t == NULL){
		perror("error was NULL");
		return NULL;
	}
	if(index < 0||t->length<=index){
		perror("error was index");
		return NULL;
	}
	EncNode_Str *p=t->head;
	int i=0;
	while(p!=NULL){
		if(i==index){

			return p;
		}
		i++;
		p=p->next;
	}
	return NULL;
	
}


EncList_Str *encList_Str__splitAt(EncList_Str* t, int index){
	if(t == NULL){
		perror("error was NULL\n");
		return NULL;
	}
	if(index < 0 || index > t->length){
		perror("error was index\n");
		return NULL;
	}
	EncList_Str *re = encList_Str__alloc();
	
	re->head = encList_Str__index(t, index);
	re->tail = t->tail;
	t->tail = re->head->prev;
	t->tail->next=NULL;
	re->head->prev=NULL;
	re->length=t->length-index;
	t->length=index;
	return re;
	
}

EncNode_Str *encList_Str__getHead(EncList_Str* t){
	if(t != NULL){
		return t->head;
	}
	return NULL;
}
EncNode_Str *encList_Str__getTail(EncList_Str* t){
	if(t != NULL){
		return t->tail;
	}
	return NULL;
}


char    *encNode_Str__getStr (EncNode_Str* t){
	return t->val;
}
EncNode_Str *encNode_Str__getNext(EncNode_Str* t){
	return t->next;
}
EncNode_Str *encNode_Str__getPrev(EncNode_Str* t){
	return t->prev;
}

