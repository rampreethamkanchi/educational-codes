/*
    simulating dining philosophers problem (a popular topic in os(operating systems))
    this is not a solution, it just simulates the problem
    !! Infine loop Warning, kill the program with ctrl + C from your terminal after some time !!
    problem: https://en.wikipedia.org/wiki/Dining_philosophers_problem
    I think this simulation will cover all the possible scenarios in a dining philosopher problem: please verify 
    instructions to run : run this like you run any c program
    what you will observe: after certain time the output stops on the terminal, this is the case of deadlock
    you will eventually reach this state(deadlock) where all the philosopers need one chopstick and all of them hold one chopstick
    the while loop run infinetly but no philoshopher will be able to change thier state and wait for other indefinetly
    kill your program...
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h> // for time()

// 5 philosophers are dining in a circular table with 5 chopsticks on table
// change this to other number if u want
#define NOF_CHOPSTICKS NOF_PHILOSOPHERS
#define NOF_PHILOSOPHERS 5

// when philosopher is eating he needs no more chopsticks
#define EATING 0
#define WANT_1_CHOPSTICK 1
#define WANT_2_CHOPSTICK 2

int picked[NOF_CHOPSTICKS];  // picked[i] -> is ith chopstick picked?
int wants[NOF_PHILOSOPHERS]; // wants[i] -> how many chopsticks does ith philosopher want?

// get left chopstick
int leftstick(int philosopher) {
    return philosopher;
}

// get right chopstick
int rightstick(int philosopher) {
    return (philosopher + 1) % NOF_CHOPSTICKS;
}

// for good printing
void printTableHeader() {
    printf("printing the number of chopsticks each philosopher wants as the time progess..\n");
    printf("\t");
    for (int i = 0; i < NOF_PHILOSOPHERS; i++) {
        printf("| philosopher %d |", i + 1);
    }
    printf("\n");
}

// print state if state is changed, change if u want to print something else
void changed_state() {
    for (int i = 0; i < NOF_PHILOSOPHERS; i++) {
        printf("%16d ", wants[i]);
    }
    printf("\n");
}

// in the simulation, a random philopher is said to take action, these are the possible actions they can take based on their state
void action(int philosopher) {
    int curr_state = wants[philosopher];
    int next_state = curr_state;

    if (curr_state == EATING) {
        // EATING -> DROP 2 CHOPSTICKS
        picked[leftstick(philosopher)] = 0;
        picked[rightstick(philosopher)] = 0;
        next_state = WANT_2_CHOPSTICK;
    } else if (curr_state == WANT_1_CHOPSTICK) {
        // WANT_1_CHOPSTICK -> try to take other one
        if (picked[leftstick(philosopher)] && picked[rightstick(philosopher)]) {
            // not available
            // no change in state
        } else {
            // available
            picked[leftstick(philosopher)] = 1;
            picked[rightstick(philosopher)] = 1;
            next_state = EATING;
        }
    } else if (curr_state == WANT_2_CHOPSTICK) {
        // WANT_2_CHOPSTICK -> try to take left or right stick randomly
        if (picked[leftstick(philosopher)] && picked[rightstick(philosopher)]) {
            // no change in state
        } else if (picked[leftstick(philosopher)] || picked[rightstick(philosopher)]) {
            // one stick i s available
            picked[leftstick(philosopher)] = 1;
            picked[rightstick(philosopher)] = 1;
            next_state = WANT_1_CHOPSTICK;
        } else {
            // 2 sticks are available
            // take 1 randomly
            if (rand() % 2) {
                picked[leftstick(philosopher)] = 1;
                next_state = WANT_1_CHOPSTICK;
            } else {
                picked[rightstick(philosopher)] = 1;
                next_state = WANT_1_CHOPSTICK;
            }
        }
    } else {
        fprintf(stderr, "invalid curr_state for a philosopher\n");
        exit(1);
    }
    // update state and print changed state
    wants[philosopher] = next_state;
    if (next_state != curr_state)
        changed_state();
}

int main() {
    // initialise
    for (int i = 0; i < NOF_CHOPSTICKS; i++) {
        picked[i] = 0;
    }
    for (int i = 0; i < NOF_PHILOSOPHERS; i++) {
        wants[i] = 2;
    }
    srand(time(NULL));
    printTableHeader();
    int philosopher;
    // endless scenario in time
    while (1) {
        // pick a random philosopher
        philosopher = rand() % NOF_PHILOSOPHERS;
        // take action
        action(philosopher);
        // repeat
    }
    return 0;
}