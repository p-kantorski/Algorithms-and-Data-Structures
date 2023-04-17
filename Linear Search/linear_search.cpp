#include <iostream>
#include <time.h>
#include <cstdlib>
#include <fstream>

using namespace std;

int *RandomTable(int length);
int SequentialSearch(int *tab, int length, int searched, int &steps);
int LosujIndeks(int length);
void TestSearch();

int main(){
srand(time(NULL));

TestSearch();
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

int SequentialSearch(int *tab, int length, int searched, int &steps)
{
    for(int i = 0; i < length; i++)
    {
        steps++;
        if(tab[i] == searched)
            return i;
    }
    return -1;
}

int LosujIndeks(int length)
{
    int r;
        do
    {
        r = rand();
    }
    while(r>(length-1));
    return r;
}

double SequentialSearchStatistics(double max_iterations, int length)
{
    int steps = 0;
    int index;
    for(int i = 0; i < max_iterations; i++)
    {
        int *tab = RandomTable(length);
        index = LosujIndeks(length);
        SequentialSearch(tab, length, tab[index], steps);
        delete [] tab;
    }
    return steps/max_iterations;
}

void TestSearch()
{
    ofstream file("linear_search.txt");
    const double y = 100;
    for(int i = 10; i<=1000; i+=10)
    {
        file << i <<" "<< SequentialSearchStatistics(y, i)<<endl;
    }
    file.close();
}
