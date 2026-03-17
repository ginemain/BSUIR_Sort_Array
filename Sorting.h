#ifndef SortingH
#define SortingH

#include <vector>
#include <Vcl.Forms.hpp>

using namespace std;

// структура для статистики сортировки
struct SortStats
{
    long long comparisons = 0; // количество сравнений
    long long swaps = 0;       // количество перестановок
};

// Класс со всеми алгоритмами сортировки
class Sorting
{
public:
    static void bubbleSort(vector<int>& arr, SortStats& stats, TForm* form, bool animate, int delay);
    static void insertionSort(vector<int>& arr, SortStats& stats, TForm* form, bool animate, int delay);
    static void selectionSort(vector<int>& arr, SortStats& stats, TForm* form, bool animate, int delay);
    static void shellSort(vector<int>& arr, SortStats& stats, TForm* form, bool animate, int delay);
    static void quickSort(vector<int>& arr, SortStats& stats, int low, int high);

private:
    static int partition(vector<int>& arr, SortStats& stats, int low, int high);
};

#endif
