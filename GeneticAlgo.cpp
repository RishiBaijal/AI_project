
#include "GameOfLife.hpp"
using namespace std;

#define MAX_SIZE 1000
#define TIME_END 10000

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>
#include <math.h>

#define POPULATION_SIZE 2000
#define MAX_ITER 100
#define ELITE_RATE 0.10f
#define MUTATION_RATE 0.25f
#define MUTATION RAND_MAX * MUTATION_RATE
#define GA_TARGET std::string("Hello World. How are you?")

struct colony{
    vector<bool> gen[MAX_SIZE];
    unsigned int fitness;
    long long int init_alive;
};


long long int col_target1;
long long int col_target2;

long long int alive=0;

struct ga_struct
{
    string str;
    unsigned int fitness;
};

long long int ROW_NUMBER;
long long int COL_NUMBER;
long long int rows,cols;
colony prot;


typedef vector<ga_struct> ga_vector;
typedef vector<colony> col_vector;


void copy(vector<bool> source[MAX_SIZE], vector<bool> dest[MAX_SIZE])
{
    int i, j;
    for (i = 0; i < ROW_NUMBER; i++)
        for (j = 0; j < COL_NUMBER; j++)
            dest[i][j] = source[i][j];
}


bool compare(vector<bool> array1[MAX_SIZE], vector<bool> array2[MAX_SIZE])
{
    bool flag=true;
    int i, j;
    for (i = 0; i < ROW_NUMBER; i++)
        for (j = 0; j < COL_NUMBER; j++)
            if (array1[i][j] != array2[i][j])
                flag=false;
    
    return flag;
}

long long int printArr(vector<bool> array[MAX_SIZE], int genCount)
{
    long long int alive_now=0;
    int i, j;
    printf("\n");
    for (i = 1; i < ROW_NUMBER - 1; i++)
    {   printf("  ");
        for (j = 1; j < COL_NUMBER - 1; j++)
        {
            if (array[i][j]){
                cout<<"#"<<" ";
                alive_now++;
            }
            else{
                cout<<"."<<" ";
            }
        }
        cout<<"\n";
    }
    printf("--------------------------------\n GENERATION %d : Life Count: %lld\n--------------------------------\n ",genCount,alive_now);
    printf("\n");
    return alive_now;
}

long long int getalivecells(vector<bool> array[MAX_SIZE], int genCount)
{
    long long int alive_now=0;
    int i, j;
    for (i = 1; i < ROW_NUMBER - 1; i++)
    {   for (j = 1; j < COL_NUMBER - 1; j++)
    {
        if (array[i][j]){
            alive_now++;
        }
        else{
        }
    }
    }
    return alive_now;
}
bool life_state(vector<bool> arr[MAX_SIZE])
{
    alive=0;
    int flag=false;
    int i, j, count;
    bool prev_row[COL_NUMBER];
    bool this_row[COL_NUMBER];
    bool prev=false;
    
    for(i=0;i<COL_NUMBER;i++)
    {
        prev_row[i]=arr[0][i];
        this_row[i]=arr[1][i];
    }
    
    for (i = 1; i < ROW_NUMBER - 1; i++)
    {
        for (j = 1; j < COL_NUMBER-1; j++)
        {
            count =
            (int)prev_row[j - 1]              //arr[i-1][j-1]
            + (int)prev_row[j]                  //arr[i-1][j]
            + (int)prev_row[j + 1]              //arr[i-1][j+1]
            + (int)prev                         //arr[i][j-1]
            + (int)arr[i][j + 1]                //the unchanged arr variables
            + (int)arr[i + 1][j - 1]
            + (int)arr[i + 1][j]
            + (int)arr[i + 1][j + 1];
            
            prev=arr[i][j];                 //maintaining temp vars
            prev_row[j-1]=this_row[j-1];
            this_row[j-1]=arr[i+1][j-1];
            
            
            if (count < 2 || count > 3)
                arr[i][j] = false;
            
            if (count == 3)
                arr[i][j] = true;
            
            if(arr[i][j]!=prev)
                flag=true;
            
            if(arr[i][j])
                alive++;
        }
        prev=false;
        prev_row[COL_NUMBER-2]=this_row[COL_NUMBER-2];
        this_row[COL_NUMBER-2]=arr[i+1][COL_NUMBER-2];
    }
    return flag;
}

long long int debugscore=0;
long long int run_simulation(vector<bool> gen0[MAX_SIZE],long long int endoftime=100)
{
    int i, j;
    char run_again;
    string sanity_check;
    bool change = false;
    
    long long int overallscore=0;
    long long int finalscore=0;
    // system("clear");
    int genCount = 0;
    do
    {
        // system("sleep 0.1");
        // system("clear");
        
        change  =life_state(gen0);
        finalscore=getalivecells(gen0, genCount);
        overallscore+=finalscore;
        
        /*
         if(genCount>1 && genCount%100==0)
         {
         printf("\nContinue Simulation?:");
         cin>>run_again;
         if(run_again!='y')
         break;
         }
         */
        genCount++;
    }
    while (change && genCount<endoftime);//upper limit is endofline. change it to user inpt.
    if(overallscore>debugscore)
        debugscore=overallscore;
    //printf("Debug score:%lld\n",debugscore);
    
    return overallscore;
}

long long int initialize(vector<bool> arr[MAX_SIZE])
{
    
    int i,j;
    int randtemp;
    long long int thisalive=0;
    for(i=0;i<ROW_NUMBER;i++)
    {
        
        arr[i].clear();
        for(j=0;j<COL_NUMBER;j++)
        {
            if(i==0||j==0||i==ROW_NUMBER-1||j==COL_NUMBER-1)//setting borders to permanently false
            {
                arr[i].push_back(false);
            }
            else                                            //randomly deciding what the initial cells will be
            {
                randtemp= rand()%2;
                if(randtemp==1)
                {
                    arr[i].push_back(true);
                    thisalive++;
                }
                else
                {
                    arr[i].push_back(false);
                }
                
            }
        }
    }
    return thisalive;
}

long long int upperbound;


void userinteract()
{
    //    long long int n,m;
    
    char run_again;
    //struct organism* prototype=(organism*)malloc(sizeof(organism));
    //organism prot;
    
    
    
    printf("Enter Grid Size:   ");
    scanf("%lld %lld",&ROW_NUMBER,&COL_NUMBER);
    printf("Enter End of Time: ");
    scanf("%lld",&upperbound);
    if(upperbound==-1)
        upperbound=TIME_END;
    
    col_target1=ROW_NUMBER*COL_NUMBER*upperbound;
    col_target2=ROW_NUMBER*COL_NUMBER;
    ROW_NUMBER+=2;
    COL_NUMBER+=2;
    //initialize(prototype->gen0);
    //run_simulation(prototype->gen0,upper_bound);
    
    //    initialize(prot.gen);
    //    run_simulation(prot.gen,upper_bound);
    
}





// void init_population(ga_vector &population, ga_vector &buffer)
// {
//     int tsize = GA_TARGET.size();
//     int i, j;
//     for (i = 0; i < POPULATION_SIZE; i++)
//     {
//         ga_struct citizen;
//         citizen.fitness = 0;
//         citizen.str.erase();
//         for (j = 0; j < tsize; j++)
//         {
//             citizen.str+=(rand() % 90) + 32;
//         }
//         population.push_back(citizen);

//     }
//     buffer.resize(POPULATION_SIZE);
// }


void init_population1(col_vector &population, col_vector &buffer)
{
    int tsize = GA_TARGET.size();
    int i, j;
    for (i = 0; i < POPULATION_SIZE; i++)
    {
        
        colony col;
        col.fitness = 0;
        //citizen.str.erase();
        long long int gotalive=initialize(col.gen);
        col.init_alive=gotalive;
        
        //        printf("do: %lld\n",col.init_alive);
        population.push_back(col);
        
    }
    buffer.resize(POPULATION_SIZE);
}


void calculate_fitness1(col_vector &population)
{
    
    //   string target = GA_TARGET;
    //    int tsize = target.size();
    unsigned int fitness;
    int i, j;
    for (i = 0; i < POPULATION_SIZE; i++)
    {
        fitness = 0;
        colony tempcol=population[i];
        fitness=run_simulation(tempcol.gen,upperbound);
        //  cout<<"Fitness= "<<fitness<<endl;
        population[i].fitness = fitness;
    }
}

// bool fitness_sort(ga_struct x, ga_struct y)
// {
//     return (x.fitness < y.fitness);
// }
//
//bool fitness_sort1(colony x, colony y)
//{
//    return (x.fitness > y.fitness);
//}

struct Comparator
{
    bool operator()(colony x, colony y)
    {
        return (x.fitness > y.fitness);
    }
};


inline void sort_by_fitness1(col_vector &population)
{
    sort(population.begin(), population.end(), Comparator());
}

// void elitism(ga_vector &population, ga_vector &buffer, int esize)
// {
//     int i;
//     for (i = 0; i < esize; i++)
//     {
//         buffer[i].str = population[i].str;
//         buffer[i].fitness = population[i].fitness;
//     }
// }


void elitism1(col_vector &population, col_vector &buffer, int esize)
{
    int i;
    for (i = 0; i < esize; i++)
    {
        //   buffer[i].gen = population[i].gen;
        //    buffer[i].fitness = population[i].fitness;
        buffer[i]=population[i];
        
    }
}
// void mutate(ga_struct &member)
// {
//     int tsize = GA_TARGET.size();
//     int ipos = rand() % tsize;
//     int delta = (rand() % 90) + 32;

//     member.str[ipos] = ((member.str[ipos] + delta) % 122);
// }

void mutate1(colony &member)
{
    
    int ipos = rand() % ROW_NUMBER;
    int jpos = rand() % COL_NUMBER;
    //    int delta = (rand() % 90) + 32;
    
    member.gen[ipos][jpos] = !member.gen[ipos][jpos];
    
}

void mutate2(colony &member)
{
    int ipos = rand() % ROW_NUMBER;
    int jpos = rand() % COL_NUMBER;
    //    int delta = (rand() % 90) + 32;
    for(jpos=1;jpos<COL_NUMBER-1;jpos++)
        member.gen[ipos][jpos] = !member.gen[ipos][jpos];
}

// void mate(ga_vector &population, ga_vector &buffer)// this is where the fucking happens
// {
//     int esize = POPULATION_SIZE * ELITE_RATE;
//     int tsize = GA_TARGET.size(), spos, i1, i2, i;
//     elitism(population, buffer, esize);
//     for (i = esize; i < POPULATION_SIZE; i++)
//     {
//         i1 = rand() % (POPULATION_SIZE / 2);
//         i2 = rand() % (POPULATION_SIZE / 2);
//         spos = rand() % tsize;

//         buffer[i].str = population[i1].str.substr(0, spos) + population[i2].str.substr(spos, esize - spos);

//         if (rand() < MUTATION)
//         {
//             mutate(buffer[i]);
//         }
//     }
// }

void mate1(col_vector &population, col_vector &buffer)// this is where the fucking happens
{
    int esize = POPULATION_SIZE * ELITE_RATE;
    int tsize = ROW_NUMBER, spos, i1, i2, i;
    elitism1(population, buffer, esize);
    for (i = esize; i < POPULATION_SIZE; i++)
    {
        i1 = rand() % (POPULATION_SIZE / 2);
        i2 = rand() % (POPULATION_SIZE / 2);
        spos = rand() % tsize;
        int j;
        for(j=0;j<spos;j++)
        {
            buffer[i].gen[j]=population[i1].gen[j];
        }
        for(;j<ROW_NUMBER;j++)
        {
            buffer[i].gen[j]=population[i2].gen[j];
        }
        //        buffer[i].str = population[i1].str.substr(0, spos) + population[i2].str.substr(spos, esize - spos);
        
        if (rand() < MUTATION)
        {
            mutate1(buffer[i]);
        }
    }
}


// inline void swap(ga_vector *&population, ga_vector *&buffer)
// {
//     ga_vector *temp = population;
//     population = buffer;
//     buffer = temp;
// }

inline void swap1(col_vector *&population, col_vector *&buffer)
{
    col_vector *temp = population;
    population = buffer;
    buffer = temp;
}

// inline void print_best(ga_vector ga)
// {
//     cout<<"String: "<< ga[0].str<<"\n";
//     cout<<"Fitness value: "<< ga[0].fitness<<"\n";
// }
inline void print_best1(col_vector ga)
{
    //cout<<"String: "<< ga[0].str<<"\n";
    //printArr(ga[0].gen,0);
    cout<<"Fitness value: "<< ga[0].fitness<<"\n";
}


ga_vector init_pop, init_buffer, *population1, *buffer1;

col_vector init_cols, init_buffers, *colonies1, *buffers1;

int main()
{
    
    
    //  srand(time(NULL));
    userinteract();
    srand(unsigned(time(NULL)));
    init_population1(init_cols, init_buffers);
    //  init_population(init_pop, init_buffer);
    colonies1 = &init_cols;
    buffers1 = &init_buffers;
    int i;
    for (i = 0; i < MAX_ITER; i++)
    {
        //    printf("ITERATION %d\n\n\n\n",i);
        //    calculate_fitness(*population1);
        printf("Calculating fitness of colonies\n");
        calculate_fitness1(*colonies1);
        //sort_by_fitness(*population1);
        printf("Sorting fitness of colonies\n");
        sort_by_fitness1(*colonies1);
        int j;
        /*
         for(j=0;j<POPULATION_SIZE;j++)
         {
         printf("Fitness= %u\n",init_cols[j].fitness);
         }
         */
        //print_best(*population1);
        printf("Printing the best colony fitness\n");
        
        print_best1(*colonies1);
        //if ((*population1)[0].fitness == 0)
        //{
        //    break;
        //}
        //mate(*population1, *buffer1);
        printf("Mating colonies\n");
        
        mate1(*colonies1,*buffers1);
        printf("Swapping colonies\n");
        
        //swap(population1, buffer1);
        swap1(colonies1,buffers1);
        printf("\nDone with iteration:%d\n",i);
    }
    return 0;
    
}