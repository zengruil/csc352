/*
 * course: CSc352
 * Author: Zengrui Luo
 * assignment: assignment7
 *
 * this assignment is to sort string.
 */
#include "proj07_strList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/*
Insertion sort from big to small, 
the input parameter of the function is the first address of the array, 
and the length of the array, to insert sort the array 
*/
void insertsort(char **arr, int len){
    int i,j;
	for(i=1;i<len;i++){
            for(j=i-1;j>=0;j--){
                   if(strcmp(arr[j],arr[j+1])<0){
                          char *temp=arr[j];
                          arr[j]=arr[j+1];
                          arr[j+1]=temp;
                   }else{
                             
                          break;
                   }
            }
          }
}
/*
Read data from the input file,
Store the data in a string array,
And dynamically expand the array capacity according to the number,
Then insert and sort the array, and finally build a linked list,
And return the head node of the linked list, and release the memory of the string array 
*/ 
StrList *readInput(FILE* inputFile){
	
          int len = 0;
          int thread = 10;
	
	StrList* head = malloc(sizeof(StrList));
          head->next=NULL;
	char **array = malloc(10 * sizeof(char*));
	if(array == NULL){

		return NULL;
	}
	if(array == NULL){
	          return NULL;
	}
          
	do{
		char *rc = readLongStr(inputFile);
                    if(strcmp(rc, "") == 0 ){
			free(rc);
			continue;
		}
                    array[len]=rc;
                    len++;
		if(len == thread){
                             char **buffer = malloc(thread * 10 * sizeof(char*));
			if(buffer == NULL){
				
				break;
			}
			memcpy(buffer, array, thread * sizeof(char*));
			thread *= 10;
			free(array);
			array = buffer;

                    }
		
	}while(!feof(inputFile));
          
	insertsort(array,  len );
	
	for(int i = 0; i < len; i++){
		StrList* new = malloc(sizeof(StrList));
		if(new == NULL){
			break;
		}
                    new->val = array[i];
		new->next = head->next;
                    head->next=new;
	}
	free(array);
          StrList* p=head->next;
          free(head);
	return p;
}

/*
Read a string of any length, the default length is 8,
  If the length exceeds 8, expand the length *2, and finally return the read string

*/ 
char *readLongStr(FILE* in){
          char c;
          int len = 0;
          int thread = 8;
	char *str = malloc(8 * sizeof(char));
	
	
	while((c = (char)fgetc(in))&&isspace(c));
		
         
	while(c != EOF){
                    if(isspace(c)){
                              break;
                    }
		str[len] = c;
                    c = (char)fgetc(in);
		len++;
		
		if(len == thread){
			char *buffer = malloc(2 * thread * sizeof(char));
			if(buffer == NULL){
				break;
			}
			memcpy(buffer, str, thread);
			thread *= 2;
			free(str);
			str = buffer;
		}

	} 
	str[len] = '\0';
	
	return str;
}

/*
Get the length of the linked list

*/ 
int getLen(StrList* p){
          if(p==NULL){
               return 0;
          }else {
               return getLen(p->next)+1;
          }
}



/*
Traverse all the nodes of the linked list and print the information
*/ 
void writeOutput(StrList* p, FILE* out){
	int i=0;
          while(p!=NULL){
                  fprintf(out, "%d: %s\n", i, p->val);
                  ++i;
                  p=p->next;  
          }
}
/*
Release the memory of all nodes in the linked list
*/ 
void freeList(StrList* p){
	if(p == NULL) return;
	while(p != NULL){
                    StrList *back = p->next;
                    free(p->val);
		free(p);
                    p=back;
	}
}
