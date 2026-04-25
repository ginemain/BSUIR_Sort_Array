#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Sorting.h"
#include "Visualizer.h"

#include <fstream>
#include <chrono>
#include <System.IOUtils.hpp>


using namespace std;

#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;

__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
    // для рандома цифр
    srand(time(NULL));

	// ИНИЦИАЛИЗИРУЕМ УКАЗАТЕЛИ
    originalArray = nullptr;
    sortedArray = nullptr;
    arraySize = 0;

    MemoResults->Clear();
    MemoResults->Lines->Add("Здесь будет информация о сортировке");
}

// ДЕСТРУКТОР - ОСВОБОЖДАЕМ ПАМЯТЬ
__fastcall TForm1::~TForm1()
{
    if(originalArray != nullptr)
        delete[] originalArray;
    if(sortedArray != nullptr)
        delete[] sortedArray;
}

// Проверка корректности ввода
bool TForm1::validateInput()
{
    if(editSize->Text.IsEmpty()) return false;
    if(editMin->Text.IsEmpty()) return false;
    if(editMax->Text.IsEmpty()) return false;

    int size = StrToInt(editSize->Text);
    return size > 0;
}

// Генерация массива
void __fastcall TForm1::btnGenerateClick(TObject *Sender)
{
    if(!validateInput())
    {
        ShowMessage("Ошибка ввода данных!");
        return;
    }

	// ОСВОБОЖДАЕМ СТАРУЮ ПАМЯТЬ
    if(originalArray != nullptr)
    {
        delete[] originalArray;
        originalArray = nullptr;
    }
    if(sortedArray != nullptr)
    {
        delete[] sortedArray;
        sortedArray = nullptr;
    }

    int size   = StrToInt(editSize->Text);
    int minVal = StrToInt(editMin->Text);
    int maxVal = StrToInt(editMax->Text);

	// ВЫДЕЛЯЕМ ПАМЯТЬ И ЗАПОЛНЯЕМ
	arraySize = size;
    originalArray = new int[arraySize];

    for(int i = 0; i < arraySize; i++)
        originalArray[i] = minVal + rand() % (maxVal - minVal + 1);

    currentFileName = "generated";

    Visualizer::drawArray(this, originalArray, arraySize, -1, arraySize);
}

// Сортировка выбранным алгоритмом
void __fastcall TForm1::btnSortSelectedClick(TObject *Sender)
{
    SortStats stats;

	if(originalArray == nullptr || arraySize == 0) return;

	// КОПИРУЕМ ИСХОДНЫЙ МАССИВ В sortedArray
    if(sortedArray != nullptr)
        delete[] sortedArray;

    sortedArray = new int[arraySize];
    for(int i = 0; i < arraySize; i++)
        sortedArray[i] = originalArray[i];

	bool animate = cbAnimation->Checked && arraySize <= 100;
    int delay = 101 - trackSpeed->Position;

    auto start = chrono::high_resolution_clock::now();

    switch(cbAlgorithms->ItemIndex)
    {
        case 0: Sorting::bubbleSort(sortedArray, arraySize, stats, this, animate, delay); break;
        case 1: Sorting::insertionSort(sortedArray, arraySize, stats, this, animate, delay); break;
        case 2: Sorting::selectionSort(sortedArray, arraySize, stats, this, animate, delay); break;
        case 3: Sorting::shellSort(sortedArray, arraySize, stats, this, animate, delay); break;
        case 4: Sorting::quickSort(sortedArray, arraySize, stats, 0, arraySize - 1); break;
    }

    auto end = chrono::high_resolution_clock::now();
    double time = chrono::duration<double, milli>(end - start).count();

    // вывод в Memo
    String resultLine =
        cbAlgorithms->Text +
        " | time: " + FloatToStr(time) + " ms" +
        " | comp: " + IntToStr(stats.comparisons) +
        " | swap: " + IntToStr(stats.swaps);

    MemoResults->Lines->Add(resultLine);

    // оставляем отсортированный массив весь зеленым
    Visualizer::drawArray(this, sortedArray, arraySize, -1, 0);
    ShowMessage("Массив отсортирован!");
}

// Сортировка всеми (без анимации)
void __fastcall TForm1::btnSortAllClick(TObject *Sender)
{
	if(originalArray == nullptr || arraySize == 0) return;

    MemoResults->Clear();

    for(int i = 0; i < 5; i++)
    {
		// КОПИРУЕМ ИСХОДНЫЙ МАССИВ
        int* temp = new int[arraySize];
        for(int j = 0; j < arraySize; j++)
            temp[j] = originalArray[j];

        auto start = chrono::high_resolution_clock::now();

        SortStats stats;

        switch(i)
        {
            case 0: Sorting::bubbleSort(temp, arraySize, stats, this, false, 0); break;
            case 1: Sorting::insertionSort(temp, arraySize, stats, this, false, 0); break;
            case 2: Sorting::selectionSort(temp, arraySize, stats, this, false, 0); break;
            case 3: Sorting::shellSort(temp, arraySize, stats, this, false, 0); break;
            case 4: Sorting::quickSort(temp, arraySize, stats, 0, arraySize - 1); break;
        }

        auto end = chrono::high_resolution_clock::now();
        double time = chrono::duration<double, milli>(end - start).count();

        String sortName = cbAlgorithms->Items->Strings[i];

        // ВЫВОД
        String resultLine =
            sortName +
            " | time: " + FloatToStr(time) + " ms" +
            " | comp: " + IntToStr(stats.comparisons) +
            " | swap: " + IntToStr(stats.swaps);

        MemoResults->Lines->Add(resultLine);

		// ОБНОВЛЯЕМ sortedArray
        if(sortedArray != nullptr)
            delete[] sortedArray;
        sortedArray = temp;
    }

    // рисуем отсортированный массив весь зеленым
    Visualizer::drawArray(this, sortedArray, arraySize, -1, 0);
    ShowMessage("Массив отсортирован всеми видами сортировок!");
}

// сохранение в папку Output
void TForm1::saveToOutputFolder(String sortName)
{
    // Проверяем, есть ли отсортированный массив
	if (sortedArray == nullptr || arraySize == 0)
    {
        ShowMessage("Сначала нужно выполнить сортировку!");
        return; // ничего не сохраняем
    }

    // Путь к папке рядом с exe
    String outputFolder = ExtractFilePath(Application->ExeName) + "output\\";

    // Если папки нет — создаём
    if (!DirectoryExists(outputFolder))
    {
        CreateDir(outputFolder);
    }

    // Если файл загружался — берём его имя,
    // если нет — пишем "generated"
    String baseName;

    if (currentFileName != "")
        baseName = currentFileName;
    else
        baseName = "generated";

    // Формируем имена файлов
    String sortedFileName =
        outputFolder + baseName + "_" + sortName + "_sorted.txt";

    String resultFileName =
        outputFolder + baseName + "_" + sortName + "_result.txt";

    // Сохраняем отсортированный массив
    ofstream fileSorted(AnsiString(sortedFileName).c_str());

	for (int i = 0; i < arraySize; i++)
    {
        fileSorted << sortedArray[i] << " ";
    }

    fileSorted.close();

    // Сохраняем результаты из Memo
    ofstream fileResult(AnsiString(resultFileName).c_str());

    for(int i = 0; i < MemoResults->Lines->Count; i++)
    {
        String line = MemoResults->Lines->Strings[i];

        // сохраняем только строки с результатами (где есть time)
        if(line.Pos("time") > 0)
        {
            fileResult << AnsiString(line).c_str() << endl;
        }
    }

    fileResult.close();

    ShowMessage("Файлы сохранены в папку output");
}

// Загрузка массива из текстового файла
void __fastcall TForm1::btnLoadClick(TObject *Sender)
{
  if(OpenDialog1->Execute())
  {
    ifstream file(AnsiString(OpenDialog1->FileName).c_str());

    // проверка файла на открытие
    if(!file)
    {
      ShowMessage("Не удалось открыть файл!");
      return;
    }

	// ОСВОБОЖДАЕМ СТАРУЮ ПАМЯТЬ
    if(originalArray != nullptr)
    {
        delete[] originalArray;
        originalArray = nullptr;
    }

	// СНАЧАЛА СЧИТАЕМ КОЛИЧЕСТВО ЧИСЕЛ В ФАЙЛЕ
    int count = 0;
    int value;
    while(file >> value)
    {
        count++;
    }

    if(count == 0)
    {
        ShowMessage("Файл пуст!");
        file.close();
        return;
    }

	// ВОЗВРАЩАЕМСЯ В НАЧАЛО ФАЙЛА
    file.clear();
    file.seekg(0, ios::beg);

	// ВЫДЕЛЯЕМ ПАМЯТЬ И ЧИТАЕМ ЧИСЛА
    arraySize = count;
    originalArray = new int[arraySize];

    for(int i = 0; i < arraySize; i++)
    {
        file >> originalArray[i];
    }

    // проверка на неверные символы
    if(file.fail() && !file.eof())
    {
        ShowMessage("Ошибка! Файл содержит недопустимые символы.");
        file.close();
        delete[] originalArray;
        originalArray = nullptr;
        arraySize = 0;
        return;
    }

    file.close();

    // проверка на пустоту массива
	if(arraySize == 0)
    {
        ShowMessage("Файл пуст!");
        return;
    }

    // сохраняем имя файла
    currentFileName = ChangeFileExt(
        ExtractFileName(OpenDialog1->FileName), ""
    );

    // информация пользователю
    MemoResults->Lines->Add(
        "Загружен файл: " + currentFileName + ".txt"
    );

    MemoResults->Lines->Add(
		"Размер массива: " + IntToStr(arraySize) + " элементов."
    );

    // рисуем массив
    Visualizer::drawArray(this, originalArray, arraySize, -1, arraySize);

    ShowMessage("Массив загружен успешно!");
  }
}

// save sorted
void __fastcall TForm1::btnSaveSortedClick(TObject *Sender)
{
	if (sortedArray == nullptr || arraySize == 0)
    {
        ShowMessage("Нет отсортированного массива!");
        return;
    }

    String sortName = cbAlgorithms->Text;
    saveToOutputFolder(sortName);
}

// save results
void __fastcall TForm1::btnSaveResultsClick(TObject *Sender)
{
    if (MemoResults->Lines->Count == 0)
    {
        ShowMessage("Нет результатов для сохранения!");
        return;
    }

    String sortName = cbAlgorithms->Text;
    saveToOutputFolder(sortName);
}


