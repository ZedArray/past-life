#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

int roll;

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

void change_state(fsm *state, States nextState) {
    Sleep(2000);
    state->prevState = state->currState;
    state->currState = nextState;
    printf("Entering %s state, leaving %s state\n", getName(state->currState), getName(state->prevState));
}


void boot_state(fsm *state) {
    printf("Currently on %s state\n", getName(state->currState));
    change_state(state, IDLE);
}
void idle_state(fsm *state) {
    printf("Currently on %s state\n", getName(state->currState));

    if (roll > 10 || state->prevState == LOW_POWER) {
        change_state(state, NOMINAL);
    }
    else {
        change_state(state, LOW_POWER);
    }
}
void nominal_state(fsm *state) {
    printf("Payload and Sensor activites activated\n");

    if (roll >= 13) {
        // printf("Success\n");
        change_state(state, IDLE);
    }
    else if (roll <= 6) {
        // printf("Something broke\n");
        change_state(state, FAULT);
    }
}
void lp_state(fsm *state) {
    printf("Low Power Mode\n");

    if (roll < 10) {
        // printf("New task received\n");
        change_state(state, IDLE);
    }
}
void fault_state(fsm *state) {
    printf("AAAAAAAAAAAAAAA\n");

    if (roll > 12) {
        change_state(state, SAFE);
    }
}
void safe_state(fsm *state) {
    printf("Recovery Mode\n");
    
    if (roll > 12) {
        change_state(state, IDLE);
    }
}

void state_loop(fsm *state) {
    while (state->currState != NONE) {
        Sleep(2000);
        srand(time(NULL));
        roll = rand() % 20 + 1;
        switch (state->currState)
        {
        case BOOT:
            boot_state(state);
            break;

        case IDLE:
            idle_state(state);
            break;

        case NOMINAL:
            nominal_state(state);
            break;

        case LOW_POWER:
            lp_state(state);
            break;

        case FAULT:
            fault_state(state);
            break;

        case SAFE:
            safe_state(state);
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
    }
}

int main() {
    fsm state;

    state.currState = BOOT;
    state.prevState = NONE;
    state_loop(&state);

    return 0;
}