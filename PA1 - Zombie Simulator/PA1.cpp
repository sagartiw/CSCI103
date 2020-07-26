#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>
using namespace std;

const int MAXPOP = 100000;

double findavg(int data[], int simulations);
int findmax(int data[], int simulations);
int findmin(int data[], int simulations);
bool arepeoplealive(bool pop[], int population);
void resetzombies(bool pop[], int k);
void resethumans(bool pop[], int k, int N);

int main()
{
    // Array with enough entries for the maximum population size possible.
    bool pop[MAXPOP];
    
    int N, k, M, s;//Total population, Initial # of zombies, # of simulations to run, seed for rand.
    int nightcounter = 0;//Going to use this to store the # of nights.
    int results[MAXPOP];//Going to use this array to store the results of each simulation.
    bool oldzombies[MAXPOP];//Going to use this array to evaluate if zombies are new or old.
    cout << "Enter the following: N k M seed" << endl;
    cin >> N >> k >> M >> s;
    
    if(k > N){ //Quits program if initial zombies are greater than the total population.
        return 0;
    }
    srand(s); //Uses srand at the seed value to ensure that all simulations follow the same pseudo random order.
    resetzombies(pop, k);
    resethumans(pop, k, N);
    
    for(int i = 0; i < M; i++){//Loop for each individual simulation
        nightcounter = 0;
        while(arepeoplealive(pop, N)){//Loop evaluating whether or not humans still exist.
            for(int j = 0; j < N; j++){//Presets which zombies can have effective bites tonight.
                if(pop[j]){
                    oldzombies[j] = true;
                }
                else{
                    oldzombies[j] = false;
                }
            }
            for(int h = 0; h < N; h++){
                if(oldzombies[h]){//The bite only happens if the perpetrator is an old zombie.
                    pop[(rand()%N)] = true;//rand()%N scales the random numbers between 0-N.
                }
            }
            nightcounter++;
        }
        results[i] = nightcounter;//Stores nights for each simulation.
        resetzombies(pop, k);
        resethumans(pop, k, N);
    }
    
    cout << "Average Nights: " << findavg(results, M) << endl;
    cout << "Max Nights: " << findmax(results, M) << endl;
    cout << "Min Nights: " << findmin(results, M) << endl;
    
    return 0;
}

double findavg(int data[], int simulations){//Takes the data from my results array and outputs the avg.
    int total = 0;
    double average;
    for(int i = 0; i < simulations; i++){
        total += data[i];
    }
    average = (double) total/simulations;
    return average;
}


int findmax(int data[], int simulations){//Takes the data from my results array and outputs the max.
    int max = 0;
    for(int i = 0; i < simulations; i++){
        if(data[i] > max){
            max = data[i];
        }
    }
    return max;
}

int findmin(int data[], int simulations){//Takes the data from my results array and outputs the min.
    int min = 10000;
    for(int i = 0; i < simulations; i++){
        if(data[i] < min){
            min = data[i];
        }
    }
    return min;
}

bool arepeoplealive(bool pop[], int population){//Evaluates whether or not another night is needed.
    for(int i = 0; i < population; i++){
        if(!pop[i]){
            return true;
        }
    }
    return false;
}

void resetzombies(bool pop[], int k){//Initializes index values 0-(k-1) in pop[] as true, or as zombies.
    for(int i = 0; i < k; i++){
        pop[i] = true;
    }
}

void resethumans(bool pop[], int k, int N){//Initializes index values k-(N-1) in pop[] as false, or as humans.
    for(int i = k; i < N; i++){
        pop[i] = false;
    }
}
