/*
 * course: CSc352
 * Author: Zengrui Luo
 * assignment: assignment7
 *
 * this assignment is to sort integer.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proj07_intList.h"
 /*
Insertion sort from big to small, 
the input parameter of the function is the first address of the array, 
and the length of the array, to insert sort the array 
*/
void insertsort(int *arr, int len){
          int i,j;
	for(i=1;i<len;i++){
            int temp=arr[i];
            for(j=i-1;j>=0;j--){
                   if(arr[j]<=temp){
                             arr[j+1]=arr[j];
                   }else{
                             
                             break;
                   }
            }
           arr[j+1]=temp;
          }
}

/*
Read data from the input file,
Store the data in a string array,
And dynamically expand the array capacity according to the number,
Then insert and sort the array, and finally build a linked list,
And return the head node of the linked list, and release the memory of the string array 
*/ 
IntList *readInput(FILE* inputFile){
          int len = 0;
          int thread = 2;
	int rc;
	IntList* head = malloc(sizeof(IntList));
          head->next=NULL;
	int *array = malloc(2 * sizeof(int));
	if(array == NULL){
	          return NULL;
	}
	while((rc=fscanf(inputFile, "%d", array + len))!=EOF&&rc>0){
                    len++;
		if(len == thread){
                              int *Buffer = malloc(thread * 2 * sizeof(int));
                              if(Buffer == NULL){
                                     break;
                              }
                              memcpy(Buffer, array, thread * sizeof(int));
                              thread *= 2;
                              free(array);
                              array = Buffer;

                    }
		
	}
	if(rc == 0){
			perror("Non-numeric");
		}
	insertsort(array, len );
     
	for(int i = 0; i < len; i++){
		IntList* new = malloc(sizeof(IntList));
		if(new == NULL){
			break;
		}
                    new->val = array[i];
		new->next = head->next;
                    head->next=new;
	}
	free(array);
          IntList* p=head->next;
          free(head);
	return p;
}

/*
Get the length of the linked list

*/ 
int getLen(IntList* p){
          if(p==NULL){
               return 0;
          }else {
               return getLen(p->next)+1;
          }
}

/*
Traverse all the nodes of the linked list and print the information
*/ 
void writeOutput(IntList* p, FILE* out){
	int i=0;
          while(p!=NULL){
                  fprintf(out, "%d: %d\n", i, p->val);
                  ++i;
                  p=p->next;  
          }
}
/*
Release the memory of all nodes in the linked list
*/ 
void freeList(IntList* p){
	if(p == NULL) return;
	while(p != NULL){
                    IntList *back = p->next;
		free(p);
                    p=back;
	}
}
