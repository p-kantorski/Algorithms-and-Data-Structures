#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

int *RandomTable(int length);
void Swap(int *tab, int idx_a, int idx_b);
int BubbleSort1(int *tab, int length);
int BubbleSort2(int *tab, int length);
float BubbleSortStatistics1(int max_iterations, int length);
void TestBubbleSort1();
float BubbleSortStatistics2(int max_iterations, int length);
void TestBubbleSort2();


int main()
{
    srand(time(NULL));
    TestBubbleSort1();
    TestBubbleSort2();
    return 0;
}

int *RandomTable(int length)
{
    int *tab = new int[length];
    for(int i = 0; i < length; i++)
    {
        tab[i] = rand();
            for(int y = 0; y < i; y++)
            {
                while(tab[y]==tab[i])
                {
                    tab[i] = rand();
                    y = 0;
                }

            }
    }
    return tab;
}

void Swap(int *tab, int idx_a, int idx_b)
{
    int c = tab[idx_a];
    tab[idx_a] = tab[idx_b];
    tab[idx_b] = c;
}

int BubbleSort1(int *tab, int length)
{
    bool if_changed;
    int comp = 0;
    do
    {
    if_changed = 0;
       for(int i = 0; i < length -1; i++)
        {
            if(tab[i]>tab[i+1])
            {
            if_changed = 1;
            Swap(tab, i, i+1);
            }
        comp++;
        }
    }
    while(if_changed != 0);
    return comp;
}

int BubbleSort2(int *tab, int length)
{
    bool if_changed;
    int comp = 0;
    int p = 0;
    do
    {
    if_changed = 0;
    for(int i = 0; i < length-p-1; i++)
    {
        if(tab[i]>tab[i+1])
        {
        if_changed = 1;
        Swap(tab, i, i+1);
        }
    comp++;
    }
    p+=1;
    }
    while(if_changed != 0);
    return comp;
}

float BubbleSortStatistics1(float max_iterations, int length)
{
    int steps = 0;
    for(int i = 0; i < max_iterations; i++)
    {
        int *tab = RandomTable(length);
        steps += BubbleSort1(tab, length);
        delete [] tab;
    }
    return steps/max_iterations;
}

float BubbleSortStatistics2(float max_iterations, int length)
{
    int steps = 0;
    for(int i = 0; i < max_iterations; i++)
    {
        int *tab = RandomTable(length);
        steps += BubbleSort2(tab, length);
        delete [] tab;
    }
    return steps/max_iterations;
}

void TestBubbleSort1()
{
    ofstream file("bubblesort1.txt");
    const float y = 100;
    for(int i = 10; i<=1000; i+=10)
    {
        file << i <<" "<< BubbleSortStatistics1(y, i)<<endl;
    }
    file.close();
}

void TestBubbleSort2()
{
    ofstream file("bubblesort2.txt");
    const float y = 100;
    for(int i = 10; i<=1000; i+=10)
    {
        file << i <<" "<< BubbleSortStatistics2(y, i)<<endl;
    }
    file.close();
}
