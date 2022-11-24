#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


void BubbleSort(int argvSize,  char** argv );
void swap(char**c, char**d);

int main(int argc, char **argv){
char * charpointer = (char*)malloc(sizeof(char));
BubbleSort(argc, argv);
  for (int i=1; i < argc; i++){
    printf("%s\n", argv[i]);
    }

free(charpointer);

return 0;
}

void BubbleSort(int argvSize,  char** argv ){
    
    for (int i=0; i<argvSize-1;i++){
        for(int j=1; j < argvSize-i-1;j++){
            if (strcmp(argv[j], argv[j+1])>0&&strcmp(argv[j], argv[j+1])!=-1){
                if (strcmp(argv[j], argv[j+1])==1){
                swap(&argv[j+1],&argv[j]);
                }
            }
        }
    }

return;
}

void swap (char** c, char** d){
    char*temp = *c;
    *c = *d;
    *d=temp;
}


