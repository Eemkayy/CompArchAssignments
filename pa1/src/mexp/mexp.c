#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


int main(int argc, char const *argv[]){
    FILE* file = fopen(argv[1], "r");
    int matrixSize;
    fscanf(file,"%d",&matrixSize);
    //Matrix size works fine
    int **resultMatrix = (int**)malloc(matrixSize*sizeof(int*));
    int **refMatrix =(int**) malloc(matrixSize*sizeof(int*));
    int **actualMatrix = (int**) malloc(matrixSize*sizeof(int*));

    for (int i=0; i<matrixSize;i++){
        resultMatrix[i] = (int*)malloc(matrixSize*sizeof(int));
        refMatrix[i] = (int*)malloc(matrixSize*sizeof(int));
        actualMatrix[i] = (int*)malloc(matrixSize*sizeof(int));
    }

    for(int i=0; i< matrixSize;i++){
        for (int j=0; j<matrixSize;j++){
            fscanf(file, "%d", &refMatrix[i][j]);
             resultMatrix[i][j]=refMatrix[i][j];
             actualMatrix[i][j] = 0;
        }
    }

    int timesExponent;

    fscanf(file,"%d", &timesExponent);

    fclose(file);

    if(timesExponent==0){

        for (int i=0; i<matrixSize;i++){
            for (int j=0; j<matrixSize;j++){
                if (i==j){
                    resultMatrix[i][j] = 1;
                } else {
                    resultMatrix[i][j] = 0;
                }

            }
        }

        for(int i=0; i<matrixSize;i++){
            for(int j=0;j<matrixSize;j++){
                printf("%d", resultMatrix[i][j]);
                if(j!=matrixSize-1){
                    printf(" ");
                }
            }
            printf("\n");
        }
        

    } else if (timesExponent==1){

        for(int i=0; i<matrixSize;i++){
            for(int j=0;j<matrixSize;j++){
                printf("%d", resultMatrix[i][j]);
            }
            printf("\n");
        }

    } else {

       
   
        int resultNumber;
        for (int timesNeededToLoop = 0; timesNeededToLoop<timesExponent-1; timesNeededToLoop++){ //Exponent multiplier

            for (int i=0; i<matrixSize;i++){

                for (int j=0; j<matrixSize; j++){ //Accessing row
                    resultNumber = 0;
                 
                    for (int k=0;k<matrixSize;k++){ //Accessing column
                        resultNumber = resultNumber + refMatrix[i][k]*resultMatrix[k][j];
                    }

                    actualMatrix[i][j] = resultNumber;

                }
            }

            for (int i=0; i<matrixSize;i++){
                for (int j=0; j<matrixSize;j++){
                    resultMatrix[i][j] = actualMatrix[i][j];
                }
            }

            
        }



        for(int i=0;i<matrixSize;i++){

            printf("%d",actualMatrix[i][0]);
            for(int j=1;j<matrixSize;j++){
                printf(" %d",actualMatrix[i][j]);
            }
            printf("\n");
        }


    }


    for(int i=0; i<matrixSize;i++){
        free(refMatrix[i]);
        free(resultMatrix[i]);
        free(actualMatrix[i]);
    }
    free(actualMatrix);
    free(refMatrix);
    free(resultMatrix);

    return EXIT_SUCCESS;

}