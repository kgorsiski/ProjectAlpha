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
#include <vector>
#include <assert.h>
#include <fstream>



using namespace std;

int num_stat_runs = 30;

double alph;
double eps;

void act();
void react();



class slotmachine{
public:
    double mu;
    double sigma;
    double earnings = 0;
    int counter;
};

class agent{
public:
    int state;
    double average_earnings = 0;
    double previous_average = 0;

    
    int epsilon_greedy_action();
    int random_action();
    int greedy_action();
};



class adaptive_system{
public:
    agent* pagent;
    
    int num_machines = 1; // Number of machines
    int action;
    double alph = .1;
    double eps = .1;
    
    
    
    void sense(vector<slotmachine>* pslot,vector<agent>* pagent, int num_machines);
    void decide();
    void act(vector<slotmachine>* pslot,int input);
    void react(vector<agent>* pagent, vector<slotmachine>* pslot, int input, double alph);
    
    void init();
    void stat_run();
    int epsilon_greedy_action();
};


// Box-Muller transform code from wikipedia page posted on class wiki
double generateGaussianNoise(double mu, double sigma){
    const double epsilon = numeric_limits<double>::min();
    const double two_pi = 2.0*3.14159265358979323846;
    
    static double z0, z1;
    static bool generate;
    generate = !generate;
    
    if (!generate)
        return z1 * sigma + mu;
    
    double u1, u2;
    do
    {
        u1 = rand() * (1.0 / RAND_MAX);
        u2 = rand() * (1.0 / RAND_MAX);
    }
    while ( u1 <= epsilon );
    
    z0 = sqrt(-2.0 * log(u1)) * cos(two_pi * u2);
    z1 = sqrt(-2.0 * log(u1)) * sin(two_pi * u2);
    return z0 * sigma + mu;
}


int userinput(){
    int input;
    cout << " Choose an arm to pull. \n";
    cin >> input;
    return input;
}



void adaptive_system::sense(vector<slotmachine>* pslot,vector<agent>* pagent, int num_machines ){
    
    for(int index = 0; index < num_machines; index++){
        cout << "Slot Machine: " << index << "Has mu: " << pslot->at(index).mu << endl;
        cout << "Agent: " << index << "Has average earnings of: " << pagent->at(index).average_earnings << endl;
    }
}

void adaptive_system::decide(){
    int action;
    for(int index = 0; index < num_stat_runs; index++){
        double a = (double)rand()/RAND_MAX;
        if (a < eps)
            action = alph;
        else
            action = eps;
    }
    return;
}

void act(vector<slotmachine>* pslot,int input){
    
    pslot->at(input).earnings = generateGaussianNoise(pslot->at(input).mu, pslot->at(input).sigma);
    return;
}


void react(vector<agent>* pagent, vector<slotmachine>* pslot, int input, double alph ){
    
    pagent->at(input).average_earnings = pslot->at(input).earnings * alph + pagent->at(input).previous_average*(1-alph);
    pagent->at(input).previous_average = pagent->at(input).average_earnings;
    
    return;
}

void init(vector<slotmachine>* pslot, vector<agent>* pagent, int num_machines){
   
    slotmachine tempslot;
    agent Agent;
    
    for(int index = 0; index < num_machines; index++){
        tempslot.sigma = rand()/RAND_MAX;
        tempslot.mu = rand() % 30 + 1;
        Agent.previous_average = 0;
        Agent.average_earnings = 0;
        pagent->push_back(Agent);
        pslot->push_back(tempslot);
    
    }
}

int epsilon_greedy_action(vector<agent>* pagent, int num_machines, double eps){
    
    
    
    int temp = 0;
    int storage = rand() % num_machines;
    if(rand() / RAND_MAX > eps){
        storage = 0;
        for(int index = 0; index < num_machines; index++){
            if(pagent->at(index).average_earnings > temp){
                temp = pagent->at(index).average_earnings;
                storage = index;
            }
        }
        
    }
    return storage;
}


void stat_run(double alph, double eps ){
    
    int num_machines;
    int iter = 10000;
    int num_stat_runs;
    int input = 0;
    
    vector<slotmachine>* pslot;
    vector<agent>*  pagent;
    init(pslot,pagent,num_machines);
    ofstream outputFile;
    outputFile.open("Output.txt");
    
    if(outputFile.is_open()){
        for(int index = 0; index < num_stat_runs; index++){
            for(int index2 = 0; index2 < iter; index2++){
                input = epsilon_greedy_action(pagent, num_machines, eps);
                outputFile << pagent->at(input).average_earnings << endl;
                act(pslot, input);
                react(pagent, pslot, input, alph);
    
                }
            }
        }
    outputFile.close();
}

void Fxn_A(double alph){
    
    int input = 0;
    int num_machines = 1;
    int iterations = 10000;
    
    vector<slotmachine>* pslot;
    vector<agent>*  pagent;
    init(pslot,pagent,num_machines);
    
    int mu = 10;
    int sigma = 1;
    
    pslot->at(input).mu = mu;
    pslot->at(input).sigma = sigma;
    
    for(int index = 0; index < iterations; index++){
        act(pslot, input);
        react(pagent, pslot, input, alph);
        
    }
    assert(pagent->at(input).average_earnings = mu + sigma / 2);
    cout << "Test A Successful" << endl;
    
}

void Fxn_B(double eps){
    int num_machines = 3;
    int iterations = 10000;
    
    vector<slotmachine>* pslot;
    vector<agent>*  pagent;
    ::init(pslot,pagent,num_machines);
    
    int mu_1 = 10;
    int mu_2 = 5;
    int mu_3 = 15;
    int sigma = 1;
    
    pslot->at(0).mu = mu_1;
    pslot->at(1).mu = mu_2;
    pslot->at(3).mu = mu_3;
    pslot->at(0).sigma = sigma;
    pslot->at(1).sigma = sigma;
    pslot->at(3).sigma = sigma;
    
    
    for(int index = 0; index < iterations; index++){
        int input = epsilon_greedy_action(pagent, num_machines, eps);
        act(pslot, input);
        pslot->at(input).counter ++;
        }
    assert(pslot->at(3).counter > pslot->at(1).counter);
    assert(pslot->at(3).counter > pslot->at(2).counter);
    
    cout << "Test B Successful" << endl;
    

}


int main() {
    srand((unsigned)time(NULL));
    cout << "Program Start\n";
    double alph = .1;
    double eps = .05;
 
    Fxn_A(alph);
    Fxn_B(eps);

    
    /*
    int num_stat_runs = 30;
    
    for(int i=0; i<num_stat_runs; i++){
        stat_run(alph , eps);
    }
    
    */
    cout << "Program End\n";
    
    return 0;
}
