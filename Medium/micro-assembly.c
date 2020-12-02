#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int a, b, c, d, n, tmp_val;
int current_instruction = 0;
char _ins[16][17];
char tmp_i[17];

int* getVar( char* p_o ) {
    switch( *p_o ) {
        case 'a' : return &a;
        case 'b' : return &b;
        case 'c' : return &c;
        case 'd' : return &d;
        default  : tmp_val = atoi(p_o); return &tmp_val;
    }
}

void executeInstruction ( char p_ins[17] ) {
    strcpy(tmp_i, p_ins); current_instruction++;
    char *op[4] = { strtok(tmp_i, " "), strtok(NULL, " "), strtok(NULL, " "), strtok(NULL, " ") };
    if      ( strcmp(op[0], "MOV") == 0 ) { *getVar(op[1]) = *getVar(op[2]);                                                   }
    else if ( strcmp(op[0], "ADD") == 0 ) { *getVar(op[1]) = *getVar(op[2]) + *getVar(op[3]);                                  }
    else if ( strcmp(op[0], "SUB") == 0 ) { *getVar(op[1]) = *getVar(op[2]) - *getVar(op[3]);                                  }
    else if ( strcmp(op[0], "JNE") == 0 ) { if ( *getVar(op[2]) != *getVar(op[3]) ) { current_instruction = atoi(op[1]); }     }
}

main() {
    scanf("%d%d%d%d%d", &a, &b, &c, &d, &n); fgetc(stdin);    
    for (int i = 0; i < n; i++) { fgets(_ins[i], 17, stdin); if(_ins[i][strlen(_ins[i])-1] == '\n') _ins[i][strlen(_ins[i])-1] = '\0'; }
    
    while(current_instruction < n)  executeInstruction(_ins[current_instruction]);
    printf("%d %d %d %d\n", a, b, c, d);
}