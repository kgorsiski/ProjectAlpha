//
//  main.cpp
//  Project Alpha
//
//  Created by Kyle Gorsiski on 2/14/17.
//  Copyright © 2017 Kyle Gorsiski. All rights reserved.
//

#include <iostream>
#include <random>
#include <time.h>

using namespace std;


class system;
class agent;
class domain;

class adaptive_system{
public:
    agent* pAgent;
    domain* pDomain;
    
    void sense();
    void decide();
    void act();
    void react();
    
    void init();
    void stat_run();
};

class agent{
public:
    int state;
    
    int epsilon_greedy_action();
    int random_action();
    int greedy_action();
};

class domain{
public:
    int get_agent_state();
};

void adaptive_system::sense(){
    // agent gets state information from system
    pAgent->state = pDomain->get_agent_state();
}

void adaptive_system::decide(){
    // agent decides what to do
    return;
}

void adaptive_system::act(){
    // agent acts on system
    return;
}

void adaptive_system::react(){
    // agent gets feedback from system
    return;
}

void adaptive_system::init(){
    // initialize agent and domain
    /// potentially write a function for the agent and domain and use:
    // pAgent->init();
    // pDomain->init();
    return;
}

void adaptive_system::stat_run(){
    return;
}

int domain::get_agent_state(){
    return -1;
}

int agent::epsilon_greedy_action(){
    return -1;
}
int agent::random_action(){
    return -1;
}
int agent::greedy_action(){
    return -1;
}

int main() {
    srand((unsigned)time(NULL));
    cout << "Program Start\n";
    
    adaptive_system S;
    agent A;
    domain D;
    
    S.pAgent = &A;
    S.pDomain = &D;
    
    S.init();
    
    int num_stat_runs = 30;
    
    for(int i=0; i<num_stat_runs; i++){
        S.stat_run();
    }
    
    /// don't forget to put some kind of results reporting mechanism
    
    cout << "Program End\n";
    
    return 0;
}
