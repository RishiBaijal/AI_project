#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>
#include <math.h>

#define POPULATION_SIZE 2048
#define MAX_ITER 16384
#define ELITE_RATE 0.10f
#define MUTATION_RATE 0.25f
#define MUTATION RAND_MAX * MUTATION_RATE
#define GA_TARGET std::string("The blood is making me horny.")

using namespace std;

struct ga_struct
{
    string str;
    unsigned int fitness;
};

typedef vector<ga_struct> ga_vector;
void init_population(ga_vector &population, ga_vector &buffer)
{
    int tsize = GA_TARGET.size();
    int i, j;
    for (i = 0; i < POPULATION_SIZE; i++)
    {
        ga_struct citizen;
        citizen.fitness = 0;
        citizen.str.erase();
        for (j = 0; j < tsize; j++)
        {
            citizen.str+=(rand() % 90) + 32;
        }
        population.push_back(citizen);
        
    }
    buffer.resize(POPULATION_SIZE);
}

void calculate_fitness(ga_vector &population)
{
    string target = GA_TARGET;
    int tsize = target.size();
    unsigned int fitness;
    int i, j;
    for (i = 0; i < POPULATION_SIZE; i++)
    {
        fitness = 0;
        for (j = 0; j < tsize; j++)
        {
            fitness += (abs(int(population[i].str[j] - target[j])));
        }
        population[i].fitness = fitness;
    }
}

bool fitness_sort(ga_struct x, ga_struct y)
{
    return (x.fitness < y.fitness);
}

inline void sort_by_fitness(ga_vector &population)
{
    sort(population.begin(), population.end(), fitness_sort);
}

void elitism(ga_vector &population, ga_vector &buffer, int esize)
{
    int i;
    for (i = 0; i < esize; i++)
    {
        buffer[i].str = population[i].str;
        buffer[i].fitness = population[i].fitness;
    }
}

void mutate(ga_struct &member)
{
    int tsize = GA_TARGET.size();
    int ipos = rand() % tsize;
    int delta = (rand() % 90) + 32;
    
    member.str[ipos] = ((member.str[ipos] + delta) % 122);
}

void mate(ga_vector &population, ga_vector &buffer)// this is where the fucking happens
{
    int esize = POPULATION_SIZE * ELITE_RATE;
    int tsize = GA_TARGET.size(), spos, i1, i2, i;
    elitism(population, buffer, esize);
    for (i = esize; i < POPULATION_SIZE; i++)
    {
        i1 = rand() % (POPULATION_SIZE / 2);
        i2 = rand() % (POPULATION_SIZE / 2);
        spos = rand() % tsize;
        
        buffer[i].str = population[i1].str.substr(0, spos) + population[i2].str.substr(spos, esize - spos);
        
        if (rand() < MUTATION)
        {
            mutate(buffer[i]);
        }
    }
}

inline void swap(ga_vector *&population, ga_vector *&buffer)
{
    ga_vector *temp = population;
    population = buffer;
    buffer = temp;
}
inline void print_best(ga_vector ga)
{
    cout<<"String: "<< ga[0].str<<"\n";
    cout<<"Fitness value: "<< ga[0].fitness<<"\n";
}

int main()
{
    srand(unsigned(time(NULL)));
    
    ga_vector init_pop, init_buffer, *population, *buffer;
    init_population(init_pop, init_buffer);
    population = &init_pop;
    buffer = &init_buffer;
    int i;
    for (i = 0; i < MAX_ITER; i++)
    {
        calculate_fitness(*population);
        sort_by_fitness(*population);
        print_best(*population);
        if ((*population)[0].fitness == 0)
        {
            break;
        }
        mate(*population, *buffer);
        swap(population, buffer);
    }
    return 0;
    
}