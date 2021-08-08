/*
 * course: CSc352
 * Author: Zengrui Luo
 * assignment: assignment6
 *
 * this assignment is to record inputs,
 * store and expand the buffer periodically
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Record{
        int Key_1;
        int Key_2;
        char value[32];
}Record;
int size = 1;//Array capacity
//Determine if the input is "End"
int IsEnd(){
	printf("scanf() returned 0, so now we'll check to see if the string is \"END\"...\n");
	char buffer[32];
	int rc = scanf("%3s", buffer);
          if(rc<0){
                  
                    return 0;
          }
          if(strcmp(buffer, "END") != 0){
                 
                    return 0;
          }
          printf("...\"END\" found.  Will now read the indices...\n");
          return 1;
}
//Output record 
void printRecord(Record *records){
	printf("%d %d %s\n", records->Key_1, records->Key_2, records->value);
	return;
}
/*
Expand the array, re-apply for the memory of the array, 
copy the original content to the new memory, and then release the old memory

*/ 
void expend(Record **records) {
	printf("Need to extend the array; the buffer is full (with %d records)\n", size);
	printf("  Before extending the array, element 0 is: ");
	
	printf("%d %d %s\n", (*records)->Key_1, (*records)->Key_2, (*records)->value);
	size *= 2 ;
	Record *Buffer = malloc(size * sizeof(Record));
	memcpy(Buffer, *records, size * sizeof(Record)/2);
	free(*records);
	*records = Buffer;
	printf("  After  extending the array, element 0 is: ");
	printRecord(*records);
	
}
/*
Read the input file, read the data first, and then read the index for query
*/ 
int main(int argc, char *argv[]){
	Record *records = malloc(sizeof(Record));
	int rc = 1, i = 0;
          for(i=0;rc>0;i++){

			if(i >= size){
			       expend(&records);
			}
            rc = scanf("%d %d %15s", &records[i].Key_1, &records[i].Key_2, records[i].value);
            if(rc !=0 && rc != 3 ){
                      
                      free(records);
                      fprintf(stderr, "ERROR");
                              
				return 1;
            }

                    if(rc==0){
                              if(IsEnd()){
                                        break;
                              }
                    }
          }
	int len=i;
	int index = -1;
	while((rc=scanf("%d", &index))!=EOF){
                     if(rc==0){
			free(records);
			fprintf(stderr, "ERROR");
			return 1;     
		}
		printf("[%d] ", index); 
		if(index >= 0 && index < len){
			printRecord(records+ index);
			
		} else {
			printf("<invalid index>\n");
		}
	}
         
	free(records);
          
	return 0;

}

