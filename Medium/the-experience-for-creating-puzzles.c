void main() {
    int Level, Xp, N; scanf("%d%d%d", &Level, &Xp, &N);
    for (int i = 0; i < N; ++i) {
        Xp -= 300;
        while (Xp <= 0) { Level++; Xp += (int)(Level * sqrt(Level) * 10); }
    }
    printf("%d\n%d\n", Level, Xp);
}