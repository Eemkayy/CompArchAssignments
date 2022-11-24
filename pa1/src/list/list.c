#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
typedef struct  Node{
        int number;
      struct Node* nextNode;
} Node;
Node* createNode(int number);
int inTheList(Node* front, int number);
void addToList(Node** trackingFront, Node* newNumber);
int printsize(Node*front);
void freeSpace(Node*front);
void printList(Node* front);
void deleteNode(Node** trackingFront, int number);




int main(int argc, char const *argv[]){
    Node* front = NULL;
    Node** trackfront = &front;
    int number;
    char option[100];
    while(scanf("%s %d",option, &number )!=EOF){
        if (option[0]!='i'&& option[0]!='d'){
            break;
        }
         if(option[0]=='i'){
            if (inTheList(front, number)==1){
                printf("%d :", printsize(front));
                printList(front);
                printf("\n");
                continue;
            } else {           
                if (front==NULL){
                    front = createNode (number);
                } else{ 
                    Node* newNode = createNode (number);
                    addToList(trackfront, newNode);
                }
                printf("%d :", printsize(front));
                printList(front);
                printf("\n");
            }
        }    
         if (option[0]=='d'){
            if (inTheList(front,number)==0){
                printf("%d :", printsize(front));
                printList(front);
                printf("\n");
                continue;
            } else{
                deleteNode(trackfront,number);
                printf("%d :", printsize(front));
                printList(front);
                printf("\n");
            }
        }
    }
    Node* c = *trackfront;
    while(c != NULL) {
        Node* tmp = c;
        c = c->nextNode;
        free(tmp);
    }   
    return EXIT_SUCCESS;
}
void deleteNode(Node**trackingFront, int number){
    Node* front = *trackingFront;
    Node* pointer = front;
    //If it's at the beginning and by itself
    if (pointer->number==number&&pointer->nextNode==NULL){
        free(pointer);
        *trackingFront =NULL;
        return;
    }
    //If it's at the beginning
     else if (pointer->number==number&&pointer->nextNode!=NULL){
        *trackingFront = pointer->nextNode;
        free(pointer);
        return;
    } 
    //Somewhere in the middle
    else {
        while(pointer->nextNode->nextNode!=NULL){
        if (pointer->nextNode->number==number){
            Node* tempalloc = pointer->nextNode->nextNode;
            free(pointer->nextNode);
            pointer->nextNode = tempalloc;
            return;
        }
        pointer = pointer->nextNode;
    }
    //If it's at the end
    if (pointer->nextNode->nextNode==NULL){
        free(pointer->nextNode);
        pointer->nextNode =NULL;
        return;
    }
    }
}
void freeSpace(Node* front){
    while (front!=NULL){
        Node* tempalloc = front->nextNode;
        free(front);
        front = tempalloc;
    }
}
void printList(Node* front){
    while(front!=NULL){
        printf(" %d", front->number );
        front = front->nextNode;
    }
}
int printsize(Node* front){
     int number =0;
    if (front == NULL){
        return 0;
    } else {
        while (front!=NULL){
            number++;
            front = front->nextNode;
        }
    }
    return number;
}
int inTheList(Node*front, int number){
    if(front==NULL){
        return 0;
    } else {
        while(front!=NULL){
            if (front->number==number){
                return 1;
            } else {
                front = front->nextNode;
            }
        }
    }
    return 0;
}
Node* createNode(int number){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->nextNode = NULL;
    newNode->number = number;
    return newNode;
}
void addToList(Node** trackingFront, Node* newNode ){
    Node* front = *trackingFront;
    Node* pointer = front;
    if(pointer->number>newNode->number){
    newNode->nextNode = pointer;
    *trackingFront = newNode;
    return;
        // assigning newNode as front
    } else {
        //if the next node is already bigger than this one.
        while (pointer->nextNode!=NULL){
            if (pointer->nextNode->number>newNode->number){
                Node* tempalloc = pointer->nextNode;
                pointer->nextNode = newNode;
                newNode->nextNode = tempalloc;
                return;
            } else {
                pointer = pointer->nextNode;
            }
        } 
        pointer->nextNode = newNode;
    }
}  