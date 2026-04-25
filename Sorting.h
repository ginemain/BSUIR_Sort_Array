#ifndef SortingH
#define SortingH


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
	static void bubbleSort(int* arr, int size, SortStats& stats, TForm* form, bool animate, int delay);
	static void insertionSort(int* arr, int size, SortStats& stats, TForm* form, bool animate, int delay);
	static void selectionSort(int* arr, int size, SortStats& stats, TForm* form, bool animate, int delay);
	static void shellSort(int* arr, int size, SortStats& stats, TForm* form, bool animate, int delay);
	static void quickSort(int* arr, int size, SortStats& stats, int low, int high);

private:
	static int partition(int* arr, SortStats& stats, int low, int high);
};

#endif
