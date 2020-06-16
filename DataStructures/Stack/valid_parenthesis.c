#include <stdbool.h>
#include <stdlib.h>

typedef struct node_ node_t;

struct node_ {
    char ch;
    struct node_ *next;
};

bool push (node_t **head, char ch) {
    if (!head) return false;
    node_t *node = calloc(1, sizeof *node);
    if (!node) return false;
    switch (ch) {
        case '(':
            node->ch = ')';
            break;
        case '[':   
            node->ch = ']';
            break;
        case '{':   
            node->ch = '}';
            break;
        default:
            free(node);
            return false;
    }
    if (!*head) {
        *head = node;
        return true;
    }
    node->next = *head;
    *head = node;
    return true;
}

bool pop (node_t **head, char *ch) {
    if (!head || !ch || !*head) return false;
    node_t *node = *head;    
    *head = node->next;
    *ch = node->ch;
    free(node);
    return true;
}

bool isValid(char * s){

    // Parentheses are ( ), brackets are square [ ], and braces are curly { }
    int parentheses, brackets, braces;
    parentheses = brackets = braces = 0;
    node_t *node = NULL;
    
    while (s && *s != '\0') {
        char ch = *s++;
        char chpop = '\0';
        switch (ch) {
            case '(':  
                parentheses++;
                push(&node, ch);
                break;
            case ')':
                if (parentheses == 0) return false;
                parentheses--;
                pop(&node, &chpop);
                if (chpop != ch) return false;
                break;
            case '[':
                brackets++;
                push(&node, ch);
                break;
            case ']':
                if (brackets == 0) return false;
                brackets--;
                pop(&node, &chpop);
                if (chpop != ch) return false;
                break;
            case '{':
                braces++;
                push(&node, ch);
                break;
            case '}':
                if (braces == 0) return false;
                braces--;
                pop(&node, &chpop);
                if (chpop != ch) return false;
                break;
            default:
                return false;
        }
    }
    return (parentheses || brackets || braces) ? false : true ;
}


int main () {

    bool ret = isValid("()[]{}");

    return 0;
}
