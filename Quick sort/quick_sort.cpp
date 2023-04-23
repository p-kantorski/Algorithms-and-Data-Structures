#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;

int *RandomTable(int length);
void Swap(int *tab, int idx_a, int idx_b);
void QuickSort(int *tab, int left, int right, int &steps);
float QuickSortStatistics(float max_iterations, int length);
void TestQuickSort();

int main()
{
    srand(time(NULL));
    TestQuickSort();
    return 0;
}

int *RandomTable(int length)
{
    int *tab = new int[length];
    for(int i = 0; i < length; i++)
    {
        tab[i] = rand();
    }
    return tab;
}

void Swap(int *tab, int idx_a, int idx_b)
{
    int c = tab[idx_a];
    tab[idx_a] = tab[idx_b];
    tab[idx_b] = c;
}

void QuickSort(int *tab, int left, int right, int &steps)
{
    if(left>=right)
        return;
    int pos = left;
    int i = left+1;
    while(i<=right)
    {
        steps++;
        if(tab[i]<tab[left])
        {
            pos++;
            Swap(tab, pos, i);
        }
        i++;
    }
    Swap(tab, pos, left);
    QuickSort(tab, left, pos-1, steps);
    QuickSort(tab, pos+1, right, steps);
}

float QuickSortStatistics(float max_iterations, int length)
{
    int steps = 0;
    for(int i = 0; i < max_iterations; i++)
    {
        int *tab = RandomTable(length);
        QuickSort(tab, 0, length-1, steps);
        delete [] tab;
    }
    return steps/max_iterations;
}


void TestQuickSort()
{
    ofstream file("quicksort.txt");
    const float y = 1000;
    for(int i = 10; i<=10000; i+=10)
    {
        file << i <<" "<< QuickSortStatistics(y, i)<<endl;
    }
    file.close();
}
