#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef enum {AND, OR, NAND, NOR, XOR, NOT, PASS, DECODER, MULTIPLEXER, NONE} type_t;
char *kinds[17] = {"AND","OR","NAND","NOR","XOR","NOT","PASS","DECODER","MULTIPLEXER","NONE"};

typedef struct gate_linkedlist{
    type_t typeOfGate;
    int num_inputs;
    int num_outputs;
    int num_selectors;
    int *inputs;
    int *outputs;
    struct gate_linkedlist *next;
} gate;

typedef struct ctable{
    int num_inputs;
    int num_outputs;
    int num_variables;
    int num_gates;
    char *outputs;
    char *inputs;
    char *variables;
    int *indexes;
    gate *head;
}circuit;

type_t stringToEnum_Convert (char type[17]){
    for (int i = 0; i < 9; i++)
        if (strcmp(type,kinds[i])==0) 
            return i;
    return NONE;
}


void pushGate(circuit **circ, gate **head, char type[17], int num_inputs, int num_outputs, int *inputs, int *outputs){
    gate *new = malloc(sizeof(gate));

    new->outputs = outputs;
    new->num_outputs = num_outputs;
    new->num_inputs = num_inputs;
    new->inputs = inputs;
    new->next = NULL;
    new->typeOfGate = stringToEnum_Convert(type);

    if (new->typeOfGate == MULTIPLEXER){ 
        
        new->num_selectors = log2(num_inputs);
        new->num_inputs += new->num_selectors;
    } else new->num_selectors = 0;

    if (*head == NULL) (*head) = new;
    else {
        gate *tmp = *head;
        for (; tmp->next != NULL; tmp = tmp->next){} 
        tmp->next = new;
    }

    (*circ)->num_gates++;
}

void createNewVariable(circuit **circ, char *k){
    (*circ)->variables = realloc((*circ)->variables, ((*circ)->num_variables+1)*17*sizeof(int));
    (*circ)->indexes = realloc((*circ)->indexes, ((*circ)->num_variables+1)*sizeof(int));

    sprintf((*circ)->variables + ((*circ)->num_variables)*17,"%s",k);
    (*circ)->indexes[(*circ)->num_variables] = (*circ)->num_variables;

    (*circ)->num_variables ++;
}

int getVariable(circuit *circ, char *k){
    for (int i = 0; i < circ->num_variables; i++)
        if (strcmp(circ->variables + (i*17), k)==0)
            return i;
    
    return -1;
}

void circuitCompute(circuit *c, int n, int **input);

int main(int argc, char const *argv[]){

    FILE* file = fopen(argv[1],"r");
    circuit *circ = malloc(sizeof(circuit));
    circ->num_variables = 2;
    circ->num_gates = 1;
    circ->head = NULL;
    fscanf(file, "INPUT %d", &circ->num_inputs);
    circ->inputs = malloc((circ->num_inputs)*sizeof(char)*17);

    circ->variables = malloc(17*circ->num_inputs*sizeof(char));
    circ->indexes = malloc(circ->num_inputs*sizeof(int));


    
    for (int i = 0; i < 2; i++){
        sprintf(circ->variables+(i*17), "%d", i);
        circ->indexes[i] = i;
    }
    
    for (int i = 0; i < circ->num_inputs; i++){
        fscanf(file, "%s ", circ->inputs+(17*i));
        createNewVariable(&circ, circ->inputs+(17*i));
    }

    fscanf(file, "OUTPUT %d", &circ->num_outputs);
    circ->outputs = malloc(17*circ->num_outputs*sizeof(char));
    for (int i = 0; i < circ->num_outputs; i++){
        fscanf(file, "%s ", circ->outputs+(17*i));
        createNewVariable(&circ, circ->outputs+(17*i));
    }

    char gate_name[17];
    while (fscanf(file, "%16s", gate_name) != EOF) {
        int in = 0, out = 1, sel = 0;
        
        if (strcmp(gate_name,"MULTIPLEXER")==0 || strcmp(gate_name,"DECODER")==0){
            fscanf(file, "%d", &in);
            if (strcmp(gate_name,"DECODER")==0) out = pow(2,in);
            else                                sel = in, in = pow(2,in);
        } else
            if (strcmp(gate_name,"PASS")==0 || strcmp(gate_name,"NOT")==0)      in = 1;
            else                                                                in = 2;

        int *inputs = malloc((in+sel)*sizeof(int));
        int *outputs = malloc(out*sizeof(int));

        for (int i = 0; i < in+out+sel; i++, out=out){
            char var[17] = "";
            fscanf(file, "%s", var);
            int vi = getVariable(circ, var);

            if (i < in+sel) inputs[i] = (vi == -1) ? circ->num_variables : vi;                
            else            outputs[i-in-sel] = (vi == -1) ? circ->num_variables : vi;
            
            if (vi == -1) createNewVariable(&circ, var);
        }

        pushGate(&circ, &(circ->head), gate_name, in, out, inputs, outputs);
    }
    int bits = pow(2, circ->num_inputs);
    int *input = malloc(sizeof(int)*bits);
    for (int i = 0; i < circ->num_inputs; i++) input[i] = 0;
    for (int i = 0; i < bits; i++){
        circuitCompute(circ, circ->num_inputs, &input);

        for (int i = 0; i < bits; i++){ 
            input[i] = !input[i];
            if (input[i]==1) break;
        }
    }

    free(input);
    
    free(circ->inputs);
    free(circ->outputs);
    free(circ->indexes);
    free(circ->variables);
    gate* startPoint = circ->head;
    while(startPoint!=NULL){
        free(startPoint->inputs);
        free(startPoint->outputs);
        gate* del = startPoint;
        startPoint = startPoint->next;
        free(del);
    }

    free(circ);

    return 0;
}



void circuitCompute(circuit *c, int n, int **input){
    int num_vars = c->num_variables;

    int *mem_v = malloc(num_vars*sizeof(int));
    mem_v[0] = 0, mem_v[1] = 1;

    for (int i = 2; i < n+2; i++) mem_v[i] = (*input)[n-i+1];
    for (int i = 2; i < n+2; i++) printf("%d ",mem_v[i]); 

    printf("|");
    

    for (gate *tmp = c->head; tmp != NULL; tmp = tmp->next){
        int *inputs = malloc(tmp->num_inputs*sizeof(int));
      
        for (int i = 0; i < tmp->num_inputs; i++){
            inputs[i] = mem_v[tmp->inputs[i]];
            
        }
        int output = 0;
        if (tmp->typeOfGate==AND){
            output = inputs[0]&inputs[1];
        } else if (tmp->typeOfGate==OR){
             if (inputs[0]+inputs[1]==2){
                output = 1;
            } else {
                output = inputs[0] | inputs[1];
            }
        }else if (tmp->typeOfGate==NAND){
            output = !(inputs[0]&inputs[1]);
        }else if (tmp->typeOfGate==NOR){

            if (inputs[0]+inputs[1]==2){
                output = 0;
            } else {
                output = !(inputs[0] | inputs[1]);
            }

        }else if (tmp->typeOfGate==XOR){
            output = (~inputs[0]&inputs[1])|(inputs[0]&~inputs[1]);
        }else if (tmp->typeOfGate==NOT){
            output = ~inputs[0];
        }else if (tmp->typeOfGate==PASS){
            output = inputs[0];
        }else if (tmp->typeOfGate==DECODER){
        int s = 0;
            for (int j = tmp->num_inputs-1; j>=0;j--){
            s += pow(2,tmp->num_inputs-j-1)*inputs[j];
        }
        output = s;

        }else if (tmp->typeOfGate==MULTIPLEXER){

            int numberset = log2(tmp->num_inputs-tmp->num_selectors);
            int s = 0;
            for (int k = 0; k< numberset;k++){
                s+= inputs[k+tmp->num_inputs-tmp->num_selectors] * pow(2, numberset-k-1);
            }
            output = inputs[s];

        } else {
            printf("INVALID GATE TYPE: %d=%s\n",tmp->typeOfGate,kinds[tmp->typeOfGate]); output = 0;

        }
        if (tmp->typeOfGate == DECODER){
            for (int i = 0; i < tmp->num_outputs; i++){
                mem_v[tmp->outputs[i]] = (i == output);
            
            }
        } else {
            mem_v[tmp->outputs[0]] = output;
          
        }

        free(inputs);
    }


    for (int i = 0; i < c->num_outputs; i++){
  
        printf(" %d",mem_v[c->num_inputs+i+2]);
    }

    printf("\n");
    free(mem_v);
}