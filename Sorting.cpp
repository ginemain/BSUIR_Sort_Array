#include "Sorting.h"
#include "Visualizer.h"

using namespace std;

// Пузырьковая сортировка
void Sorting::bubbleSort(vector<int>& arr, SortStats& stats, TForm* form, bool animate, int delay)
{
    int n = arr.size();

    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            stats.comparisons++;

            if(arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                stats.swaps++;
            }

            if(animate)
            {
                Visualizer::drawArray(form, arr, j, n - i);
                Sleep(delay);
                Application->ProcessMessages();
            }
        }
    }
}

// Сортировка вставками
void Sorting::insertionSort(vector<int>& arr, SortStats& stats, TForm* form, bool animate, int delay)
{
    int n = arr.size();

    for(int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;

        while(j >= 0)
        {
            stats.comparisons++;

            if(arr[j] > key)
            {
                arr[j + 1] = arr[j];
                stats.swaps++;
                j--;
            }
            else break;

            if(animate)
            {
                Visualizer::drawArray(form, arr, j, n);
                Sleep(delay);
                Application->ProcessMessages();
            }
        }

        arr[j + 1] = key;
    }
}

// Сортировка выбором
void Sorting::selectionSort(vector<int>& arr, SortStats& stats, TForm* form, bool animate, int delay)
{
    int n = arr.size();

    for(int i = 0; i < n - 1; i++)
    {
        int minIndex = i;

        for(int j = i + 1; j < n; j++)
        {
            stats.comparisons++;

            if(arr[j] < arr[minIndex])
                minIndex = j;
        }

        if(minIndex != i)
        {
            swap(arr[i], arr[minIndex]);
            stats.swaps++;
        }

        if(animate)
        {
            Visualizer::drawArray(form, arr, i, n);
            Sleep(delay);
            Application->ProcessMessages();
        }
    }
}

// Shell Sort
void Sorting::shellSort(vector<int>& arr, SortStats& stats, TForm* form, bool animate, int delay)
{
    int n = arr.size();

    for(int gap = n / 2; gap > 0; gap /= 2)
    {
        for(int i = gap; i < n; i++)
        {
            int temp = arr[i];
            int j;

            for(j = i; j >= gap; j -= gap)
            {
                stats.comparisons++;

                if(arr[j - gap] > temp)
                {
                    arr[j] = arr[j - gap];
                    stats.swaps++;
                }
                else break;

                if(animate)
                {
                    Visualizer::drawArray(form, arr, j, n);
                    Sleep(delay);
                    Application->ProcessMessages();
                }
            }

            arr[j] = temp;
        }
    }
}

// partition для quick sort
int Sorting::partition(vector<int>& arr, SortStats& stats, int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for(int j = low; j < high; j++)
    {
        stats.comparisons++;

        if(arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
            stats.swaps++;
        }
    }

    swap(arr[i + 1], arr[high]);
    stats.swaps++;

    return i + 1;
}

// Quick Sort
void Sorting::quickSort(vector<int>& arr, SortStats& stats, int low, int high)
{
    if(low < high)
    {
        int pi = partition(arr, stats, low, high);

        quickSort(arr, stats, low, pi - 1);
        quickSort(arr, stats, pi + 1, high);
    }
}
