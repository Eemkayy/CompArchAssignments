#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


int main(int argc, char const *argv[]){

    

    for (int i =1; i< argc;i++){
    int j= 0;
     while( argv[i][j] != 0){
        if(isalpha(argv[i][j]) != 0){

            if ((int)argv[i][j]>=97 && (int)argv[i][j]<=122){
                if (((int)argv[i][j] + 13>=97 && (int)argv[i][j]+13<=122)){

                    int tempchar = (int)argv[i][j]+13;
                    printf("%c", (char)tempchar);

                }  else {
                    int tempchar = (int) argv[i][j]+13;

                        tempchar = (tempchar%122)+96;
                        printf("%c", (char) tempchar);

                    }
                

            } else if((int)argv[i][j]>=65 && (int)argv[i][j]<=90){
                if(((int)argv[i][j]+13>=65&&(int)argv[i][j]+13<=90)){
                    int tempchar = (int)argv[i][j] +13;
                    printf("%c", (char)tempchar);
                } else {
                    int tempchar = (int) argv[i][j]+13;
                    tempchar = (tempchar%90)+64;
                    printf("%c",(char)tempchar);

                }


            }


        } else {
            printf("%c", (char)argv[i][j]);

        }

        j++;
     }
    }
    
    printf("\n");

    return 0;

}