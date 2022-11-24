#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


typedef struct  Node{
    int number;
    struct Node* leftNode;
    struct Node* rightNode;
} Node;


Node* creatingNode(int number);
void addToTree(Node** trackingRoot, Node*newNode);
int inTheTree(Node* root, int number);
void insertNode(Node*addingNode);
Node* deleteFromTree(Node** trackRoot,Node* root, int number);
void addToTree(Node** trackingRoot, Node* newNode); //Add to the tree in general
void postOrderTraversal(Node*front); //delete all items (free)
void inOrderPrint(Node*voyager);
Node* inOrderPredecessor(Node* root);

int main(int argc, char const *argv[]){
    Node*root = NULL;
    Node** trackRoot = &root;
    int number;
    char option[100];
    while(scanf("%s %d", option,&number)!=EOF){
        if (option[0]!='i'&&option[0]!='d'&&option[0]!='p'&&option[0]!='s'){
            break;
        }
        if (option[0]=='i'){
            

            if(inTheTree(root, number)==0){
                printf("not inserted\n");
            } else {
                if (root==NULL){
                    root = creatingNode(number);
                    printf("inserted\n");
                } else {
                    Node * newNode = creatingNode(number);
                    addToTree(trackRoot, newNode);
                    printf("inserted\n");
                }
            }
        } else if (option[0]=='d'){

            root = *trackRoot;

            if (inTheTree(root, number)==1){
                printf("absent\n");
            } else {
                root = deleteFromTree(trackRoot,root, number);
                printf("deleted\n");
            }



        } else if (option[0]=='p'){
            Node* voyager = *trackRoot;
            inOrderPrint(voyager);
            printf("\n");
            
        } else {

            root = *trackRoot;

            if (inTheTree(root, number)==0){
                printf("present\n");
            } else {
                printf("absent\n");
            }
            
        }
    }
    root = *trackRoot;
    postOrderTraversal(root);
    return EXIT_SUCCESS;
}


Node* deleteFromTree(Node** trackingRoot,Node* root, int number){
struct Node* eyePre;
if (root==NULL){
    return NULL;
}
if (root->leftNode==NULL&&root->rightNode==NULL){
    free(root);
    return NULL;
}
if (number<root->number){
    root->leftNode = deleteFromTree(trackingRoot,root->leftNode,number);
} else if (number>root->number){
    root->rightNode = deleteFromTree(trackingRoot,root->rightNode,number);
}
else {

    if (root->leftNode==NULL){
        Node* temp = root->rightNode;
        free(root);
        return temp;
    } else if (root->rightNode==NULL){
        Node* temp = root->leftNode;
        free(root);
        return temp;
    }


    eyePre = inOrderPredecessor(root);
    root->number = eyePre->number;
    root->leftNode = deleteFromTree(trackingRoot, root->leftNode, eyePre->number);
}
return root;
}

Node* inOrderPredecessor(Node* root){
    root = root->leftNode;
    while (root->rightNode!=NULL){
        root = root->rightNode;
    }

    return root;

}
    


void inOrderPrint(Node*voyager){

    if (voyager==NULL){
        return;
    }
    printf("(");
    inOrderPrint(voyager->leftNode);
    printf("%d",voyager->number);
    inOrderPrint(voyager->rightNode);
    printf(")");
    


}

void postOrderTraversal(Node*front){
    if (front==NULL){
        return;
    }
    postOrderTraversal(front->leftNode);
    postOrderTraversal(front->rightNode);
    free(front);

}



void addToTree(Node** trackingRoot, Node* newNode){

    Node * front = *trackingRoot;

    if (front == NULL){
        *trackingRoot = newNode;
        return;
    }


    if (front->leftNode == NULL&&front->number>newNode->number){
        front->leftNode = newNode;  //Simple if root doesn't have kids iteration
        return;
    } else if (front->rightNode==NULL&&front->number<newNode->number){
        front->rightNode = newNode;
        return;
    } 

    //If root has kids

    

    while (front->leftNode!=NULL||front->rightNode!=NULL){

        if (front->number>newNode->number&&front->leftNode!=NULL){
            
            front = front->leftNode;
        } else if (front->number<newNode->number&&front->rightNode!=NULL){
            
            front = front->rightNode;
            
        } else {
            break;
        }
    }

    if (front->number>newNode->number){
        front->leftNode = newNode;
        return;
    } else {
        front->rightNode = newNode;
        return;
    }
}

Node* creatingNode(int number){
    Node * newNode = (Node*)malloc(sizeof(Node));
    newNode->number = number;
    newNode->leftNode = NULL;
    newNode->rightNode = NULL;
    return newNode;
}

int inTheTree(Node* root, int number){
    if (root==NULL){ 
        return 1;
    } else if (root->number==number){
        return 0;
    }

    while(root!=NULL){
        if (root->number==number){
            return 0;
        } else if ( (root->number > number)){
            root = root->leftNode;
        } else {
            root = root->rightNode;
        }
    }
    return 1;
}
