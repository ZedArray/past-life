#include <stdio.h>

typedef enum States {
    State1,
    State2,
    State3,
    State4
}States;

int add(int a, int b) {
    return a+b;
}

int sub(int a, int b) {
    return a-b;
}

void le(int a, int b, int (*op)(int, int)) {
    printf("%d\n", op(a, b));
}

int main() {
    States s;
    s = State1;
    switch (s)
    {
    case State1:
        printf("Currently on state1\n");
        break;
    
    case State2:
        printf("Stat2\n");
        break;
    
    default:
        break;
    }
}