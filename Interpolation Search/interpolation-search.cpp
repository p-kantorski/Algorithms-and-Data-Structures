#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

int *RandomTable(int length);
void Swap(int *tab, int idx_a, int idx_b);
int LosujIndeks(int length);
int Interpolation(int *tab, int left, int right, int s);
int InterSearch(int *tab, int length, int s, int &steps);
void QuickSort(int *tab, int left, int right);
void TestInterSearch();

int main()
{
    srand(time(NULL));
    TestInterSearch();
    return 0;
}

int *RandomTable(int length)
{
    int *tab = new int[length];
    for(int i = 0; i < length; i++)
        tab[i] = rand();
    return tab;
}

void Swap(int *tab, int idx_a, int idx_b)
{
    int c = tab[idx_a];
    tab[idx_a] = tab[idx_b];
    tab[idx_b] = c;
}

int Interpolation(int *tab, int left, int right, int s)
{
    return left + (s-tab[left])*(right-left)/(tab[right]-tab[left]);
}

int InterSearch(int *tab, int length, int s, int &steps)
{
    int mid;
    int left = 0;
    int right = length-1;
    while(left<=right)
    {
        mid = Interpolation(tab, left, right, s);
        steps++;
        if(tab[mid]==s)
            return mid;
        steps++;
        if(tab[mid]<s)
            left=mid+1;
        else
            right=mid-1;
    }
    return -1;
}

float InterSearchStatistics(float max_iterations, int length)
{
    int steps = 0;
    for(int i = 0; i < max_iterations; i++)
    {
        int *tab = RandomTable(length);
        QuickSort(tab, 0, length-1);
        InterSearch(tab, length, tab[LosujIndeks(length)], steps);
        delete [] tab;
    }
    return steps/max_iterations;
}

int LosujIndeks(int length)
{
    int r;
    do
    {
        r = rand();
    }
    while(r>length-1);
    return r;
}

void QuickSort(int *tab, int left, int right)
{
    if(left>=right)
        return;
    int pos = left;
    int i = left+1;
    while(i<=right)
    {
        if(tab[i]<tab[left])
        {
            pos++;
            Swap(tab, pos, i);
        }
        i++;
    }
    Swap(tab, pos, left);
    QuickSort(tab, left, pos-1);
    QuickSort(tab, pos+1, right);
}

void TestInterSearch()
{
    ofstream file("intersearch.txt");
    const float y = 1000;
    for(int i = 10; i<=10000; i+=10)
    {
        file << i <<" "<<InterSearchStatistics(y, i)<<endl;
    }
    file.close();
}
