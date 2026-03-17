#ifndef SortingH
#define SortingH

#include <vector>
#include <Vcl.Forms.hpp>

using namespace std;

// Класс со всеми алгоритмами сортировки
class Sorting
{
public:
    static void bubbleSort(vector<int>& arr, TForm* form, bool animate, int delay);
    static void insertionSort(vector<int>& arr, TForm* form, bool animate, int delay);
    static void selectionSort(vector<int>& arr, TForm* form, bool animate, int delay);
    static void shellSort(vector<int>& arr, TForm* form, bool animate, int delay);
    static void quickSort(vector<int>& arr, int low, int high);

private:
    static int partition(vector<int>& arr, int low, int high);
};

#endif