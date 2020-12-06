#include <stdio.h>

int main() {
    unsigned char ip[4], tmp;
    scanf("%hhd.%hhd.%hhd.%hhd/%hhd", ip+3, ip+2, ip+1, ip, &tmp);
    int mask = (tmp == 32) ? 0 : (unsigned)~0 >> tmp;
    *(int *)ip &= ~mask; printf("%d.%d.%d.%d\n", ip[3], ip[2], ip[1], ip[0]);
    *(int *)ip |= mask ; printf("%d.%d.%d.%d\n", ip[3], ip[2], ip[1], ip[0]);
}