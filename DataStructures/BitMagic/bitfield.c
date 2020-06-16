#include <stdio.h>
typedef enum e_ myenum;

enum e_ { 
    A, 
    B 
}; 

struct foo_ {
        myenum      a_or_b  : 8;
};

int main() {

	printf("size : %lu \n", sizeof(struct foo_));
}
