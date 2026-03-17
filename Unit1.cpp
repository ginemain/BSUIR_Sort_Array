#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Sorting.h"
#include "Visualizer.h"

#include <fstream>
#include <chrono>
#include <algorithm>
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

	MemoResults->Clear();
	MemoResults->Lines->Add("Здесь будет информация о сортировке");
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

    originalArray.clear();

    int size   = StrToInt(editSize->Text);
    int minVal = StrToInt(editMin->Text);
    int maxVal = StrToInt(editMax->Text);

    for(int i = 0; i < size; i++)
        originalArray.push_back(minVal + rand() % (maxVal - minVal + 1));

    currentFileName = "generated";

	Visualizer::drawArray(this, originalArray, -1, originalArray.size());
}

// Сортировка выбранным алгоритмом
void __fastcall TForm1::btnSortSelectedClick(TObject *Sender)
{
	SortStats stats;

    if(originalArray.empty()) return;

    sortedArray = originalArray;

    bool animate = cbAnimation->Checked && sortedArray.size() <= 100;
    int delay = 101 - trackSpeed->Position;

    auto start = chrono::high_resolution_clock::now();

	switch(cbAlgorithms->ItemIndex)
    {
		case 0: Sorting::bubbleSort(sortedArray, stats, this, animate, delay); break;
		case 1: Sorting::insertionSort(sortedArray, stats, this, animate, delay); break;
		case 2: Sorting::selectionSort(sortedArray, stats, this, animate, delay); break;
		case 3: Sorting::shellSort(sortedArray, stats, this, animate, delay); break;
		case 4: Sorting::quickSort(sortedArray, stats, 0, sortedArray.size()-1); break;
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
	Visualizer::drawArray(this, sortedArray, -1, 0);
	ShowMessage("Массив отсортирован!");


}

// Сортировка всеми (без анимации)
void __fastcall TForm1::btnSortAllClick(TObject *Sender)
{

    if(originalArray.empty()) return;

	MemoResults->Clear();

    for(int i = 0; i < 5; i++)
    {
        vector<int> temp = originalArray;

        auto start = chrono::high_resolution_clock::now();

		SortStats stats;

		switch(i)
		{
			case 0: Sorting::bubbleSort(temp, stats, this, false, 0); break;
			case 1: Sorting::insertionSort(temp, stats, this, false, 0); break;
			case 2: Sorting::selectionSort(temp, stats, this, false, 0); break;
			case 3: Sorting::shellSort(temp, stats, this, false, 0); break;
			case 4: Sorting::quickSort(temp, stats, 0, temp.size()-1); break;
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

		sortedArray = temp;
	}

	// рисуем отсортированный массив весь зеленым
	Visualizer::drawArray(this, sortedArray, -1, 0);
	ShowMessage("Массив отсортирован всеми видами сортировок!");
}


// сохранение в папку Output
void TForm1::saveToOutputFolder(String sortName)
{
    // Проверяем, есть ли отсортированный массив
    if (sortedArray.empty())
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

	for (int i = 0; i < sortedArray.size(); i++)
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

    originalArray.clear();

    int value;

    // читаем числа
    while(file >> value)
    {
      originalArray.push_back(value);
    }

    // проверка на неверные символы
    if(file.fail() && !file.eof())
    {
      ShowMessage("Ошибка! Файл содержит недопустимые символы.");
	  file.close();

	  originalArray.clear();

      return;
    }

    file.close();

	// проверка на пустоту массива
    if(originalArray.empty())
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
      "Размер массива: " + IntToStr((int)originalArray.size())
      + " элементов."
    );

    // рисуем массив
    Visualizer::drawArray(this, originalArray, -1, originalArray.size());

    ShowMessage("Массив загружен успешно!");
  }
}

// save sorted
void __fastcall TForm1::btnSaveSortedClick(TObject *Sender)
{
	if (sortedArray.empty())
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
__fastcall TForm1::~TForm1()
{
}


