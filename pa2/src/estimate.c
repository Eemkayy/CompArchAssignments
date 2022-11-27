#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>




/* Things to do:
    - Include all libraries
    - Copy MEXP multiplication process (malloc too prolly).
    - Write a transpose method (should be pretty ez).
    - Write Inverse
    - Write the W formula 
    - Finish
*/

double** transpose(double** matrixNormal, double** matrixTranspose, int rowSize, int columnSize);
double** multiplication(double** matrixA, double** matrixB, double** matrixC, int rowMatrix1, int columnMatrix2, int columnMatrix1);
double* multiplicationForW(double** matrixA, double** matrixB, double* matrixC, int rowMatrix1, int columnMatrix2, int columnMatrix1);
double** inverse(double** matrixA, double** identityMatrix, int rowSize, int colSize);
double* multiplicationForY(double** matrixA, double* matrixB, double* matrixC, int rowMatrix1, int columnMatrix2, int columnMatrix1);


int main(int argc, char const *argv[]){
    FILE* file = fopen(argv[1], "r");
    int columnsSizeX;
    int rowSizeX;  
    
    fscanf(file,"%*s");

    fscanf(file, "%d", &columnsSizeX);
    columnsSizeX = columnsSizeX+1;
    fscanf(file, "%d", &rowSizeX);

   

    //First 2 lines are read.

    double** X = (double**)malloc((rowSizeX)*sizeof(double*));
    double** Y = (double**)malloc(rowSizeX*sizeof(double*));


    //X = 10 rows 5 columns, 5 rows 10 columns

    double** Xt = (double**)malloc((columnsSizeX)*sizeof(double*));
    double** XtX = (double**)malloc(rowSizeX*sizeof(double*));
    double** XtXXt = (double**)malloc(columnsSizeX*sizeof(double*));
    
    

    double** identityMatrix = (double**)malloc((rowSizeX)*sizeof(double*));
    for (int i=0; i< rowSizeX;i++){
        identityMatrix[i] = (double*)malloc(rowSizeX*sizeof(double));
    }
    for (int i=0; i<rowSizeX;i++){
        for (int j=0;j<rowSizeX;j++){
            if (i==j){
                identityMatrix[i][j] = 1;
            }
            else {
                identityMatrix[i][j] =0;
            }
        }
    }

    for (int i=0; i<columnsSizeX;i++){
        Xt[i] = (double*)malloc((rowSizeX)*sizeof(double));
        XtX[i] = (double*)malloc(columnsSizeX*sizeof(double));
        XtXXt[i] = (double*)malloc(rowSizeX*sizeof(double));
        
    }


    for (int i=0; i<rowSizeX;i++){
        X[i] = (double*)malloc((columnsSizeX)*sizeof(double));
        Y[i] = (double*)malloc((sizeof(double)));
       
        X[i][0] = 1;
        for (int j=1;j<columnsSizeX;j++){
            double scanNumber = 0;
            fscanf(file, "%lf", &scanNumber);
            X[i][j] = scanNumber;
        }
        double scanLast = 0;
        fscanf(file, "%lf", &scanLast);
        Y[i][0] = scanLast;

    }
    
    fclose(file);

    //FORMULA: W=(X^TX)^-1X^TY

    //10x5 then xt has to be 5x10

    Xt = transpose(X, Xt, columnsSizeX, rowSizeX); //transpose tested and works for train.00.txt

    //5x10 10x5
    //  Xt  X

    XtX = multiplication(Xt, X, XtX, columnsSizeX, columnsSizeX, rowSizeX);


    XtX = inverse(XtX, identityMatrix, columnsSizeX, columnsSizeX);

    

    //5x5 5x10

    XtXXt = multiplication(XtX,Xt,XtXXt, columnsSizeX, rowSizeX,columnsSizeX);

    double* W = (double*)malloc(columnsSizeX*sizeof(double));

    //5x10 10x1                   5x1

    W = multiplicationForW(XtXXt,Y,W,columnsSizeX,1,rowSizeX);

    for (int i=0; i<rowSizeX;i++){
        printf("%lf", W[i]);
    }

    FILE* file2 = fopen(argv[2], "r");
    int columnsSize2;
    int rowSize2;  
    
    fscanf(file2,"%*s");

    fscanf(file2, "%d", &columnsSize2);
    columnsSize2 = columnsSize2+1;
    fscanf(file2, "%d", &rowSize2);

    double** dataMatrix = (double**)malloc(rowSize2*sizeof(double*));

    for (int i=0; i<rowSize2;i++){
        dataMatrix[i] = (double*)malloc(columnsSize2*sizeof(double));
    }
    for (int i=0; i<rowSize2;i++){
        dataMatrix[i][0]=1;

        for (int j=1;j<columnsSize2;j++){
            double numberScan = 0;
            fscanf(file2,"%lf", &numberScan);
            dataMatrix[i][j]=numberScan;
        }
    }
    fclose(file2);
    double* newW = (double*)malloc(rowSize2*sizeof(double));

    //10x5 5x1 

    newW = multiplicationForY(dataMatrix,W,newW,rowSize2,1,columnsSize2);

    for (int i=0; i<rowSize2;i++){
        printf("%.0f\n", newW[i]);
    }

    




    free(newW);


   

   

    // if the matrix itself is a 3x2 and the transpose is a 2x3, we multiply 2x3 3x2 to get 2x2, rowsize.


    //freeing the variables
    for (int i=0; i<rowSizeX;i++ ){
        free(X[i]);   
    }
    free(X);
    for (int i=0; i<rowSizeX;i++){
        free(Y[i]);
    }
    free(Y);
    for (int i=0; i<columnsSizeX;i++){
        free(Xt[i]);
    }
    free(Xt);
    for (int i=0; i< rowSizeX;i++){
        free(XtX[i]);
    }
    free(XtX);
    for (int i=0; i<columnsSizeX;i++){
        free(XtXXt[i]);
    }
    free(XtXXt);
    
    free(W);

    for (int i=0; i<rowSize2;i++){
        free(dataMatrix[i]);
    }
    free(dataMatrix);


    
    return EXIT_SUCCESS;

    

}

double* multiplicationForY(double** matrixA, double* matrixB, double* matrixC, int rowMatrix1, int columnMatrix2, int columnMatrix1){

    // 3x3 3x1

    //10x5 5x1 
     for (int i=0; i<rowMatrix1;i++){ 
        
            double resultNumber = 0;
            for (int k=0;k<columnMatrix1;k++){ 
                resultNumber = resultNumber + matrixA[i][k]*matrixB[k];
            }
            matrixC[i]= resultNumber;
        
    }   
    
    return matrixC;

}



double* multiplicationForW(double** matrixA, double** matrixB, double* matrixC, int rowMatrix1, int columnMatrix2, int columnMatrix1){

     for (int i=0; i<rowMatrix1;i++){ //10
        for (int j=0; j<columnMatrix2; j++){ //10
            double resultNumber = 0;
            for (int k=0;k<columnMatrix1;k++){ //5
                resultNumber = resultNumber + matrixA[i][k]*matrixB[k][j];
            }
            matrixC[i]= resultNumber;
        }
    }   
    //10x4 4x10
    return matrixC;

}

double** transpose(double** matrix, double**matrixTranspose, int rowSize, int columnSize){
    for (int i=0; i< rowSize;i++){
        for (int j=0; j <columnSize;j++){
            matrixTranspose[i][j] = matrix[j][i];
        }
    }
    return matrixTranspose;
}

double** multiplication(double** matrixA, double** matrixB, double** matrixC, int rowMatrix1, int columnMatrix2, int columnMatrix1){
    //10x5 5x10

    for (int i=0; i<rowMatrix1;i++){ //10
        for (int j=0; j<columnMatrix2; j++){ //10
            double resultNumber = 0;
            for (int k=0;k<columnMatrix1;k++){ //5
                resultNumber = resultNumber + matrixA[i][k]*matrixB[k][j];
            }
            matrixC[i][j] = resultNumber;
        }
    }   
    //10x4 4x10
    return matrixC;
}

double** inverse(double** matrixA, double** identityMatrix,int rowSize, int colSize){

    //Identity matrix created

    for (int p=0;p<rowSize;p++){
        double divideNumber = matrixA[p][p];
        for(int i=0;i<rowSize;i++){
            matrixA[p][i] = matrixA[p][i]/divideNumber;
            identityMatrix[p][i] = identityMatrix[p][i]/divideNumber;
        }
        for (int i=p+1;i< rowSize;i++){
            double multiplier = matrixA[i][p];
            for (int j=0;j<rowSize;j++){
                matrixA[i][j] = matrixA[i][j] - multiplier*matrixA[p][j];
                identityMatrix[i][j] = identityMatrix[i][j] - multiplier*identityMatrix[p][j];
            }
        }
    }
    for (int p=rowSize-1;p>=0;p--){
        for (int i = p-1; i>=0;i--){
            double multiplier2 = matrixA[i][p];
            for (int j=0; j<rowSize;j++){

                matrixA[i][j] = matrixA[i][j] - multiplier2*matrixA[p][j];
                identityMatrix[i][j] = identityMatrix[i][j] - multiplier2*identityMatrix[p][j];
            }
        }
    }


    for (int i=0; i<rowSize;i++){
        free(matrixA[i]);
    }
    free(matrixA);


    return identityMatrix;




}
