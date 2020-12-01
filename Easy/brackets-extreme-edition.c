#include <stdio.h>

struct l_list { 
   char          data; 
   struct l_list *next; 
}; 
  
void push(struct l_list** ref, int new_data) {
  struct l_list* l_new = (struct l_list*) malloc(sizeof(struct l_list)); 
  l_new->data  = new_data; 
  l_new->next  = *ref;   
  *ref         = l_new; 
}
  
char pop(struct l_list** ref) {
  struct l_list *top = *ref;
  char result        = top->data; 
  *ref               = top->next; 
  free(top); 
  return result;
}
  
int matching(const char c1, const char c2) { 
    return ( (c1 == '{' && c2 == '}') || (c1 == '[' && c2 == ']') || (c1 == '(' && c2 == ')') ); 
} 

void main() {
    struct sNode *stack = NULL; 
    char e[2049];
    scanf("%s", e);

    for (int i = 0; i < strlen(e); ++i)
      if      (e[i] == '{' || e[i] == '(' || e[i] == '[') push(&stack, e[i]); 
      else if (e[i] == '}' || e[i] == ')' || e[i] == ']') 
        if ( ( stack == NULL ) || ( !matching(pop(&stack), e[i]) ) ) { printf("false\n"); return; }
      printf("%s", (stack == NULL) ? "true\n" : "false\n");
}