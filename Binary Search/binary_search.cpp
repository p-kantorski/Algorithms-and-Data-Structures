#include <iostream>
#include <fstream>
#include <time.h>
#include <chrono>

using namespace std::chrono;
using namespace std;

int BinarySearch(int *tab, int length, int s, int &steps);
int *RandomTable(int length);
void Swap(int *tab, int idx_a, int idx_b);
float BinarySearchStatistics(float max_iterations, int length);
int LosujIndeks(int length);
void QuickSort(int *tab, int left, int right);
void TestBinarySearch();

int main()
{
    srand(time(NULL));
    TestBinarySearch();
    return 0;
}
int BinarySearch(int *tab, int length, int s, int &steps)
{
    int left = 0;
    int right = length-1;
    while(left<=right)
    {
        int mid = (left + right)/2;
        steps++;
        if(tab[mid]==s)
        {
            return mid;
        }
        steps++;
        if(tab[mid]<s)
            left = mid+1;
        else
            right = mid-1;
    }
    return -1;

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

float BinarySearchStatistics(int max_iterations, int length)
{
    int steps = 0;
    for(int i = 0; i < max_iterations; i++)
    {
        int *tab = RandomTable(length);
        QuickSort(tab, 0, length-1);
        BinarySearch(tab, length, tab[LosujIndeks(length)], steps);
        delete [] tab;
    }
    return (float(steps) / float (max_iterations));
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

void TestBinarySearch()
{
    ofstream file("binarysearch.txt");
    const int y = 1000;
    for(int i = 10; i<=10000; i+=10)
    {
        file << i << " ";
        auto start = high_resolution_clock::now();
        file << BinarySearchStatistics(y,i) << " ";
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        file << duration.count() << endl;
    }
    file.close();
}
