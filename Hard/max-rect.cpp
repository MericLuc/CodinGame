#include <stdio.h>
#include <limits.h>

int H, W;

int maxSum1D(int* arr, int* st, int* end ) { 
    int sum = 0, l_st = 0, res = INT_MIN; *end = -1; 
  
    for (int i = 0; i < H; ++i) { 
        sum += arr[i]; 
        if      (sum < 0  ) { sum = 0; l_st = i+1;             } 
        else if (sum > res) { res = sum; *st = l_st; *end = i; } 
    } 

    if (*end != -1) return res; 
  
    res = arr[0]; *st = *end = 0; 
    for (int i = 1; i < H; i++) if (arr[i] > res) { res = arr[i]; *st = *end = i; } 
    return res; 
} 

int maxSum2D(int c[101][101]) { 
    int res = INT_MIN, l_lft, l_rht, l_top, l_bot; 
    int left, right, sum, start, finish; 
  
    for (left = 0; left < W; ++left) { 
       int tmp[H] = {0};

        for (right = left; right < W; ++right) { 
            for (int i = 0; i < H; ++i) { tmp[i] += c[i][right]; }
            
            sum = maxSum1D(tmp, &start, &finish);
            if (sum > res) { res = sum; l_lft = left; l_rht = right; l_top = start; l_bot = finish; } 
        } 
    }
    return res;
}

main() {
    int arr[101][101];
    scanf("%d%d", &W, &H); fgetc(stdin);
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++) { scanf("%d", &arr[i][j]); }
    
    printf("%d\n", maxSum2D(arr) );
}