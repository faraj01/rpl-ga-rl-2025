/* RPL Optimization with Hybrid GA-RL Approach
 * Author: Hamzah Faraj
 * Date: March 12, 2025
 */

#include "contiki.h"
#include "net/rpl/rpl.h"
#include "dev/leds.h"
#include <stdio.h>
#include <stdlib.h>

// GA Parameters
#define POP_SIZE 100
#define GENERATIONS 50
#define MUTATION_RATE 0.1

// RL Parameters
#define LEARNING_RATE 0.1
#define DISCOUNT_FACTOR 0.9
#define EPISODES 10
#define STATES 50
#define ACTIONS 10

// Fitness Function (Simplified)
float fitness(float apc, float pdr, float e2ed) {
    return 0.6 * apc + 0.2 * (1.0 / pdr) + 0.2 * e2ed;
}

// Q-Learning Update
void update_q_table(float q_table[STATES][ACTIONS], int state, int action, float reward, int next_state) {
    float max_next_q = 0;
    for (int a = 0; a < ACTIONS; a++) {
        if (q_table[next_state][a] > max_next_q) max_next_q = q_table[next_state][a];
    }
    q_table[state][action] += LEARNING_RATE * (reward + DISCOUNT_FACTOR * max_next_q - q_table[state][action]);
}

PROCESS(rpl_ga_rl_process, "RPL GA-RL Optimization");
AUTOSTART_PROCESSES(&rpl_ga_rl_process);

PROCESS_THREAD(rpl_ga_rl_process, ev, data)
{
    static struct etimer timer;
    static float q_table[STATES][ACTIONS] = {0};
    static int current_state = 0, action = 0;
    static float apc = 0.6, pdr = 0.85, e2ed = 200; // Initial values
    static int generation = 0, episode = 0;

    PROCESS_BEGIN();

    printf("Starting RPL GA-RL optimization...\n");

    // GA Phase
    while (generation < GENERATIONS) {
        float best_fitness = fitness(apc, pdr, e2ed);
        if (rand() / (float)RAND_MAX < MUTATION_RATE) apc *= 0.9; // Simulate mutation
        generation++;
    }
    // Initialize Q-table with GA fitness
    for (int s = 0; s < STATES; s++) {
        for (int a = 0; a < ACTIONS; a++) {
            q_table[s][a] = 0.5 * fitness(apc, pdr, e2ed);
        }
    }

    // RL Phase
    while (episode < EPISODES) {
        etimer_set(&timer, CLOCK_SECOND * 250); // 250 ms per episode
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
        float reward = - (0.6 * apc + 0.2 * e2ed - 0.2 * pdr); // Reward function
        update_q_table(q_table, current_state, action, reward, (current_state + 1) % STATES);
        current_state = (current_state + 1) % STATES;
        action = rand() % ACTIONS;
        episode++;
        printf("Episode %d: APC %.2f, Latency %.2f, PDR %.2f\n", episode, apc, e2ed, pdr);
    }

    PROCESS_END();
}
