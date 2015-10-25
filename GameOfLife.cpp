#include "GameOfLife.hpp"

#define ROW_NUMBER 102
#define COL_NUMBER 102

using namespace std;

void copy(int source[ROW_NUMBER][COL_NUMBER], int dest[ROW_NUMBER][COL_NUMBER])
{
    int i, j;
    for (i = 0; i < ROW_NUMBER; i++)
    {
        for (j = 0; j < COL_NUMBER; j++)
        {
            dest[i][j] = source[i][j];
        }
    }
}

void life_state(int array[ROW_NUMBER][COL_NUMBER])//, char choice)
{
    int temp[ROW_NUMBER][COL_NUMBER];
    copy(array, temp);
    int i, j, count;
    for (i = 1; i < ROW_NUMBER - 1; i++)
    {
        for (j = 1; j < COL_NUMBER; j++)
        {
            count = 0;
            //if (choice == 'm')
            {
                count = array[i - 1][j - 1]
                + array[i - 1][j]
                + array[i - 1][j + 1]
                + array[i][j - 1]
                + array[i][j + 1]
                + array[i + 1][j - 1]
                + array[i + 1][j]
                + array[i + 1][j + 1];
                
                if (count < 2 || count > 3)
                {
                    temp[i][j] = 0;
                }
                if (count == 2)
                {
                    temp[i][j] = array[i][j];
                }
                if (count == 3)
                {
                    temp[i][j] = 1;
                }
            }
//            else if (choice == 'v')
//            {
//                count = array[j-1][i] +
//                array[j][i-1] +
//                array[j+1][i] +
//                array[j][i+1];
//                
//                if (count < 2 || count > 3)
//                {
//                    temp[i][j] = 0;
//                }
//                if (count == 2)
//                {
//                    temp[i][j] = array[i][j];
//                }
//                if (count == 3)
//                {
//                    temp[i][j] = 1;
//                }
//            }
        }
    }
    
    copy(temp, array);
}

bool compare(int array1[ROW_NUMBER][COL_NUMBER], int array2[ROW_NUMBER][COL_NUMBER])
{
    int count = 0;
    int i, j;
    for (i = 0; i < ROW_NUMBER; i++)
    {
        for (j = 0; j < COL_NUMBER; j++)
        {
            if (array1[i][j] == array2[i][j])
            {
                count++;
            }
        }
    }
    
    if (count == (ROW_NUMBER * COL_NUMBER))
    {
        return true;
    }
    else
    {
        return false;
    }
}


void printArr(int array[ROW_NUMBER][COL_NUMBER])
{
    int i, j;
    for (i = 1; i < ROW_NUMBER - 1; i++)
    {
        for (j = 1; j < COL_NUMBER - 1; j++)
        {
            if (array[i][j] == 1)
            {
                cout<<"#"<<" ";
            }
            else
            {
                cout<<"."<<" ";
            }
        }
        cout<<"\n";
    }
}

int main()
{
    int i, j;
    int gen0[ROW_NUMBER][COL_NUMBER], todo[ROW_NUMBER][COL_NUMBER], backup[ROW_NUMBER][COL_NUMBER];
    char run_again;
    string sanity_check;
    bool comparison = false;
    do
    {
        system("clear");
        int genCount = 0;
        do
        {
            srand(time(NULL));
            for (i = 1; i < ROW_NUMBER; i++)
            {
                for (j = 1; j < COL_NUMBER; j++)
                {
                    gen0[i][j] = rand() % 2;
                }
            }
            if (genCount < 10)
            {
                sanity_check = "----------";
            }
            else if (genCount>=10 && genCount<=100)
            {
                sanity_check = "------------------";
            }
            else if (genCount >=100 && genCount<=1000)
            {
                sanity_check = "-------------------------";
            }
            else
            {
                sanity_check = "-------------------------------";
            }
            
            cout<< sanity_check<<"\n" << "Generation # "<< genCount<<"\n"<<sanity_check<<"\n";
            if (genCount == 0)
            {
                copy(gen0, todo);
            }
            copy(todo, backup);
            printArr(todo);
            life_state(todo);
            genCount++;
            system("sleep 0.1");
            if (genCount %100 == 1 && genCount != 1)
            {
                do
                {
                    cout<<"Would you like to continue the simulation? ";
                    cin>>run_again;
                }while (run_again!='y' && run_again!='n');
            }
            if (run_again == 'n')
            {
                break;
            }
            comparison = compare(todo, backup);
            if (comparison == false)
            {
                system("clear");
            }
            if (comparison == true)
            {
                cout<<"\n";
            }
        }
        while (comparison == false);
        do
        {
            run_again = ' ';
            cout<<"Would you like to run another simulation? ";
            cin>>run_again;
        }
        while (run_again!='y' && run_again != 'n');
        
            
    }
    while (run_again=='y');
    
}
