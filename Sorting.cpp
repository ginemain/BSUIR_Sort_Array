#include "Sorting.h"
#include "Visualizer.h"

using namespace std;

// ѕузырькова€ сортировка
void Sorting::bubbleSort(vector<int>& arr, TForm* form, bool animate, int delay)
{
    int n = arr.size();

    // внешний цикл - количество проходов
    for(int i = 0; i < n - 1; i++)
    {
        // внутренний цикл - сравнение соседних элементов
        for(int j = 0; j < n - i - 1; j++)
        {
            // если левый элемент больше правого Ч мен€ем местами
            if(arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);

            // визуализаци€ шага алгоритма
            if(animate)
            {
                // j Ч текущий элемент
                // n - i Ч начало уже отсортированной части справа
                Visualizer::drawArray(form, arr, j, n - i);

                Sleep(delay);
                Application->ProcessMessages();
            }
        }
    }
}

// —ортировка вставками
void Sorting::insertionSort(vector<int>& arr, TForm* form, bool animate, int delay)
{
    int n = arr.size();

    // начинаем со второго элемента
    for(int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;

        // сдвигаем элементы вправо
        while(j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;

            if(animate)
            {
                Visualizer::drawArray(form, arr, j, n);
                Sleep(delay);
                Application->ProcessMessages();
            }
        }

        // вставл€ем элемент на нужное место
        arr[j + 1] = key;
    }
}

// —ортировка выбором
void Sorting::selectionSort(vector<int>& arr, TForm* form, bool animate, int delay)
{
    int n = arr.size();

    // перебираем позиции массива
    for(int i = 0; i < n - 1; i++)
    {
        int minIndex = i;

        // ищем минимальный элемент
        for(int j = i + 1; j < n; j++)
        {
            if(arr[j] < arr[minIndex])
                minIndex = j;
        }

        // мен€ем найденный минимум с текущим элементом
        swap(arr[i], arr[minIndex]);

        if(animate)
        {
            // i Ч текуща€ позици€
            // i + 1 Ч отсортированна€ часть слева
            Visualizer::drawArray(form, arr, i, n);

            Sleep(delay);
            Application->ProcessMessages();
        }
    }
}

// Shell Sort
void Sorting::shellSort(vector<int>& arr, TForm* form, bool animate, int delay)
{
    int n = arr.size();

    // начинаем с большого шага и уменьшаем его
    for(int gap = n / 2; gap > 0; gap /= 2)
    {
        for(int i = gap; i < n; i++)
        {
            int temp = arr[i];
            int j;

            // сортировка элементов с заданным шагом
            for(j = i; j >= gap && arr[j - gap] > temp; j -= gap)
            {
                arr[j] = arr[j - gap];

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

// ¬спомогательна€ функци€ Quick Sort
int Sorting::partition(vector<int>& arr, int low, int high)
{
    int pivot = arr[high]; // опорный элемент
    int i = low - 1;

    for(int j = low; j < high; j++)
    {
        if(arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Ѕыстра€ сортировка (Quick Sort)
void Sorting::quickSort(vector<int>& arr, int low, int high)
{
    if(low < high)
    {
        int pi = partition(arr, low, high);

        // рекурсивна€ сортировка частей массива
        quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
    }
}
