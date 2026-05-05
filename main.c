#include <stdio.h>

typedef enum States {
    NONE,
    BOOT,
    IDLE,
    NOMINAL,
    LOW_POWER,
    FAULT,
    SAFE
}States;

typedef struct fsm {
    States currState;
    States prevState;
}fsm;

char* getName(States state) {
    switch (state)
    {
    case NONE:
        return "NONE";
        break;
    
    case BOOT:
        return "BOOT";
        break;

    case IDLE:
        return "IDLE";
        break;

    case NOMINAL:
        return "NOMINAL";
        break;
    
    case LOW_POWER:
        return "LOW_POWER";
        break;
    
    case FAULT:
        return "FAULT";
        break;
    
    case SAFE:
        return "SAFE";
        break;
    
    default:
        break;
    }
}

void boot_state(fsm state) {
    printf("Entering %s state, leaving %s state\n", getName(state.currState), getName(state.prevState));
}
void idle_state();
void nominal_state();
void lp_state();
void fault_state();
void safe_state();

void state_loop(fsm state) {
    // while (state.currState != NONE) {
        switch (state.currState)
        {
        case BOOT:
            boot_state(state);
            break;

        case IDLE:
            printf("Current state is IDLE\n");
            break;

        case NOMINAL:
            printf("Current state is NOMINAL\n");
            break;

        case LOW_POWER:
            printf("Current state is LOW_POWER\n");
            break;

        case FAULT:
            printf("Current state is FAULT\n");
            break;

        case SAFE:
            printf("Current state is SAFE\n");
            break;
            
        default:
            break;
        }
        // printf("Select which state to go next: ");
        // scanf("%d", &state);
        // if (state > 5) {
        //     printf("State does not exist. Moving into IDLE state\n");
        //     state = 1;
        // }
        // else if (state == 0) {
        //     printf("Cannot go back to BOOT state. Moving into IDLE state\n");
        //     state = 1;
        // }
    // }
}

int main() {
    fsm state;

    state.currState = BOOT;
    state.prevState = NONE;
    // printf("%d\n", state.currState);
    // printf("%d\n", state.prevState);
    state_loop(state);

    return 0;
}