#include <stdio.h>
#include <conio.h>

#define MAX_SIZE 10
#define MAX_PROCESS 20
#define QUANTUM 5

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

Clock_tick clock;

typedef void (*ptrFunc)(Buffer*);

// Como ambos os métodos de escalonamento, aqui presentes, utilizam como parametro o tempo restante, foi 
// feito um escalonador generico para realizar o agendamento dos processos
void generic_scheduler(Buffer* buffer){
    if(buffer->current==buffer->final){
        return;
    }

    Process aux;
    int next = buffer->current;
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

int add_process(Buffer* b, Process processo){
    if((b->final+1) % MAX_SIZE != b->current){
        return 0;
    }

    b->processes[b->final] = processo;
    b->final = (b->final+1) % MAX_SIZE;
    return 1;
}

int remove_process(Buffer* buffer){
    if(buffer->current==buffer->final){
        return -1;
    }

    int aux = buffer->current;
    buffer->current = (buffer->current+1) % MAX_SIZE;
    return aux;
}

// Escalonador Shortest Remaining-Time Next
void scheduler_SRTN(Buffer* buffer){
    if(buffer->processes[buffer->current].time_left==0){ //Processo acababou
        remove_process(buffer);
        generic_scheduler(buffer);
        clock.quantum_size=QUANTUM;
    }else if(clock.quantum_size==0){ //Quantum estourou
        int aux;
        aux = remove_process(buffer);
        if(aux>-1)
            add_process(buffer, buffer->processes[aux]);
    }
}

// Escalonador Shortest Process Next
void scheduler_SPN(Buffer* buffer){
    if(buffer->processes[buffer->current].time_left==0){
        if(remove_process(buffer)>-1)
            generic_scheduler(buffer);
    }
}

void init_Buffer(Buffer* buffer, ptrFunc type_scheduler){
    buffer->current = 0;
    buffer->final = 0;
    buffer->scheduler = type_scheduler;
}

void init_clock_tick(){
    clock.count = 0;
    clock.quantum_size = QUANTUM;
}

// Retira os dados de um arquivo salvando-os como processos em um vetor  
void get_dados(Process* queue, char* file_name){
    FILE* arq;
    int request, time, priority, i;
    
    arq = fopen(file_name,"r");
    if(arq == NULL){
        printf("\nErro na leitura do arquivo\nVerifique se o arquivo está vazio ou na mesma pasta que o código fonte");
        fclose(arq);
        return;
    }
    
    i=0;
    while((fscanf(arq, "%d%d%d", &request, &time, &priority)!=-1) && i<MAX_PROCESS){
        queue[i].id = i;
        queue[i].requested = request;
        queue[i].time_left = time;
        queue[i].priority = priority;
        i++;
    }
    printf("\n%d processos foram adicionados.", i);
    fclose(arq);
}

void print_status(FILE* file, Buffer* buffer){
    fprintf(file,"\n================================================================================\n");
    fprintf(file,"Timing: %d \t Current process: P%d", clock.count, buffer->processes[buffer->current].id);
    fprintf(file,"\n-------------------------------------------------------------------------------\n");
    fprintf(file,"Waiting processes: ");
    for(int i=(buffer->current+1)%MAX_SIZE;i!=buffer->final;i=(i+1)%MAX_SIZE){
        fprintf(file,"P%d ", buffer->processes[i].id);
    }
    fprintf(file,"\n================================================================================\n");

}

void kernel(Buffer* buffer, Process* queue, char* file_name){
    int i;
    int last_time = 0; // variavel de controle para adicao de processos ao buffer
    int count_process = 0; // variavel de controle para encerramento do looping de rotina
    ptrFunc foo = buffer->scheduler;
    FILE* arq;

    arq = fopen(file_name,"a");
    
    while(1){
        //Adiciona processos no buffer se o mesmo não estiver cheio
        for(i=0; i<MAX_PROCESS; i++){
            if(queue[i].requested<=clock.count && queue[i].requested>=last_time){
                if(add_process(buffer, queue[i])){
                    count_process++;
                    last_time=clock.count;
                }
            }
        }

        foo(buffer); // Agendamento
        
        print_status(arq, buffer);

        //Avança tempo
        clock.count++;
        buffer->processes[buffer->current].time_left--;
        clock.quantum_size--;

        //Finaliza Kernel
        if(count_process==MAX_PROCESS && buffer->current==buffer->final)
            fclose(arq);
            return;
    }
}

void main (){
    return;
}


