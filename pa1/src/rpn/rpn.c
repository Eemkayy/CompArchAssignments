#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


typedef struct  stack{
    int number;
    struct stack* nextNumber;
} stack;

int numberOfItems(stack*front);


//write a method that checks the stack length, gotta be >=2 to be able to operate.


//write a method to create a stackNode

stack* createNode(int number){

    stack* newNode = (stack*)malloc(sizeof(stack));
    newNode->number = number;
    newNode->nextNumber = NULL;

    return newNode;

}

//write a method that pushes (literally adding in linkedlist)

void push(stack** trackFirst, stack* newStack){
    stack* explorer = *trackFirst;
    stack* setter = explorer;
    if(setter==NULL){
        *trackFirst = newStack;
        
        return;
    }
    while(setter->nextNumber!=NULL){
        setter = setter->nextNumber;
    }
    setter->nextNumber = newStack;

    
   
    return;

}

//write a method that pops (literally deleting the last one)


int pop(stack** trackFirst){
    stack* deletion = *trackFirst;
    stack* pointer = deletion;
    int number =0;
    if(pointer->nextNumber==NULL){
         number = pointer->number;
        *trackFirst = NULL;
        free(pointer);
        
    } else {

        while (pointer->nextNumber->nextNumber!=NULL){
        pointer = pointer->nextNumber;
    }
    if (pointer->nextNumber->nextNumber==NULL){
         number = pointer->nextNumber->number;
        free(pointer->nextNumber);
        pointer->nextNumber = NULL;
    }
    }

    

    return number;
}



int main(int argc, char  *argv[]){
    stack* firstNumber = NULL;
    stack** trackFirst = &firstNumber;
    char storage[100];
    int track=0;
    int numbersetter=0;
    for (int i=0; i<100;i++){

        if (argv[1][i]>=48&&argv[1][i]<=57){
            storage[track]=argv[1][i];
            track++;
            continue;
        }
        else if (argv[1][i]==44){ //if its comma

            if (track!=0){
        for (int j=0; j<track;j++){
            if((storage[j]>=48&&storage[j]<=57)){
            numbersetter = numbersetter*10 + (int)(storage[j]-48);
            }
        }

        stack* newNumber = createNode(numbersetter);
        push(trackFirst, newNumber);

        }


            for (int j=0; j<track;j++){
                storage[j]=0;
            }

            numbersetter = 0;
            track = 0;
            
            continue;


        } else if (argv[1][i]==43){ //if its a addition
        numbersetter = 0;
        if (track!=0){
        for (int j=0; j<track;j++){
            if((storage[j]>=48&&storage[j]<=57)){
            numbersetter = numbersetter*10 + (int)(storage[j]-48);
            }
        }

        stack* newNumber = createNode(numbersetter);
        push(trackFirst, newNumber);

        }
        if (numberOfItems(*trackFirst)<2){
            stack * updatedFirst = *trackFirst;
            while(updatedFirst!=NULL){
            stack* nextNumber = updatedFirst;
            updatedFirst = updatedFirst->nextNumber;
            free (nextNumber);
            }
            return EXIT_FAILURE;
        }

        int result = pop(trackFirst) + pop(trackFirst);
        stack* ResultNumber = createNode(result);
        push(trackFirst, ResultNumber);
        for (int j=0; j<track;j++){
            storage[j]=0;
        }
        track = 0;
        numbersetter=0;


        } else if (argv[1][i]==45){ //if its a subtraction

        numbersetter = 0;
        
        if (track!=0){
        for (int j=0; j<track;j++){
            if((storage[j]>=48&&storage[j]<=57)){
            numbersetter = numbersetter*10 + (int)(storage[j]-48);
            }
        }

        stack* newNumber = createNode(numbersetter);
        push(trackFirst, newNumber);

        }

        if (numberOfItems(*trackFirst)<2){
            stack * updatedFirst = *trackFirst;
            while(updatedFirst!=NULL){
            stack* nextNumber = updatedFirst;
            updatedFirst = updatedFirst->nextNumber;
            free (nextNumber);
            }
            return EXIT_FAILURE;
        }



        
        int result = -pop(trackFirst) + pop(trackFirst);
        stack* ResultNumber = createNode(result);
        push(trackFirst, ResultNumber);
        for (int j=0; j<track;j++){
            storage[j]=0;
        }
        track = 0;
        numbersetter = 0;

        continue;

        } else if (argv[1][i]==47){ //if its a division

        numbersetter = 0;
        if (track!=0){
        for (int j=0; j<track;j++){
            if((storage[j]>=48&&storage[j]<=57)){
            numbersetter = numbersetter*10 + (int)(storage[j]-48);
            }
        }

        stack* newNumber = createNode(numbersetter);
        push(trackFirst, newNumber);

        }

        if (numberOfItems(*trackFirst)<2){
            stack * updatedFirst = *trackFirst;
            while(updatedFirst!=NULL){
            stack* nextNumber = updatedFirst;
            updatedFirst = updatedFirst->nextNumber;
            free (nextNumber);
            }
            return EXIT_FAILURE;
        }

        int divisor = pop(trackFirst);

        if (divisor==0){

            stack * updatedFirst = *trackFirst;
            while(updatedFirst!=NULL){
            stack* nextNumber = updatedFirst;
            updatedFirst = updatedFirst->nextNumber;
            free (nextNumber);
            }
            
            return EXIT_FAILURE;
        
        }

        int dividend = pop(trackFirst);
        

        int result = dividend/divisor;
        stack* ResultNumber = createNode(result);
        push(trackFirst, ResultNumber);
        for (int j=0; j<track;j++){
            storage[j]=0;
        }
        track = 0;
        numbersetter =0;

        continue;

        } else if (argv[1][i]==120){//if its a multiplication

        numbersetter = 0;
        if (track!=0){
        for (int j=0; j<track;j++){
            if((storage[j]>=48&&storage[j]<=57)){
            numbersetter = numbersetter*10 + (int)(storage[j]-48);
            }
        }

        stack* newNumber = createNode(numbersetter);
        push(trackFirst, newNumber);

        }

        if (numberOfItems(*trackFirst)<2){
            stack * updatedFirst = *trackFirst;
            while(updatedFirst!=NULL){
            stack* nextNumber = updatedFirst;
            updatedFirst = updatedFirst->nextNumber;
            free (nextNumber);
            }
            return EXIT_FAILURE;
        }

        int firstnum = pop(trackFirst);
        int secondNumber = pop(trackFirst);

        

        int result = firstnum * secondNumber;

        stack* ResultNumber = createNode(result);
        push(trackFirst, ResultNumber);

        for (int j=0; j<track;j++){
            storage[j]=0;
        }
        track = 0;
        numbersetter = 0;

        continue;

        } else {
            break;
        }

        
    }

    

    
    /* use atoi, strncpy to get what u need out of the main string.
    */

   /* example: put 123 as a number 
   (((1*10)+2)*10)*10+3)
   */


  if (storage[0]!=0){
    for (int j=0; j<track;j++){
            if((storage[j]>=48&&storage[j]<=57)){
            numbersetter = numbersetter*10 + (int)(storage[j]-48);
            }
        }
        stack* newNumber = createNode(numbersetter);
        push(trackFirst, newNumber);
  }

  stack * updatedFirst = *trackFirst;


    if (numberOfItems(updatedFirst)!=1||track!=0){
            stack * updatedFirst = *trackFirst;
            while(updatedFirst!=NULL){
            stack* nextNumber = updatedFirst;
            updatedFirst = updatedFirst->nextNumber;
            free (nextNumber);
            }
        return EXIT_FAILURE;
    } else {

    while(updatedFirst!=NULL){
    stack* nextNumber = updatedFirst;
    printf("%d",nextNumber->number);
    updatedFirst = updatedFirst->nextNumber;
    free (nextNumber);
  }
  printf("\n");

    }

  

  



    return EXIT_SUCCESS;
}

int numberOfItems(stack*front){
    int number =0;
    while (front!=NULL)
    {
        number++;
        front = front->nextNumber;
    }
    
return number;

}
