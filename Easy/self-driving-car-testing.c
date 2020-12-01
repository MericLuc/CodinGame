#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct Cmd {
    char  dir  ;         // L, R, S
    int   times;         // number of times
};

bool Cmd_get( const char* p_in, struct Cmd *p_cmd ) {
    char tmp[100];
    if( p_in == NULL || strlen(p_in) < 2 ) return false;

    p_cmd->dir = p_in[strlen(p_in)-1];
    if ( p_cmd->dir != 'L' && p_cmd->dir != 'R' && p_cmd->dir != 'S' ) return false;
    memmove(tmp, p_in, (strlen(p_in)-1)*sizeof(char));
    p_cmd->times = atoi(tmp);
    return true;
}

void Cmd_updatePos(int *p_pos, struct Cmd *p_cmd) {
    if      ( p_cmd->dir == 'L' ) --(*p_pos);
    else if ( p_cmd->dir == 'R' ) ++(*p_pos);
}

void Cmd_exec( int *p_pos, char p_pattern[], struct Cmd *p_cmd ) {
    Cmd_updatePos(p_pos, p_cmd);
    p_pattern[*p_pos-1] = '#';
    printf("%s\n", p_pattern);
}

main() {
    int    N;               // Number of lines in the road pattern
    int    p_init;          // Car initial position
    int    cmd_numbers = 0; // Number of commands
    int    pat_numbers = 0; // Number of patterns
    struct Cmd cmds[100];   // Liste of the commands
    char patterns[100][257];// Liste des patterns
    char X[257];            // Input 1
    char R[257];            // Input 2
    
    scanf("%d", &N); fgetc(stdin);
    fgets(X, 257, stdin);
    
    if (X[strlen(X)-1] == '\n') { X[strlen(X)-1] = '\0'; }
    p_init = atoi( strtok(X, ";") );

    for(;;) {
        char *p = strtok(NULL, ";");
        if( !Cmd_get(p, &cmds[cmd_numbers]) ) break;
        memset( p, 0, strlen(p) );
        cmd_numbers++;
    }

    for (int i = 0; i < N; i++) {
        fgets(R, 257, stdin);
        if (R[strlen(R)-1] == '\n') { R[strlen(R)-1] = '\0'; }
        
        int R_number = atoi( strtok(R, ";") );
        char *p      = strtok(NULL, ";");
        for( int j = 0; j < R_number; j++ ) {
            memmove( patterns[pat_numbers++], p, strlen(p) * sizeof(char) );
        }
    }

    int tmp = 0;
    for ( int i = 0; i < cmd_numbers; i++ ) {
        for ( int j = 0; j < cmds[i].times; j++ ) {
            Cmd_exec(&p_init, patterns[tmp], &cmds[i]);
            tmp++;
        }
    }
}