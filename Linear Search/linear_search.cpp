#include <iostream>
#include <fstream>
#include <time.h>
#include <chrono>

using namespace std::chrono;
using namespace std;

int *RandomTable(int length);
int SequentialSearch(int *tab, int length, int searched, int &steps);
float SequentialSearchStatistics(int max_iterations, int length);
int LosujIndeks(int length);
void TestSequentialSearch();

int main(){
    srand(time(NULL));
    TestSequentialSearch();
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

float SequentialSearchStatistics(int max_iterations, int length)
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
    return (float(steps) / float (max_iterations));
}

void TestSequentialSearch()
{
    ofstream file("linear_search.txt");
    const int y = 100;
    for(int i = 10; i<=1000; i+=10)
    {
        file << i << " ";
        auto start = high_resolution_clock::now();
        file << SequentialSearchStatistics(y,i) << " ";
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        file << duration.count() << endl;
    }
    file.close();
}
