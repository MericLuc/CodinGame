#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MACRO
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define BUFF_LEN 256
#define MAX_VAL  999
#define MIN_VAL  -MAX_VAL

#define ALLOC(p, n)                                         \
do                                                          \
{                                                           \
    if ( !( (p) = malloc((n) * sizeof(*(p)) ) ) )           \
    {                                                       \
        fprintf(stderr, "Memory allocation failed");        \
        exit(EXIT_FAILURE);                                 \
    }                                                       \
    memset( (p), 0, (n) * sizeof(*(p)) );                   \
}                                                           \
while(0)

#define ALLOC_ARR(p, n)                                     \
do                                                          \
{                                                           \
    if ( !( (p) = malloc((n) * sizeof(*(p)) ) ) )           \
    {                                                       \
        fprintf(stderr, "Memory allocation failed");        \
        exit(EXIT_FAILURE);                                 \
    }                                                       \
    for ( int i = 0; i < (n); ++i )                         \
    {                                                       \
        if ( !( *(p + i) = malloc(BUFF_LEN * sizeof(*(p)))))\
        {                                                   \
            fprintf(stderr, "Memory allocation failed");    \
            exit(EXIT_FAILURE);                             \
        }                                                   \
        memset( *(p + i), 0, BUFF_LEN * sizeof(*(p)) );     \
    }                                                       \
}                                                           \
while(0)

#define TK strtok(NULL, " ")

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// STRUCTS
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
typedef struct LblMap {
    uint _capacity;
    uint _count;

    int*           _lines; /*< Lines containing labels */
    unsigned long* _hashs; /*< Hashed values of the corresponding labels */
} LblMap;

unsigned long lbl_hash(const char *str) {
    unsigned long ret = 5381;
    int c;

    while (c = *str++) ret = ((ret << 5) + ret) + c;
    return ret;
}

LblMap* lbl_new(uint capacity) {
    LblMap* ret;
    ALLOC(ret, 1);

    ret->_capacity = capacity;
    ret->_count    = 0;
    ALLOC(ret->_lines, ret->_capacity);
    ALLOC(ret->_hashs, ret->_capacity);

    return ret;
}

int lbl_del(LblMap* map) {
    // TODO
}

int lbl_add(LblMap* map, const char* label, int line) {
    if ( NULL == map || NULL == label  ) return 0;
    if ( map->_count >= map->_capacity ) return 0;

    ++map->_count;

    fprintf(stderr, "\tlbl_add(%s, %d)\n", label, line);

    unsigned long hash = lbl_hash(label);
    map->_lines[map->_count - 1] = line;
    map->_hashs[map->_count - 1] = hash;
}

int lbl_get(LblMap* map, const char* label, int* ret) {
    if ( NULL == map || NULL == label ) return 0;

    unsigned long hash = lbl_hash(label);
    for ( int i = 0; i < map->_count; ++i ) {
        if ( hash == map->_hashs[i] ) {
            *ret = map->_lines[i];
            return 1;
        }
    }
    return 0;
}

int clmp(int ret) {
    return (ret > MAX_VAL) ? MAX_VAL : (ret < MIN_VAL) ? MIN_VAL : ret;
}

char *trimwhitespace(char *str) {
    char *end;

    while (isspace((unsigned char)*str)) str++;

    if (*str == 0) return str;

    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\0';

    return str;
}

int get_digit(int val, int n) {
    static int po10[] = {1, 10, 100};
    return ((val / po10[n]) % 10);
}

void set_digit(int* val, int n, int new_digit) {
    static int po10[] = {1, 10, 100};
    *val = *val - ((*val / po10[n]) % 10) * po10[n] + new_digit * po10[n];
}

typedef enum {
    RET_FAILURE,
    RET_SUCCESS
} RET_VAL;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// GLOBAL VARIABLES
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool    BPLUS = false, BMINUS = false;
int     k, n, code_size = 0;
int    *acc, *dat, *x0;
char**  code   = NULL;
LblMap* labels = NULL;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// FUNCTIONS
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int buff_read(const char* reg) {
    fprintf(stderr, "\tbuff_read(%s)\n", reg);
    if      ( 0 == strncmp("acc", reg, BUFF_LEN) ) return *acc;
    else if ( 0 == strncmp("dat", reg, BUFF_LEN) ) return *dat;
    else if ( 0 == strncmp("x0" , reg, BUFF_LEN) ) return *x0++;
    else                                           return strtol(reg, NULL, 10);
}

RET_VAL buff_nwrite(const char* reg, int val) {
    fprintf(stderr, "\tbuff_nwrite(%s,%d)\n", reg, val);
    static bool first = true;
    if      ( 0 == strncmp("acc", reg, BUFF_LEN) ) *acc = val;
    else if ( 0 == strncmp("dat", reg, BUFF_LEN) ) *dat = val;
    else if ( 0 == strncmp("x1" , reg, BUFF_LEN) ) {
        if ( first ) fprintf(stdout, "%d" , val), first = false;
        else         fprintf(stdout, " %d", val);
    }
    return RET_SUCCESS;
}

RET_VAL buff_vwrite(int* reg, int* val) {
    if ( NULL == reg || NULL == val ) return RET_FAILURE;
    *reg = *val;
    return RET_SUCCESS;
}

RET_VAL label_get(const char* label, int* ret) {
    return (RET_VAL)(lbl_get(labels, label, ret));
}

RET_VAL label_add(const char* label, int line) {
    return (RET_VAL)(lbl_add(labels, label, line));
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MAIN
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main() {
    int i;

    // --------------------------
    // MEMORY INITIALIZATION
    // --------------------------
    ALLOC    (x0  , 100);
    ALLOC    (acc ,   1);
    ALLOC    (dat ,   1);
    ALLOC_ARR(code,  40);
    labels = lbl_new(20);

    scanf("%d", &k);
    for (i = 0; i < k; ++i) scanf("%d", x0 + i);

    // --------------------------
    // PREPROCESS CODE
    // --------------------------
    scanf("%d", &n); fgetc(stdin);
    for (i = 0; i < n; ++i) {
        char* line, *jmp_label, *jmp_inst;
        scanf("%[^\n]", code[code_size]), fgetc(stdin);
        line = code[code_size];

        if ( '#' == line[0] ) continue;

        if ( NULL == strchr(line, ':') ) { ++code_size; continue; }

        jmp_label = strtok(line, ":");
        jmp_inst  = strtok(NULL, ":");

        label_add(jmp_label, code_size);

        if ( NULL != jmp_inst ) code[code_size++] = trimwhitespace(jmp_inst);
    }

    // --------------------------
    // EXECUTE CODE
    // --------------------------
    i = 0;
    while ( i < code_size ) {
        int   val;
        char* line = strdup(code[i]);
        char* tkn  = strtok(line, " ");

        // Instruction modifiers
        if ( NULL == tkn                ) goto next;
        if ( '#' == *tkn || '$' == *tkn ) goto next;
        if ( '+' == *tkn && !BPLUS      ) goto next;
        if ( '-' == *tkn && !BMINUS     ) goto next;
        if ( '@' == *tkn                ) { tkn = TK; code[i][0] = '$'; }
        if ( '-' == *tkn || '+' == *tkn ) tkn = TK;

        // Arithmetic instructions
        if      ( 0 == strncmp("add", tkn, 3) ) *acc = clmp( *acc + buff_read( TK ) );
        else if ( 0 == strncmp("sub", tkn, 3) ) *acc = clmp( *acc - buff_read( TK ) );
        else if ( 0 == strncmp("mul", tkn, 3) ) *acc = clmp( *acc * buff_read( TK ) );
        else if ( 0 == strncmp("not", tkn, 3) ) *acc = (0 == *acc) ? 100 : 0;
        else if ( 0 == strncmp("dgt", tkn, 3) ) *acc = get_digit(*acc, buff_read( TK ));
        else if ( 0 == strncmp("dst", tkn, 3) ) val = buff_read( TK ), set_digit(acc,
                    val, buff_read( TK ) );

        // Basic instructions
        else if ( 0 == strncmp("mov", tkn, 3) ) val = buff_read(TK), buff_nwrite(TK,
                    val);
        else if ( 0 == strncmp("jmp", tkn, 3) ) { label_get(TK, &i); goto free_data; }

        // Branching instructions
        else if ( 0 == strncmp("teq", tkn, 3) ) {
            if ( buff_read(TK) == buff_read(TK) ) BPLUS = true , BMINUS = false;
            else                                  BPLUS = false, BMINUS = true ;
        } else if ( 0 == strncmp("tgt", tkn, 3) ) {
            if ( buff_read(TK) > buff_read(TK) ) BPLUS = true , BMINUS = false;
            else                                 BPLUS = false, BMINUS = true ;
        } else if ( 0 == strncmp("tlt", tkn, 3) ) {
            if ( buff_read(TK) < buff_read(TK) ) BPLUS = true , BMINUS = false;
            else                                 BPLUS = false, BMINUS = true ;
        } else if ( 0 == strncmp("tcp", tkn, 3) ) {
            int A = buff_read(TK), B = buff_read(TK);
            if      ( A == B ) BPLUS = false, BMINUS = false;
            else if ( A >  B ) BPLUS = true , BMINUS = false;
            else if ( A <  B ) BPLUS = false, BMINUS = true ;
        }

next:
        ++i;

free_data:
        free(line);
    }

    return EXIT_SUCCESS;
}