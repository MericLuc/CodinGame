#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Calcule la position d'une abscisse/ordonnée après 1 itération
int prime(int pos, int dim)
{
    return (pos%2 == 0) ? pos/2 : pos/2 + dim/2;
}

// Calcule la période pour tous les éléments d'une ligne/colonne
void compute1D(int* line, int* out_size, int dim)
{
    int x;
    int cmpt = 0;
    for ( int i = 0; i < dim; ++i )
    {
        cmpt = 0;
        x    = i;
        do { ++cmpt; x = prime(x, dim); } while( x != i );
        
        // Add to the array if not in it already
        bool dbl = false;
        for(int j = 0; j < *out_size; j++)
            if( line[j] == cmpt ) { dbl = true; break; }
       
        if( !dbl ) { line[*out_size] = cmpt; (*out_size)++; }
    }
}

// Calcule le PPCM de deux entiers
int lcm(int a, int b)
{
    int m = 1;
    while(m%a || m%b) m++;
 
    return m;
}

// Calcule le PPCM de tous les nombres d'un tableau
long long ppcm(int* arr, int size)
{
    int result = arr[0];
 
    for (int i = 1; i < size; ++i)
        result = lcm(result, arr[i]);
        
    return result;
}

// Calcule la période de retour
// (i.e. le ppcm de la période de chaque pixel)
long long computeT(int dim_x, int dim_y)
{
    int size = 0;
    int T[dim_x + dim_y];

    compute1D(T, &size, dim_x);
    compute1D(T, &size, dim_y);

    return ppcm(T, size);
}

main()
{
    int it;   // Iterations
    int W, H; // Image dimensions
    
    scanf("%d", &it);
    while(it--) 
    {
        scanf ("%d%d", &W, &H        );
        printf("%d\n", computeT(W, H));
    }
}