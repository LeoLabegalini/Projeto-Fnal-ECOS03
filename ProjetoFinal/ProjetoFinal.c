#include <stdio.h>
#include <conio.h>
#define MAX_SIZE 5

/*Definicao do tipo processo:
 - tempo em que foi criado/requisitado
 - tempo necessario para ser concluido
 - prioridade
*/ 
typedef struct{
    int id;
    int requested; 
    int time_left; 
    int priority; 
}Process;

/*Estrutura do Buffer circular:
 - vetor a ser utilizado de forma circular
 - varivel de controle para indicacao do primeiro processo no buffer
 - variavel de controle para indicacao do ultimo processo no buffer
 - ponteiro que retem o escalonador utilizado para aquele buffer
*/
typedef struct no{
    Process processes[MAX_SIZE];
    int current;
    int final;
    void (*scheduler)(struct no*);
}Buffer;

/*Estrutura de controle do quantum:
 - contador
 - tamanho maximo de quantum a ser utilizado por um processo
*/ 
typedef struct{
    int count;
    int quantum_size;
}Clock_tick;

//Clock_tick tick;

typedef void (*ptrFunc)(Buffer*);

// Escalonador Shortest Remaining-Time Next
void scheduler_SRTN(Buffer* buffer){}

// Escalonador Shortest Process Next
void scheduler_SPN(Buffer* buffer){}

void init_Buffer(Buffer* buffer, ptrFunc type_scheduler){
    buffer->current = 0;
    buffer->final = 0;
    buffer->scheduler = type_scheduler;
}

// void init_clock_tick(int size){
//     tick.count = 0;
//     tick.quantum_size = size;
// }

int add_process(Buffer* b, int id, int request, int time, int priority){
    if((b->final+1) % MAX_SIZE != b->current){
        return 0;
    }

    Process p = {id, request, time, priority};
    b->processes[b->final] = p;
    b->final = (b->final+1) % MAX_SIZE;
    return 1;
}

// Retira os dados do arquivo de entrada stdin.txt preenchendo primeiro o buffer b1 e em seguida o buffer b2 
void get_dados(Buffer* b1, Buffer* b2){
    FILE* arq;
    int request, time, priority, i;
    
    arq = fopen("stdin.txt","r");
    if(arq == NULL){
        printf("Erro na leitura do arquivo ou arquivo vazio");
        fclose(arq);
        return;
    }
    
    i=0;
    while((fscanf(arq, "%d%d%d", &request, &time, &priority)!=-1) && b1->final<MAX_SIZE){
        if(add_process(i++, b1,request,time,priority) == 0){
            break;
        }
    }

    while((fscanf(arq, "%d %d %d", &request, &time, &priority)!=-1) && b2->final<MAX_SIZE){
        if(add_process(i++, b2,request,time,priority) == 0){
            break;
        }
    }
    printf("\nOs %d primeiros processos foram adicionados aos buffers", i);
    fclose(arq);
}

void main (){
    
}
