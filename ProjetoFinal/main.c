#include <stdio.h>
#include <conio.h>
#include "shortTime.h"

void main (){
    Buffer b;
    Process fila[MAX_PROCESS];

    init_Buffer(&b,scheduler_SPN);
    get_dados(fila,"stdin.txt");
    init_clock_tick();
    int c=0;
    for(int i=0;i<MAX_PROCESS;i++){
        c+=fila[i].time_left;
    }
    printf("\n\nTempo necessario: %d\n",c);
    kernel(&b,fila,"stdout.txt");
    return;
}
