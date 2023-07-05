#include <stdio.h>
#include <conio.h>
#define MAX_SIZE 10

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

void generic_scheduler(Buffer* buffer){
    if(buffer->current==buffer->final){
        return;
    }

    Process aux;
    int next = (buffer->current+1)%MAX_SIZE;
    int i = (next+1)%MAX_SIZE;

    while(i != buffer->final){
        if((buffer->processes[i].time_left < buffer->processes[next].time_left)||
            ((buffer->processes[i].time_left == buffer->processes[next].time_left) &&
            (buffer->processes[i].priority > buffer->processes[next].priority))){
            next=i;
        }
        i = (i+1)%MAX_SIZE;
    }

    aux=buffer->processes[(buffer->current+1)%9];
    buffer->processes[(buffer->current+1)%9]=buffer->processes[next];
    buffer->processes[next]=aux;
}

Process* remove_process(Buffer* buffer){
    if(buffer->current==buffer->final){
        return NULL;
    }

    int aux = buffer->current;
    buffer->current = (buffer->current+1) % MAX_SIZE;
    return &buffer->processes[aux];
}

// Escalonador Shortest Remaining-Time Next
void scheduler_SRTN(Buffer* buffer){
    //...
    generic_scheduler(buffer);
    //...
}

// Escalonador Shortest Process Next
void scheduler_SPN(Buffer* buffer){
    //...
    generic_scheduler(buffer);
    //...
}

void init_Buffer(Buffer* buffer, ptrFunc type_scheduler){
    buffer->current = 0;
    buffer->final = 0;
    buffer->scheduler = type_scheduler;
}

// void init_clock_tick(int size){
//     tick.count = 0;
//     tick.quantum_size = size;
// }

int add_process(Buffer* b, Process processo){
    if((b->final+1) % MAX_SIZE != b->current){
        return 0;
    }

    b->processes[b->final] = processo;
    b->final = (b->final+1) % MAX_SIZE;
    return 1;
}

// Retira os dados do arquivo de entrada stdin.txt salvando-os na fila  
void get_dados(Process* queue, int size){
    FILE* arq;
    int request, time, priority, i;
    
    arq = fopen("stdin.txt","r");
    if(arq == NULL){
        printf("\nErro na leitura do arquivo\nVerifique se o arquivo está vazio ou na mesma pasta que o código fonte");
        fclose(arq);
        return;
    }
    
    i=0;
    while((fscanf(arq, "%d%d%d", &request, &time, &priority)!=-1) && i<size){
        queue[i].id = i;
        queue[i].requested = request;
        queue[i].time_left = time;
        queue[i].priority = priority;
        i++;
    }
    printf("\n%d processos foram adicionados.", i);
    fclose(arq);
}

void main (){
    return;
}

void kernel(Buffer buffer, Process process[], Clock_tick clock){
    int i;

    //Adiciona processos no buffer
    while(1){
        for(i=0;i<20;i++){
            if(process[i].requested==count)
        add_process(process[i]);
    }
    //Avança tempo
    clock.cout++;
    buffer[current].time_left--;
    clock.quantum_size--;

    //Processo acababou
    if(time_left==0){
        buffer.current=(buffer.current+1) %9;
        clock.quantum_size=QUANTUM;
    }else{
        //Quantum estourou
        if(quantum==0){
            add_process(buffer.processes[buffer.current]);
            buffer.current=(buffer.current+1) %9;
        }
    }
    //Escreve processo atual
    printi" t"=count "process" = buffer.current

    //Finaliza Kernel
    if(fila==NULL  and current==final)
        return;
    }
}
