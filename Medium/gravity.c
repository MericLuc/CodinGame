#include <stdio.h>

int a[100];

main() {
    int w, h; scanf("%d%d", &w, &h);
    
    for (int i = 0; i < h; i++) {
        char line[257]; scanf("%s", line);
        for (int j = 0; j < w; j++) { a[j] += (line[j]=='#');           }
    }
    for (int i = h; i > 0; i--) {
        for (int j = 0; j < w; j++) { printf("%c", a[j] < i ? '.':'#'); }
        printf("\n");
    }
}