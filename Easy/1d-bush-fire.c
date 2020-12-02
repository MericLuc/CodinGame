#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main()
{
    int          tests;
    scanf("%d", &tests); fgetc(stdin);
    while ( tests-- ) 
    {
        char line[256];
        fgets(line, 256, stdin);
        
        int l_result = 0;
        
        for ( int j = 0; j < strlen(line); ++j )
            if ( line[j] == 'f' ) { ++l_result; j+=2; }
        
        printf("%d\n", l_result);
    }
}