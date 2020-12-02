#include <stdio.h>
#include <string.h>

main() {
    char op[257];    fgets(op, 257, stdin);
    int  num;        scanf("%d", &num); fgetc(stdin);
    char rot[3][27];
    char mesg[1025];

    for (int i = 0; i < 3; i++) { fgets(rot[i], 27, stdin); fgetc(stdin); }
    fgets(mesg, 1025, stdin);
    
    if     (op[0] == 'E') {
        for (int i = 0; i < strlen(mesg); i++) { mesg[i] = ((mesg[i] -'A' + num + i ) % 26)+'A'; }
        for (int i = 0; i < 3; i++) for(int j = 0; j < strlen(mesg); j++) { mesg[j] = rot[i][mesg[j]-'A']; }
    }
    else if(op[0] == 'D') {
        for (int i = 2; i >= 0; i--)
            for(int j = 0; j < strlen(mesg); j++)
                for ( int c = 0; c < strlen(rot[i]); c++)
                    if(rot[i][c]==mesg[j]) { mesg[j] = 'A'+c; break; }
        for (int i = 0; i < strlen(mesg); i++) { 
            int idx = (mesg[i] +'A' - (num + i));
            idx    += (idx<0)?26:0;
            mesg[i] = (idx % 26)+'A'; 
        }
    }
    printf("%s\n", mesg);
}