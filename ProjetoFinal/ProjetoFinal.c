#include <stdio.h>
#include <conio.h>
#define MAX_SIZE 5

/*definicao do tipo processo:
 - tempo em que foi criado/requisitado
 - tempo necessario para ser concluido
 - prioridade
*/ 
typedef struct{
    int requested; 
    int time_left; 
    int priority; 
}Process;

/*Estrutura do Buffer circular:
 - vetor a ser utilizado de forma circular
 - varivel de controle para indicacao do processo atual
 - variavel de controle para indicacao do ultimo processo no buffer
 - ponteiro que retem o escalonador utilizado para aquele buffer
*/
typedef struct {
    Process buffer[MAX_SIZE];
    int current_process;
    int final_process;
    void (*scheduler)(void);
}Buffer;

/*estrutura de controle do quantum:
 - contador
 - tamanho maximo de quantum a ser utilizado por um processo
*/ 
typedef struct{
    int count;
    int quantum_size;
}clock_tick;

typedef void (*ptrFunc)(void);

// escalonador Shortest Remaining-Time Next
void scheduler_SRTN(){}

// escalonador Shortest Process Next
void scheduler_SPN(){}

void init_Buffer(ptrFunc func){}

void add_process(Buffer* b, int request, int time, int priority){
    if((b->final_process+1) % MAX_SIZE != b->current_process){
        Process p = {request, time, priority};
        b->buffer[b->final_process] = p;
        b->final_process = (b->final_process+1) % MAX_SIZE;
    }
}

// retira os dados do arquivo de entrada stdin.txt preenchendo primeiro o buffer b1 e em seguida o buffer b2 
void get_dados(Buffer* b1, Buffer* b2){
    FILE* arq;
    int request, time, priority;

    arq = fopen("stdin.txt","r");

    if(arq == NULL){
        printf("Erro na leitura do arquivo ou arquivo vazio");
        fclose(arq);
        return;
    }
    
    while((fscanf(arq, "%d%d%d", &request, &time, &priority)!=-1) && b1->final_process<MAX_SIZE){
        add_process(b1,request,time,priority);
        
    }

    while((fscanf(arq, "%d %d %d", &request, &time, &priority)!=-1) && b2->final_process<MAX_SIZE){
        add_process(b2,request,time,priority);
    }

    fclose(arq);
}

void main (){
    
}
